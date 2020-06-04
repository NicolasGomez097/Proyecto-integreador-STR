#ifndef PID_CLASS
#define PID_CLASS 
class PID {
    public:
        PID (float kp, float ki, float kd);
        void setSpeed (float);
        float getActualSpeed ();
        void setActualSpeed (float);
        void setKp (float);
        void setKi (float);
        void setKd (float);
        void setDt (float);
        float calculateTorque ();
        
    private:
        float speed;
        float actualSpeed;
        float kp;
        float ki;
        float kd;
        float dt;
        float lastError;
        float acumulatedError;
};
#endif
