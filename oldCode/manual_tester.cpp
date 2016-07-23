#include <iostream>
#include <thread>
#include <atomic>
#include <unistd.h>
#include "InterfaceKit.h"
#include "Eyes.h"
#include "Compass.h"
#include "Motor.h"
#include "Stepper.h"
#include "Spatial.h"

InterfaceKit ifkit;
Eyes cam;
Compass comp;
Motor mot;
Stepper gimbal;
Spatial spat;

int main(){//commands are send by first the letter representing the component, then another representing the command, then the value associated with that commmand
  std::cout << "e:camera c:compass m:motors l:leftmotor r:rightmotor g:stepper s:spatial" << std::endl;
  bool flag = false;
  /*std::thread t([&]{
    std::this_thread::sleep_for(std::chrono::seconds(20));
  
    if(flag==false)
      std::terminate();
  });
  t.join();*/
  //while(true){
    char component, command;
    int value;
    std::cin >> component >> command;
    sleep(5);
    switch(component){
    case 'e'://camera
      switch(command){
      case 'f'://save frame
	cam.saveFrame();
	break;
      case 'e'://getErrorLine
	int r, b, g, pres, error;
	std::cin >> r >> b >> g >> pres >> error;
	std::cout << cam.getErrorLine(r,g,b,pres,error);
	break;
      }
    case 'c'://compass
      break;
    case 'm'://motors
      if(command == 's')
	mot.setSpeed(0);
      else{
	int value, time;
	std::cin >> value >> time;
	mot.setLeftSpeed(value-3);//left an right switched
	mot.setRightSpeed(value-3);
	sleep(time);
	mot.setSpeed(0);
      }
      break;
    case 'l'://leftmotor
      if(command == 's')
	mot.setLeftSpeed(0);
      else{
	int value;
	std::cin >> value;
	mot.setLeftSpeed(value);
      }
      break;
    case 'r'://rightmotor
      if(command == 's')
	mot.setRightSpeed(0);
      else{
        int value;
        std::cin >> value;
        mot.setRightSpeed(value);
      }
      break;
    case 'g'://gimbal
      switch(command){
      case 'z'://zero the gimbal
	gimbal.zero();
	break;
      case 's'://set angle
	int value;
	std::cin >> value;
	gimbal.setAngle(value);
	break;
      case 'g'://get Angle
	std::cout << gimbal.getAngle() << std::endl;
	break;
      }
      break;
    case 's'://spatial
      break;
    case 'q':
      return 0;
    }
  //}
}
