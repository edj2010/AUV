#include <iostream>
#include <thread>
#include <atomic>
#include <unistd.h>
#include "Motor.h"
#include "Stepper.h"

Motor mot;
Stepper gimbal;

int main(){
  sleep(5);
  std::cout << "tilting gimbal" << std::endl;
  gimbal.setAngle(10);
  sleep(5);
  mot.setLeftSpeed(-13);
  mot.setRightSpeed(-13);
  sleep(3);
  gimbal.setAngle(0);
  sleep(10);
}