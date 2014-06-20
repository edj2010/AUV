#ifndef LCD_H
#define LCD_H

#include <string>
#include <sstream>
#include <cstring>

#include <phidget21.h>

class LCD
{
public:
    LCD();
    
    int getBrightness() { return brightness; }
    int getContrast() { return contrast; }
    int getBacklight() { return backlight; }
    std::string getText(int line) { return line==0 ? l0 : l1; }
    void setBrightness(int brightness);
    void setContrast(int contrast);
    void setBacklight(int backlight);
    void setText(std::string text, int line);
    
    void clear();
    
    ~LCD();

private:
    CPhidgetTextLCDHandle txt_lcd;
    int brightness;
    int contrast;
    int backlight;
    std::string l0;
    std::string l1;
};

#endif //LCD_H
