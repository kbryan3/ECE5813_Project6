################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/adc.c \
../source/circularbuffer.c \
../source/dac.c \
../source/led_control.c \
../source/logger.c \
../source/main.c \
../source/mtb.c \
../source/program1.c \
../source/program2.c \
../source/semihost_hardfault.c 

OBJS += \
./source/adc.o \
./source/circularbuffer.o \
./source/dac.o \
./source/led_control.o \
./source/logger.o \
./source/main.o \
./source/mtb.o \
./source/program1.o \
./source/program2.o \
./source/semihost_hardfault.o 

C_DEPS += \
./source/adc.d \
./source/circularbuffer.d \
./source/dac.d \
./source/led_control.d \
./source/logger.d \
./source/main.d \
./source/mtb.d \
./source/program1.d \
./source/program2.d \
./source/semihost_hardfault.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DSDK_OS_BAREMETAL -DFSL_RTOS_BM -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DFSL_RTOS_FREE_RTOS -DSDK_OS_FREE_RTOS -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I../board -I../source -I../ -I../freertos -I../drivers -I../CMSIS -I../utilities -I../startup -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


