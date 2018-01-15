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
    
	for (;;) {
		digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
		delay(200);               // wait for a secon
		digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
		delay(50);                 // wait for a second

		glob->dc1->setPosition(100);
        encoder1_ISR();
		delay(5000);              
		Serial.println(glob->dc1->getPosition());
        glob->dc1->stop();
        break;

		if (serialEventRun) serialEventRun();
	}
        
	return 0;
}

