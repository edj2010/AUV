
#include <unistd.h>
#include <cmath>
#include <iostream>

#include <phidget21.h>
#include "Stepper.h"
#include "PID_Controller.h"
#include "Compass.h"
#include "InterfaceKit.h"
#include "LCD.h"
#include "Motor.h"
#include "Spatial.h"
#include "Eyes.h"
using namespace std;

const int LINE_C_RED = 0;//0-255
const int LINE_C_GREEN = 0;//0-255
const int LINE_C_BLUE = 0;//0-255
const int PRECISION = 10; //must be greater that 0
const int MAX_COLOUR_ERROR = 100;//0-255




Motor motor;//
Stepper gimble;
Compass compass;//
//LCD lcd;
//InterfaceKit ifKit;
//Spatial spatial;//
//Eyes eye;//
PID_Controller pid; 
void waitForGo();
int move(int meters);

double diff(double degA, double degB);
double displace(double forDistance, double deg, double sideDistance=0);

int main(){
  //lcd.setBacklight(0);
  std::cout << "sleeping" << std::endl;
  usleep(1000000);
  //waitForGo();
  motor.setLeftSpeed(0);
  motor.setRightSpeed(0);
  int time;
  std::cout << "time" << std::endl;
  std::cin >> time;
  sleep(5);
  std::cout << "moving" << std::endl;
  move(time);
  std::cout << "end" << std::endl;
  //gimble.setAngle(10);
  //move(5);
  //followLine();
  // std::cout << "Turning motors downwards..." << std::endl;
  // motor.aimDown();
  
  // std::cout << "Motor pivot downwards complete. Press ENTER to move forward:" << endl;
  // std::cin.ignore();
  
  // std::cout << "Moving AUV forward..." << std::endl;
  // move(1);
  // std::cout << "Move complete. Press ENTER to aim motors upwards:" << endl;
  // std::cin.ignore();
  // std::cout << "Turning motors upwards..." << std::endl;
  // motor.aimUp();
  
  // std::cout << "Moving AUV forward..." << std::endl;
  // std::cin.ignore();
  // move(30);
    
  // std::cout << "Program Complete. Press ENTER to quit." << endl;
  // std::cin.ignore();
  
  // std::cout << "Program Complete." << endl;
}

/*void waitForGo()
{
  std::cout << "Program initialized. Waiting for switch to be pulled..." << std::endl;
   
   while (!ifKit.isRunning()) {
     std::cout << "." << std::endl;
     usleep(1000000); //check every 1 seconds
   }
   
   std::cout << "Switch pulled. Program will commence in 5 seconds." << std::endl;
   
   usleep(5000000); //5 seconds
}*/

/*void followLine(){
  std::cout << "following line" << std::endl;
  motor.setLeftSpeed(120);
  motor.setLeftSpeed(120);
  std::cin.ignore();
  int corr = 0;
  do{
    motor.setLeftSpeed(120-corr);
    motor.setRightSpeed(120+corr);
    corr = eye.getErrorLine(LINE_C_RED,LINE_C_GREEN,LINE_C_BLUE,PRECISION,MAX_COLOUR_ERROR);
  }while(true);
}*/

/*void move(int meters){
  cout << "moving" << endl;
  motor.setLeftSpeed(10);
  motor.setRightSpeed(10);
  cin.ignore();
  for(int i = 0; i < meters; i++){
    motor.setRightSpeed(10);
    usleep(1000000);
    motor.setRightSpeed(0);
    usleep(4700000);
  }    
  cout << "done moving" << endl;
  motor.setSpeed(0);
  motor.pause();
}*/

//void move(int meters)
//{
//    //declare variables
//    double desiredHeading = compass.getHeading();
//    double CHeading =0;
//    
//    PID_Controller zAxis(1,1,1);
//    PID_Controller Drift(1,1,1);
//    PID_Controller xAxis(1,1,1);
//    PID_Controller fTimer;
//    PID_Controller sTimer;
//    double displacement=0;
//    
//    //forward
//    double fspeed=0;
//    double flspeed=0;
//    double faccel=0;
//    double flaccel=0;
//    double ftime=fTimer.getTime();
//    double fltime=0;
//    
//    //sideways
//    double sspeed=0;
//    double slspeed=0;
//    double saccel=0;
//    double slaccel=0;
//    double stime=sTimer.getTime();
//    double sltime=0;
//    
//    while(displacement < meters) {
//        
//        usleep(100000);
//        CHeading = compass.getHeading();
//        faccel = spatial.getAcceleration(1);
//        
//        //calculate fdistance
//        flaccel=faccel;
//        faccel = spatial.getAcceleration(AXIS_Y);//read accelerometer
//        flspeed = fspeed;
//        fltime = ftime;
//        ftime = fTimer.getTime();
//        double ftimestamp = ftime-fltime;
//        fspeed += (flaccel+faccel)/2*ftimestamp;
//        double fdistance = (flspeed+fspeed)/2*ftimestamp;
//        
//        //calculate sdistance
//        slaccel=saccel;
//        saccel = spatial.getAcceleration(AXIS_X);//read accelerometer
//        slspeed = sspeed;
//        sltime = stime;
//        stime = sTimer.getTime();
//        double stimestamp = stime-sltime;
//        sspeed += (slaccel+saccel)/2*stimestamp;
//        double sdistance = (slspeed+sspeed)/2*stimestamp;
//        
//        //calculate correction
//        double zCorrection = zAxis.getCorrection(diff(CHeading,desiredHeading));
//        double DriftCorrection = Drift.getCorrection(displace(sdistance, diff(CHeading, desiredHeading), fdistance));
//        
//        //set motor speeds
//        if (zCorrection+DriftCorrection > 0) {
//            motor.setRightSpeed(90-zCorrection-DriftCorrection);
//            motor.setLeftSpeed(10);
//            motor.commit();
////            cout << "set left speed: " << (90-zCorrection-DriftCorrection) << ". set right speed: 80";
//        }
//        else {
//            motor.setRightSpeed(90);
//            motor.setLeftSpeed(10+zCorrection+DriftCorrection);
//            motor.commit();
////            cout << "set left speed: 90. set right speed: " << (80+zCorrection+DriftCorrection);
//        }
//        
//        //calculate displacement
//        displacement += displace(fdistance, diff(CHeading, desiredHeading), sdistance);
//        cout << displacement << endl;
//    }
//}

