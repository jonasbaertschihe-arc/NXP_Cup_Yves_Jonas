################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/Modules/mAccelMagneto.c \
../Sources/Modules/mAd.c \
../Sources/Modules/mCpu.c \
../Sources/Modules/mDac.c \
../Sources/Modules/mDelay.c \
../Sources/Modules/mLeds.c \
../Sources/Modules/mRS232.c \
../Sources/Modules/mSpi.c \
../Sources/Modules/mSwitch.c \
../Sources/Modules/mTimer.c \
../Sources/Modules/mWifi.c 

OBJS += \
./Sources/Modules/mAccelMagneto.o \
./Sources/Modules/mAd.o \
./Sources/Modules/mCpu.o \
./Sources/Modules/mDac.o \
./Sources/Modules/mDelay.o \
./Sources/Modules/mLeds.o \
./Sources/Modules/mRS232.o \
./Sources/Modules/mSpi.o \
./Sources/Modules/mSwitch.o \
./Sources/Modules/mTimer.o \
./Sources/Modules/mWifi.o 

C_DEPS += \
./Sources/Modules/mAccelMagneto.d \
./Sources/Modules/mAd.d \
./Sources/Modules/mCpu.d \
./Sources/Modules/mDac.d \
./Sources/Modules/mDelay.d \
./Sources/Modules/mLeds.d \
./Sources/Modules/mRS232.d \
./Sources/Modules/mSpi.d \
./Sources/Modules/mSwitch.d \
./Sources/Modules/mTimer.d \
./Sources/Modules/mWifi.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/Modules/%.o: ../Sources/Modules/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"../Sources" -I"../Includes" -I"U:\Dev\KSDK - Freescale Cup\Freescale Cup 16-17\Sources\Applications" -I"U:\Dev\KSDK - Freescale Cup\Freescale Cup 16-17\Sources\Interfaces" -I"U:\Dev\KSDK - Freescale Cup\Freescale Cup 16-17\Sources\Modules" -I"U:\Dev\KSDK - Freescale Cup\Freescale Cup 16-17\Sources\Utils" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


