#include <Arduino.h>
#include "Robobo.h"
#include "EncoderISR.h"
//#include "Arduino_FreeRTOS.h"
//#include "task.h"

void initVariant() __attribute__((weak));
void initVariant() { }


int main(void)
{
	watchdogSetup();
	init();
	initVariant();

	delay(1);

#if defined(USBCON)
	USBDevice.attach();
#endif

    pinMode(LED_BUILTIN, OUTPUT);

  	Robobo r;
    r.createSetupV1();
//	Serial.begin(r.serialSpeed);

    

//    r.dc1->setPosition(100);
//    encoder1_ISR();
//    delay(5000);              
//    Serial.println(r.dc1->getPosition());
//    r.dc1->stop();
//
//	vTaskStartScheduler(); // initialise and run the freeRTOS scheduler. Execution should never return here.
//	vApplicationMallocFailedHook(); // Probably we've failed trying to initialise heap for the scheduler. Let someone know.

    for (;;)
    {
        digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
        delay(3000);                        // wait for a second
        digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
        delay(100);    

		if (serialEventRun) serialEventRun();
    }
        
	return 0;
}

