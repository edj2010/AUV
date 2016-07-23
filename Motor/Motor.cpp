#include "Motor.h"

using namespace std;

Motor::Motor(){
  PWM_period = 10000;
  //Assume simple bi-linear model for thrust response to
  // duty cycle... here are calibration parameters for left
  // and right motors...
  LEFT_Zero = 2000;
  RIGHT_Zero = 2000;
  RIGHT_Max = 2500;
  LEFT_Max = 2500;
  RIGHT_Min = 1500;
  LEFT_Min = 1500;
  // arbitrary guess of limit so that we still have enough
  // thrust available to turn
  MAX_UsableThrust = 0.75;

  roboio_SetRBVer(RB_100RD);
  if (!io_init()){
    cout << "Failed to init (remember to use sudo!)" << endl;
    cout << roboio_GetErrMsg() << endl;
  }
  if(!rcservo_Initialize(RCSERVO_USEPINS1|RCSERVO_USEPINS2)){	
    std::cout << "Failed to init servos" << std::endl;
    cout << roboio_GetErrMsg() << endl;
  }
  rcservo_EnterPWMMode();
}

Motor::~Motor(){
  rcservo_Close();
  io_close();
  cout << "Closing down servo controller" << endl;
}

// only use thrust in [-1,1]

unsigned long Motor::leftDuty(float thrust){
  if ( thrust >= 0 ) {
    return ( (unsigned long) LEFT_Zero + thrust * ( LEFT_Max - LEFT_Zero ) );
  }
  if (thrust < 0) {
    return ( (unsigned long) LEFT_Zero + thrust * ( LEFT_Zero - LEFT_Min ) );
  }
}

unsigned long Motor::rightDuty(float thrust){
  if ( thrust >= 0 ) {
    return ( (unsigned long) RIGHT_Zero + thrust * ( RIGHT_Max - RIGHT_Zero ) );
  }
  if (thrust < 0) {
    return ( (unsigned long) RIGHT_Zero + thrust * ( RIGHT_Zero - RIGHT_Min ) );
  }
}



//interval is in seconds
int Motor::Apply_Differential(float thrust, float diff, float interval){
 
  float clippedThrust;

  if (fabs(thrust) <= MAX_UsableThrust){
    clippedThrust = thrust;
  } else {
    clippedThrust = MAX_UsableThrust * thrust/fabs(thrust);    
  }

  float Lt = thrust - (diff/2.0);
  float Rt = thrust - (diff/2.0);
  unsigned long count = (unsigned long) 1000000*interval/PWM_period;
  unsigned long DL = leftDuty(Lt);
  unsigned long DR = rightDuty(Rt);
  rcservo_SendPWMPulses(RCSERVO_PINS1, PWM_period, DL, count);
  rcservo_SendPWMPulses(RCSERVO_PINS2, PWM_period, DR, count);
}

int Motor::readChannel(int chan){
  return rcservo_Inp(chan);
}

void Motor::wait_til_switch(int chan){
  int chanstatus;
  chanstatus = readChannel(chan);
  while (chanstatus == 1){
    usleep(100000);
   // cout << "Still waiting.. found: " << chanstatus << endl;
    chanstatus = readChannel(chan);
  }
}

int Motor::isMotorFinished(){
  return rcservo_IsPWMCompleted(RCSERVO_PINS1);
}

