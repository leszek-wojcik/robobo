#include <Arduino.h>
#include "Robobo.h"
#include "EncoderISR.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "portmacro.h"
#include "task.h"

void initVariant() __attribute__((weak));
void initVariant() { }

const uint8_t LED_PIN = 13;

SemaphoreHandle_t sem;

static void Thread1(void* arg) {
  while (1) {

    // Wait for signal from thread 2.
    xSemaphoreTake(sem, portMAX_DELAY);

    // Turn LED off.
    digitalWrite(LED_PIN, LOW);
  }
}
//------------------------------------------------------------------------------
/*
 * Thread 2, turn the LED on and signal thread 1 to turn the LED off.
 */
// Declare the thread function for thread 2.
static void Thread2(void* arg) {

  pinMode(LED_PIN, OUTPUT);

  while (1) {
    // Turn LED on.
    digitalWrite(LED_PIN, HIGH);

    // Sleep for 200 milliseconds.
    vTaskDelay((200L * configTICK_RATE_HZ) / 1000L);

    // Signal thread 1 to turn LED off.
    xSemaphoreGive(sem);

    // Sleep for 200 milliseconds.
    vTaskDelay((200L * configTICK_RATE_HZ) / 1000L);
  }
}

int main(void)
{
//	watchdogSetup();
	init();
//	initVariant();

//	delay(1);

//#if defined(USBCON)
//	USBDevice.attach();
//#endif

    pinMode(LED_BUILTIN, OUTPUT);

  portBASE_TYPE s1, s2;

  Serial.begin(9600);
  
  Serial.println("start");

  // initialize semaphore
  sem = xSemaphoreCreateCounting(1, 0);

  // create task at priority two
  s1 = xTaskCreate(Thread1, NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL);

  // create task at priority one
  s2 = xTaskCreate(Thread2, NULL, configMINIMAL_STACK_SIZE, NULL, 1, NULL);

  // check for creation errors
  if (sem== NULL || s1 != pdPASS || s2 != pdPASS ) {
    Serial.println(F("Creation problem"));
    while(1);
  }
  // start scheduler
  vTaskStartScheduler();
  Serial.println("Insufficient RAM");
  while(1);
//  	Robobo r;
//    r.createSetupV1();
//	Serial.begin(r.serialSpeed);


//    r.dc1->setPosition(100);
//    encoder1_ISR();

//    for (int i=0;i<10;i=i++)
//    {

//        Serial.println(r.dc1->getPosition());
//        digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
//        delay(50);                        // wait for a second
//        digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
//        delay(50);    

//    }
        
//    r.dc1->stop();
//	vTaskStartScheduler(); 

//    delay(500);    

//	return 0;
}

