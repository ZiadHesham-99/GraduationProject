################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/MCAL/ADC_program.c \
../src/MCAL/GPIO_config.c \
../src/MCAL/GPIO_program.c \
../src/MCAL/I2C_config.c \
../src/MCAL/I2C_program.c \
../src/MCAL/NVIC_program.c \
../src/MCAL/RCC_program.c \
../src/MCAL/SPI_program.c \
../src/MCAL/SYSTICK_program.c \
../src/MCAL/TIMER_config.c \
../src/MCAL/TIMER_program.c \
../src/MCAL/UART_program.c 

OBJS += \
./src/MCAL/ADC_program.o \
./src/MCAL/GPIO_config.o \
./src/MCAL/GPIO_program.o \
./src/MCAL/I2C_config.o \
./src/MCAL/I2C_program.o \
./src/MCAL/NVIC_program.o \
./src/MCAL/RCC_program.o \
./src/MCAL/SPI_program.o \
./src/MCAL/SYSTICK_program.o \
./src/MCAL/TIMER_config.o \
./src/MCAL/TIMER_program.o \
./src/MCAL/UART_program.o 

C_DEPS += \
./src/MCAL/ADC_program.d \
./src/MCAL/GPIO_config.d \
./src/MCAL/GPIO_program.d \
./src/MCAL/I2C_config.d \
./src/MCAL/I2C_program.d \
./src/MCAL/NVIC_program.d \
./src/MCAL/RCC_program.d \
./src/MCAL/SPI_program.d \
./src/MCAL/SYSTICK_program.d \
./src/MCAL/TIMER_config.d \
./src/MCAL/TIMER_program.d \
./src/MCAL/UART_program.d 


# Each subdirectory must supply rules for building sources it contributes
src/MCAL/%.o: ../src/MCAL/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F401xC -DUSE_HAL_DRIVER -DHSE_VALUE=25000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


