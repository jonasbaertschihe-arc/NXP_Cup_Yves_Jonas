################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/Interfaces/iAd.c \
../Sources/Interfaces/iCpu.c \
../Sources/Interfaces/iDac.c \
../Sources/Interfaces/iDio.c \
../Sources/Interfaces/iFlextimer.c \
../Sources/Interfaces/iI2C.c \
../Sources/Interfaces/iPit.c \
../Sources/Interfaces/iSpi.c \
../Sources/Interfaces/iUart.c 

OBJS += \
./Sources/Interfaces/iAd.o \
./Sources/Interfaces/iCpu.o \
./Sources/Interfaces/iDac.o \
./Sources/Interfaces/iDio.o \
./Sources/Interfaces/iFlextimer.o \
./Sources/Interfaces/iI2C.o \
./Sources/Interfaces/iPit.o \
./Sources/Interfaces/iSpi.o \
./Sources/Interfaces/iUart.o 

C_DEPS += \
./Sources/Interfaces/iAd.d \
./Sources/Interfaces/iCpu.d \
./Sources/Interfaces/iDac.d \
./Sources/Interfaces/iDio.d \
./Sources/Interfaces/iFlextimer.d \
./Sources/Interfaces/iI2C.d \
./Sources/Interfaces/iPit.d \
./Sources/Interfaces/iSpi.d \
./Sources/Interfaces/iUart.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/Interfaces/%.o: ../Sources/Interfaces/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"../Sources" -I"../Includes" -I"U:\Dev\KSDK - Freescale Cup\Freescale Cup 16-17\Sources\Applications" -I"U:\Dev\KSDK - Freescale Cup\Freescale Cup 16-17\Sources\Interfaces" -I"U:\Dev\KSDK - Freescale Cup\Freescale Cup 16-17\Sources\Modules" -I"U:\Dev\KSDK - Freescale Cup\Freescale Cup 16-17\Sources\Utils" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


