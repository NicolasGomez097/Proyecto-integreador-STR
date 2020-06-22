rtc_demo: demo.cpp rtc.o pid.o
	gcc demo.cpp rtc.o pid.o -o demo
	make -s clean

pid_server: pidServer.cpp rtc.o pid.o ServerSocket.o motor_udp.o ClientSocket.o utils.o SelectManager.o
	g++ pidServer.cpp \
		rtc.o pid.o ServerSocket.o motor_udp.o ClientSocket.o utils.o SelectManager.o \
		-w -o server;
	make -s clean 

rtc.o: rtc/rtc.cpp rtc/rtc.h
	g++ rtc/rtc.cpp -c

pid.o: pid/PID.cpp pid/PID.h
	g++ pid/PID.cpp -c -o pid.o

ServerSocket.o:
	g++ socket/ServerSocket.cpp -c -o ServerSocket.o

ClientSocket.o:
	g++ socket/ClientSocket.cpp -c -w -o ClientSocket.o

SelectManager.o:
	g++ select/SelectManager.cpp -c -w -o SelectManager.o

motor.o:
	g++ motor/motor.cpp -c -o motor.o

motor_udp.o:
	g++ motor/motor_udp.cpp -c -o motor_udp.o

utils.o:
	g++ utils/utils.cpp -c -o utils.o

clean:
	rm -rf *.o
