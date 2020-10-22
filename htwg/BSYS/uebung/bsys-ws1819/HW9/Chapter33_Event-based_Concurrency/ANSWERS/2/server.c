#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#include "server.h"

int main(void) {
    server_t server;
    init(&server);

    while(1) {
        check_for_new_clients_to_connect(&server);
        int status = get_command_from_client_and_response(&server);
        if (status == 1) {
          break;
        }
    }

    close_socket(&server.server_socket_fd);
    return 0;
}
