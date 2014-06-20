// - Advanced Servo simple -
// This simple example sets up an Advanced Servo object, hooks the event handlers and opens it for device connections.  
// Once an Advanced Servo is attached it will move the motor to various positions, displaying the event details to the console.
//
// Copyright 2008 Phidgets Inc.  All rights reserved.
// This work is licensed under the Creative Commons Attribution 2.5 Canada License. 
// view a copy of this license, visit http://creativecommons.org/licenses/by/2.5/ca/

#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <phidget21.h>

using std::cout;
using std::cin;
using std::endl;

const int LEFT_MOTOR = 7;
const int CENTER_MOTOR = 4;
const int RIGHT_MOTOR = 3;

int CCONV AttachHandler(CPhidgetHandle ADVSERVO, void *userptr)
{
	int serialNo;
	const char *name;

	CPhidget_getDeviceName (ADVSERVO, &name);
	CPhidget_getSerialNumber(ADVSERVO, &serialNo);
	printf("%s %10d attached!\n", name, serialNo);

	return 0;
}

int CCONV DetachHandler(CPhidgetHandle ADVSERVO, void *userptr)
{
	int serialNo;
	const char *name;

	CPhidget_getDeviceName (ADVSERVO, &name);
	CPhidget_getSerialNumber(ADVSERVO, &serialNo);
	printf("%s %10d detached!\n", name, serialNo);

	return 0;
}

int CCONV ErrorHandler(CPhidgetHandle ADVSERVO, void *userptr, int ErrorCode, const char *Description)
{
	printf("Error handled. %d - %s\n", ErrorCode, Description);
	return 0;
}

//Display the properties of the attached phidget to the screen.  We will be displaying the name, serial number and version of the attached device.
int display_properties(CPhidgetAdvancedServoHandle phid)
{
	int serialNo, version, numMotors;
	const char* ptr;

	CPhidget_getDeviceType((CPhidgetHandle)phid, &ptr);
	CPhidget_getSerialNumber((CPhidgetHandle)phid, &serialNo);
	CPhidget_getDeviceVersion((CPhidgetHandle)phid, &version);

	CPhidgetAdvancedServo_getMotorCount (phid, &numMotors);

	printf("%s\n", ptr);
	printf("Serial Number: %10d\nVersion: %8d\n# Motors: %d\n", serialNo, version, numMotors);

	return 0;
}

