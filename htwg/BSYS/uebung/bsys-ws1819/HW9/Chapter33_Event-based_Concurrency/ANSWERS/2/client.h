#ifndef __CLIENT_H__
#define __CLIENT_H__

#define PORT 15000
#define BUFFER_SIZE 100

typedef struct __client_t {
  int client_socket_fd;
  struct sockaddr_in server_addr;
} client_t;

void init(client_t *client);
void create_socket(client_t *client);
void set_server_addr(client_t *client);
void connect_to_server(client_t *client);
void get_user_input(char *buffer);
void send_command_to_server(client_t *client, char *data);
void receive_data_from_server(client_t *client);
void print_help_text(void);
void close_socket(client_t *client);


void init(client_t *client) {
  create_socket(client);
  set_server_addr(client);
  connect_to_server(client);
}

void create_socket(client_t *client) {
  client->client_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (client->client_socket_fd < 0) {
    fprintf(stderr, "Error occurred in socket(): %s!\n", strerror(errno));
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
    fprintf(stderr, "Error occurred in connect(): %s!\n", strerror(errno));
    exit(-2);
  }
}

void get_user_input(char *buffer) {
  printf("Enter a command: ");
  char *user_input = fgets(buffer, BUFFER_SIZE, stdin);

  if (user_input == NULL) {
    fprintf(stderr, "Error occurred in fgets(): %s!\n", strerror(errno));
    exit(-1);
  }
}

void send_command_to_server(client_t *client, char *data) {
  size_t bytes_written = write(client->client_socket_fd, data, BUFFER_SIZE);

  if (bytes_written < 0 || bytes_written != BUFFER_SIZE) {
    fprintf(stderr, "Error occured in write(): %s!\n", strerror(errno));
    exit(-3);
  }
}

void receive_data_from_server(client_t *client) {
  char *buffer = (char *) malloc(BUFFER_SIZE);
  memset(buffer, 0, BUFFER_SIZE);

  size_t bytes_read = read(client->client_socket_fd, buffer, BUFFER_SIZE);
  if (bytes_read <= 0) {
    printf("The server closed the connection.\n");
    free(buffer);
    exit(-4);
  }

  printf("Received from server: %s", buffer);
  free(buffer);
}

void close_socket(client_t *client) {
  close(client->client_socket_fd);
  printf("Closed socket succefully.\n");
}

void print_help_text(void) {
  printf("\nAvailable commands:\n\n");
  printf("get time: receive the current date and time from server.\n");
  printf("exit: disconnect from server.\n");
  printf("close server: close the server properly.\n\n");
}

#endif
