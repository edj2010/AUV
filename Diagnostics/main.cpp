#include <iostream>
#include <sstream>
#include <cstring>
#include <string>
#include <cstdio>
#include <ctime>
#include <iomanip>

#include <phidget21.h>

#include "Compass.h"
#include "InterfaceKit.h"
#include "LCD.h"
#include "Spatial.h"

int LocalErrorCatcher (int errorCode);

// -------------------- Event Functions ---------------------------------------

int CCONV AttachHandler (CPhidgetHandle device, void *userptr) {

    int serialNumber;
    const char *name;
    
    LocalErrorCatcher(
        CPhidget_getDeviceName(device, &name));
    LocalErrorCatcher(
        CPhidget_getSerialNumber(device, &serialNumber));
    
    printf("Hello Device %s, Serial Number: %d\n", name, serialNumber);
    
    return 0;
}

int CCONV DetachHandler (CPhidgetHandle device, void *userptr) {

    int serialNumber;
    const char *name;
    
    LocalErrorCatcher(
        CPhidget_getDeviceName(device, &name));
    LocalErrorCatcher(
        CPhidget_getSerialNumber(device, &serialNumber));
    
    printf("Goodbye Device %s, Serial Number: %d\n", name, serialNumber);
    
    return 0;
}

// When using an error handler with the manager, it takes a
// CPhidgetManagerHandle, when using an individual object, the
// object serves as its own handle.
int CCONV LibraryErrorHandler (CPhidgetManagerHandle device, void *usrptr, 
                    int errorCode, const char *errorDescription) {
    printf("Error Event: %d - %s\n", errorCode, errorDescription);
    return 0;
}

// This error handler can handle any CPhidget function that returns an int
int LocalErrorCatcher (int errorCode) {
	
	const char *errorDescription;
    
	// If the error code is 0, everything is okay
    if (errorCode != 0) {
    
        // Otherwise, you can print specific messages or perform actions by error value.
        switch (errorCode) {
           default:
               printf("Error: An error occurred with code %d.\n", errorCode);
               
               LocalErrorCatcher(
                   CPhidget_getErrorDescription (errorCode, &errorDescription));
               printf("The description for this error is: %s\n", errorDescription);
               break;
       }
    }
	return 0;
}

// -------------------- Main Code ---------------------------------------------

int main() {
    
    Compass testCompass;
    InterfaceKit ifKit;
    LCD lcd;
    Motor motor;
    Spatial spatial;

    CPhidgetManagerHandle device = 0;
    LocalErrorCatcher(
        CPhidgetManager_create(&device));
    
    LocalErrorCatcher(
        CPhidgetManager_set_OnAttach_Handler((CPhidgetManagerHandle) device, 
                                         AttachHandler, NULL));
    
    LocalErrorCatcher(
        CPhidgetManager_set_OnDetach_Handler((CPhidgetManagerHandle ) device,
                                         DetachHandler, NULL));
    
    LocalErrorCatcher(
        CPhidgetManager_set_OnError_Handler((CPhidgetManagerHandle) device,
                                        LibraryErrorHandler, NULL));
    printf("Starting Phidget Playground...\n");
    // Most opening and closing would be via a cast to
    // (CPhidgetHandle), however, this manager has its
    // own handle struct to cast to.
	
	LocalErrorCatcher(
        CPhidgetManager_open((CPhidgetManagerHandle) device));
    
    std::stringstream ss;
    lcd.clear();
	
    for(int i=0;i<1000;i++){
        testCompass.refresh();
        ss << std::fixed <<  std::setprecision(1) << "Heading: " << testCompass.getHeading();
        lcd.setText(ss.str(), 0);
        ss.str(std::string());
        
        ss << std::fixed << std::setprecision(2) << spatial.getAcceleration(AXIS_X) << " " << spatial.getAcceleration(AXIS_Y) << " " << spatial.getAcceleration(AXIS_Z);
        lcd.setText(ss.str(), 1);
        ss.str(std::string());
        
        usleep(100000);
    }

    printf("Press Enter to end...\n");
    getchar();

    LocalErrorCatcher(
        CPhidgetManager_close((CPhidgetManagerHandle) device));
    LocalErrorCatcher(
        CPhidgetManager_delete((CPhidgetManagerHandle) device));

    return 0;
}
