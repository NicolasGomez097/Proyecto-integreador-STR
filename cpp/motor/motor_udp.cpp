#include "motor.h"
#include "socket/socketClient.h"

#define THIS this->

Motor::Motor (float maxSpeed, float sensitivity) {
    THIS maxSpeed = maxSpeed;
    THIS sensitivity = sensitivity;
    THIS torque = 0;
}

void Motor::setMaxSpeed (float maxSpeed) {
    THIS maxSpeed = maxSpeed;
}

void Motor::setTorque (float torque) {
    THIS torque = torque;
}

float Motor::getTorque () {
    return THIS torque;
}

float Motor::getSpeed() {
    float finalVelocity = THIS maxSpeed * (1.0 - exp(-THIS torque * THIS sensitivity));
    THIS speed = lerp(THIS speed, finalVelocity, ACCELERATION);
    
    return THIS speed;
}