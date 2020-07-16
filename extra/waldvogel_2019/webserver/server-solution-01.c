/**
 * Diese Lösung ist nicht perfekt, aber sie vermittelt die grundlegende Idee.
 * Solltet ihr sie weiter verwenden, strukturiert sie bitte besser (weniger 
 * Verschachtelung) und beseitigt die Fehler (z.B. Host: localhost muss nicht
 * im Header stehen).
 */
#include <netinet/ip.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

#define DEFAULT_PORT       "8080"
#define LISTENQUEUE        256 /* This server can only process one client simultaenously * \
	                             * How many connections do we want to queue? */

#define RESPONSESTART      "HTTP/1.1 "
#define RESPONSE400        "400 Bad Request\r\n"
#define RESPONSE501        "501 Not Implemented\r\n"
#define RESPONSE301        "301 Moved Permanently\r\nLocation: /index.html\r\n"
#define RESPONSE200        "200 OK\r\n"
#define RESPONSE404        "404 Not Found\r\n"
#define RESPONSE304        "304 Not Modified\r\n"

#define RESPONSESERVER     "Server: PK\r\n"
#define RESPONSEDATE       "Date: " /* Date value needs to be added at runtime */
#define RESPONSECLOSE      "Connection: close\r\n\r\n"

#define HELLOWORLD         "Hello World!"

#define MAXSTRINGLENGTH    4096
#define MAXFIELDS          30
#define MAXFIELDKEY        32
#define MAXFIELDVALUE      256

int startServer(const char *iface, const char *port, struct addrinfo *res)
{
	int listenfd;

	struct addrinfo hints;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family   = AF_INET; /* type of socket */
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags    = AI_PASSIVE; /* socket will use bind later */

	if (getaddrinfo(iface, port, &hints, &res) != 0)
	{
		perror("Could not get address info");
		exit(1);
	}

	listenfd = socket(res->ai_family, res->ai_socktype, 0);

	if (bind(listenfd, res->ai_addr, res->ai_addrlen) != 0)
	{
		perror("Could not bind to address");
		exit(1);
	}

	if (listen(listenfd, LISTENQUEUE) != 0)
	{
		perror("Could not listen for connections on socket");
	}

	printf("Server listening on %s:%s...\n", iface, port);

	return listenfd;
}


void closeServer(struct addrinfo *res)
{
	freeaddrinfo(res);
}


int substring(const char *string, const char *substring)
{
	return strncmp(string, substring, strlen(substring));
}


int substringcase(const char *string, const char *substring)
{
	return strncasecmp(string, substring, strlen(substring));
}


/* Response status code is returned on errors, if 0 then path is written in requestpath */
int parse_header(char *request, char **requestpath, char **fieldkeys, char **fieldvalues, size_t *fields_len)
{
	if (strcasestr(request, "Host: localhost") == NULL)
	{
		/* Note: HTTP 1.0 lacks Host field, so this breaks it, but that's OK for us */
		return 400;
	}

	if (substring(request, "GET ") != 0)
	{
		return 501;
	}
	if (substring(request, "GET /") != 0)
	{
		return 400;
	}
	request += 4;                                    /* skip GET */

	char *skippedrequestpath = strstr(request, " "); /* skip until blank */
	*skippedrequestpath = '\0';
	skippedrequestpath++;

	*requestpath = request;
	request      = skippedrequestpath;

	/* HTTP version now remaining in Request-Line */
	size_t i     = 0;
	char   *line = request;
	while ((line = strstr(line, "\r\n")) != NULL)
	{
		line[0] = '\0';
		line[1] = '\0';

		line += 2;

		if ((line[0] == '\0') || ((line[0] == '\r') && (line[1] == '\n')))
		{
			/* We can rely on there being CRLF CRLF since we require at least one header field (Host) */
			break;
		}

		char *colon = strstr(line, ":");
		if (colon == NULL)     /* Header line contains no : delimiter */
		{
			return 400;
		}

		colon[0]       = '\0';
		fieldkeys[i]   = line;
		colon         += 2; /* skip 0 and blank */
		fieldvalues[i] = colon;
		i++;
		line = colon;
	}
	(*fields_len) = i;
	return 0;
}


