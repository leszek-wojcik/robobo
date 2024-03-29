#!/usr/bin/env python3

from ronin.cli import cli
from ronin.contexts import new_context
from ronin.gcc import GccBuild
from ronin.gcc import GccCompile
from ronin.gcc import GccLink
from ronin.gcc import GccExecutor
from ronin.gcc import which_gcc
from ronin.phases import Phase
from ronin.pkg_config import Package
from ronin.projects import Project
from ronin.utils.paths import glob
from ronin.ninja import configure_ninja
from ronin.ninja import NinjaFile
from ronin.extensions import ExplicitExtension
from ronin.executors import ExecutorWithArguments
import sys


class ARExecutor(ExecutorWithArguments):
    
    def __init__(self, command=None ):
        
        super(ARExecutor, self).__init__()
        self.command = command
        self.add_argument_unfiltered('qc', '$out')
        self.add_argument_unfiltered('$in')

class BinExecutor(ExecutorWithArguments):
    
    def __init__(self, command=None ):
        
        super(BinExecutor, self).__init__()
        self.command = command
        self.add_argument_unfiltered('-O binary', '$in')
        self.add_argument_unfiltered('$out')

class SAMLinkExecutor(ExecutorWithArguments):
    
    def __init__(self, command=None):
        
        super(SAMLinkExecutor, self).__init__()
        self.command = command

        self.add_argument_unfiltered("-mcpu=cortex-m3")
        self.add_argument_unfiltered("-mthumb")
        self.add_argument_unfiltered("-Os")
        self.add_argument_unfiltered("-Wl,--gc-sections")
        self.add_argument_unfiltered("-TArduinoCore-sam/variants/arduino_due_x/linker_scripts/gcc/flash.ld")
        self.add_argument_unfiltered("-Wl,-Map,robobo.map")
        self.add_argument_unfiltered('-o', '$out')
        self.add_argument_unfiltered("-Wl,--cref")
        self.add_argument_unfiltered("-Wl,--check-sections")
        self.add_argument_unfiltered("-Wl,--gc-sections")
        self.add_argument_unfiltered("-Wl,--entry=Reset_Handler")
        self.add_argument_unfiltered("-Wl,--unresolved-symbols=report-all")
        self.add_argument_unfiltered("-Wl,--warn-common")
        self.add_argument_unfiltered("-Wl,--warn-section-align")
        self.add_argument_unfiltered("-Wl,--start-group")
        self.add_argument_unfiltered(   "-u _sbrk", 
                                        "-u link", 
                                        "-u _close", 
                                        "-u _fstat", 
                                        "-u _isatty", 
                                        "-u _lseek", 
                                        "-u _read", 
                                        "-u _write", 
                                        "-u _exit", 
                                        "-u kill", 
                                        "-u _getpid")
        self.add_argument_unfiltered('$in')
        self.add_argument_unfiltered('ArduinoCore-sam/variants/arduino_due_x/libsam_sam3x8e_gcc_rel.a')
        self.add_argument_unfiltered('-Wl,--end-group')
        self.add_argument_unfiltered('-lm')
        self.add_argument_unfiltered('-lstdc++')
        self.add_argument_unfiltered('-gcc')


