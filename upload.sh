#!/bin/bash

#/usr/bin/lsusb | /bin/grep SAMBA

#/home/leszek/.arduino15/packages/arduino/tools/bossac/1.6.1-arduino/bossac -i -d --port=ttyACM0 -U true  -e -w -v -b build/arm/bin/robobo.bin -R
/home/leszek/.arduino15/packages/arduino/tools/bossac/1.6.1-arduino/bossac -i --port=ttyACM0 -U false -e -w  -b  build/arm/bin/robobo.bin -R