int servo_simple()
{
	int result;

	const char *err;
	double minAccel, maxVel;

	//Declare an advanced servo handle
	CPhidgetAdvancedServoHandle servo = 0;

	//create the advanced servo object
	CPhidgetAdvancedServo_create(&servo);

	//Set the handlers to be run when the device is plugged in or opened from software, unplugged or closed from software, or generates an error.
	CPhidget_set_OnAttach_Handler((CPhidgetHandle)servo, AttachHandler, NULL);
	CPhidget_set_OnDetach_Handler((CPhidgetHandle)servo, DetachHandler, NULL);
	CPhidget_set_OnError_Handler((CPhidgetHandle)servo, ErrorHandler, NULL);
    
	//open the device for connections
	CPhidget_open((CPhidgetHandle)servo, -1);

	//get the program to wait for an advanced servo device to be attached
	printf("Waiting for Phidget to be attached....");
	if((result = CPhidget_waitForAttachment((CPhidgetHandle)servo, 10000)))
	{
		CPhidget_getErrorDescription(result, &err);
		printf("Problem waiting for attachment: %s\n", err);
		return 0;
	}

	//Display the properties of the attached device
	display_properties(servo);

	//read event data
	printf("Reading.....\n");

	//Set up some initial acceleration and velocity values    
    CPhidgetAdvancedServo_setPosition (servo, LEFT_MOTOR, 90.00);
	CPhidgetAdvancedServo_getAccelerationMin(servo, LEFT_MOTOR, &minAccel);
	CPhidgetAdvancedServo_setAcceleration(servo, LEFT_MOTOR, minAccel*2);
	CPhidgetAdvancedServo_getVelocityMax(servo, LEFT_MOTOR, &maxVel);
	CPhidgetAdvancedServo_setVelocityLimit(servo, LEFT_MOTOR, maxVel/2);
    CPhidgetAdvancedServo_setEngaged(servo, LEFT_MOTOR, 1);
    
    CPhidgetAdvancedServo_setPosition (servo, CENTER_MOTOR, 120.00);
	CPhidgetAdvancedServo_getAccelerationMin(servo, CENTER_MOTOR, &minAccel);
	CPhidgetAdvancedServo_setAcceleration(servo, CENTER_MOTOR, minAccel*2);
	CPhidgetAdvancedServo_getVelocityMax(servo, CENTER_MOTOR, &maxVel);
	CPhidgetAdvancedServo_setVelocityLimit(servo, CENTER_MOTOR, maxVel/2);
    CPhidgetAdvancedServo_setEngaged(servo, CENTER_MOTOR, 0);
    
    CPhidgetAdvancedServo_setPosition (servo, RIGHT_MOTOR, 110.00);
    CPhidgetAdvancedServo_getAccelerationMin(servo, RIGHT_MOTOR, &minAccel);
	CPhidgetAdvancedServo_setAcceleration(servo, RIGHT_MOTOR, minAccel*2);
	CPhidgetAdvancedServo_getVelocityMax(servo, RIGHT_MOTOR, &maxVel);
	CPhidgetAdvancedServo_setVelocityLimit(servo, RIGHT_MOTOR, maxVel/2);
    CPhidgetAdvancedServo_setEngaged(servo, RIGHT_MOTOR, 1);

//    CPhidgetAdvancedServo_setPosition (servo, CENTER_MOTOR, 140.00);
//    cin.ignore();
//    CPhidgetAdvancedServo_setPosition (servo, CENTER_MOTOR, 120.00);
//    cin.ignore();
//    CPhidgetAdvancedServo_setPosition (servo, CENTER_MOTOR, 110.00);
//    cin.ignore();
//    CPhidgetAdvancedServo_setPosition (servo, CENTER_MOTOR, 120.00);
    
	//change the motor position
	//valid range is -23 to 232, but for most motors ~30-210
	//we'll set it to a few random positions to move it around
    
    
    
//    char input;
//    
//    while (true) {
//        cout << "Choose a Command:" << endl;
//        cout << "1. Spin both side motors" << endl;
//        cout << "2. Spin port motor" << endl;
//        cout << "3. Spin starboard motor" << endl;
//        cout << "4. Pitch motors downwards" << endl;
//        cout << "5. Pitch motors upward" << endl;
//        cout << "6. Quit program" << endl;
//        cout << "Enter a number between 1-6: ";
//        
//        input = cin.get();
//        
//        switch (input) {
//                
//            case '1':
//                CPhidgetAdvancedServo_setPosition (servo, LEFT_MOTOR, 150.00);
//                CPhidgetAdvancedServo_setPosition (servo, RIGHT_MOTOR, 150.00);
//                cout << "Press ENTER to stop...";
//                cin.ignore();
//                cin.get();
//                CPhidgetAdvancedServo_setPosition (servo, LEFT_MOTOR, 120.00);
//                CPhidgetAdvancedServo_setPosition (servo, RIGHT_MOTOR, 120.00);
//                break;
//                
//            case '2':
//                CPhidgetAdvancedServo_setPosition (servo, LEFT_MOTOR, 150.00);
//                cout << "Press ENTER to stop...";
//                cin.ignore();
//                cin.get();
//                CPhidgetAdvancedServo_setPosition (servo, LEFT_MOTOR, 120.00);
//                break;
//                
//            case '3':
//                CPhidgetAdvancedServo_setPosition (servo, RIGHT_MOTOR, 150.00);
//                cout << "Press ENTER to stop...";
//                cin.ignore();
//                cin.get();
//                CPhidgetAdvancedServo_setPosition (servo, RIGHT_MOTOR, 120.00);
//                break;
//                
//            case '4':
//                CPhidgetAdvancedServo_setPosition (servo, CENTER_MOTOR, 122.00);
//                cout << "Press ENTER to stop...";
//                cout << input;
//                cin.get();
//                CPhidgetAdvancedServo_setPosition (servo, CENTER_MOTOR, 120.00);
//                break;
//                
//            case '5':
//                CPhidgetAdvancedServo_setPosition (servo, CENTER_MOTOR, 118.00);
//                cout << "Press ENTER to stop...";
//                cin.ignore();
//                cin.get();
//                CPhidgetAdvancedServo_setPosition (servo, CENTER_MOTOR, 120.00);
//                break;
//                
//            case '6':
//                break;
//        }
//    }

    CPhidgetAdvancedServo_setEngaged(servo, LEFT_MOTOR, 0);
    CPhidgetAdvancedServo_setEngaged(servo, CENTER_MOTOR, 0);
    CPhidgetAdvancedServo_setEngaged(servo, RIGHT_MOTOR, 0);

	//since user input has been read, this is a signal to terminate the program so we will close the phidget and delete the object we created
	printf("Closing...\n");
    
	CPhidget_close((CPhidgetHandle)servo);
	CPhidget_delete((CPhidgetHandle)servo);

	//all done, exit
	return 0;
}

int main(int argc, char* argv[])
{
	servo_simple();
	return 0;
}

