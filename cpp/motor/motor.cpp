#include "motor.h"
#include <cmath>


#define THIS this->
#define ACCELERATION 0.02 // Velocidad de reaccion del motor, 0 < ACCELERATION <= 1;

float lerp(float v1, float v2, float t);

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

float lerp(float v1, float v2, float t) {
    return v1 + (v2 - v1) * t;
}