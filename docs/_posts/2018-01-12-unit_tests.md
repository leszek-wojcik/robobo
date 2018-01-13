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
test execution on developer machine. For medium and large scale projects this
is big benefit as it speeds up development process. There are several pitfalls
which you should be aware of before starting such approach in your project.

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
tests run on developer machine (Intel or AMD x86) while production code is
run on target (in our case Arduino). On development machine we have
advanced OS like Linux or Windows while on target Arduino we usually have no OS
at all. 

# PC and Arduino differences
Lets try to summarize what is different on these two platforms and how we
should protect ourselves between these differences. 

# Built in types 
Almost all C/C++ books refers to platforms specific details on data types. C/C++
doesn't guarantee sizes of basic data types. For instance if we deal with `int`
type on a PC you will probably have 4 bytes representation in integral value.
On Arduino you will have only 2 bytes for integral representations. What does
this mean for you? Answer is quite simple.  Maximum and minimum value for
integral representations are `2147483647` and `-2147483648` on PC and `32767`
and `-32768` on Arduino. 

In most cases you might ignore this fact but if you are crossing boundaries you
might expect functional differences when running unit tests and target code.
Below are two different code snippet that you can use to determine sizes of
data types.

PC:

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

PC output:
```
sizeof(int):    4
sizeof(short):  2
sizeof(long):   8
sizeof(float):  4
sizeof(double): 8
```

Arduino Mega:

```C
void loop()
{
  Serial.print("sizeof(int):"); 
  Serial.println(sizeof(int));
  
  Serial.print("sizeof(short):");
  Serial.println(sizeof(short));
  
  Serial.print("sizeof(long):");
  Serial.println(sizeof(long));
  
  Serial.print("sizeof(float):");
  Serial.println(sizeof(float));
  
  Serial.print("sizeof(double):");
  Serial.println(sizeof(double));
  
  delay (1000);
}
```

Arduino output:
```
sizeof(int):2
sizeof(short):2
sizeof(long):4
sizeof(float):4
sizeof(double):4
```

In order to avoid potential problems with data types there is convenient method
of variable declarations. Modern standard libraries provides you set of
`typedef`s that you can use without worry about size. These are examples:

```
int8_t
int16_t
uint8_t
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
```C++
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
```C++
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
programs results producing same value as both platforms are little endian.

There is a lot of engineering practices built on endiannes pitfalls. Engineers
would like to write a code that is portable between machines. In this article I
wont cover all of these methods but I would like to give you some common sense
what are such practices about. 

Some advices I can give from my past experience:
- Avoid performing memory operations outside of variables
- Similarly as above if you dealing with tables then don't expect code
  portability when casting table elements to different types
- Avoid bit shift operators 
- Take a caution when casting memory to `struct`s or `class`es
- Don't use bit fields
- First places to look for endianness issues are places were you dealing with
  interfaces that provides you chunks of memory on input instead of variables.
  These are: network sockets, files, block devices and similar.

# Final remarks
In today article I described embedded engineering practice on unit test execution on
development machine instead of target. I also described areas which might
cause you a problem when doing so. As always I encourage you to visit
[Robobo project](https://leszek-wojcik.github.io/robobo/) and see how unit
tests are organized there. 

