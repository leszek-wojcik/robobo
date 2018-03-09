---
layout: post
title:  "Robobo Software Design"
date:   2018-03-09 13:40:00 +0100
excerpt: "Article presents implementation of Active Object design pattern for
FreeRTOS based application"
categories: C++, FreeRTOS, ActiveObject
---
In history of programming we can see definitive trend where procedural
programming languages give way to object oriented. Object oriented approach
increases code reuse and by this speeds up development.  Even for low level
embedded programming such as Arduino objective approach is standard. This
article describes Robobo abstraction for FreeRTOS interface.


# Robobo case study
Before going into details lets try to do some analysis about requirements and
motivations we would have for our application. 

- Robobo design should be prepared to accept variability of executive elements. 
  We would like to have ability to introduce new executive elements by
code addition not by code modification. Examples of elements are: Stepper
Motor, hydraulic or pneumatic actuator. Even if these elements will not be part
of project we want our software ready to accommodate them just in case. 

- Motor abstraction should be flexible enough to change control algorithm
  during runtime. For instance if we would like to change PID algorithm
parameters or even exchange PID with other algorithm Robobo design should allow
to do that. For control algorithm introduction please refer to my [servo post](
https://leszek-wojcik.github.io/robobo/arduino/servo/encoder/pololu/hbridge/pid/2017/12/29/servo.html).

- Separate threads are to handle control over each motor. Although most of
  Robobo Motors will be PID driven we would like still have ability to
prioritize control. PID itself does not require complex computation but having
each servo calculated independently provides much more flexibility compared to
single thread approach.

- Robobo design assumes existence of main controller entity. This entity is
  responsible for communication with all motors. Main controller would run on
thread with lower priority than servo controllers. It woudl receive
notification when requested Motor position will be achieved. Main controller
will be responsible for geometry calculation. 

- Robobo design will allow to read external communication from an user. 
  This communication could be AWS cloud or CLI provided by serial USB interface.

- Robobo design should abstract FreeRTOS in such a way that potential movement
  to different OS would be easy. No hard dependencies between Robobo Logic with
OS.

# Active Object

Before going into detailed class design I would like to clarify active object
design pattern. In Object Oriented programming special concept of active object
was created. Active object is an object which has important property added on
top of regular object. This property is execution context. Whenever calling a
method on Active Object it executes on context of particular task/thread. 

Please refer to my previous article about [Real Time Operation
System](https://leszek-wojcik.github.io/robobo/rtos/2018/01/21/rtos.html). In
FreeRTOS we are assigning a priority for each task. Consider a case where you
have two Active objects and these two objects are assigned to two different
FreeRTOS tasks. Suppose you execute method on both of them
then execution order is determined by priority you selected for tasks.

Active object is like any other object. You treat it as normal object but
since active objects are assigned to particular task they are dynamic from user
perspective. Once method call is invoked then its execution can happen using
concurrency mechanisms provided by OS layer;

In order to highlight importance of active object design please consider our
Robobo case. Each `DCMotor` executes PID algorithm. PID algorithm is actual
computation that takes CPU from other tasks. If somebody would like to have
each `DCMotor` object acting as active object then he would get ability to
prioritize PID algorithm execution among multiple `DCMotor` objects.

Following is UML diagram that represents relationship between `DCMotor` and
`ActiveObject` classes. If you are unfamiliar with UML you might ignore this
and refer to code directly.

