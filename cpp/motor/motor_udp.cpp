#include <string>
#include "motor_udp.h"
#include "../utils/utils.h"

#define THIS this->


Motor::Motor (char* host, int port, bool isTCP) {
    THIS torque = 0;
    THIS connection.initConection(host, port, isTCP);
}

void Motor::setTorque (float torque) {
    THIS torque = torque;
    std::string msg = "torque,";
    msg.append(std::to_string(int(torque)));
    THIS connection.sendMsg(msg.c_str());
}

float Motor::getTorque () {
    return THIS torque;
}

float Motor::getSpeed() {
    std::string msg = THIS connection.readSocket(THIS connection.getFD());
    msg = substring(msg)[1];
    THIS speed = atof(msg.c_str());
    return THIS speed;
}

int Motor::getFD() {
    return THIS connection.getFD();
}