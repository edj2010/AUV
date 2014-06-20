#ifndef INTERFACEKIT_H
#define INTERFACEKIT_H

#include <phidget21.h>

class InterfaceKit
{
public:
    InterfaceKit();
    
    int inputChangeHandler(int index, int state);
    void printProperties(); //to be implemented later
    CPhidgetInterfaceKitHandle getHandle() { return ifKit; }
    
    //Hall effect sensor
    void refreshCounter() { count=0; }
    int getCount() { return count; }
    bool isRunning() { return running; }
    
    //Depth sensor
    void refresh();
    double getPressure();
    double getDepth() { return depth; }
    
    ~InterfaceKit();
    
private:
    CPhidgetInterfaceKitHandle ifKit;
    

    bool running;
    int count;
    double pressure_psi;
    double depth;
        
    double calculateDepth(int sensor1, int sensor2);
};

#endif // INTERFACEKIT_H
