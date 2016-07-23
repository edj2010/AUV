#include <rb/roboard.h>
#include <iostream>
#include <unistd.h>
#include <math.h>

class Motor {
 public:
  Motor();
  int Apply_Differential(float,float,float);
  unsigned long leftDuty(float); 
  unsigned long rightDuty(float); 
  int isMotorFinished(); 
  int readChannel(int); 
  void wait_til_switch(int);
  ~Motor();
 private:
  unsigned long PWM_period;
  //Assume simple bi-linear model for thrust response to
  // duty cycle... here are calibration parameters for left
  // and right motors...
  unsigned long LEFT_Zero;
  unsigned long RIGHT_Zero;
  unsigned long RIGHT_Max;
  unsigned long LEFT_Max;
  unsigned long RIGHT_Min;
  unsigned long LEFT_Min;
  // arbitrary guess of limit so that we still have enough
  // thrust available to turn
  float MAX_UsableThrust;
};
