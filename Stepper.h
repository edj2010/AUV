#include <phidget21.h>

#ifndef STEPPER_H
#define STEPPER_H

const int ANG_FACTOR=450;//"degrees" for 1 degree of rotation;

class Stepper{
  long pos;//zero is flat
  double minAccel, maxVel;
  int stopped;
  CPhidgetStepperHandle stepper;
 public:
  Stepper();
  long getAngle(){return pos;}
  void setAngle(long);
  void zero();
  ~Stepper();
};

#endif
