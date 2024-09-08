################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Device_Devices/ADXL_345_accelerometer/ADXL_345_accelerometer.c 

OBJS += \
./Drivers/Device_Devices/ADXL_345_accelerometer/ADXL_345_accelerometer.o 

C_DEPS += \
./Drivers/Device_Devices/ADXL_345_accelerometer/ADXL_345_accelerometer.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Device_Devices/ADXL_345_accelerometer/%.o Drivers/Device_Devices/ADXL_345_accelerometer/%.su Drivers/Device_Devices/ADXL_345_accelerometer/%.cyclo: ../Drivers/Device_Devices/ADXL_345_accelerometer/%.c Drivers/Device_Devices/ADXL_345_accelerometer/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-Device_Devices-2f-ADXL_345_accelerometer

clean-Drivers-2f-Device_Devices-2f-ADXL_345_accelerometer:
	-$(RM) ./Drivers/Device_Devices/ADXL_345_accelerometer/ADXL_345_accelerometer.cyclo ./Drivers/Device_Devices/ADXL_345_accelerometer/ADXL_345_accelerometer.d ./Drivers/Device_Devices/ADXL_345_accelerometer/ADXL_345_accelerometer.o ./Drivers/Device_Devices/ADXL_345_accelerometer/ADXL_345_accelerometer.su

.PHONY: clean-Drivers-2f-Device_Devices-2f-ADXL_345_accelerometer

