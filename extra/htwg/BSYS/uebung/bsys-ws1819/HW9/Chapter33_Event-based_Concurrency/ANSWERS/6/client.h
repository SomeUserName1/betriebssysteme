#ifndef __CLIENT_H__
#define __CLIENT_H__

#define PORT 15000
#define BUFFER_SIZE 1000000

typedef struct __client_t {
  int client_socket_fd;
  struct sockaddr_in server_addr;
} client_t;

void init(client_t *client);
void create_socket(client_t *client);
void set_server_addr(client_t *client);
void connect_to_server(client_t *client);
void close_socket(int *socket);
void get_user_input(char *buffer);
void send_command_to_server(client_t *client, char *data);
void receive_data_from_server(client_t *client);
void print_help_text(void);


void init(client_t *client) {
  create_socket(client);
  set_server_addr(client);
  connect_to_server(client);
}

void create_socket(client_t *client) {
  client->client_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (client->client_socket_fd < 0) {
    fprintf(stderr, "Error occured in socket(): %s!\n", strerror(errno));
    exit(-1);
  }
}

void set_server_addr(client_t *client) {
  client->server_addr.sin_family = AF_INET;
  client->server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  client->server_addr.sin_port = htons(PORT);
}

void connect_to_server(client_t *client) {
  int connect_status = connect(client->client_socket_fd,
                               (struct sockaddr *) &client->server_addr,
                               sizeof(client->server_addr));
  if (connect_status < 0) {
    fprintf(stderr, "Error occured in connect(): %s!\n", strerror(errno));
    exit(-2);
  }
}

void get_user_input(char *buffer) {
  printf("Enter a command: ");
  char *user_input = fgets(buffer, BUFFER_SIZE, stdin);

  if (user_input == NULL) {
    fprintf(stderr, "Error occured in fgets(): %s!\n", strerror(errno));
    exit(-4);
  }
}

void send_command_to_server(client_t *client, char *data) {
  size_t bytes_written = write(client->client_socket_fd, data, strlen(data) + 1);

  if (bytes_written < 0) {
    fprintf(stderr, "Error occured in write(): %s!\n", strerror(errno));
    exit(-5);
  }
}

void receive_data_from_server(client_t *client) {
  char *buffer = (char *) malloc(BUFFER_SIZE);
  memset(buffer, 0, BUFFER_SIZE);

  size_t bytes_read = read(client->client_socket_fd, buffer, BUFFER_SIZE);

  if (bytes_read <= 0) {
    printf("The server closed the connection.\n");
    close(client->client_socket_fd);
    free(buffer);
    exit(-6);
  }

  printf("Received from server: %s", buffer);
  free(buffer);
}

void close_socket(int *socket) {
  int close_status = close(*socket);

  if (close_status < 0) {
    fprintf(stderr, "Error occurred in close(): %s\n", strerror(errno));
    exit(-3);
  }
}

void print_help_text(void) {
  printf("\nAvailable commands:\n\n");
  printf("get time: receive the current date and time from server.\n");
  printf("get file <path_to_file_and_file_name>: receive the requested file"
         " from the server.\n");
  printf("get primes: receive the current calculated prime numbers from the server\n");
  printf("exit: disconnect from server.\n");
  printf("close server: close the server properly.\n\n");
}

#endif