with new_context(output_path_relative='build') as ctx:

    configure_ninja(ninja_command='ninja',
                    encoding='utf8',
                    file_name='build',
                    columns=100,
                    strict=False)

    utproject = Project(name='Off-target unit tests',variant='ut')
    
    unittestextensions = [Package('gmock_main')]
    unittestextensions += [ExplicitExtension(libraries=['pthread'])]
    unittestcompile = GccCompile(command='/usr/bin/g++')
    unittestcompile.add_argument("-std=c++11")
    unittestcompile.add_argument("-ggdb")
    unittestcompile.add_include_path('src/unittests/')
    unittestcompile.add_include_path('src/robobo/')
    unittestcompile.add_include_path('src/FreeRTOS/')
    unittestcompile.define("ROBOBO_VERSION_STRING","\'\"Robobo 0.1\"\'")
    unittestlink = GccLink(command='/usr/bin/g++')
    unittestsources = glob('src/unittests/*.cpp')
    unittestsources += glob('src/robobo/*.cpp')

    Phase(  project=utproject,
            name='utcompile',
            executor=unittestcompile,
            extensions=unittestextensions,
            inputs=unittestsources 
            )

    Phase(  project=utproject,
            name='utlink',
            executor=unittestlink,
            inputs_from=['utcompile'],
            extensions=unittestextensions,
            output='unittests',
            run_output=1 if ctx.build.run else 0)

    ard = Project(name='target build', variant="arm")
    
    ardCCompile   = GccCompile(command='/home/leszek/.arduino15/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-gcc')
    ardCXXCompile = GccCompile(command='/home/leszek/.arduino15/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-g++')
    ardASMCompile = GccCompile(command='/home/leszek/.arduino15/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-gcc')
    ardAR         = ARExecutor(command='arm-none-eabi-ar')
    ardLink       = SAMLinkExecutor(command='/home/leszek/.arduino15/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-gcc')
    ardBinary     = BinExecutor(command= 'arm-none-eabi-objcopy')

    ardCCompile.define("F_CPU","84000000L")
    ardCCompile.define("ROBOBO_VERSION_STRING","\'\"Robobo 0.1\"\'")
    ardCCompile.define("ARDUINO","10805")
    ardCCompile.define("ARDUINO_SAM_DUE")
    ardCCompile.define("ARDUINO_ARCH_SAM")  
    ardCCompile.define("__SAM3X8E__")
    ardCCompile.define("USB_VID","0x2341")
    ardCCompile.define("USB_PID","0x003e") 
    ardCCompile.define("USBCON") 
    ardCCompile.define("USB_MANUFACTURER","\'\"Arduino LLC\"\'")
    ardCCompile.define("USB_PRODUCT","\'\"Arduino Due\"\'")
    ardCCompile.add_argument("-mthumb")
    ardCCompile.add_argument("-g")
    ardCCompile.add_argument("-Os")
    ardCCompile.add_argument("-w")
    ardCCompile.add_argument("-std=gnu11")
    ardCCompile.add_argument("-ffunction-sections")
    ardCCompile.add_argument("-fdata-sections")
    ardCCompile.add_argument("-nostdlib")
    ardCCompile.add_argument("-nostdinc")
    ardCCompile.add_argument("--param max-inline-insns-single=500")
    ardCCompile.add_argument("-Dprintf=iprintf")
    ardCCompile.add_argument("-MMD")
    ardCCompile.add_argument("-mcpu=cortex-m3")
    ardCCompile.add_include_path("src/Arduino")
    ardCCompile.add_include_path("src/robobo")
    ardCCompile.add_include_path("src/FreeRTOS")
    ardCCompile.add_include_path("ArduinoCore-sam/system/libsam/")
    ardCCompile.add_include_path("ArduinoCore-sam/system/CMSIS/Device/ATMEL//")
    ardCCompile.add_include_path("ArduinoCore-sam/system/CMSIS/CMSIS/Include/")
    ardCCompile.add_include_path("ArduinoCore-sam/variants/arduino_due_x")

    ardCCompile.add_include_path("/home/leszek/github/arm-gnu-toolchain-12.2.mpacbti-bet1-x86_64-arm-none-eabi/lib/gcc/arm-none-eabi/12.2.0/include")
    ardCCompile.add_include_path("/home/leszek/github/arm-gnu-toolchain-12.2.mpacbti-bet1-x86_64-arm-none-eabi/arm-none-eabi/include")
    ardCCompile.add_include_path("/home/leszek/github/arm-gnu-toolchain-12.2.mpacbti-bet1-x86_64-arm-none-eabi/arm-none-eabi/include/machine")
    ardCCompile.add_include_path("/home/leszek/github/arm-gnu-toolchain-12.2.mpacbti-bet1-x86_64-arm-none-eabi/arm-none-eabi/include/c++/12.2.0")
    ardCCompile.add_include_path("/home/leszek/github/arm-gnu-toolchain-12.2.mpacbti-bet1-x86_64-arm-none-eabi/arm-none-eabi/include/c++/12.2.0/arm-none-eabi")
    ardCCompile.add_include_path("/home/leszek/github/arm-gnu-toolchain-12.2.mpacbti-bet1-x86_64-arm-none-eabi/arm-none-eabi/include")

    ardCXXCompile.define("F_CPU","84000000L")
    ardCXXCompile.define("ARDUINO","10607")
    ardCXXCompile.define("ARDUINO_SAM_DUE")
    ardCXXCompile.define("ARDUINO_ARCH_SAM")  
    ardCXXCompile.define("__SAM3X8E__")
    ardCXXCompile.define("USB_VID","0x2341")
    ardCXXCompile.define("USB_PID","0x003e") 
    ardCXXCompile.define("USBCON") 
    ardCXXCompile.define("USB_MANUFACTURER","\'\"Arduino LLC\"\'")
    ardCXXCompile.define("USB_PRODUCT","\'\"Arduino Due\"\'")
    ardCXXCompile.define("ROBOBO_VERSION_STRING","\'\"Robobo 0.1\"\'")
    ardCXXCompile.add_argument("-mthumb")
    ardCXXCompile.add_argument("-g")
    ardCXXCompile.add_argument("-Os")
    ardCXXCompile.add_argument("-w")
    ardCXXCompile.add_argument("-std=gnu++11")
    ardCXXCompile.add_argument("-ffunction-sections")
    ardCXXCompile.add_argument("-fdata-sections")
    ardCXXCompile.add_argument("-nostdlib")
 #   ardCXXCompile.add_argument("-nostdinc++")
    ardCXXCompile.add_argument("-fno-threadsafe-statics")
    ardCXXCompile.add_argument("-fno-rtti -fno-exceptions") 
    ardCXXCompile.add_argument("--param max-inline-insns-single=500")
#   ardCXXCompile.add_argument("-Dprintf=iprintf")
    ardCXXCompile.add_argument("-MMD")
    ardCXXCompile.add_argument("-mcpu=cortex-m3")

