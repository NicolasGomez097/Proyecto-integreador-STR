pid_server: cpp/pidServer.cpp rtc.o pid.o ServerSocket.o motor_udp.o ClientSocket.o utils.o SelectManager.o
	g++ cpp/pidServer.cpp \
		rtc.o pid.o ServerSocket.o motor_udp.o ClientSocket.o utils.o SelectManager.o \
		-w -o server;
	make -s clean 

pid_server_sim: cpp/pidServerSim.cpp rtc.o pid.o ServerSocket.o motor.o ClientSocket.o utils.o SelectManager.o
	g++ cpp/pidServerSim.cpp \
		rtc.o pid.o ServerSocket.o motor.o ClientSocket.o utils.o SelectManager.o \
		-w -o server;
	make -s clean

clean:
	rm -rf *.o

rtc.o:
	g++ cpp/rtc/rtc.cpp -c

pid.o:
	g++ cpp/pid/PID.cpp -c -o pid.o

ServerSocket.o:
	g++ cpp/socket/ServerSocket.cpp -c -o ServerSocket.o

ClientSocket.o:
	g++ cpp/socket/ClientSocket.cpp -c -w -o ClientSocket.o

SelectManager.o:
	g++ cpp/select/SelectManager.cpp -c -w -o SelectManager.o

motor.o:
	g++ cpp/motor/motor.cpp -c -o motor.o

motor_udp.o:
	g++ cpp/motor/motor_udp.cpp -c -o motor_udp.o

utils.o:
	g++ cpp/utils/utils.cpp -c -o utils.o
