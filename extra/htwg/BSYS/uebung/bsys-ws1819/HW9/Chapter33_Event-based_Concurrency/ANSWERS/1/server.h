#ifndef __SERVER_H__
#define __SERVER_H__

#define PORT 15000
#define BUFFER_SIZE 100

int already_printed = 0;

typedef struct __server_t {
  int server_socket_fd;
  int client_socket_fd;
  struct sockaddr_in addr;
} server_t;

void init(server_t *server);
void create_socket(server_t *server);
void set_server_addr(server_t *server);
void bind_socket(server_t *server);
void listen_socket(server_t *server);
void accept_client(server_t *server);
void receive_command_from_client(server_t *server, char *data);
void send_date_and_time_to_client(server_t *server);
void send_unkown_command_to_client(server_t *server);
void close_socket(int *socket);


void init(server_t *server) {
  create_socket(server);
  set_server_addr(server);
  bind_socket(server);
  listen_socket(server);
  accept_client(server);
}

void create_socket(server_t *server) {
  server->server_socket_fd = socket(AF_INET, SOCK_STREAM, 0);

  if (server->server_socket_fd < 0) {
    fprintf(stderr, "Error occured in socket(): %s!\n", strerror(errno));
    exit(-1);
  }
}

void set_server_addr(server_t *server) {
  server->addr.sin_family = AF_INET;
  server->addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server->addr.sin_port = htons(PORT);
}

void bind_socket(server_t *server) {
  int bind_status = bind(server->server_socket_fd,
                         (struct sockaddr *) &server->addr,
                         sizeof(server->addr));
  if (bind_status < 0) {
    fprintf(stderr, "Error occured in bind(): %s!\n", strerror(errno));
    exit(-2);
  }
}

void listen_socket(server_t *server) {
  int listen_status = listen(server->server_socket_fd, 1);
  if (listen_status < 0) {
    fprintf(stderr, "Error occurred in listen(): %s!\n", strerror(errno));
    exit(-3);
  }
}

void accept_client(server_t *server) {
  unsigned int addr_len = sizeof(server->addr);
  server->client_socket_fd = accept(server->server_socket_fd,
                                 (struct sockaddr *) &server->addr, &addr_len);

  if (server->client_socket_fd < 0) {
    fprintf(stderr, "Error occurred in accept(): %s!\n", strerror(errno));
    exit(-4);
  }

  printf("A new client connected.\n");
}

void receive_command_from_client(server_t *server, char *data) {
  size_t bytes_read = read(server->client_socket_fd, data, BUFFER_SIZE);

  if (bytes_read <= 0 && already_printed == 0) {
    printf("A client disconnected.\n");
    already_printed = 1;
  }
}

void send_date_and_time_to_client(server_t *server) {
  time_t t = time(NULL);
  struct tm *time_info = localtime(&t);
  char *time_as_str = asctime(time_info);

  size_t bytes_to_write = strlen(time_as_str) + 1;
  size_t bytes_written = write(server->client_socket_fd, time_as_str,
                               bytes_to_write);

  if (bytes_written != bytes_to_write) {
    fprintf(stderr, "Error occurred in write(): %s!\n", strerror(errno));
  }
}

void send_unkown_command_to_client(server_t *server) {
  char *unknown_command_msg = "Unknown command!\n";

  size_t bytes_to_send = strlen(unknown_command_msg) + 1;
  size_t bytes_send = write(server->client_socket_fd, unknown_command_msg,
                            bytes_to_send);

  if (bytes_send < 0 || bytes_send != bytes_to_send) {
    fprintf(stderr, "Error occurred in send(): %s\n", strerror(errno));
  }
}

void close_socket(int *socket) {
  int close_status = close(*socket);

  if (close_status < 0) {
    fprintf(stderr, "Error occurred in close(): %s\n", strerror(errno));
    exit(-5);
  }
}

#endif
