#include <stdlib.h>
#include <unistd.h>
#include <cmath>
#include <iostream>
#include <iomanip>

//#include <phidget21.h>
//#include "Stepper.h"
//#include "PID_Controller.h"
#include "Compass.h"
//#include "InterfaceKit.h"
//#include "LCD.h"
//#include "Motor.h"
//#include "Spatial.h"
//#include "Eyes.h"
using namespace std;


int main(int count, char *arg[]){
  int reps = atoi(arg[1]);
  int i;
  Compass compass;
  for (i=0; i<reps; ++i){
    compass.refresh();
//    compass.debug();
    cout << setw(8) << compass.getHeading() << " "
	 << setw(8) << compass.getPitch() << " "
	 << setw(8) << compass.getRoll()  << " "
	 << setw(8) << compass.getTemp() << " "
	 << setw(8) << compass.getDepth() << " "
         << setw(8) << DEPTH_OFFSET << endl;
    usleep(100000);
  }
}  
