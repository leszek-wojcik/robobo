# various programs
CC = /usr/bin/avr-gcc
CPP = /usr/bin/avr-g++
AR = /usr/bin/avr-ar
OBJ_COPY = /usr/bin/avr-objcopy
AVRDUDE = /usr/bin/avrdude
AVRDUDECONF = /usr/share/arduino/hardware/tools/avrdude.conf 

MAIN_SKETCH = Blink.cpp

# CPU settings 
F_CPU = 16000000
MCU = atmega2560

# compile flags
GENERAL_FLAGS = -c -g -Os -Wall -ffunction-sections -fdata-sections -mmcu=$(MCU) -DF_CPU=$(F_CPU)L -MMD -DUSB_VID=null -DUSB_PID=null -DARDUINO=105 -D__PROG_TYPES_COMPAT__
CPP_FLAGS = $(GENERAL_FLAGS) -fno-exceptions
CC_FLAGS  = $(GENERAL_FLAGS)

# location of include files
ARDUINO_LIB_DIR = src/Arduino/
MEAGA_LIB_DIR = src/mega/
AVR_LIB_DIR = src/avr-libc/
INCLUDE_FILES = -I$(ARDUINO_LIB_DIR) -I$(MEAGA_LIB_DIR)

clean :
	rm -f *.o
	rm -f *.d
	rm -f core.a

core.a :
	$(CC) $(CC_FLAGS) $(INCLUDE_FILES) $(AVR_LIB_DIR)malloc.c -o malloc.o
	$(CC) $(CC_FLAGS) $(INCLUDE_FILES) $(AVR_LIB_DIR)realloc.c -o realloc.o

	$(CC) $(CC_FLAGS) $(INCLUDE_FILES) $(ARDUINO_LIB_DIR)WInterrupts.c -o WInterrupts.o
	$(CC) $(CC_FLAGS) $(INCLUDE_FILES) $(ARDUINO_LIB_DIR)wiring.c -o wiring.o
	$(CC) $(CC_FLAGS) $(INCLUDE_FILES) $(ARDUINO_LIB_DIR)wiring_analog.c -o wiring_analog.o
	$(CC) $(CC_FLAGS) $(INCLUDE_FILES) $(ARDUINO_LIB_DIR)wiring_digital.c -o wiring_digital.o
	$(CC) $(CC_FLAGS) $(INCLUDE_FILES) $(ARDUINO_LIB_DIR)wiring_pulse.c -o wiring_pulse.o
	$(CC) $(CC_FLAGS) $(INCLUDE_FILES) $(ARDUINO_LIB_DIR)wiring_shift.c -o wiring_shift.o
	$(CPP) $(CPP_FLAGS) $(INCLUDE_FILES) $(ARDUINO_LIB_DIR)CDC.cpp -o CDC.o
	$(CPP) $(CPP_FLAGS) $(INCLUDE_FILES) $(ARDUINO_LIB_DIR)HardwareSerial.cpp -o HardwareSerial.o
	$(CPP) $(CPP_FLAGS) $(INCLUDE_FILES) $(ARDUINO_LIB_DIR)HID.cpp -o HID.o
	$(CPP) $(CPP_FLAGS) $(INCLUDE_FILES) $(ARDUINO_LIB_DIR)IPAddress.cpp -o IPAddress.o
	$(CPP) $(CPP_FLAGS) $(INCLUDE_FILES) $(ARDUINO_LIB_DIR)main.cpp -o main.o
	$(CPP) $(CPP_FLAGS) $(INCLUDE_FILES) $(ARDUINO_LIB_DIR)new.cpp -o new.o
	$(CPP) $(CPP_FLAGS) $(INCLUDE_FILES) $(ARDUINO_LIB_DIR)Print.cpp -o Print.o
	$(CPP) $(CPP_FLAGS) $(INCLUDE_FILES) $(ARDUINO_LIB_DIR)Stream.cpp -o Stream.o
	$(CPP) $(CPP_FLAGS) $(INCLUDE_FILES) $(ARDUINO_LIB_DIR)Tone.cpp -o Tone.o
	$(CPP) $(CPP_FLAGS) $(INCLUDE_FILES) $(ARDUINO_LIB_DIR)USBCore.cpp -o USBCore.o
	$(CPP) $(CPP_FLAGS) $(INCLUDE_FILES) $(ARDUINO_LIB_DIR)WMath.cpp -o WMath.o
	$(CPP) $(CPP_FLAGS) $(INCLUDE_FILES) $(ARDUINO_LIB_DIR)WString.cpp -o WString.o
	$(AR) rcs core.a malloc.o
	$(AR) rcs core.a realloc.o
	$(AR) rcs core.a WInterrupts.o
	$(AR) rcs core.a wiring.o
	$(AR) rcs core.a wiring_analog.o
	$(AR) rcs core.a wiring_digital.o
	$(AR) rcs core.a wiring_pulse.o
	$(AR) rcs core.a wiring_shift.o
	$(AR) rcs core.a CDC.o
	$(AR) rcs core.a HardwareSerial.o
	$(AR) rcs core.a HID.o
	$(AR) rcs core.a IPAddress.o
	$(AR) rcs core.a main.o
	$(AR) rcs core.a new.o
	$(AR) rcs core.a Print.o
	$(AR) rcs core.a Stream.o
	$(AR) rcs core.a Tone.o
	$(AR) rcs core.a USBCore.o
	$(AR) rcs core.a WMath.o
	$(AR) rcs core.a WString.o
build:
	$(CPP) $(CPP_FLAGS) $(INCLUDE_FILES) $(MAIN_SKETCH) -o $(MAIN_SKETCH).o
	$(CC) -Os -Wl,--gc-sections,--relax -mmcu=$(MCU) -o $(MAIN_SKETCH).elf $(MAIN_SKETCH).o core.a -lm
	$(OBJ_COPY) -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0 $(MAIN_SKETCH).elf $(MAIN_SKETCH).eep
	$(OBJ_COPY) -O ihex -R .eeprom $(MAIN_SKETCH).elf $(MAIN_SKETCH).hex
	$(AVRDUDE) -C$(AVRDUDECONF) -v -patmega2560 -cwiring -P/dev/ttyACM0 -b115200 -D -Uflash:w:$(MAIN_SKETCH).hex:i 

