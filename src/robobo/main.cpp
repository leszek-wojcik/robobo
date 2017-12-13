#include <Arduino.h>

int led = 13;

void setup() {                
  pinMode(led, OUTPUT);     
}

int main(void)
{
	init();
	setup();
    
	for (;;) {
		digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
		delay(2000);               // wait for a secon
		digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
		delay(50);               // wait for a second

		if (serialEventRun) serialEventRun();
	}
        
	return 0;
}

