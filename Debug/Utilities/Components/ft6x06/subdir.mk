################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Utilities/Components/ft6x06/ft6x06.c 

OBJS += \
./Utilities/Components/ft6x06/ft6x06.o 

C_DEPS += \
./Utilities/Components/ft6x06/ft6x06.d 


# Each subdirectory must supply rules for building sources it contributes
Utilities/Components/ft6x06/%.o: ../Utilities/Components/ft6x06/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32F407VGTx -DSTM32F4 -DSTM32F4DISCOVERY -DSTM32 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -I"/Users/domenicoamelino/Documents/openstm32/workspace/stm32f4_boot_puf/inc" -I"/Users/domenicoamelino/Documents/openstm32/workspace/stm32f4_boot_puf/CMSIS/core" -I"/Users/domenicoamelino/Documents/openstm32/workspace/stm32f4_boot_puf/CMSIS/device" -I"/Users/domenicoamelino/Documents/openstm32/workspace/stm32f4_boot_puf/HAL_Driver/Inc/Legacy" -I"/Users/domenicoamelino/Documents/openstm32/workspace/stm32f4_boot_puf/HAL_Driver/Inc" -I"/Users/domenicoamelino/Documents/openstm32/workspace/stm32f4_boot_puf/Utilities/Components/ampire480272" -I"/Users/domenicoamelino/Documents/openstm32/workspace/stm32f4_boot_puf/Utilities/Components/ampire640480" -I"/Users/domenicoamelino/Documents/openstm32/workspace/stm32f4_boot_puf/Utilities/Components/Common" -I"/Users/domenicoamelino/Documents/openstm32/workspace/stm32f4_boot_puf/Utilities/Components/cs43l22" -I"/Users/domenicoamelino/Documents/openstm32/workspace/stm32f4_boot_puf/Utilities/Components/exc7200" -I"/Users/domenicoamelino/Documents/openstm32/workspace/stm32f4_boot_puf/Utilities/Components/ft6x06" -I"/Users/domenicoamelino/Documents/openstm32/workspace/stm32f4_boot_puf/Utilities/Components/ili9325" -I"/Users/domenicoamelino/Documents/openstm32/workspace/stm32f4_boot_puf/Utilities/Components/ili9341" -I"/Users/domenicoamelino/Documents/openstm32/workspace/stm32f4_boot_puf/Utilities/Components/l3gd20" -I"/Users/domenicoamelino/Documents/openstm32/workspace/stm32f4_boot_puf/Utilities/Components/lis302dl" -I"/Users/domenicoamelino/Documents/openstm32/workspace/stm32f4_boot_puf/Utilities/Components/lis3dsh" -I"/Users/domenicoamelino/Documents/openstm32/workspace/stm32f4_boot_puf/Utilities/Components/lsm303dlhc" -I"/Users/domenicoamelino/Documents/openstm32/workspace/stm32f4_boot_puf/Utilities/Components/mfxstm32l152" -I"/Users/domenicoamelino/Documents/openstm32/workspace/stm32f4_boot_puf/Utilities/Components/n25q128a" -I"/Users/domenicoamelino/Documents/openstm32/workspace/stm32f4_boot_puf/Utilities/Components/n25q256a" -I"/Users/domenicoamelino/Documents/openstm32/workspace/stm32f4_boot_puf/Utilities/Components/n25q512a" -I"/Users/domenicoamelino/Documents/openstm32/workspace/stm32f4_boot_puf/Utilities/Components/otm8009a" -I"/Users/domenicoamelino/Documents/openstm32/workspace/stm32f4_boot_puf/Utilities/Components/ov2640" -I"/Users/domenicoamelino/Documents/openstm32/workspace/stm32f4_boot_puf/Utilities/Components/s25fl512s" -I"/Users/domenicoamelino/Documents/openstm32/workspace/stm32f4_boot_puf/Utilities/Components/s5k5cag" -I"/Users/domenicoamelino/Documents/openstm32/workspace/stm32f4_boot_puf/Utilities/Components/st7735" -I"/Users/domenicoamelino/Documents/openstm32/workspace/stm32f4_boot_puf/Utilities/Components/stmpe1600" -I"/Users/domenicoamelino/Documents/openstm32/workspace/stm32f4_boot_puf/Utilities/Components/stmpe811" -I"/Users/domenicoamelino/Documents/openstm32/workspace/stm32f4_boot_puf/Utilities/Components/ts3510" -I"/Users/domenicoamelino/Documents/openstm32/workspace/stm32f4_boot_puf/Utilities/Components/wm8994" -I"/Users/domenicoamelino/Documents/openstm32/workspace/stm32f4_boot_puf/Utilities" -I"/Users/domenicoamelino/Documents/openstm32/workspace/stm32f4_boot_puf/Utilities/STM32F4-Discovery" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


