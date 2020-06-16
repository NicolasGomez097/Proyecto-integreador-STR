#ifndef PID_CLASS
#define PID_CLASS 
class PID {
    public:
        PID (float kp, float ki, float kd);
        void setDesiredSpeed (int);
        int getDesiredSpeed ();
        int getActualSpeed ();
        void setActualSpeed (int);
        void setKp (float);
        void setKi (float);
        void setKd (float);
        void setDt (float);
        int getTorque ();
        int calculateTorque ();
        
    private:
        int desiredSpeed;
        int actualSpeed;
        float kp;
        float ki;
        float kd;
        float dt;
        float lastError;
        float acumulatedError;
        int torque;
};
#endif
