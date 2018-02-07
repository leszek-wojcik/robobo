#!/bin/bash -x

stty -F /dev/ttyACM0 raw ispeed 1200 cs8 -cstopb -parenb; sleep 3
stty -F /dev/ttyACM0 raw ispeed 1200 cs8 -cstopb -parenb; sleep 3
stty -F /dev/ttyACM0 raw ispeed 9600 cs8 -cstopb -parenb; sleep 3
stty -F /dev/ttyACM0 raw ispeed 1200 cs8 -cstopb -parenb; sleep 3
stty -F /dev/ttyACM0 raw ispeed 1200 cs8 -cstopb -parenb; sleep 3

/home/leszek/.arduino15/packages/arduino/tools/bossac/1.6.1-arduino/bossac -i -d --port=ttyACM0 -U false -e -w -v -b robobo.bin -R
