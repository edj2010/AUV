#include <phidget21.h>
#include <unistd.h>
#include "Motor.h"
#include "Stepper.h"
#include <iostream>
using namespace std;

int main(){
  Motor motors;
  //Stepper gimbal;
  motors.setSpeed(120);
  //gimbal.setAngle(0);
  std::cout << "setting angle to 90" << std::endl;
  sleep(3);
  motors.setSpeed(0);
  //gimbal.setAngle(90);
  sleep(2);
  motors.setSpeed(120);
  std::cout << "setting back" << std::endl;
  //gimbal.setAngle(0);
}