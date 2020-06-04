#include <stdio.h>
#include <sys/select.h>

#include "rtc/rtc.h"
#include "pid/PID.h"

int main() {
    int cant = 30;
    int i, fd, res;
    PID pid(0.0, 0.0, 0.0);
    printf("%f\n", pid.getActualSpeed());
    fd_set readfds;
    struct timeval timeout = {1, 0};

    FD_ZERO(&readfds);

    fd = rtc_init(16);
    FD_SET(fd, &readfds);

    for (i = 0; i < cant; i++) {
        res = select(1, &readfds, NULL, NULL, &timeout);
        rtc_tick();
   	printf("*");
	fflush(stdout);
    }
    printf("\n");
    rtc_close();
}
