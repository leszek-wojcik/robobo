#include <Arduino.h>
#include "Robobo.h"
#include "EncoderISR.h"
#include "Arduino_FreeRTOS.h"
#include "task.h"

int led = 13;

int main(void)
{
	init();
	Robobo r;
    r.createSetupV1();
	Serial.begin(r.serialSpeed);

    
    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(200);               // wait for a secon
    digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
    delay(50);                 // wait for a second

    r.dc1->setPosition(100);
    encoder1_ISR();
    delay(5000);              
    Serial.println(r.dc1->getPosition());
    r.dc1->stop();

	vTaskStartScheduler(); // initialise and run the freeRTOS scheduler. Execution should never return here.
	vApplicationMallocFailedHook(); // Probably we've failed trying to initialise heap for the scheduler. Let someone know.
        
	return 0;
}

