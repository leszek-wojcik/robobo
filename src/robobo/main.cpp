#include <Arduino.h>
#include "Globals.h"
#include "EncoderISR.h"

int led = 13;

int main(void)
{
	init();
	Globals *glob = Globals::createInstance();
    glob->dc1.setPinModes();
	Serial.begin(glob->serialSpeed);

	pinMode(led, OUTPUT);     
	attachInterrupt(digitalPinToInterrupt(glob->dc1.encoderAPin),encoder1_ISR, CHANGE);
	attachInterrupt(digitalPinToInterrupt(glob->dc1.encoderBPin),encoder1_ISR, CHANGE);
    
	for (;;) {
		digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
		delay(200);               // wait for a secon
		digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
		delay(50);                 // wait for a second

		Serial.println(glob->dc2.encoderPos);
        
        glob->dc1.setDirectionLeft();
        glob->dc1.setVoltage(120);

		delay(5000);               // wait for a secon
        glob->dc1.stop();
        break;

		if (serialEventRun) serialEventRun();
	}
        
	return 0;
}

