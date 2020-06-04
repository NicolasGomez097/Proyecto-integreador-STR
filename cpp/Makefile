rtc_demo: demo.cpp rtc.o pid.o
	gcc demo.cpp rtc.o pid.o -o demo
	make -s clean

rtc.o: rtc/rtc.cpp rtc/rtc.h
	gcc rtc/rtc.cpp -c

pid.o: pid/PID.cpp pid/PID.h
	gcc ./pid/PID.cpp -c -o pid.o

clean:
	rm -rf *.o
