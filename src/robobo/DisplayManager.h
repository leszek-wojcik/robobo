#ifndef DISPLAY_MANAGER_INCLUDED
#define DISPLAY_MANAGER_INCLUDED

#include "ActiveObject.h"
#include "LiquidCrystal.h"
#include <string>
#include <map>

// Class is active object with reference to LiquidCrystal. It delegates
// calls to LiquidCrystal object.

class DisplayManager: public ActiveObject
{
    struct DisplayDataRecord
    {
        string header;
        string unit;
        string value;
    };

    private:
        LiquidCrystal *myLcd;
        TimerHandle_t switchTimer;
        int counter;
        std::map<int, DisplayDataRecord>::iterator pos;
        std::map<int, DisplayDataRecord> data;

    public:
        DisplayManager( string name, 
                        UBaseType_t priority, 
                        LiquidCrystal *lcd,
                        int period=1000);
        void switchData();
        void print(string);

        void registerDisplayData( int *handle, 
                    string desc, 
                    string unit="");

        void displayHeader(int handle);
        void displayValue(int handle);

        void postData(int handle, int data);


};

#endif
