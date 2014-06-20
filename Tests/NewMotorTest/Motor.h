#ifndef MOTOR_H
#define MOTOR_H

#include <phidget21.h>

const int LEFT_MOTOR = 7;
const int CENTER_MOTOR = 4;
const int RIGHT_MOTOR = 3;

const int LEFT_STOP_RATE = 120;
const int CENTER_STOP_RATE = 120;
const int RIGHT_STOP_RATE = 120;

const int PIVOT_TIME = 500000;

class Motor
{
public:
    Motor();
    
    int getLeftSpeed() { return leftSpeed; }
    int getRightSpeed() { return rightSpeed; }

    void setLeftSpeed(int leftSpeed);
    void setRightSpeed(int rightSpeed);
    
    void setSpeed(int speed);
    
    int getCenterPos() { return centerPos; }
    void setCenterPos(int centerPos);
    
    void aimUp();
    void aimDown();
    
    void pause();
    void unpause();
    
    void commit();
    
    ~Motor();
    
private:
    CPhidgetAdvancedServoHandle servo;

    int leftSpeed;
    int rightSpeed;
    int centerPos;
    
    int leftPrevSpeed;
    int rightPrevSpeed;
    int centerPrevPos;

    float minRate;
    float maxRate;
    float stopRate;
    
    int result;
    double currPos;
    const char *err;
    double minAccel, maxVel;
    
    double diff(double degA, double degB);
};

#endif // MOTOR_H
