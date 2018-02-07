cmake_minimum_required (VERSION 2.6)
project (Robobo)

enable_language(CXX)
enable_language(C)
enable_language(ASM)

SET(CMAKE_C_COMPILER /home/leszek/.arduino15/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-gcc )
SET(CMAKE_ASM_COMPILER /home/leszek/.arduino15/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-gcc )
SET(CMAKE_CXX_COMPILER /home/leszek/.arduino15/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-g++ )
SET(CMAKE_AR /home/leszek/.arduino15/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-ar )
SET(CMAKE_LINKER /home/leszek/.arduino15/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-gcc )
SET(OBJ_COPY /home/leszek/.arduino15/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-objcopy )
SET(MAIN_PROGRAM robobo)

SET(CMAKE_FIND_ROOT_PATH /usr/)
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
SET(CMAKE_SOURCE_DIR /home/leszek/github/robobo/)

SET(CMAKE_CXX_FLAGS "-c -g -Os -w -std=gnu++11 -ffunction-sections -fdata-sections -nostdlib -fno-threadsafe-statics --param max-inline-insns-single=500 -fno-rtti -fno-exceptions -Dprintf=iprintf -MMD -mcpu=cortex-m3 -mthumb -DF_CPU=84000000L -DARDUINO=10805 -DARDUINO_SAM_DUE -DARDUINO_ARCH_SAM  -D__SAM3X8E__ -mthumb -DUSB_VID=0x2341 -DUSB_PID=0x003e -DUSBCON '-DUSB_MANUFACTURER=\"Arduino LLC\"' '-DUSB_PRODUCT=\"Arduino Due\"'")
SET(CMAKE_C_FLAGS "-c -g -Os -w -std=gnu11 -ffunction-sections -fdata-sections -nostdlib --param max-inline-insns-single=500 -Dprintf=iprintf -MMD -mcpu=cortex-m3 -mthumb -DF_CPU=84000000L -DARDUINO=10805 -DARDUINO_SAM_DUE -DARDUINO_ARCH_SAM  -D__SAM3X8E__ -mthumb -DUSB_VID=0x2341 -DUSB_PID=0x003e -DUSBCON -DUSB_MANUFACTURER=\"Arduino LLC\" -DUSB_PRODUCT=\"Arduino Due\"") 

SET(CMAKE_ASM_FLAGS "-c -g -x assembler-with-cpp -MMD -mcpu=cortex-m3 -mthumb -DF_CPU=84000000L -DARDUINO=10805 -DARDUINO_SAM_DUE -DARDUINO_ARCH_SAM  -D__SAM3X8E__ -mthumb -DUSB_VID=0x2341 -DUSB_PID=0x003e -DUSBCON -DUSB_MANUFACTURER=\"Arduino LLC\" -DUSB_PRODUCT=\"Arduino Due\"")

SET(LINKER_SCRIPT "/home/leszek/.arduino15/packages/arduino/hardware/sam/1.6.11/variants/arduino_due_x/linker_scripts/gcc/flash.ld" )
SET(LINKER_FLAGS "-mcpu=cortex-m3" "-mthumb" "-Os" "-Wl,--gc-sections" "-T${LINKER_SCRIPT}" "-Wl,-Map,${MAIN_PROGRAM}.map" "-o" "${MAIN_PROGRAM}.elf" "-Wl,--cref" "-Wl,--check-sections" "-Wl,--gc-sections" "-Wl,--entry=Reset_Handler" "-Wl,--unresolved-symbols=report-all" "-Wl,--warn-common" "-Wl,--warn-section-align" "-Wl,--start-group" "-u" "_sbrk" "-u" "link" "-u" "_close" "-u" "_fstat" "-u" "_isatty" "-u" "_lseek" "-u" "_read" "-u" "_write" "-u" "_exit" "-u" "kill" "-u" "_getpid" "CMakeFiles/main.dir/home/leszek/github/robobo/src/main/main.cpp.o" "CMakeFiles/variant.dir/home/leszek/github/robobo/src/arduino_due_x/variant.cpp.o" "libsam_sam3x8e_gcc_rel.a" "libcore.a" "-Wl,--end-group" "-lm" "-gcc")


file(GLOB ROBOBO_SRC
   "../../src/robobo/*.cpp"
   "../../src/Arduino/*.c"
   "../../src/Arduino/*.S"
   "../../src/Arduino/*.cpp"
   "../../src/Arduino/USB/*.cpp"
   "../../src/Arduino/avr/*.c"
)

file(GLOB MAIN_SRC
   "../../src/main/*.cpp"
)

file(GLOB VARIANT_SRC
   "../../src/arduino_due_x/variant.cpp"
)

include_directories( 
    "../../src/Arduino"
    "../../src/robobo"
    "../../src/libsam"
    "../../src/CMSIS/Device/ATMEL"
    "../../src/CMSIS/CMSIS/Include"
    "../../src/arduino_due_x"
    )

add_library(core ${ROBOBO_SRC})
add_library(main OBJECT ${MAIN_SRC})
add_library(variant OBJECT ${VARIANT_SRC})


add_custom_command (
        OUTPUT 
            ${MAIN_PROGRAM}.elf 
            ${MAIN_PROGRAM}.bin 
        DEPENDS
            core main variant
        COMMAND 
            ${CMAKE_C_COMPILER} ${LINKER_FLAGS} 
        COMMAND
            ${OBJ_COPY} -O binary ${MAIN_PROGRAM}.elf ${MAIN_PROGRAM}.bin)

add_custom_command (
        OUTPUT 
            ${MAIN_PROGRAM}.upl
        DEPENDS
            ${MAIN_PROGRAM}.bin 
        COMMAND
            touch ${MAIN_PROGRAM}.upl
        COMMAND
            ./upload.sh
)



add_custom_target(
    build
    DEPENDS ${MAIN_PROGRAM}.elf ${MAIN_PROGRAM}.bin core main variant
)

add_custom_target(
    upload
    DEPENDS ${MAIN_PROGRAM}.upl
)

