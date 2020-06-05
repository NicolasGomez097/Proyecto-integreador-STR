rtc_demo: demo.cpp rtc.o pid.o
	gcc demo.cpp rtc.o pid.o -o demo
	make -s clean

pid_server: pidServer.cpp rtc.o pid.o socket.o
	gcc pidServer.cpp rtc.o pid.o socket.o -o server
	make -s clean 

rtc.o: rtc/rtc.cpp rtc/rtc.h
	gcc rtc/rtc.cpp -c

pid.o: pid/PID.cpp pid/PID.h
	gcc pid/PID.cpp -c -o pid.o

socket.o:
	gcc socket/socket.cpp -c -o socket.o

clean:
	rm -rf *.o
