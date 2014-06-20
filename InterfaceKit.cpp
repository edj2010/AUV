#include <iostream>

#include <phidget21.h>

#include "InterfaceKit.h"

using namespace std;

const int MISSION_GO_INDEX = 0;
const int HALL_EFFECT_INDEX = 1;
const int PRESSURE_SENSOR_INDEX[2] = {2, 3};

namespace Handler
{
    int CCONV inputChangeHandler(CPhidgetInterfaceKitHandle IFK, void *usrptr, int index, int state)
    {
        cout << "Input Change Detected. Index: " << index << ". State: " << state << "." << endl;
        
        ((InterfaceKit *) usrptr)->inputChangeHandler(index, state);
        
        return 0;
    }
}

InterfaceKit::InterfaceKit()
{
    CPhidgetInterfaceKit_create(&ifKit);
    CPhidget_open((CPhidgetHandle)ifKit, -1);
    
    running = false;
    
    if(CPhidget_waitForAttachment((CPhidgetHandle)ifKit, 1000)) {
        std::cout << "Error attaching Phidget Interface Kit." << std::endl;
    }
    
    CPhidgetInterfaceKit_set_OnInputChange_Handler(ifKit, Handler::inputChangeHandler, this);
    
    int c;
    CPhidgetInterfaceKit_getOutputState(ifKit, MISSION_GO_INDEX, &c);
    cout << "IFKit connected. Mission run index: " << c << endl;
}

int InterfaceKit::inputChangeHandler(int index, int state)
{
    if ((index == HALL_EFFECT_INDEX) && (state == 1)) {
        count++;
    }
    
    if ((index == MISSION_GO_INDEX) && (state == 1)) {
        running = true;
    }
    
    if ((index == MISSION_GO_INDEX) && (state == 0)) {
        running = false;
    }
    
    return 0;
}

void InterfaceKit::printProperties()
{
    //to be implemented
}

void InterfaceKit::refresh()
{
    int sensor1, sensor2;
    
    CPhidgetInterfaceKit_getSensorValue(ifKit, PRESSURE_SENSOR_INDEX[0], &sensor1);
    CPhidgetInterfaceKit_getSensorValue(ifKit, PRESSURE_SENSOR_INDEX[1], &sensor2);
    
    depth = calculateDepth(sensor1, sensor2);
}

double InterfaceKit::calculateDepth(int sensor1, int sensor2)
{
    return 0;
}

InterfaceKit::~InterfaceKit() {
    
    CPhidget_close((CPhidgetHandle)ifKit);
    CPhidget_delete((CPhidgetHandle)ifKit);
}
