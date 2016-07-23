#include <stdlib.h>
#include <unistd.h>
#include <cmath>
#include <iostream>
#include <iomanip>

//#include <phidget21.h>
//#include "Stepper.h"
//#include "PID_Controller.h"
#include "Compass.h"
#include "PID_Controller.h"
//#include "InterfaceKit.h"
//#include "LCD.h"
//#include "Motor.h"
//#include "Spatial.h"
//#include "Eyes.h"
using namespace std;


int main(int count, char *arg[]){
  int reps = atoi(arg[1]);
  double direction = atof(arg[2]);
  int i;
  Compass compass;
  PID_Controller pid_controller(0.1,0.05,0);
  double current_heading;
  double err;
  for (i=0; i<reps; ++i){   
    compass.refresh();
    current_heading = compass.getHeading();
    err = compass.angleDif(direction, current_heading);
    cout << setw(8) << err << " "
	 << setw(8) << direction << " "
	 << setw(8) << current_heading << " "
	 << setw(8) << pid_controller.getCorrection(err) << endl;    
   usleep(100000);
  }
}  
