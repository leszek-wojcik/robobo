#include <Arduino.h>
#include "Robobo.h"
#include "ISR.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "portmacro.h"
#include "task.h"
#include <tuple>
#include "MethodRequest.h"

void initVariant() __attribute__((weak));
void initVariant() { }


int main(void)
{

	watchdogSetup();
	init();
	delay(1);

#if defined(USBCON)
	USBDevice.attach();
#endif

    pinMode(LED_BUILTIN, OUTPUT);
    
    for(int i=0; i<10; i++)
    {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(1000);
      digitalWrite(LED_BUILTIN, LOW);
      delay(1000);
    }

    Serial.begin(9600);
    Serial.println("Robobo ver ...");

  	Robobo *r = new Robobo();
    r->createSetupV3();

    Serial.println("Robobo start");

    vTaskStartScheduler();
    Serial.println("Insufficient RAM");
    while(1);

}

