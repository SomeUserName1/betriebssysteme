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
  struct aiocb aio_cb;
} server_t;

void init(server_t *server);
void create_socket(server_t *server);
void set_server_addr(server_t *server);
void bind_socket(server_t *server);
void listen_socket(server_t *server);
void accept_socket(server_t *server);
void check_client_connections_for_data(server_t *server);
int get_commands_from_clients(server_t *server);
void set_aio_cb(server_t *server, int *fd, char *buffer, int size);
ssize_t asynchronous_read(server_t *server, int *fd, char *buffer, int size);
int parse_command_and_response(server_t *server, char *command_buffer);
void send_date_and_time_to_client(server_t *server);
void send_unkown_command_to_client(server_t *server);
void send_content_of_file_to_client(server_t *server, char *file_path);
ssize_t asynchronous_write(server_t *server, int *fd, char *buffer, int size);
void send_open_error_to_client(server_t *server);
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
                                     SO_REUSEADDR, (char *) &opt,
                                     sizeof(opt));

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
  server->client_socket_fd = accept(server->server_socket_fd,
                                    (struct sockaddr *) &server->addr,
                                    &addr_len);
  if (server->client_socket_fd < 0) {
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

  if (server->num_socket_fds < 0) {
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

int get_commands_from_clients(server_t *server) {
  for (int i = 0; i < FD_SETSIZE; i++) {
      server->data_socket_fd = server->client_sockets[i];

      if (FD_ISSET(server->data_socket_fd, &server->reading_fd_set)) {
          char *command_buffer = (char *) malloc(BUFFER_SIZE);
          memset(command_buffer, 0, BUFFER_SIZE);


          ssize_t bytes_read = asynchronous_read(server, &server->data_socket_fd,
                                                 command_buffer, BUFFER_SIZE);

          if (bytes_read == 0) {
            close_socket(&server->data_socket_fd);
            server->client_sockets[i] = 0;
            free(command_buffer);
            printf("A client disconnected.\n");
          } else if (bytes_read < 0) {
            fprintf(stderr, "Error occured in asynchronous_read(): %s\n", strerror(errno));
          } else {
            printf("Received from client: %s", command_buffer);
            int status = parse_command_and_response(server, command_buffer);
            free(command_buffer);
            if (status == 1) {
              return 1;
            }
          }
      }
  }
  return 0;
}

void set_aio_cb(server_t *server, int *fd, char *buffer, int size) {
  memset(&server->aio_cb, 0, sizeof(server->aio_cb));
  server->aio_cb.aio_nbytes = size;
  server->aio_cb.aio_fildes = *fd;
  server->aio_cb.aio_buf = buffer;
}

ssize_t asynchronous_read(server_t *server, int *fd, char *buffer, int size) {
  set_aio_cb(server, fd, buffer, size);

  if (aio_read(&server->aio_cb) < 0) {
    fprintf(stderr, "Error occurred in aio_read(): %s!\n", strerror(errno));
    exit(-7);
  }

  while(aio_error(&server->aio_cb) == EINPROGRESS) {
    ;
  }

  return aio_return(&server->aio_cb);
}

int parse_command_and_response(server_t *server, char *command_buffer) {
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
    send_date_and_time_to_client(server);
  } else if(strcmp(tokens[0], "get") == 0 && strcmp(tokens[1], "file") == 0) {
    char *path_to_file_without_newline = strtok(tokens[2], "\n");
    send_content_of_file_to_client(server, path_to_file_without_newline);
  } else if (strcmp(tokens[0], "close") == 0 && strcmp(tokens[1], "server\n") == 0) {
    return 1;
  } else {
    send_unkown_command_to_client(server);
  }
  return 0;
}

void send_date_and_time_to_client(server_t *server) {
  time_t t = time(NULL);
  struct tm *time_info = localtime(&t);
  char *time_as_str = asctime(time_info);

  size_t bytes_to_write = strlen(time_as_str) + 1;
  ssize_t bytes_written = asynchronous_write(server, &server->data_socket_fd,
                                             time_as_str, bytes_to_write);

  if (bytes_written < 0 || bytes_written != bytes_to_write) {
    fprintf(stderr, "Error occured in asynchronous_write(): %s!\n", strerror(errno));
  }
}

void send_unkown_command_to_client(server_t *server) {
  char *unknown_command_msg = "Unknown command!\n";

  size_t bytes_to_write = strlen(unknown_command_msg) + 1;
  ssize_t bytes_written = asynchronous_write(server, &server->data_socket_fd,
                                             unknown_command_msg, bytes_to_write);

  if (bytes_written < 0 || bytes_written != bytes_to_write) {
    fprintf(stderr, "Error occurred in asynchronous_write(): %s\n", strerror(errno));
  }
}

void send_content_of_file_to_client(server_t *server, char *file_path) {
  int file_fd = open(file_path, O_RDONLY);

  if (file_fd < 0) {
    fprintf(stderr, "Error occured in open(): %s!\n", strerror(errno));
    send_open_error_to_client(server);
    return;
  }

  struct stat file_stat;

  fstat(file_fd, &file_stat);

  char *file_content_buffer = (char *) malloc(file_stat.st_size);

  ssize_t bytes_read = asynchronous_read(server, &file_fd, file_content_buffer,
                                         file_stat.st_size);

  if (bytes_read < 0) {
    fprintf(stderr, "Error occured in asynchronous_read(): %s!\n", strerror(errno));
  }

  ssize_t bytes_written = asynchronous_write(server, &server->data_socket_fd,
                                             file_content_buffer,
                                             file_stat.st_size);

  if (bytes_written < 0 || bytes_written != file_stat.st_size) {
    fprintf(stderr, "Error occured in asynchronous_write(): %s!\n", strerror(errno));
  }

  free(file_content_buffer);
  close(file_fd);
}

ssize_t asynchronous_write(server_t *server, int *fd, char *buffer, int size) {
  set_aio_cb(server, fd, buffer, size);

  if (aio_write(&server->aio_cb) < 0) {
    fprintf(stderr, "Error occurred in aio_write(): %s!\n", strerror(errno));
    exit(-7);
  }

  while(aio_error(&server->aio_cb) == EINPROGRESS) {
    ;
  }

  return aio_return(&server->aio_cb);
}

void send_open_error_to_client(server_t *server) {
  char *open_error_msg;
  int rc = asprintf(&open_error_msg, "Error occured in open(): %s!\n",
                    strerror(errno));

  if (rc < 0) {
    fprintf(stderr, "Error occured in asprintf(): %s!\n", strerror(errno));
  }

  size_t bytes_to_write = strlen(open_error_msg) + 1;
  ssize_t bytes_written = asynchronous_write(server, &server->data_socket_fd,
                                             open_error_msg, bytes_to_write);

  if (bytes_written < 0 || bytes_written != bytes_to_write) {
    fprintf(stderr, "Error occured in asynchronous_write(): %s!\n", strerror(errno));
  }

  free(open_error_msg);
}

void close_socket(int *socket) {
  int close_status = close(*socket);

  if (close_status < 0) {
    fprintf(stderr, "Error occurred in close(): %s\n", strerror(errno));
    exit(-8);
  }
}

#endif
