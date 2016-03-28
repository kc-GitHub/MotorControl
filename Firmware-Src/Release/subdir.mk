################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../.ino.cpp \
../hardware.cpp 

INO_SRCS += \
../HM-LC-Bl1-FM_AES.ino 

INO_DEPS += \
./HM-LC-Bl1-FM_AES.ino.d 

CPP_DEPS += \
./.ino.cpp.d \
./hardware.cpp.d 

LINK_OBJ += \
./.ino.cpp.o \
./hardware.cpp.o 


# Each subdirectory must supply rules for building sources it contributes
.ino.cpp.o: ../.ino.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"D:/Programme/arduino-1.6.0/hardware/tools/avr/bin/avr-g++" -c -g -Os -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega328p -DF_CPU=8000000L -DARDUINO=160 -DARDUINO_AVR_PRO -DARDUINO_ARCH_AVR     -I"D:\Programme\arduino-1.6.0\hardware\arduino\avr\cores\arduino" -I"D:\Programme\arduino-1.6.0\hardware\arduino\avr\variants\eightanaloginputs" -I"E:\Projekte\Elektronik\Arduino-Libs\Wire" -I"E:\Projekte\Elektronik\Arduino-Libs\Wire\utility" -I"D:\Programme\arduino-1.6.0\hardware\tools\avr\lib\gcc\avr\4.8.1" -I"D:\Programme\arduino-1.6.0\hardware\tools\avr\avr\include" -I"D:\Programme\arduino-1.6.0\hardware\tools\avr\lib\gcc\avr\4.8.1\include" -I"D:\Programme\arduino-1.6.0\hardware\tools\avr\lib\gcc\avr\4.8.1\include-fixed" -I"U:\Development\Homematic-HB\Devices\HB-UW-Mot-BL1\Firmware-Src\Libraries\NewAskSin" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -w
	@echo 'Finished building: $<'
	@echo ' '

HM-LC-Bl1-FM_AES.o: ../HM-LC-Bl1-FM_AES.ino
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"D:/Programme/arduino-1.6.0/hardware/tools/avr/bin/avr-g++" -c -g -Os -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega328p -DF_CPU=8000000L -DARDUINO=160 -DARDUINO_AVR_PRO -DARDUINO_ARCH_AVR     -I"D:\Programme\arduino-1.6.0\hardware\arduino\avr\cores\arduino" -I"D:\Programme\arduino-1.6.0\hardware\arduino\avr\variants\eightanaloginputs" -I"E:\Projekte\Elektronik\Arduino-Libs\Wire" -I"E:\Projekte\Elektronik\Arduino-Libs\Wire\utility" -I"D:\Programme\arduino-1.6.0\hardware\tools\avr\lib\gcc\avr\4.8.1" -I"D:\Programme\arduino-1.6.0\hardware\tools\avr\avr\include" -I"D:\Programme\arduino-1.6.0\hardware\tools\avr\lib\gcc\avr\4.8.1\include" -I"D:\Programme\arduino-1.6.0\hardware\tools\avr\lib\gcc\avr\4.8.1\include-fixed" -I"U:\Development\Homematic-HB\Devices\HB-UW-Mot-BL1\Firmware-Src\Libraries\NewAskSin" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -w
	@echo 'Finished building: $<'
	@echo ' '

hardware.cpp.o: ../hardware.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"D:/Programme/arduino-1.6.0/hardware/tools/avr/bin/avr-g++" -c -g -Os -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega328p -DF_CPU=8000000L -DARDUINO=160 -DARDUINO_AVR_PRO -DARDUINO_ARCH_AVR     -I"D:\Programme\arduino-1.6.0\hardware\arduino\avr\cores\arduino" -I"D:\Programme\arduino-1.6.0\hardware\arduino\avr\variants\eightanaloginputs" -I"E:\Projekte\Elektronik\Arduino-Libs\Wire" -I"E:\Projekte\Elektronik\Arduino-Libs\Wire\utility" -I"D:\Programme\arduino-1.6.0\hardware\tools\avr\lib\gcc\avr\4.8.1" -I"D:\Programme\arduino-1.6.0\hardware\tools\avr\avr\include" -I"D:\Programme\arduino-1.6.0\hardware\tools\avr\lib\gcc\avr\4.8.1\include" -I"D:\Programme\arduino-1.6.0\hardware\tools\avr\lib\gcc\avr\4.8.1\include-fixed" -I"U:\Development\Homematic-HB\Devices\HB-UW-Mot-BL1\Firmware-Src\Libraries\NewAskSin" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -w
	@echo 'Finished building: $<'
	@echo ' '


