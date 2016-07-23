#include <iostream>
#include <string>
#include <sstream>
#include <cstring>

#include <phidget21.h>

#include "LCD.h"

LCD::LCD()
{
    txt_lcd = 0;
    brightness = 255;
    contrast = 110;
    backlight = 1;
    
    CPhidgetTextLCD_create(&txt_lcd);
    CPhidget_open((CPhidgetHandle)txt_lcd, -1); //PLEASE COMMENT THIS
    if(CPhidget_waitForAttachment((CPhidgetHandle)txt_lcd, 1000)) {
        std::cout << "Error attaching Phidget Text LCD." << std::endl;
    }
    
    CPhidgetTextLCD_setBacklight(txt_lcd, backlight);
    CPhidgetTextLCD_setContrast(txt_lcd, contrast);
    CPhidgetTextLCD_setBrightness(txt_lcd, brightness);
}

void LCD::setBrightness(int brightness)
{
    this->brightness = brightness;
    CPhidgetTextLCD_setBrightness(txt_lcd, brightness);
}

void LCD::setContrast(int contrast)
{
    this->contrast = contrast;
    CPhidgetTextLCD_setContrast(txt_lcd, contrast);
}

void LCD::setBacklight(int backlight)
{
    this->backlight = backlight;
    CPhidgetTextLCD_setBacklight(txt_lcd, backlight);
}

void LCD::setText(std::string text, int line)
{
    (line==0 ? l0 : l1) = text;
    std::stringstream strText;
    strText << text;
    char* charText = strdup(strText.str().c_str());
    CPhidgetTextLCD_setDisplayString (txt_lcd, line, charText);
}

void LCD::clear()
{
    setText("", 0);
    setText("", 1);
}

LCD::~LCD() {
    setBacklight(0);
    setText("",0);
    setText("",1);
    CPhidget_close((CPhidgetHandle)txt_lcd);
    CPhidget_delete((CPhidgetHandle)txt_lcd);
}