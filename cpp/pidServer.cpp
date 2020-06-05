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
    tick_fd = rtc_init(1);

    // inicializacion socket TCP
    server.initSocketServer();
    
    printf("Server FD: %d\n", server.getFD());
    fflush(stdout);

    

    while (true)
    {
        // Inicializando el SET para el select
        FD_ZERO(&readfds);
        FD_SET(tick_fd, &readfds);
        FD_SET(server.getFD(), &readfds);

        res = select(5, &readfds, NULL, NULL, NULL);
 
        if(FD_ISSET(tick_fd, &readfds)) {
            printf("*");
            fflush(stdout);
            rtc_tick();
        }
        if (FD_ISSET(server.getFD(), &readfds)) {
            char* msg = server.readSocket();
            server.sendMsg("Response");
            printf("%s\n", msg);
            fflush(stdout);
        }
    }
    printf("\n");
    rtc_close();
}
