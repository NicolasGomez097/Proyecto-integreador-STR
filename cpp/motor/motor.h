#ifndef MOTOR_CLASS
#define MOTOR_CLASS 
class Motor {
    public:
        Motor (float maxSpeed, float sensitivity);
        void setMaxSpeed (float);
        void setTorque (float);
        float getTorque ();
        float getSpeed();
        
    private:
        float speed;
        float maxSpeed;
        float torque;
        float sensitivity;
};
#endif
