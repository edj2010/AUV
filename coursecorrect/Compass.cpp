#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <string>
#include <cstring>

#include "Compass.h"

Compass::Compass(){
    std::string portname = "/dev/ttyUSB0";
    
    buf[0]='*';
    buf[1]='1';
    buf[2]='\r';
    buf[3]='\0';
    strcpy(buf,"*1\r");
    fd = open (portname.c_str(), O_RDWR | O_NOCTTY | O_SYNC);
    if (fd < 0) {
        printf ("Error attaching OceanServer Compass on %s.\n", portname.c_str());
    }
    initializeInterface(B19200);
    sendCommand(3);
}

void Compass::refresh(){
    readCompass();
}

int Compass::initializeInterface(int speed)
{
    struct termios tty;
    memset (&tty, 0, sizeof tty);
    if (tcgetattr (fd, &tty) != 0)
    {
        printf ("Error %d from tcgetattr.\n", errno);
        return -1;
    }
    
    cfsetspeed (&tty, speed); // set the BAUD Rate
    
	cfmakeraw(&tty);          // simplest version IO
    tty.c_cflag = (tty.c_cflag | CS8);// 8-bit chars
	tty.c_cflag &= ~CSTOPB;           // One Stop Bit
    tty.c_cflag &= ~CRTSCTS;          // No Hardware Flow Control
    
    tty.c_cc[VMIN]  = 0;            // read doesn't block
    tty.c_cc[VTIME] = 10;            // 0.5 seconds read timeout
    
    
    if (tcsetattr (fd, TCSANOW, &tty) != 0)
    {
        printf ("Error %d from tcsetattr.\n", errno);
        return -1;
    }
    
    return 0;
}

void Compass::readUntil(char s,int offset){
    char c=0;
    int count = 0;
    while (c!=s){
        read (fd, &c, 1);
        buf[count++]=c;
    }
    for (int i=0; i<offset; ++i){
        read (fd, &c, 1);
        buf[count++]=c;
    }
    buf[count]=0;
}


void Compass::sendCommand(int length){
    char c = 27;
    write(fd,&c,1);
    usleep(30000);
    for(int i=0; i<length; ++i){
        write(fd,(char *) (buf+i*sizeof(char)),1);
        usleep(30000);
    }
    tcflush(fd,TCIOFLUSH);
}

void Compass::readCompass(){
  // The serial data buffer can get filled up with previous readings,
  // but when we go to read the compass we really want the most recent
  // reading, so flush the buffer and then start reading  This may add 
  // some lag inresonse while we wait for the new reading to come in.
  tcflush(fd,TCIOFLUSH);
  
  //read to start of compass sentence
  readUntil('$',0);
  // read to the end of the compass sentence, and then two more chars
  readUntil('*',2);
  // parse our read buffer
  sscanf(buf,"C%fP%fR%fT%fD%f*", &heading, &pitch, &roll, &temperature, &depth); 
 //"C%.1fP%.1fR%.1fT%.1f*
}

void Compass::debug(){
  printf("|%s|\n",buf);
}

float Compass::angleDif(float a, float b){
  float c;
  c = a - b;
  if (c > 180.0){c -= 360.0;}
  if (c <= -180.0){c += 360.0;}
  return (c);

}
