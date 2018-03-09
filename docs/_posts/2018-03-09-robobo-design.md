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


#Robobo case study
Before going into details lets try to do some analysis about requirements we
would have for our application. 

- Design should be prepared to accept variability of execution elements such as
  motors. We would like to have ability to introduce new execution elements by
code addition not by code modification. Examples are: Stepper Motor, hydraulic
or pneumatic actuator.

- Motor abstraction should be flexible enough to change control algorithm
  during runtime. 

- Separate threads are to handle control over each engine. Although most of
  Robobo Motors will be PID driven but we would like to to prioritize control in cases
where stepper Motor will be used or different control mechanisms implemented.

- Robobo design assumes main controller entity which be communicating with all
  motors and would get notification when requested Motor position will be
achieved. Main controller will be responsible for geometry calculation. 

- Robobo design will allow to pull in external communication component in order
  to communicate Main controller with user. This communication could be AWS
cloud or CLI provided by serial USB interface.

- Robobo design should abstract FreeRTOS in such a way that potential movement
  to different OS would be easy. No hard dependencies between Robobo Logic with
OS.

#Active Object

Before going into detailed class design I would like to clarify Active Object
design pattern. In Object Oriented programming special concept of Active Object
exist. Active Object is an object which have important property. That property
is execution context. Whenever calling a method on object it executes on
context of particular task/thread. 

Please refer to my previous article about Real Time Operation System. In
FreeRTOS we are assigning a priority for each task. If you have
two active objects and both of them are different execution context and if you
execute method on both of them then execution order is determined by priority
you selected for tasks (context)

Active Object is an object of a class and you treat it as normal object but
since Active Objects are assigned to particular task they are dynamic from user
perspective.

In order to highlight importance of design note consider our Robobo case. Each
DC motor executes PID algorithm. PID algorithm is actual computation that takes
CPU from other tasks. If I would have each `DCMotor` Active Object property
then I'm getting ability to prioritize PID algorithm execution among multiple
DCMotors.

Following is UML diagram that represents relationship between `DCMotor` and
`ActiveObject` classes. If you are unfamiliar with UML you might ignore this
and refer to code directly.

