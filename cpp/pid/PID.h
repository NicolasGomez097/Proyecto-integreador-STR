#ifndef PID_CLASS
#define PID_CLASS 
class PID {
    public:
        PID (float kp, float ki, float kd);
        void setDesiredSpeed (float);
        float getDesiredSpeed ();
        float getActualSpeed ();
        void setActualSpeed (float);
        void setKp (float);
        void setKi (float);
        void setKd (float);
        void setDt (float);
        float getTorque ();
        float calculateTorque ();
        
    private:
        float desiredSpeed;
        float actualSpeed;
        float kp;
        float ki;
        float kd;
        float dt;
        float lastError;
        float acumulatedError;
        float torque;
};
#endif
