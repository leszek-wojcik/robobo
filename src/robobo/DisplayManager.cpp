#include "DisplayManager.h"
#include "Arduino.h"

DisplayManager::DisplayManager(string name, UBaseType_t priority, LCDisplay *lcd):
        ActiveObject( name, priority), myLcd(lcd)
{
    myLcd->begin(16, 2);
    myLcd->print("AO Display Manager");
    couter = 0;

    refreshTimer = createTimer(
            std::function<void()>(std::bind(&DisplayManager::refresh, this)),
            1000,
            1);
    xTimerStart(refreshTimer,0);

}

void DisplayManager::print(string str)
{
    myLcd->print(str.c_str()) ;
}

void DisplayManager::refresh()
{
    Serial.println("refresh");
    myLcd->setCursor(0, 1);
    myLcd->print(couter++);
}
