################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../utilities/fsl_assert.c \
../utilities/fsl_debug_console.c \
../utilities/fsl_str.c 

OBJS += \
./utilities/fsl_assert.o \
./utilities/fsl_debug_console.o \
./utilities/fsl_str.o 

C_DEPS += \
./utilities/fsl_assert.d \
./utilities/fsl_debug_console.d \
./utilities/fsl_str.d 


# Each subdirectory must supply rules for building sources it contributes
utilities/%.o: ../utilities/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MIMXRT1052DVL6B -DCPU_MIMXRT1052DVL6B_cm7 -DSDK_DEBUGCONSOLE=1 -DPRINTF_FLOAT_ENABLE=0 -DSCANF_FLOAT_ENABLE=0 -DPRINTF_ADVANCED_ENABLE=0 -DSCANF_ADVANCED_ENABLE=0 -DXIP_EXTERNAL_FLASH=1 -DXIP_BOOT_HEADER_ENABLE=1 -DFSL_RTOS_FREE_RTOS -DCR_INTEGER_PRINTF -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DSERIAL_PORT_TYPE_UART=1 -I"/Users/stlp/Desktop/CubeSat/soci_cdh_rtos/cdh_peripherals_test/drivers" -I"/Users/stlp/Desktop/CubeSat/soci_cdh_rtos/cdh_peripherals_test/utilities" -I"/Users/stlp/Desktop/CubeSat/soci_cdh_rtos/cdh_peripherals_test/device" -I"/Users/stlp/Desktop/CubeSat/soci_cdh_rtos/cdh_peripherals_test/CMSIS" -I"/Users/stlp/Desktop/CubeSat/soci_cdh_rtos/cdh_peripherals_test/xip" -I"/Users/stlp/Desktop/CubeSat/soci_cdh_rtos/cdh_peripherals_test/component/serial_manager" -I"/Users/stlp/Desktop/CubeSat/soci_cdh_rtos/cdh_peripherals_test/component/lists" -I"/Users/stlp/Desktop/CubeSat/soci_cdh_rtos/cdh_peripherals_test/component/uart" -I"/Users/stlp/Desktop/CubeSat/soci_cdh_rtos/cdh_peripherals_test/drivers" -I"/Users/stlp/Desktop/CubeSat/soci_cdh_rtos/cdh_peripherals_test/utilities" -I"/Users/stlp/Desktop/CubeSat/soci_cdh_rtos/cdh_peripherals_test/device" -I"/Users/stlp/Desktop/CubeSat/soci_cdh_rtos/cdh_peripherals_test/CMSIS" -I"/Users/stlp/Desktop/CubeSat/soci_cdh_rtos/cdh_peripherals_test/xip" -I"/Users/stlp/Desktop/CubeSat/soci_cdh_rtos/cdh_peripherals_test/component/serial_manager" -I"/Users/stlp/Desktop/CubeSat/soci_cdh_rtos/cdh_peripherals_test/component/lists" -I"/Users/stlp/Desktop/CubeSat/soci_cdh_rtos/cdh_peripherals_test/component/uart" -I../board -I../drivers/freertos -I../source -I../ -I../drivers -I../device -I../CMSIS -I../amazon-freertos/include -I../amazon-freertos/FreeRTOS/portable -I../utilities -I../component/serial_manager -I../component/uart -I../component/lists -I../xip -O0 -fno-common -g3 -Wall -c  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m7 -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


