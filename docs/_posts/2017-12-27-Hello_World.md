---
layout: post
title:  "Hello World Robobo"
date:   2017-12-27 21:19:00 +0100
description: Robobo is C++ project with Doxygen generated documentation, blog,
off-target unit tests written in GoogleTest and GoogleMock framework on Github.
categories: makefile githubpages
---

More than two weeks past since first commit and a lot did happen on repository.
First at all decent makefile was created in purpose of:
 - compiling, building, uploading avr code for Arduino Mega
 - compiling and running off-target gtest unit tests with gmocks
 - doxygen documentation
 - minicom connection to arduino serial

Few targets are available:
 - make build - creates *.hex file for avr 
 - make ut - compiles and runs off target unit tests
 - make docs - generates doxygen documentation out of source code
 - make all - compiles target, loads it and hookup minicom session using USB

Sounds simple but its not. I found myslef spending a lot of time on roots
projects. I hope this will payoff later on when project start to expand. Whole
ecosystem is intended to make project maintainable.



