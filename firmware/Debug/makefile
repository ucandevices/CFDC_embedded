################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include Middlewares/ST/STM32_USB_Device_Library/Core/Src/subdir.mk
-include Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/subdir.mk
-include Drivers/STM32G4xx_HAL_Driver/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
CDC_libUSB_basic.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
CDC_libUSB_basic.list \

OBJCOPY_BIN += \
CDC_libUSB_basic.bin \


# All Target
all: CDC_libUSB_basic.elf secondary-outputs

# Tool invocations
CDC_libUSB_basic.elf: $(OBJS) $(USER_OBJS) F:\CANFD_firmware\CFDC_embedded\firmware\STM32G431CBUX_FLASH.ld
	arm-none-eabi-gcc -o "CDC_libUSB_basic.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"F:\CANFD_firmware\CFDC_embedded\firmware\STM32G431CBUX_FLASH.ld" --specs=nosys.specs -Wl,-Map="CDC_libUSB_basic.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

CDC_libUSB_basic.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "CDC_libUSB_basic.list"
	@echo 'Finished building: $@'
	@echo ' '

CDC_libUSB_basic.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "CDC_libUSB_basic.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
