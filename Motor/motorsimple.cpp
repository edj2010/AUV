#include <stdio.h>
#include <rb/roboard.h>

int main(void){
	roboio_SetRBVer(101);
	if (io_init()){
		printf("first init success");
	} else {
		printf(roboio_GetErrMsg());
	}
	if (rcservo_Initialize(RCSERVO_USECHANNEL0)){
		printf("Initialized. Channel0\n");
		rcservo_Close();
	} else {
		printf(roboio_GetErrMsg());
	}
	io_close();
	
	return 0;
}
