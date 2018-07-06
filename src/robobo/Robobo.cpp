#include "Robobo.h"
#include "Arduino.h"
#include "DCMotor.h"
#include "EncoderISR.h"
#include "PID.h"
#include "DisplayManager.h"


Robobo::Robobo()
{
    //Serial
    serialSpeed=9600;
    instance = this;
    dc1 = NULL;
    dc2 = NULL;
    pid1 = NULL;
    pid2 = NULL;
    controller = NULL;

}
void Robobo::createSetupV2(void)
{
    const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
    lcd = new LCDisplay(rs, en, d4, d5, d6, d7);
    disp = new DisplayManager("lcd_task\0", tskIDLE_PRIORITY, lcd);
}

void Robobo::createSetupV1(void)
{

    dc1 = new DCMotor(19, 20, 22, 24, 2, "dc1");
    pid1 = new PID(2,0.000001,0,dc1);
    dc1->setControlStrategy(pid1);

	attachInterrupt(digitalPinToInterrupt(19),encoder1_ISR, CHANGE);
	attachInterrupt(digitalPinToInterrupt(20),encoder1_ISR, CHANGE);

    dc2 = new DCMotor(17, 18, 26, 28, 3, "dc2"); 
    pid2 = new PID(2,0.000001,0,dc2);
    dc2->setControlStrategy(pid2);

	attachInterrupt(digitalPinToInterrupt(17),encoder2_ISR, CHANGE);
	attachInterrupt(digitalPinToInterrupt(18),encoder2_ISR, CHANGE);

    controller = new Controller(dc1,dc2);

}

Robobo *Robobo::instance = NULL;
