################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/Utils/StTime.c \
../Sources/Utils/stbp.c 

OBJS += \
./Sources/Utils/StTime.o \
./Sources/Utils/stbp.o 

C_DEPS += \
./Sources/Utils/StTime.d \
./Sources/Utils/stbp.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/Utils/%.o: ../Sources/Utils/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"../Sources" -I"../Includes" -I"U:\Dev\KSDK - Freescale Cup\Freescale Cup 16-17\Sources\Applications" -I"U:\Dev\KSDK - Freescale Cup\Freescale Cup 16-17\Sources\Interfaces" -I"U:\Dev\KSDK - Freescale Cup\Freescale Cup 16-17\Sources\Modules" -I"U:\Dev\KSDK - Freescale Cup\Freescale Cup 16-17\Sources\Utils" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


