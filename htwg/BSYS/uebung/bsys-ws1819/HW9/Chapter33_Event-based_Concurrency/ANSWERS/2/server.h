#ifndef __SERVER_H__
#define __SERVER_H__

#define PORT 15000
#define BUFFER_SIZE 255
#define MAX_NUM_TOKENS 3

typedef struct __server_t {
  int server_socket_fd;
  int client_socket_fd;
  int data_socket_fd;
  int client_sockets[FD_SETSIZE];
  int num_socket_fds;
  int max_socket_fd;
  struct sockaddr_in addr;
  fd_set reading_fd_set;
} server_t;

void init(server_t *server);
void create_socket(server_t *server);
void set_server_addr(server_t *server);
void bind_socket(server_t *server);
void listen_socket(server_t *server);
void accept_socket(server_t *server);
void check_client_connections_for_data(server_t *server);
int parse_command(char *command_buffer);
void send_date_and_time_to_client(server_t *server);
void send_unkown_command_to_client(server_t *server);
int get_command_from_client_and_response(server_t *server);
void close_socket(int *socket);

void init(server_t *server) {
  for (int i = 0; i < FD_SETSIZE; i++) {
      server->client_sockets[i] = 0;
  }

  create_socket(server);
  set_server_addr(server);
  bind_socket(server);
  listen_socket(server);
}

void create_socket(server_t *server) {
  server->server_socket_fd = socket(AF_INET, SOCK_STREAM, 0);

  if (server->server_socket_fd < 0) {
      fprintf(stderr, "Error occurred in socket(): %s\n", strerror(errno));
      exit(-1);
  }

  int opt = 1;
  int setsockopt_status = setsockopt(server->server_socket_fd, SOL_SOCKET,
                                     SO_REUSEADDR, (char *) &opt, sizeof(opt));

  if (setsockopt_status < 0) {
      fprintf(stderr, "Error occurred in setsockopt(): %s\n", strerror(errno));
      exit(-2);
  }
}

void set_server_addr(server_t *server) {
  server->addr.sin_family = AF_INET;
  server->addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server->addr.sin_port = htons(PORT);
}

void bind_socket(server_t *server) {
  int bind_status = bind(server->server_socket_fd, (struct sockaddr *) &server->addr,
                    sizeof(server->addr));

  if (bind_status < 0) {
      fprintf(stderr, "Error occurred in bind(): %s\n", strerror(errno));
      exit(-3);
  }
}

void listen_socket(server_t *server) {
  int listen_status = listen(server->server_socket_fd, 1);

  if (listen_status < 0) {
      fprintf(stderr, "Error occurred in listen(): %s\n", strerror(errno));
      exit(-4);
  }
}

void accept_client(server_t *server) {
  unsigned int addr_len = sizeof(server->addr);

  if ((server->client_socket_fd = accept(server->server_socket_fd,
          (struct sockaddr *)&server->addr, &addr_len))<0) {
      fprintf(stderr, "Error occurred in accept(): %s\n", strerror(errno));
      exit(-5);
  }
}

void check_for_new_clients_to_connect(server_t *server) {
  FD_ZERO(&server->reading_fd_set);
  FD_SET(server->server_socket_fd, &server->reading_fd_set);
  server->max_socket_fd = server->server_socket_fd;

  for (int i = 0 ; i < FD_SETSIZE ; i++) {
      server->data_socket_fd = server->client_sockets[i];

      if (server->data_socket_fd > 0) {
        FD_SET(server->data_socket_fd, &server->reading_fd_set);
      }

      if (server->data_socket_fd > server->max_socket_fd) {
        server->max_socket_fd = server->data_socket_fd;
      }
  }

  server->num_socket_fds = select(server->max_socket_fd + 1,
                                 &server->reading_fd_set, NULL, NULL, NULL);

  if ((server->num_socket_fds < 0)) {
      fprintf(stderr, "Error occurred in select(): %s\n", strerror(errno));
      exit(-6);
  }

  if (FD_ISSET(server->server_socket_fd, &server->reading_fd_set)) {
      accept_client(server);

      printf("New client connected.\n");

      for (int i = 0; i < FD_SETSIZE; i++) {
          if (server->client_sockets[i] == 0) {
              server->client_sockets[i] = server->client_socket_fd;
              break;
          }
      }
  }
}

int get_command_from_client_and_response(server_t *server) {
  for (int i = 0; i < FD_SETSIZE; i++) {
      server->data_socket_fd = server->client_sockets[i];

      if (FD_ISSET(server->data_socket_fd, &server->reading_fd_set)) {
          char *command_buffer = (char *) malloc(BUFFER_SIZE);
          memset(command_buffer, 0, BUFFER_SIZE);
          size_t bytes_read = read(server->data_socket_fd , command_buffer, BUFFER_SIZE);

          if (bytes_read == 0) {
            close_socket(&server->data_socket_fd);
            server->client_sockets[i] = 0;
            free(command_buffer);
            printf("A client disconnected.\n");
          } else if (bytes_read < 0) {
            fprintf(stderr, "Error occured in read(): %s\n", strerror(errno));
            free(command_buffer);
            exit(-7);
          } else {
            int command = parse_command(command_buffer);

            if (command == 0) {
              send_date_and_time_to_client(server);
              free(command_buffer);
            } else if (command == 1) {
              free(command_buffer);
              return 1;
            } else {
              send_unkown_command_to_client(server);
              free(command_buffer);
            }
          }
      }
  }
  return 0;
}

int parse_command(char *command_buffer) {
  char *tokens[MAX_NUM_TOKENS];
  memset(tokens, 0, sizeof(tokens));
  char *token = strtok(command_buffer, " ");

  int i = 0;
  while (token != NULL && i < MAX_NUM_TOKENS) {
    tokens[i] = token;
    i++;
    token = strtok(NULL, " ");
  }

  if (strcmp(tokens[0], "get") == 0 && strcmp(tokens[1], "time\n") == 0) {
    return 0;
  } else if (strcmp(tokens[0], "close") == 0 && strcmp(tokens[1], "server\n") == 0) {
    return 1;
  }

  return -1;
}

void send_date_and_time_to_client(server_t *server) {
  time_t t = time(NULL);
  struct tm *time_info = localtime(&t);
  char *time_as_str = asctime(time_info);

  size_t bytes_to_write = strlen(time_as_str) + 1;
  size_t bytes_written = write(server->data_socket_fd, time_as_str, bytes_to_write);

  if (bytes_written < 0 || bytes_written != bytes_to_write) {
    fprintf(stderr, "Error occured in write(): %s!\n", strerror(errno));
    exit(-9);
  }
}

void send_unkown_command_to_client(server_t *server) {
  char *unknown_command_msg = "Unknown command!\n";
  size_t bytes_to_send = strlen(unknown_command_msg) + 1;
  size_t bytes_send = send(server->data_socket_fd, unknown_command_msg,
                           bytes_to_send, 0);

  if (bytes_send < 0 || bytes_send != bytes_to_send) {
    fprintf(stderr, "Error occurred in send(): %s\n", strerror(errno));
    exit(-8);
  }
}

void close_socket(int *socket) {
  int close_status = close(*socket);

  if (close_status < 0) {
    fprintf(stderr, "Error occurred in close(): %s\n", strerror(errno));
    exit(-9);
  }
}

#endif
