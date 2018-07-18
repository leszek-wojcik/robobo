#include "Robobo.h"
#include "Arduino.h"
#include "DCMotor.h"
#include "ISR.h"
#include "PID.h"
#include "DisplayManager.h"
#include "PlatformManager.h"


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

void Robobo::createSetupV3(void)
{
    dc1 = new DCMotor(22, 23, 24, 25, 8, "dc1");
    pid1 = new PID("pid_task\0", tskIDLE_PRIORITY, 0.1,0.0000001,0,dc1);
    dc1->setControlStrategy(pid1);

    // Attaching interrupts for DC1
	attachInterrupt(digitalPinToInterrupt(22),encoder1_ISR, CHANGE);
	attachInterrupt(digitalPinToInterrupt(23),encoder1_ISR, CHANGE);
    attachInterrupt(digitalPinToInterrupt(26),limitSwitchDc1_ISR, RISING);  

    dc1->setPosition(10000);

}


void Robobo::createSetupV2(void)
{
    const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
    lcd = new LiquidCrystal(rs, en, d4, d5, d6, d7);
    disp = new DisplayManager("lcd_task\0", tskIDLE_PRIORITY, lcd, 3000);
    pm = new PlatformManager("plm_task\0", tskIDLE_PRIORITY, disp);

    dc1 = new DCMotor(22, 23, 24, 25, 8, "dc1");
    pid1 = new PID("pid_task\0", tskIDLE_PRIORITY, 0.1,0.0000001,0,dc1);
    dc1->setControlStrategy(pid1);

	attachInterrupt(digitalPinToInterrupt(22),encoder1_ISR, CHANGE);
	attachInterrupt(digitalPinToInterrupt(23),encoder1_ISR, CHANGE);

    controller = new Controller(dc1,dc1,disp);

    dc1->setPosition(10000);

}

void Robobo::createSetupV1(void)
{

    dc1 = new DCMotor(19, 20, 22, 24, 2, "dc1");
    pid1 = new PID("pid_task\0", tskIDLE_PRIORITY,2,0.000001,0,dc1);
    dc1->setControlStrategy(pid1);

	attachInterrupt(digitalPinToInterrupt(19),encoder1_ISR, CHANGE);
	attachInterrupt(digitalPinToInterrupt(20),encoder1_ISR, CHANGE);

    dc2 = new DCMotor(17, 18, 26, 28, 3, "dc2"); 
    pid2 = new PID("pid_task\0", tskIDLE_PRIORITY,2,0.000001,0,dc2);
    dc2->setControlStrategy(pid2);

	attachInterrupt(digitalPinToInterrupt(17),encoder2_ISR, CHANGE);
	attachInterrupt(digitalPinToInterrupt(18),encoder2_ISR, CHANGE);

    controller = new Controller(dc1,dc2,NULL);

}

Robobo *Robobo::instance = NULL;
