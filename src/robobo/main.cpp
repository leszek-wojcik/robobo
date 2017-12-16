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
	attachInterrupt(digitalPinToInterrupt(glob->encoder1aPin),encoder1_ISR);
    
	for (;;) {
		digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
		delay(2000);               // wait for a secon
		digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
		delay(50);               // wait for a second
		Serial.write("hello\n\r");
		if (serialEventRun) serialEventRun();
	}
        
	return 0;
}

