#define _GNU_SOURCE
#include <aio.h>
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include "server.h"

void handle_SIGUSR1_signal(int arg);


server_t server;

int main(void) {
    signal(SIGUSR1, handle_SIGUSR1_signal);
    init(&server);


    while(1) {
        check_for_new_clients_to_connect(&server);
        int status = get_commands_from_clients(&server);

        if (status == 1) {
          break;
        }
    }
    clear_file_cache(&server.client_file_cache);
    close_socket(&server.server_socket_fd);
    return 0;
}

void handle_SIGUSR1_signal(int arg) {
  clear_file_cache(&server.client_file_cache);
}
