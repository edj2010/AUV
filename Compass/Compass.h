#ifndef COMPASS_H
#define COMPASS_H
#define DEPTH_OFFSET 61.3

class Compass
{
public:
    Compass();
    
    void refresh();
    
    float getRoll() { return roll; }
    float getPitch() { return pitch; }
    float getTemp() { return temperature; }
    float getHeading() { return heading; }
    float getDepth() { return (depth - DEPTH_OFFSET); }
    void  debug();
 private:
    int initializeInterface(int speed);
    void readCompass();
    void sendCommand(int length);
    void readUntil(char,int);
    
    float heading;
    float pitch;
    float roll;
    float temperature;
    float depth;
    int fd;
    char buf [100];
};

#endif // COMPASS_H
