rtc_demo: demo.cpp rtc.o pid.o
	gcc demo.cpp rtc.o pid.o -o demo
	make -s clean

pid_server: pidServer.cpp rtc.o pid.o socket.o motor.o
	g++ pidServer.cpp \
		rtc.o pid.o socket.o motor.o \
		-o server;
	make -s clean 

rtc.o: rtc/rtc.cpp rtc/rtc.h
	g++ rtc/rtc.cpp -c

pid.o: pid/PID.cpp pid/PID.h
	g++ pid/PID.cpp -c -o pid.o

socket.o:
	g++ socket/socket.cpp -c -o socket.o

motor.o:
	g++ motor/motor.cpp -c -o motor.o

clean:
	rm -rf *.o