#   ardCXXCompile.add_include_path("src/Arduino")
#   ardCXXCompile.add_include_path("src/libsam")
#   ardCXXCompile.add_include_path("src/arduino_due_x")
    
    ardCXXCompile.add_include_path("ArduinoCore-sam/system/libsam")
    ardCXXCompile.add_include_path("ArduinoCore-sam/system/CMSIS/CMSIS/Include")
    ardCXXCompile.add_include_path("ArduinoCore-sam/system/CMSIS/Device/ATMEL")
    ardCXXCompile.add_include_path("ArduinoCore-sam/cores/arduino")
    ardCXXCompile.add_include_path("ArduinoCore-sam/variants/arduino_due_x")

#    ardCXXCompile.add_include_path("/home/leszek/github/arm-gnu-toolchain-12.2.mpacbti-bet1-x86_64-arm-none-eabi/lib/gcc/arm-none-eabi/12.2.0/include")
#    ardCXXCompile.add_include_path("/home/leszek/github/arm-gnu-toolchain-12.2.mpacbti-bet1-x86_64-arm-none-eabi/arm-none-eabi/include/machine")
#    ardCXXCompile.add_include_path("/home/leszek/github/arm-gnu-toolchain-12.2.mpacbti-bet1-x86_64-arm-none-eabi/arm-none-eabi/include/c++/12.2.0")
#    ardCXXCompile.add_include_path("/home/leszek/github/arm-gnu-toolchain-12.2.mpacbti-bet1-x86_64-arm-none-eabi/arm-none-eabi/include/c++/12.2.0/arm-none-eabi")
#    ardCXXCompile.add_include_path("/home/leszek/github/arm-gnu-toolchain-12.2.mpacbti-bet1-x86_64-arm-none-eabi/arm-none-eabi/include")
    
    ardCXXCompile.add_include_path("ArduinoCore-sam/variants/arduino_due_x")
    ardCXXCompile.add_include_path("src/robobo")
    ardCXXCompile.add_include_path("src/FreeRTOS")
    ardCXXCompile.add_include_path("src/LiquidCrystal/src")

    ardASMCompile.define("F_CPU","84000000L")
    ardASMCompile.define("ARDUINO","10805")
    ardASMCompile.define("ARDUINO_SAM_DUE")
    ardASMCompile.define("ARDUINO_ARCH_SAM")  
    ardASMCompile.define("__SAM3X8E__")
    ardASMCompile.define("USB_VID","0x2341")
    ardASMCompile.define("USB_PID","0x003e") 
    ardASMCompile.define("USBCON") 
    ardASMCompile.define("USB_MANUFACTURER","\'\"Arduino LLC\"\'")
    ardASMCompile.define("USB_PRODUCT","\'\"Arduino Due\"\'")
    ardASMCompile.add_argument("-mthumb")
    ardASMCompile.add_argument("-g")
    ardASMCompile.add_argument("-w")
#    ardASMCompile.add_argument("-x assembler-with-cpp")
    ardASMCompile.add_argument("-MMD")
    ardASMCompile.add_argument("-mcpu=cortex-m3")

    aCSources   = []
    aCXXSources = []
    aASMSources = []

    aCSources           += glob("ArduinoCore-sam/cores/arduino/*.c")
    aCXXSources         += glob("ArduinoCore-sam/cores/arduino/*.cpp")
    aCXXSourcesToRemove = glob("ArduinoCore-sam/cores/arduino/main.cpp")
    aCXXSources.remove(aCXXSourcesToRemove[0])
    aCSources           += glob("ArduinoCore-sam/cores/arduino/avr/*.c")
    aCXXSources         += glob("ArduinoCore-sam/cores/arduino/USB/*.cpp")
    aCXXSources         += glob("ArduinoCore-sam/variants/arduino_due_x/variant.cpp")
    aCSources           += glob("src/FreeRTOS/*.c")
    aCXXSources         += glob("src/robobo/*.cpp")
    aCXXSources         += glob("src/LiquidCrystal/src/*.cpp")
    aCXXSources         += glob("src/main/main.cpp")
    aASMSources         += glob("ArduinoCore-sam/cores/arduino/*.S")

    print (aCXXSources)

    Phase(  project=ard,
            name='C Sources Compile',
            executor=ardCCompile,
            inputs=aCSources)

    Phase(  project=ard,
            name='CXX Sources Compile',
            executor=ardCXXCompile,
            inputs=aCXXSources)

    Phase(  project=ard,
            name='ASM Sources Compile',
            executor=ardASMCompile,
            inputs=aASMSources)

    Phase(  project=ard,
            name='Core Link',
            executor=ardAR,
            inputs_from=['C Sources Compile','CXX Sources Compile','ASM Sources Compile'],
            output='core.a')

    Phase(  project=ard,
            name='Final Link',
            executor=ardLink,
            inputs_from=['Core Link'],
            output='robobo.elf')

    Phase(  project=ard,
            name='Binary object creation',
            executor=ardBinary,
            inputs_from=['Final Link'],
            output='robobo.bin')

    if (ctx.build.test):
        cli(utproject)
    else:
        cli(ard)

