#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "client.h"

int main(void) {
  client_t client;

  create_socket(&client);
  set_server_addr(&client);
  connect_to_server(&client);

  while (1) {
    char *buffer = (char *) malloc(BUFFER_SIZE);
    get_user_input(buffer);

    if (strcmp(buffer, "help\n") == 0) {
      print_help_text();
      continue;
    }

    send_command_to_server(&client, buffer);

    if (strcmp(buffer, "exit\n") == 0) {
      free(buffer);
      break;
    }

    receive_data_from_server(&client);
    free(buffer);
  }

  close_socket(&client.client_socket_fd);
  return 0;
}
