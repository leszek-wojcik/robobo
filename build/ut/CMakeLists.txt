cmake_minimum_required (VERSION 2.6)
project (Robobo)
enable_language(C)
enable_language(CXX)

#SET(CMAKE_C_COMPILER /usr/bin/avr-gcc )
#SET(CMAKE_CXX_COMPILER /usr/bin/avr-g++)
#SET(CMAKE_AR /usr/bin/avr-ar)
#SET(CMAKE_C_LINK_EXECUTABLE /usr/bin/avr-gcc)
#SET(LINKER_LANGUAGE "C")
#SET(OBJ_COPY /usr/bin/avr-objcopy)
#SET(MAIN_PROGRAM robobo)
#
#SET(CMAKE_FIND_ROOT_PATH /usr/)
#SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
#SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
#SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
#SET(CMAKE_SOURCE_DIR /home/leszek/github/robobo/)


#SET(GENERAL_DEFINES  "-DF_CPU=16000000L -MMD -DUSB_VID=null -DUSB_PID=null -DARDUINO=105 -D__PROG_TYPES_COMPAT__")
#SET(GENERAL_FLAGS "-c -g -Os -Wall -ffunction-sections -fdata-sections -mmcu=atmega2560")
#SET(GENERAL_CPP_FLAGS "-fno-exceptions")
#
#SET(CMAKE_CXX_FLAGS "${GENERAL_DEFINES} ${GENERAL_FLAGS} ${GENERAL_CPP_FLAGS}")
#SET(CMAKE_C_FLAGS "${GENERAL_DEFINES} ${GENERAL_FLAGS}")
#SET(CMAKE_CXX_ARCHIVE_CREATE "${CMAKE_AR} rcs -o <TARGET> <LINK_FLAGS> <OBJECTS>")
#
#set(UNITTEST_BUILD_DIR "build/ut"     CACHE INTERNAL "")
#set(ROBOBO_BUILD_DIR   "build/robobo" CACHE INTERNAL "")


file(GLOB UT_SRC
   "../../src/robobo/ut/*.cpp"
   "../../src/robobo/*.cpp"
   "../../src/robobo/*.c"
)


include_directories( 
    "../../src/robobo/ut"
    "../../src/robobo"
    "../../src/FreeRTOS"
    )

add_executable(robobo.ut ${UT_SRC})

find_package(GTest REQUIRED)
target_link_libraries(robobo.ut GTest::GTest GTest::Main gmock)


