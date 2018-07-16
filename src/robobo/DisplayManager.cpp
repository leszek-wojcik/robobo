#include "DisplayManager.h"
#include "Arduino.h"
#include "task.h"
#include <string>

DisplayManager::DisplayManager(string name, UBaseType_t priority, LiquidCrystal *lcd, int period):
        ActiveObject(name, priority), myLcd(lcd)
{
    myLcd->begin(16, 2);
    myLcd->print(ROBOBO_VERSION_STRING);
    counter = 0;

    switchTimer = createTimer(
            std::function<void()>(std::bind(&DisplayManager::switchData, this)),
            period);
    
    pos = data.begin();

}

void DisplayManager::print(string str)
{
    myLcd->print(str.c_str()) ;
}

void DisplayManager::switchData()
{
    if (data.size() != 0)
    {
        
        taskENTER_CRITICAL();
        myLcd->clear();
        myLcd->setCursor(0, 0);
        print(pos->second.header);
        myLcd->setCursor(0, 1);
        print(pos->second.value);
        taskEXIT_CRITICAL();

        Serial.println(pos->second.header.c_str());
        Serial.println(pos->second.value.c_str());

        pos++;

        if (pos == data.end())
        {
            pos = data.begin();
        }

    }

}

void DisplayManager::registerDisplayData( 
        int *handle, 
        string desc,
        string unit)
{
    counter++;
    *handle = counter;
    data[counter].header = desc;
    data[counter].unit = unit;

    // after element additon we start from begining
    pos = data.begin();
}

void DisplayManager::displayHeader(int handle)
{
    myLcd->setCursor(0, 0);
    myLcd->print (data[handle].header.c_str() );
}

void DisplayManager::postData(int handle, int dataToPost)
{
    // crapy code - reason is lack of to_string in std for arm gcc
    char str[17];
    sprintf(str,"%d", dataToPost);
    data[handle].value = string(str);
}

void DisplayManager::displayValue(int handle)
{
    myLcd->setCursor(1, 0);
    myLcd->print (data[handle].value.c_str() );
}
