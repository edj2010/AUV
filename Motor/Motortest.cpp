#include <rb/roboard.h>
#include <iostream>
#include <unistd.h>
int main(){
	roboio_SetRBVer(RB_100RD);
	std::cout << "start" << std::endl;
	if (io_init()){
		std::cout << "init" << std::endl;
		std::cout << roboio_GetErrMsg() << std::endl;
		if(rcservo_Initialize(RCSERVO_USEPINS1)){
			std::cout << "channel" << std::endl;
			rcservo_EnterPWMMode();
			std::cout << "Entered PWM Mode" << std::endl;
			unsigned long PWM_period = 10000;
			std::cout << "period: ";
			std::cin >> PWM_period;
			unsigned long PWM_duty = 0;
			unsigned long count = 1000;
			std::cout << "count: ";
			std::cin >> count;
			while (PWM_period > 0){
				std::cout << "duty: ";
				std::cin >> PWM_duty;
				rcservo_SendPWMPulses(RCSERVO_PINS1, PWM_period, PWM_duty, count);
				std::cout << "Sent some PWM Pulses - duty: " << ((float)PWM_duty)/PWM_period << std::endl;
				while (!rcservo_IsPWMCompleted(RCSERVO_PINS1)){
					usleep(1000);
				}
			}
			rcservo_Close();
		}
		io_close();
	}
	std::cout << roboio_GetErrMsg() << std::endl;
	std::cout << RCSERVO_USECHANNEL1 << std::endl;
	err_CloseLogFile();
}
