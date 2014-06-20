#include <iostream>
#include <cmath>
#include <phidget21.h>

#include "Motor.h"

Motor::Motor()
{
    CPhidgetAdvancedServo_create(&servo);
    CPhidget_open((CPhidgetHandle)servo,-1);
    
    if(CPhidget_waitForAttachment((CPhidgetHandle)servo, 1000)) {
        std::cout << "Error attaching Phidget Advanced Servo." << std::endl;
    }
    
    rightSpeed = 0;
    leftSpeed = 0;
    centerPos = 0;
    
    minRate = 0.00;
    maxRate = 220.00;
    
    CPhidgetAdvancedServo_setPosition (servo, LEFT_MOTOR, LEFT_STOP_RATE);
    CPhidgetAdvancedServo_getAccelerationMin(servo, LEFT_MOTOR, &minAccel);
    CPhidgetAdvancedServo_setAcceleration(servo, LEFT_MOTOR, minAccel*4/3);
    CPhidgetAdvancedServo_getVelocityMax(servo, LEFT_MOTOR, &maxVel);
    CPhidgetAdvancedServo_setVelocityLimit(servo, LEFT_MOTOR, maxVel/3);
    CPhidgetAdvancedServo_setEngaged(servo, LEFT_MOTOR, 1);
    
    CPhidgetAdvancedServo_setPosition (servo, RIGHT_MOTOR, LEFT_STOP_RATE);
    CPhidgetAdvancedServo_getAccelerationMin(servo, RIGHT_MOTOR, &minAccel);
    CPhidgetAdvancedServo_setAcceleration(servo, RIGHT_MOTOR, minAccel*4/3);
    CPhidgetAdvancedServo_getVelocityMax(servo, RIGHT_MOTOR, &maxVel);
    CPhidgetAdvancedServo_setVelocityLimit(servo, RIGHT_MOTOR, maxVel/3);
    CPhidgetAdvancedServo_setEngaged(servo, RIGHT_MOTOR, 1);
    setSpeed(0);
}

void Motor::setLeftSpeed(float leftSpeed)
{
    leftPrevSpeed = leftSpeed;
    this->leftSpeed = leftSpeed;
    
    commit();
}

void Motor::setRightSpeed(float rightSpeed)
{
    rightPrevSpeed = rightSpeed;
    this->rightSpeed = rightSpeed;
    
    commit();
}

void Motor::setSpeed(float speed)
{
    leftPrevSpeed = leftSpeed;
    leftSpeed = speed;
    
    rightPrevSpeed=rightSpeed;
    rightSpeed = speed;
    
    commit();
}

void Motor::setCenterPos(int centerPos)
{
    this->centerPos = centerPos;
}


void Motor::aimUp()
{
    CPhidgetAdvancedServo_setPosition(servo, CENTER_MOTOR, 115);
    usleep(PIVOT_TIME);
    CPhidgetAdvancedServo_setPosition(servo, CENTER_MOTOR, 120);
};

void Motor::aimDown()
{
    CPhidgetAdvancedServo_setPosition(servo, CENTER_MOTOR, 125);
    usleep(PIVOT_TIME);
    CPhidgetAdvancedServo_setPosition(servo, CENTER_MOTOR, 120);
}

void Motor::pause()
{
  leftPrevSpeed=leftSpeed;
  rightPrevSpeed=rightSpeed;
  leftSpeed = 0;
  rightSpeed = 0;
  commit();
}

void Motor::unpause()
{
    leftSpeed = leftPrevSpeed;
    rightSpeed = rightPrevSpeed;
    commit();
}

Motor::~Motor()
{
    pause(); //Just in case the motors are running, stops it.
    CPhidgetAdvancedServo_setEngaged(servo, LEFT_MOTOR, 0);
    CPhidgetAdvancedServo_setEngaged(servo, CENTER_MOTOR, 0);
    CPhidgetAdvancedServo_setEngaged(servo, RIGHT_MOTOR, 0);
}

void Motor::commit()
{
    float left;
    float right;
//    float center;

    left = leftSpeed + LEFT_STOP_RATE-10;
    right = rightSpeed + RIGHT_STOP_RATE-30;
    std::cout << LEFT_STOP_RATE << " " << RIGHT_STOP_RATE << std::endl;
    
//    center = (float)(diff(centerPos, centerPrevPos) * (5/9));
    centerPrevPos = centerPos;

    CPhidgetAdvancedServo_setPosition (servo, LEFT_MOTOR, left);
//    CPhidgetAdvancedServo_setPosition (servo, CENTER_MOTOR, centerPos);
    CPhidgetAdvancedServo_setPosition (servo, RIGHT_MOTOR, right);
    
    std::cout << left << " " << right << std::endl;
}

//double Motor::diff(double degA, double degB){
//    double diffA=degA-degB;
//    if(degA>degB){
//        degB+= 360;
//    }
//    else{
//        degA+=360;
//    }
//    double diffB=degA-degB;
//    if(std::abs(diffA)<std::abs(diffB)){
//        return diffA;
//    }
//    else{
//        return diffB;
//    }
//}
