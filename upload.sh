#!/bin/bash

/usr/bin/lsusb | /bin/grep SAMBA

/home/leszek/.arduino15/packages/arduino/tools/bossac/1.6.1-arduino/bossac -i -d --port=ttyACM0 -U true -e -w -v -b robobo.bin -R
