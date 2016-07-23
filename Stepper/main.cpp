
#include <unistd.h>
#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <phidget21.h>
#include "Stepper.h"
// #include "PID_Controller.h"
// #include "Compass.h"
// #include "InterfaceKit.h"
// #include "LCD.h"
// #include "Motor.h"
// #include "Spatial.h"
// #include "Eyes.h"
using namespace std;

int main(int count, char *arg[]){
  int angle = atoi(arg[1]);
  //int i;
  Stepper stepper;
  stepper.setAngle(angle);
}
