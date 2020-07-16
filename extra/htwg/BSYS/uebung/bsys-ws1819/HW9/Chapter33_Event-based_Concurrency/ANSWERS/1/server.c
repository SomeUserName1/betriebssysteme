#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <time.h>

#include "server.h"


int main(void) {
  server_t server;
  init(&server);

  while (1) {
    char *buffer = (char *) malloc(BUFFER_SIZE);
    memset(buffer, 0, BUFFER_SIZE);

    receive_command_from_client(&server, buffer);

    if (strcmp(buffer, "exit\n") == 0) {
      free(buffer);
      printf("A client disconnected.\n");
      break;
    } else if (strcmp(buffer, "get time\n") == 0) {
      send_date_and_time_to_client(&server);
      free(buffer);
    } else {
      send_unkown_command_to_client(&server);
      free(buffer);
    }
  }
  close_socket(&server.server_socket_fd);
  return 0;
}