double diff(double degA, double degB)
{
    double diffA = degA - degB;
    
    if(degA>degB) {
        degB+= 360;
    }
    
    double diffB=degA-degB;
    
    if (abs(diffA)<abs(diffB)) {
        return diffA;
    }
    else {
        return diffB;
    }
}

double displace(double forDistance, double deg, double sideDistance)
{
    deg *= 3.141592653589793238462643383279 /*Yes it is necessary*/ /180;
    
    return cos(deg)*forDistance + sin(deg)*sideDistance;
}

//void WaitForBarrelRoll(){
//    lcd.setBrightness(50);
//    lcd.setContrast(50);
//    lcd.setText("Awaiting Barrel Roll",1);
//
//    while (compass.getRoll()<60){
//        usleep(10000);
//    }
//    lcd.setText("DO A BARREL ROLL",1);
//    lcd.setText("BARRELROLLBARRELROLL",2);
//
//    while (compass.getRoll()<120){
//        usleep(10000);
//    }
//    while (compass.getRoll()<180){
//        usleep(10000);
//    }
//    while(compass.getRoll()<240){
//        usleep(10000);
//    }
//    while(compass.getRoll()<300){
//        usleep(10000);
//    }
//    while(compass.getRoll()<360){
//        usleep(10000);
//    }
//    lcd.setText("Commencing Mission!",1);
//    lcd.setText("",2);
//    usleep(500000);
//    lcd.setText("",1);
//}

//void setHeading(float deg)
//{
//    motor.setCenterPos(0);
//    float CHeading = compass.getHeading();
//    PID_Controller pid;
//    float error;
//    float correction;
//
//    while (diff(CHeading, deg) < 1) {
//
//        error = diff(CHeading, deg);
//        correction = pid.getCorrection(error);
//        correction *=10;
//
//        motor.setRightSpeed(correction);
//        motor.setLeftSpeed(-correction);
//        motor.commit();
//    }
//}

//void turn(float deg)
//{
//  motor.setCenterPos(0);
//  deg += compass.getHeading();
//  float CHeading = compass.getHeading();
//  PID_Controller pid;
//  float error;
//  float correction;
//
//  while(diff(CHeading, deg)<1) {
//    error = diff(CHeading, deg);
//    correction = pid.getCorrection(error);
//    correction *=10;
//    motor.setRightSpeed(correction);
//    motor.setLeftSpeed(-correction);
//    motor.commit();
//  }
//}

//void goUp(int meters)
//{
//  motor.setCenterPos(90);
//  motor.setSpeed(100);
//  PID_Controller Timer;
//  float accel=0;
//  float laccel=0;
//  float speed=0;
//  float lspeed=0;
//  float time=0;
//  float ltime=0;
//  float distance=0;
//  float displacement=0;
//  motor.commit();
//
//  while(displacement<meters){
//    laccel=accel;
//    accel=spatial.getAcceleration(AXIS_Z) - 1;
//    lspeed=speed;
//    ltime=time;
//    time=Timer.getTime();
//    speed=(accel+laccel)/2*(time-ltime);
//    distance=(speed+lspeed)/2*(time-ltime);
//    displacement += displace(distance,compass.getPitch());
//  }
//}

//void goDown(int meters)
//{
//  motor.setCenterPos(-90);
//  motor.setSpeed(100);
//  PID_Controller Timer;
//  float accel=0;
//  float laccel=0;
//  float speed=0;
//  float lspeed=0;
//  float time=0;
//  float ltime=0;
//  float distance=0;
//  float displacement=0;
//  motor.commit();
//
//  while (displacement < meters) {
//    laccel=accel;
//    accel= (-1) * (spatial.getAcceleration(AXIS_Z) - 1);
//    lspeed=speed;
//    ltime=time;
//    time=Timer.getTime();
//    speed=(accel+laccel)/2*(time-ltime);
//    distance=(speed+lspeed)/2*(time-ltime);
//    displacement += displace(distance, compass.getPitch());
//  }
//}

int move(int len){
  double head = compass.getHeading();
  time_t t = time(0);
  while(time(0)-t < len){
    double newHead=compass.getHeading();
    double corr = pid.getCorrection(head-newHead);
    motor.setLeftSpeed(10-corr);
    motor.setRightSpeed(10+corr);
  }
  return 0;
}