size_t generate_response(char **responsebuffer, int statuscode, char *requestpath, char **fieldkeys, char **fieldvalues, size_t fields_len)
{
	/* size for response line (+'\0') except for reason phrase */
	char response[MAXSTRINGLENGTH];
	int  position = sprintf(response, RESPONSESTART);
	char responsedata[MAXSTRINGLENGTH] = "";
	int  dataposition = 0;

	/* From now on position will be equal to the response size ('\0' cancels) */
	if (statuscode == 400)
	{
		position += sprintf(response + position, RESPONSE400);
	}
	else if (statuscode == 501)
	{
		position += sprintf(response + position, RESPONSE501);
	}
	else
	{
		if (strcmp(requestpath, "/index.php") == 0)
		{
			position += sprintf(response + position, RESPONSE301);
		}
		else if ((strcmp(requestpath, "/index.html") == 0) || (strcmp(requestpath, "/") == 0))
		{
			position += sprintf(response + position, RESPONSE200);
			strcpy(responsedata, HELLOWORLD);
		}
		else if (strcmp(requestpath, "/keys") == 0)
		{
			position += sprintf(response + position, RESPONSE200);
			for (size_t i = 0; i < fields_len; i++)
			{
				dataposition += sprintf(responsedata + dataposition, "%s\n", fieldkeys[i]);
			}
		}
		else if (strcmp(requestpath, "/values") == 0)
		{
			position += sprintf(response + position, RESPONSE200);
			for (size_t i = 0; i < fields_len; i++)
			{
				dataposition += sprintf(responsedata + dataposition, "%s\n", fieldvalues[i]);
			}
		}
		else if (strncmp(requestpath, "/header/", strlen("/header/")) == 0)
		{
			char   *requestedkey = requestpath + strlen("/header/");
			size_t i;
			for (i = 0; i < fields_len; i++)
			{
				if (strcasecmp(fieldkeys[i], requestedkey) == 0)
				{
					dataposition += sprintf(responsedata + dataposition, "%s\n", fieldvalues[i]);
					position     += sprintf(response + position, RESPONSE200);
				}
			}
			if (i == fields_len)                  /* fieldkey has not been found */
			{
				position += sprintf(response + position, RESPONSE404);
			}
		}
		else
		{
			position += sprintf(response + position, RESPONSE404);
		}
	}
	position += sprintf(response + position, RESPONSESERVER);

	/* Bonus Part */
	char      timestring[50];
	time_t    now = time(0);
	struct tm tm  = *gmtime(&now);
	strftime(timestring, 50, "%a, %d %b %Y %H:%M:%S %Z", &tm);

	position += sprintf(response + position, "%s%s\r\n", RESPONSEDATE, timestring);
	position += sprintf(response + position, RESPONSECLOSE);
	if (statuscode == 0)
	{
		position += sprintf(response + position, responsedata);
	}
	response[position] = '\0';
	*responsebuffer    = response;
	return position > 0 ? (size_t)position : 0;
}


int main(int argc, char *argv[])
{
	/* If webserver should be reachable from outside localhost
	 *  change localhost to NULL */
	const char      *iface = "localhost";
	const char      *port  = argc == 2 ? argv[1] : DEFAULT_PORT;
	struct addrinfo *res   = NULL;

	int listenfd = startServer(iface, port, res);

	while (1)
	{
		struct sockaddr_in clientaddr;
		socklen_t          addrlen = sizeof(clientaddr);
		int                client  = accept(listenfd, (struct sockaddr *)&clientaddr, &addrlen);

		if (client < 0)
		{
			perror("accept error");
		}

		printf("# New incoming connection\n");
		printf("# Request\n");

		char buf[MAXSTRINGLENGTH];

                buf[recv(client, buf, MAXSTRINGLENGTH, 0)] = '\0';
		printf("%s", buf);

                char   *requestpath;
		char   *fieldkeys[MAXFIELDS];
		char   *fieldvalues[MAXFIELDS];
		size_t fields_len     = 0;
		int    request_result = parse_header(buf, &requestpath, fieldkeys, fieldvalues, &fields_len);
		char   *response;
		size_t response_len = generate_response(&response, request_result, requestpath, fieldkeys, fieldvalues, fields_len);

                if (response_len > MAXSTRINGLENGTH)
		{
			fprintf(stderr, "response too large to send");
		}

                send(client, response, response_len, 0);

                printf("# Response\n");
		printf("%s", response);

		close(client);

		printf("\n# Waiting for next request...\n");
	}

	closeServer(res);

	return 0;
}
