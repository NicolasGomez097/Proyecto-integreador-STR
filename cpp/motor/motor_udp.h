#ifndef MOTOR_UDP_CLASS
#define MOTOR_UDP_CLASS 

#include "../socket/ClientSocket.h"

class Motor {
    public:
        Motor (char* host, int port, bool isTCP);
        void setTorque (float);
        float getTorque ();
        float getSpeed();
        int getFD();
        
    private:
        float speed;
        float torque;
        ClientSocket connection;
};
#endif
