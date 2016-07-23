#include "Motor.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

int main(int count, char *arg[]){  
  Motor myMotor;
  float thrust = 0.1;
  float diff = 0.1;
  float interval = 1.0;

  // first command line argument is number
  // of seconds to apply pattern
  if(count>1){
    interval = atof(arg[1]);    
  }
  if(count>2){
    thrust = atof(arg[2]);    
  }
  if(count>3){
    diff = atof(arg[3]);    
  }
  

  cout << "Setting pin state to " << state << endl;
  myMotor.setPin3(state);
  myMotor.Apply_Differential(thrust,diff, interval);
  cout << "Applied Thrust" << endl;
  while ( !myMotor.isMotorFinished() ) {
    usleep(1000);
  }
  cout << "Finished" << endl;
}


