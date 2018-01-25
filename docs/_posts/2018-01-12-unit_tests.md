---
layout: post
title:  "Unit Tests for Embedded Applications"
date:   2018-01-12 21:19:00 +0100
excerpt: "Article describes Unit Test approach for embedded projects using
Arduino Robobo project as example"
categories: C C++ Unit Tests Endianness Data types Arduino 
---

Robobo project is an example of embedded project where unit tests are executed
on development computer instead of Arduino target. Such approach is convenient
for developer since he doesn't need to load software to target board in order
to validate results of tests. Test feedback is delivered straight from unit
test execution on developer machine. This is big benefit for medium and large
scale projects as it speeds up development process. There are several pitfalls
which you should be aware of before starting such approach in your project.

# Unit tests
Arduino code (lets call it production code) is different than unit test code.
Purpose of unit tests is to ease developer. Major function of unit tests
is just to execute series of functions calls and validate whether their output is
aligned with requirements. Code base that is used to compile unit test
is common with production code. In the end it is a production code we want
to test.

Unit tests application is like as any other. It differers from purpose
perspective but from high level it is still compiled C/C++ code. In embedded
development we deal with additional complexity factor which is fact that same
code runs on developer machine (unit tests on Intel or AMD x86) and same code
is runs on target (in our case Arduino). There are many differences between
these two targets. For instance on development machine we have advanced OS like
Linux or Windows while on target Arduino we usually have no OS at all. 

# PC and Arduino differences
Lets try to summarize what differcies are most important when running unit
tests on development machine. Also lets learn how to write a code that wont be
causing us a problems during development. 

# Built in types on Arduino
Almost all books about C/C++ refers to platforms specific details when
describing various data types. C/C++ doesn't guarantee sizes of basic data
types. For instance if we deal with `int` type on a PC you will probably have 4
bytes representation in integral value.  On Arduino you will have only 2 bytes
for integral representations. What does this mean for you? Answer is quite
simple.  Maximum and minimum value for integral representations are
`2147483647` and `-2147483648` on PC and `32767` and `-32768` on Arduino. 

In most cases you might ignore this fact but if you are crossing boundaries you
might expect functional differences when running unit tests and target code.
Below are two different code snippet that you can use to determine sizes of
data types.

PC:

```c
int main(int argc,char *argv[])
{
    cout<<"sizeof(int):    "<<sizeof(int)<<endl;
    cout<<"sizeof(short):  "<<sizeof(short)<<endl;
    cout<<"sizeof(long):   "<<sizeof(long)<<endl;
    cout<<"sizeof(float):  "<<sizeof(float)<<endl;
    cout<<"sizeof(double): "<<sizeof(double)<<endl;
}
```

Arduino:

```c
void loop()
{
  Serial.print("sizeof(int):    "); 
  Serial.println(sizeof(int));
  
  Serial.print("sizeof(short):  ");
  Serial.println(sizeof(short));
  
  Serial.print("sizeof(long):   ");
  Serial.println(sizeof(long));
  
  Serial.print("sizeof(float):  ");
  Serial.println(sizeof(float));
  
  Serial.print("sizeof(double): ");
  Serial.println(sizeof(double));
  
  delay (1000);
}
```

# Arduino Mega Builtin data type sizes

Below table represents result from program executions on both platforms.

|PC output            |   Arduino MEGA        |  Arduino Due         |            
|---------------------|-----------------------|----------------------|          
|`sizeof(int):    4`  |  `sizeof(int):    2`  |  `sizeof(int):    4` |                              
|`sizeof(short):  2`  |  `sizeof(short):  2`  |  `sizeof(short):  2` |                              
|`sizeof(long):   8`  |  `sizeof(long):   4`  |  `sizeof(long):   4` |                              
|`sizeof(float):  4`  |  `sizeof(float):  4`  |  `sizeof(float):  4` |                              
|`sizeof(double): 8`  |  `sizeof(double): 4`  |  `sizeof(double): 8` |                               


As you can see Arduino types differ from PC. Since Arduino Mega uses 8bit
controller builtin data types are smaller than on PC.

# Best practices for embedded development

In order to avoid potential problems with data types you should use dedicated
set of typedefs. Its sizes are platform independent. This is convenient method
of variable declarations. Modern standard libraries provides you set of
typedefs that you can use without worry about size. These are examples:

```c
int8_t   // integral 8 bits signed
int16_t  // integral 16 bits signed
uint8_t  // integral 8 bits unsigned
```
When you are using them you might be assured that when you compile your code on
different target sizes will remain same. 

## Endianess
Another important aspect of running unit tests on PC when dealing with embedded
development is [endianees](https://en.wikipedia.org/wiki/Endianness). For our
Arduino case study we are lucky that both Intel x86 and Arduino AVR use little
endian. 

You might want to ask why endianness is so important from off-target unit tests
angle. Lets analyze simple code and then I will provide some explanations. 

PC:
```c++
int main(int argc, char *argv[])
{
    unsigned char tbl[]={1,2};
    unsigned short val;

    val = *(unsigned short*)tbl;
    
    cout << hex << val << endl;
    cout << dec << val << endl;
}
```

Arduino:
```c++
void loop()
{
   unsigned char tbl[]={1,2};
   unsigned short val;

   val = *(unsigned short*)tbl;
    
   Serial.println(val);
}
```

At the beginning we initialize memory assigned for `tbl` with `1` and `2`. In
memory map this memory region would look like follow: `0x0102`. Then in next
step we are assigning this memory to our `val` by using pointer cast and
dereference. And here we are touching essence of endianness because in in next
step we print out value stored in `val`. Printing out is *interpretation*
of variable memory. On little-endian this will produce a value of `0x0201`
while on big-endian we produce a value of `0x0102`. Same operation on two
different endianness will output two different values. In our case both
programs results producing same value `0x0201` (which is equal to 513 in
decimal notation) as both platforms are little endian. 

Lets put this precisely: ATSAM3X8E, ATmega2560 and Intel x86 are all little
endian.

There is a few of engineering practices built on endiannes pitfalls. Engineers
would like to write a code that is portable between machines. In this article I
wont cover all of these methods but I would like to give you some common sense
what are such practices about. 

Some advices I can give from my past experience:
- First places to look for endianness issues are places were you dealing with
  interfaces that provides you chunks of memory on input instead of variables.
  These are: network sockets, files, block devices and similar.
- Avoid performing memory operations outside of variables
- Similarly as above if you dealing with tables then don't expect code
  portability when casting table elements to different types
- Bit shift operators should be used in caution
- Take a caution when casting memory to `struct`, `class` or bit fields.


# Final remarks
In today article I described embedded engineering practice on unit test execution on
development machine instead of target. I also described areas which might
cause you a problem when doing so. As always I encourage you to visit
[Robobo project](https://leszek-wojcik.github.io/robobo/) and see how unit
tests are organized there. 

