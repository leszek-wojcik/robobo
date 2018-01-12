---
layout: post
title:  "Hello World Robobo"
date:   2018-01-12 21:19:00 +0100
excerpt: "Article describes Unit Test approach for embedded projects using
Arduino Robobo project as example"
categories: C C++ Unit Tests Google Test Google Mock
---

Robobo project is an example of embedded project where unit tests are executed
on development computer instead of Arduino target. Such approach is convenient
for developer since there is not need to load software to target bards and unit
tests results are provided immediately after execution. There is no need to load
a software to Arduino target in order to verify that new functionality works
and does not brake existing one. 

# Unit tests
Arduino code (lets call it production code) is different than unit test code.
Purpose of unit tests is to ease developer. Major function of unit tests
is just to execute series of function calls and validate whether their output is
aligned with developer intention. Code base that is used to compile unit test
is common with production code because in the end it is production code we want
to test.

Unit tests application is like as any other. It differers from purpose
perspective but from high level it is still compiled C/C++ code. In embedded
development we deal with additional complexity factor which is unit
tests are run on developer machine (Intel or AMD x86) while production code is
run on target (in our case Arduino). On development machine we have
advanced OS like Linux or Windows while on target Arduino we usually have no OS
at all. 

# PC and Arduino differences
Lets try to summarize what is different on these two platforms and how we
should protect ourselves between these differences. 

## Built in types 
Almost all C/C++ books refers to platforms specific details on data types. C/C++
doesn't guarantee sizes of basic data types. For instance if we deal with `int`
type on a PC you will probably have 4 bytes representation if integral value.
On Arduino you will have only 2 bytes for integral representations. What does
this mean for you? Answer is quite simple.  Maximum and minimum value for integral
representations are 2147483647 and -2147483648 on PC and 32767 and -32768 on Arduino. 

In most cases you might ignore this fact but if you are crossing boundaries you
might expect functional differences when running unit tests and target code.
Below are two different code snippet that you can use to determine sizes of
data types.

### PC.

```C
int main(int argc,char *argv[])
{
    cout<<"sizeof(int):    "<<sizeof(int)<<endl;
    cout<<"sizeof(short):  "<<sizeof(short)<<endl;
    cout<<"sizeof(long):   "<<sizeof(long)<<endl;
    cout<<"sizeof(float):  "<<sizeof(float)<<endl;
    cout<<"sizeof(double): "<<sizeof(double)<<endl;
}
```

output:
```
sizeof(int):    4
sizeof(short):  2
sizeof(long):   8
sizeof(float):  4
sizeof(double): 8
```

### Arduino Mega



