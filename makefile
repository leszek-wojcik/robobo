include functions.mk

# various programs
CC = /usr/bin/avr-gcc
CPP = /usr/bin/avr-g++
AR = /usr/bin/avr-ar
OBJ_COPY = /usr/bin/avr-objcopy
AVRDUDE = /usr/bin/avrdude
AVRDUDECONF = /usr/share/arduino/hardware/tools/avrdude.conf 
OBJ_DIR = obj/
UT_DIR = ut/
MAIN_PROGRAM = robobo
MINICOM = /usr/bin/minicom -D /dev/ttyACM0 -b 115200
CC_OFFTARGET = /usr/bin/gcc
CCP_OFFTARGET = /usr/bin/g++
AVR_INCLUDE = /usr/lib/avr/include
DOXYGEN = /usr/bin/doxygen

# CPU settings 
F_CPU = 16000000
MCU = atmega2560

# compile flags
GENERAL_FLAGS = -c -g -Os -Wall -ffunction-sections -fdata-sections -mmcu=$(MCU) -DF_CPU=$(F_CPU)L -MMD -DUSB_VID=null -DUSB_PID=null -DARDUINO=105 -D__PROG_TYPES_COMPAT__
CPP_FLAGS = $(GENERAL_FLAGS) -fno-exceptions
CC_FLAGS  = $(GENERAL_FLAGS)
INCLUDE_FILES = -I$(ARDUINO_LIB_DIR) -I$(MEAGA_LIB_DIR) -I$(ROBOBO_LIB_DIR) 
UT_INCLUDE_FILES = -I$(MEAGA_LIB_DIR) -I$(ROBOBO_UT_DIR) -I$(ROBOBO_LIB_DIR) 
UT_LIBRARIES = -lgmock -lgtest -lgtest_main -lpthread -lstdc++ 

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

# ALL TARGET
ALL_C_OBJ_FILES =$(ARDUINO_LIB_C_OBJ_FILES) $(AVR_LIB_C_OBJ_FILES) $(ROBOBO_LIB_C_OBJ_FILES) 
ALL_CPP_OBJ_FILES = $(ARDUINO_LIB_CPP_OBJ_FILES) $(ROBOBO_LIB_CPP_OBJ_FILES) 
ALL_OBJ_FILES = $(ALL_CPP_OBJ_FILES) $(ALL_C_OBJ_FILES)

# Unit test
ROBOBO_UT_DIR = $(ROBOBO_LIB_DIR)$(UT_DIR)
ROBOBO_UT_CPP_FILES = $(call cppfilesfromdir,$(ROBOBO_UT_DIR))  
ROBOBO_UT_OBJ_DIR = $(ROBOBO_LIB_DIR)$(UT_DIR)$(OBJ_DIR)
ROBOBO_UT_CPP_OBJ_FILES = $(call objectfilesfromlist, $(ROBOBO_UT_OBJ_DIR), $(ROBOBO_UT_CPP_FILES)) $(call objectfilesfromlist, $(ROBOBO_UT_OBJ_DIR), $(ROBOBO_LIB_CPP_FILES))
ROBOBO_UT_CPP_OBJ_FILES := $(filter-out src/robobo/ut/obj/main.o, $(ROBOBO_UT_CPP_OBJ_FILES))

OBJ_DIRS = $(ROBOBO_UT_OBJ_DIR) $(ROBOBO_LIB_OBJ_DIR) $(AVR_LIB_OBJ_DIR) $(ARDUINO_LIB_OBJ_DIR)

.PHONY: dirs
dirs: $(OBJ_DIRS)

$(OBJ_DIRS): 
	@mkdir $(OBJ_DIRS)

clean :
	@rm -f -r $(ARDUINO_LIB_DIR)$(OBJ_DIR)
	@rm -f -r $(AVR_LIB_DIR)$(OBJ_DIR)
	@rm -f -r $(ROBOBO_LIB_DIR)$(OBJ_DIR)
	@rm -f -r $(ROBOBO_UT_OBJ_DIR)
	@rm -f core.a
	@rm -f $(MAIN_PROGRAM).d
	@rm -f $(MAIN_PROGRAM).o
	@rm -f $(MAIN_PROGRAM).elf
	@rm -f $(MAIN_PROGRAM).hex
	@rm -f $(MAIN_PROGRAM).eep
	@rm -f $(MAIN_PROGRAM).ut

$(ARDUINO_LIB_DIR)$(OBJ_DIR)%.o : $(ARDUINO_LIB_DIR)%.c
	@echo "Compiling $@"
	@$(CC) $(CC_FLAGS) $(INCLUDE_FILES) -o $@ $<

$(ARDUINO_LIB_DIR)$(OBJ_DIR)%.o : $(ARDUINO_LIB_DIR)%.cpp
	@echo "Compiling $@"
	@$(CPP) $(CPP_FLAGS) -Wno-unused-variable -Wno-sign-compare $(INCLUDE_FILES) -o $@ $<

$(AVR_LIB_DIR)$(OBJ_DIR)%.o : $(AVR_LIB_DIR)%.c 
	@echo "Compiling $@"
	@$(CC) $(CC_FLAGS) $(INCLUDE_FILES) -o $@ $<

$(ROBOBO_LIB_DIR)$(OBJ_DIR)%.o : $(ROBOBO_LIB_DIR)%.cpp
	@echo "Compiling $@"
	@$(CPP) $(CPP_FLAGS) $(INCLUDE_FILES) -o $@ $<

$(ROBOBO_UT_OBJ_DIR)%.o : $(ROBOBO_UT_DIR)%.cpp
	@echo "Compiling $@"
	@$(CCP_OFFTARGET) -c $(UT_INCLUDE_FILES) -o $@ $<

$(ROBOBO_UT_OBJ_DIR)%.o : $(ROBOBO_LIB_DIR)%.cpp
	@echo "Compiling $@"
	@$(CCP_OFFTARGET) -c $(UT_INCLUDE_FILES) -o $@ $<

core.a : dirs $(ALL_OBJ_FILES)
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

ut: dirs $(ROBOBO_UT_CPP_OBJ_FILES)
	@echo "Linking"
	@$(CCP_OFFTARGET) -g -Os -Wall $(ROBOBO_UT_CPP_OBJ_FILES) -o $(MAIN_PROGRAM).ut $(UT_LIBRARIES)
	@./$(MAIN_PROGRAM).ut

.PHONY: docs
docs: 
	@$(DOXYGEN) Doxyfile 
