#include "PID.h"

#define THIS this->

PID::PID (float kp, float ki, float kd) {
    THIS speed = 0.0;
    THIS actualSpeed = 0.0;
    THIS kp = kp;
    THIS ki = ki;
    THIS kd = kd;
    THIS lastError = 0.0;
    THIS acumulatedError = 0.0;    
    THIS dt = 0.1;    
}
/**
 * Funcion para establecer la velocidad deseada.
 */
void PID::setSpeed (float speed) {
    THIS speed = speed;
}

/**
 * Funcion para obtener la velocidad actual del motor.
 */
float PID::getActualSpeed () {   //Setear velocidad actual
    return THIS actualSpeed;
}

/**
 * Funcion para establecer la velocidad actual del motor.
 */
void PID::setActualSpeed (float speed) {   //Setear velocidad actual
    THIS actualSpeed = speed;
}


/**
 * Funcion para establecer el Kp 
 */
void PID::setKp (float kp) {
    THIS kp = kp;
}

/**
 * Funcion para establecer el Ki 
 */
void PID::setKi (float ki) {
    THIS ki = ki;
}

/**
 * Funcion para establecer el Kd 
 */
void PID::setKd (float kd) {
    THIS kd = kd;
}

/**
 * Funcion para establecer el dt
 */
void PID::setDt (float dt) {
    THIS dt = dt;
}

/**
 * Funcion calcular en nuevo torque con resepecto al Kp, ki, kd, speed y actualSpeed.
 */
float PID::calculateTorque () { 
    float proportional = 0.0;
    float integral = 0.0;
    float derivative = 0.0;
    float error = THIS speed - THIS actualSpeed;
    
    proportional = THIS kp * THIS speed;
    
    THIS acumulatedError += error;
    integral = THIS ki * THIS acumulatedError * THIS dt;
    
    derivative = THIS kd * (error - THIS lastError) / THIS dt;
    THIS lastError = error;
    
    float torque = proportional + integral + derivative;
    
    if (torque < 0) {
        return 0;
    }
    return torque;
}
