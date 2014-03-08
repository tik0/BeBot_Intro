################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/BeBot_Intro.cpp \
../src/MatConverter.cpp 

OBJS += \
./src/BeBot_Intro.o \
./src/MatConverter.o 

CPP_DEPS += \
./src/BeBot_Intro.d \
./src/MatConverter.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-poky-linux-gnueabi-g++  -march=armv7-a -mthumb-interwork -mfloat-abi=hard -mfpu=neon -mtune=cortex-a8 --sysroot=/opt/poky/1.5+snapshot_neon/sysroots/cortexa8hf-vfp-neon-poky-linux-gnueabi -I/opt/poky/1.3+snapshot/sysroots/armv7a-vfp-neon-poky-linux-gnueabi/usr/include -I/opt/poky/1.3+snapshot/sysroots/armv7a-vfp-neon-poky-linux-gnueabi/usr/include/rsb -O0 -g3 -Wall -c -fmessage-length=0 `pkg-config --cflags libv4l2 rsb opencv` -Wno-write-strings -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


