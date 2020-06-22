#include "PID.h"
#include <stdio.h>


#define THIS this->

PID::PID (float kp, float ki, float kd) {
    THIS desiredSpeed = 0.0;
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
void PID::setDesiredSpeed (int desiredSpeed) {
    if(THIS desiredSpeed == desiredSpeed) {
        return;
    }
    THIS desiredSpeed = desiredSpeed;
    //THIS acumulatedError = 0.0;
}

/**
 * Funcion para obtener la velocidad deseada.
 */
int PID::getDesiredSpeed () {
    return THIS desiredSpeed;
}

/**
 * Funcion para obtener la velocidad actual del motor.
 */
int PID::getActualSpeed () {   //Setear velocidad actual
    return THIS actualSpeed;
}

/**
 * Funcion para establecer la velocidad actual del motor.
 */
void PID::setActualSpeed (int actualSpeed) {   //Setear velocidad actual
    THIS actualSpeed = actualSpeed;
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
 * Funcion calcular en nuevo torque con resepecto al Kp, ki, kd, desiredSpeed y actualSpeed.
 */
int PID::calculateTorque () { 
    float proportional = 0.0;
    float integral = 0.0;
    float derivative = 0.0;
    float error = THIS desiredSpeed - THIS actualSpeed;
    float dError = error - THIS lastError;
    /*if(dError < 0){
        dError*= -1;
    } */
    
    proportional = THIS kp * THIS desiredSpeed;
    
    THIS acumulatedError += error;
    integral = THIS ki * THIS acumulatedError * THIS dt;
    
    derivative = THIS kd * dError / THIS dt;

    THIS lastError = error;
    
    THIS torque = proportional + integral + derivative;
    
    if (THIS torque < 0) {
        THIS torque = 0;
    }
    if (THIS torque > 255) {
        THIS torque = 255;
    }
    return THIS torque;
}

int PID::getTorque() {
    return THIS torque;
}
