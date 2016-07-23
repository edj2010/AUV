#include "Motor.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

int main(int count, char *arg[]){  
  Motor myMotor;

  

  cout << "waiting for switch... " << endl;
  myMotor.wait_til_switch(RCSERVO_PINS3);
  cout << "Switch detected!" << endl;
}


