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
concurrency mechanisms provided by OS layer. In such light active object
concept is concept of requesting others to execute something. 

In order to highlight importance of active object design please consider our
Robobo case. Each `DCMotor` executes PID algorithm. PID algorithm is actual
computation that takes CPU from other tasks. If somebody would like to have
each `DCMotor` object acting as active object then he would get ability to
prioritize PID algorithm execution among multiple `DCMotor` objects.

Following is UML diagram that represents relationship between `DCMotor` and
`ActiveObject` classes. If you are unfamiliar with UML you might ignore this
and refer to code directly.

![Diagram](https://leszek-wojcik.github.io/robobo/images/DCMotor.jpg)

In FreeRTOS active object implementation we need to delegate all concurrency
control to FreeRTOS API. As mentioned above Robobo aims to separate FreeRTOS
from control logic in order to enable future design changes such as OS
replacement. This can be achieved when all FreeRTOS calls will be contained in
single class. ActiveObject implementation aims to cover all dependencies with
OS. Lets summarize:

- Each ActiveObject is associated with FreeRTOS task. During `ActiveObject`
  constructor execution following call is made:
```
    xTaskCreate( ActiveObjectTaskFunction,
            "AO", configMINIMAL_STACK_SIZE + 50 ,mrQueue , tskIDLE_PRIORITY, NULL);
```

- In order to abstract inter process communication each active object will
  contain its own FreeRTOS queue which is created in costructor:
```
    mrQueue = xQueueCreate(...);
```

- When `ActiveObject` client wishes to execute method in context of
  `ActiveObject` task it calls `executeMethod(...)`. Then call is translated to 
  `xQueueSend(mrQueue, &mr, 0);` FreeRTOS call.

- Main `ActiveObject` task routine `ActiveObjectTaskFunction` will just block
  on `mrQueue` and receive functions requests and execute them. 

- Each `ActiveObject` will provide timer creation ability to its child classes.
  ActiveObject delivers implementation of `createTimer` method which then
translates it to FreeRTOS `xTimerCreate` function:

```
    xTimerCreate
        ( "tmr",
          period,
          reload,
          mr,
          ActiveObjectTimerCallback );
```

# Method Request

As I described above in order to facilitate interprocess communication we are
using FreeRTOS queues. Whenever there is a need for calling an active object
method caller in fact will create a message and it will put it on Active Object
`mrQueue` in his own execution context. This happens under the hood of
`executeMethod()` call. 

```C
uint8_t ActiveObject::executeMethod(const std::function<void()> &f )
{
    auto mr = new MRequest(this, f);
    return xQueueSend(mrQueue, &mr, 0);
}
```

Special `MRequest` structure was created in order to pass all necessary information to
active object context to make it able to execute. Please note that
`executeMethod` doesn't block. We can call it asynchronous as we are requesting
`f` to be executed and we are not waiting for completion anyhow. That is
current assumption for Robobo design and might change in future if needed.
`MRequest` or method request is defined as follow:

```C
class MRequest
{
        ...
        ActiveObject *ao;
        std::function<void()> *func;
        bool persistent;
        ...
};
```

Each MRequest includes pointer reference to `ActiveObject`, a function call and
persistence flag. Persistence flag is detail important from heap management
perspective. I will skip explanation of this flag for now. `ActiveObject` pointer
holds pointer to object in which context execution should happen. In reality
this reference is in place in order to satisfy FreeRTOS software timer design.
Once again I will skip explanation for now.  From understanding
perspective key is `function<void()> *func`. This C++11 standard class is used to 
encapsulate function calls in objects. Reference can be found
[here](http://en.cppreference.com/w/cpp/utility/functional/function).

When client creates `MRequest` and put in on `ActiveObject` `mrQueue` then as
part of  receiver context following will happen:

```C
    for (;;) 
    {
        xQueueReceive( queue, &mr, portMAX_DELAY );
        (*(mr->func))();
        ...
    }
```

# Client interface

In order to dispatch method request following call must be executed:

```C
executeMethod(std::function<void()>(bind(&DCMotor::reportMethod,this)),
```
here we take advantage of c++11 `bind`.
[Bind](http://en.cppreference.com/w/cpp/utility/functional/bind) allows us to
create `function<void()>` objects even from methods that actually takes
parameters.  This is flexible mechanism that allows us to call literally every
method even if they require to provide parameter set. 

# Summary 

In this article I started with Robobo design considerations. Then I introduced
you active object concept. I showed you how active object allows us to isolate OS
specific function calls to make our code portable. At the end I showed you
essentials of active object mechanics realized in FreeRTOS. I hope this gives
you entry level knowledge that allows you to read code further in order to
understand remaining active objects implementation. 



