include functions.mk

# various programs
CC = /usr/bin/avr-gcc
CPP = /usr/bin/avr-g++
AR = /usr/bin/avr-ar
OBJ_COPY = /usr/bin/avr-objcopy
AVRDUDE = /usr/bin/avrdude
AVRDUDECONF = /usr/share/arduino/hardware/tools/avrdude.conf 
OBJ_DIR = obj/
MAIN_PROGRAM = robobo
MINICOM = /usr/bin/minicom -D /dev/ttyACM0 -b 115200

# CPU settings 
F_CPU = 16000000
MCU = atmega2560

# compile flags
GENERAL_FLAGS = -c -g -Os -Wall -ffunction-sections -fdata-sections -mmcu=$(MCU) -DF_CPU=$(F_CPU)L -MMD -DUSB_VID=null -DUSB_PID=null -DARDUINO=105 -D__PROG_TYPES_COMPAT__
CPP_FLAGS = $(GENERAL_FLAGS) -fno-exceptions
CC_FLAGS  = $(GENERAL_FLAGS)
INCLUDE_FILES = -I$(ARDUINO_LIB_DIR) -I$(MEAGA_LIB_DIR)

# Arduino lib 
ARDUINO_LIB_DIR = src/Arduino/
ARDUINO_LIB_C_FILES = $(call cfilesfromdir,$(ARDUINO_LIB_DIR)) 
ARDUINO_LIB_CPP_FILES = $(call cppfilesfromdir,$(ARDUINO_LIB_DIR))  
ARDUINO_LIB_OBJ_DIR = $(ARDUINO_LIB_DIR)$(OBJ_DIR)
ARDUINO_LIB_C_OBJ_FILES = $(call objectfilesfromlist, $(ARDUINO_LIB_OBJ_DIR), $(ARDUINO_LIB_C_FILES))
ARDUINO_LIB_CPP_OBJ_FILES = $(call objectfilesfromlist, $(ARDUINO_LIB_OBJ_DIR), $(ARDUINO_LIB_CPP_FILES))

# AVR lib
AVR_LIB_DIR = src/avr-libc/
AVR_LIB_C_FILES = $(call cfilesfromdir,$(AVR_LIB_DIR))
AVR_LIB_OBJ_DIR = $(AVR_LIB_DIR)$(OBJ_DIR)
AVR_LIB_C_OBJ_FILES =$(call objectfilesfromlist, $(AVR_LIB_OBJ_DIR), $(AVR_LIB_C_FILES))

# Mega lib
MEAGA_LIB_DIR = src/mega/

# Robobo
ROBOBO_LIB_DIR = src/robobo/
ROBOBO_LIB_C_FILES = $(call cfilesfromdir,$(ROBOBO_LIB_DIR)) 
ROBOBO_LIB_CPP_FILES = $(call cppfilesfromdir,$(ROBOBO_LIB_DIR))  
ROBOBO_LIB_OBJ_DIR = $(ROBOBO_LIB_DIR)$(OBJ_DIR)
ROBOBO_LIB_C_OBJ_FILES = $(call objectfilesfromlist, $(ROBOBO_LIB_OBJ_DIR), $(ROBOBO_LIB_C_FILES))
ROBOBO_LIB_CPP_OBJ_FILES = $(call objectfilesfromlist, $(ROBOBO_LIB_OBJ_DIR), $(ROBOBO_LIB_CPP_FILES))

# ALL
ALL_C_OBJ_FILES =$(ARDUINO_LIB_C_OBJ_FILES) $(AVR_LIB_C_OBJ_FILES) $(ROBOBO_LIB_C_OBJ_FILES) 
ALL_CPP_OBJ_FILES = $(ARDUINO_LIB_CPP_OBJ_FILES) $(ROBOBO_LIB_CPP_OBJ_FILES) 
ALL_OBJ_FILES = $(ALL_CPP_OBJ_FILES) $(ALL_C_OBJ_FILES)

clean :
	@rm -f $(ARDUINO_LIB_DIR)$(OBJ_DIR)*
	@rm -f $(AVR_LIB_DIR)$(OBJ_DIR)*
	@rm -f $(ROBOBO_LIB_DIR)$(OBJ_DIR)*
	@rm -f core.a
	@rm -f $(MAIN_PROGRAM).d
	@rm -f $(MAIN_PROGRAM).o
	@rm -f $(MAIN_PROGRAM).elf
	@rm -f $(MAIN_PROGRAM).hex
	@rm -f $(MAIN_PROGRAM).eep

$(ARDUINO_LIB_DIR)$(OBJ_DIR)%.o : $(ARDUINO_LIB_DIR)%.c
	@echo "Comiling $@"
	@$(CC) $(CC_FLAGS) $(INCLUDE_FILES) -o $@ $<

$(ARDUINO_LIB_DIR)$(OBJ_DIR)%.o : $(ARDUINO_LIB_DIR)%.cpp
	@echo "Comiling $@"
	@$(CPP) $(CPP_FLAGS) -Wno-unused-variable -Wno-sign-compare $(INCLUDE_FILES) -o $@ $<

$(AVR_LIB_DIR)$(OBJ_DIR)%.o : $(AVR_LIB_DIR)%.c 
	@echo "Comiling $@"
	@$(CC) $(CC_FLAGS) $(INCLUDE_FILES) -o $@ $<

$(ROBOBO_LIB_DIR)$(OBJ_DIR)%.o : $(ROBOBO_LIB_DIR)%.cpp
	@echo "Comiling $@"
	@$(CPP) $(CPP_FLAGS) $(INCLUDE_FILES) -o $@ $<

core.a : $(ALL_OBJ_FILES)
	@echo "archiving objects to core.a"
	@$(AR) rcs core.a $(ALL_OBJ_FILES)

build: core.a
	@echo "Linking"
	$(CC) -Os -Wl,--gc-sections,--relax -mmcu=$(MCU) -o $(MAIN_PROGRAM).elf core.a -lm
	@echo "Binary object creation"
	@$(OBJ_COPY) -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0 $(MAIN_PROGRAM).elf $(MAIN_PROGRAM).eep
	@$(OBJ_COPY) -O ihex -R .eeprom $(MAIN_PROGRAM).elf $(MAIN_PROGRAM).hex

install: build
	@echo "Serial Transfer"
	$(AVRDUDE) -C$(AVRDUDECONF) -patmega2560 -cwiring -P/dev/ttyACM0 -b115200 -D -Uflash:w:$(MAIN_PROGRAM).hex:i 

terminal: install
	$(MINICOM)

all: terminal
	@echo "done compiling and uploading"
