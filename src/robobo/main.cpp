#include <Arduino.h>
#include "Globals.h"
#include "EncoderISR.h"

int led = 13;

int main(void)
{
	init();
	Globals *glob = Globals::createInstance();

	Serial.begin(glob->serialSpeed);

	pinMode(led, OUTPUT);     
	pinMode(glob->encoder1aPin, INPUT );
	pinMode(glob->encoder1bPin, INPUT );
	attachInterrupt(digitalPinToInterrupt(glob->encoder1aPin),encoder1_ISR, CHANGE);
    
	for (;;) {
		digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
		delay(200);               // wait for a secon
		digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
		delay(50);                 // wait for a second

		Serial.println(glob->encoder1aVal);

		if (serialEventRun) serialEventRun();
	}
        
	return 0;
}

