################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include arduino/core/subdir.mk
-include Libraries/Wire/utility/subdir.mk
-include Libraries/Wire/subdir.mk
-include Libraries/NewAskSin/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(INC_DEPS)),)
-include $(INC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
AR += \
U:/Development/Homematic-HB/Devices/HB-UW-Mot-BL1/Firmware-Src/Release/arduino.ar \

ELF += \
HB-UW-Mot-BL1.elf \

EEP += \
HB-UW-Mot-BL1.eep \

FLASH_IMAGE += \
HB-UW-Mot-BL1.hex \


# All Target
all: HB-UW-Mot-BL1

# Tool invocations
HB-UW-Mot-BL1: $(FLASH_IMAGE)
	@echo 'Building target: $@'
	@echo 'Printing size:'
	"D:/Programme/arduino-1.6.0/hardware/tools/avr/bin/avr-size" --format=avr --mcu=atmega328p "U:/Development/Homematic-HB/Devices/HB-UW-Mot-BL1/Firmware-Src/Release/HB-UW-Mot-BL1.elf"
	@echo 'Finished building target: $@'
	@echo ' '

U:/Development/Homematic-HB/Devices/HB-UW-Mot-BL1/Firmware-Src/Release/arduino.ar: $(AR_OBJ)
	@echo 'Starting archiver'
	"D:/Programme/arduino-1.6.0/hardware/tools/avr/bin/avr-ar" rcs  "U:/Development/Homematic-HB/Devices/HB-UW-Mot-BL1/Firmware-Src/Release/arduino.ar"   $(AR_OBJ)
	@echo 'Finished building: $@'
	@echo ' '

HB-UW-Mot-BL1.elf: $(LINK_OBJ) $(AR)
	@echo 'Starting combiner'
	"D:/Programme/arduino-1.6.0/hardware/tools/avr/bin/avr-gcc" -Os -Wl,--gc-sections -mmcu=atmega328p  -o "U:/Development/Homematic-HB/Devices/HB-UW-Mot-BL1/Firmware-Src/Release/HB-UW-Mot-BL1.elf"   $(LINK_OBJ) $(AR)  "U:/Development/Homematic-HB/Devices/HB-UW-Mot-BL1/Firmware-Src/Release/arduino.ar" "-LU:/Development/Homematic-HB/Devices/HB-UW-Mot-BL1/Firmware-Src/Release" -lm
	@echo 'Finished building: $@'
	@echo ' '

HB-UW-Mot-BL1.eep: $(ELF)
	@echo 'Create eeprom image'
	"D:/Programme/arduino-1.6.0/hardware/tools/avr/bin/avr-objcopy" -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0  "U:/Development/Homematic-HB/Devices/HB-UW-Mot-BL1/Firmware-Src/Release/HB-UW-Mot-BL1.elf" "U:/Development/Homematic-HB/Devices/HB-UW-Mot-BL1/Firmware-Src/Release/HB-UW-Mot-BL1.eep"
	@echo 'Finished building: $@'
	@echo ' '

HB-UW-Mot-BL1.hex: $(EEP)
	@echo 'Create Flash image (ihex format)'
	"D:/Programme/arduino-1.6.0/hardware/tools/avr/bin/avr-objcopy" -O ihex -R .eeprom  "U:/Development/Homematic-HB/Devices/HB-UW-Mot-BL1/Firmware-Src/Release/HB-UW-Mot-BL1.elf" "U:/Development/Homematic-HB/Devices/HB-UW-Mot-BL1/Firmware-Src/Release/HB-UW-Mot-BL1.hex"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(AR)$(C_DEPS)$(FLASH_IMAGE)$(INC_DEPS)$(EEP)$(CXX_DEPS)$(S_UPPER_DEPS)$(ELF)$(C++_DEPS)$(ASM_DEPS)$(CC_DEPS)$(INO_DEPS)$(AR_OBJ)$(CPP_DEPS)$(LINK_OBJ)$(C_UPPER_DEPS)$(SIZEDUMMY) HB-UW-Mot-BL1
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
