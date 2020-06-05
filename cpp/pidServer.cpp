#include <stdio.h>
#include <sys/select.h>

#include "rtc/rtc.h"
#include "pid/PID.h"
#include "socket/socket.h"

int main() {
    // Definicion variables.
    int cant = 30;
    int i, tick_fd, res;
    fd_set readfds;
    PID pid(0.0, 0.0, 0.0);
    ServerTCP server;

    struct timeval timeout = {1, 0};
    tick_fd = rtc_init(16);

    // inicializacion socket TCP
    server.initSocketServer();

    // Inicializando el SET para el select
    FD_ZERO(&readfds);
    FD_SET(tick_fd, &readfds);
    FD_SET(server.getFD(), &readfds);

    while (true)
    {
        res = select(3, &readfds, NULL, NULL, &timeout);
 
        if(FD_ISSET(tick_fd, &readfds) == 0) {
            /*printf("*");
            fflush(stdout);*/
            rtc_tick();
        }
        if (FD_ISSET(server.getFD(), &readfds)) {
            printf("HHHHHHHHHHHHH\n");
            fflush(stdout);
            char* msg = server.readSocket();
            printf("%s", msg);
            fflush(stdout);
        }
    }
    printf("\n");
    rtc_close();
}
