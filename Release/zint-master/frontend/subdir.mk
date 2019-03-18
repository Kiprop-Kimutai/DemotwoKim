################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../zint-master/frontend/getopt.c \
../zint-master/frontend/getopt1.c 

OBJS += \
./zint-master/frontend/getopt.o \
./zint-master/frontend/getopt1.o 

C_DEPS += \
./zint-master/frontend/getopt.d \
./zint-master/frontend/getopt1.d 


# Each subdirectory must supply rules for building sources it contributes
zint-master/frontend/%.o: ../zint-master/frontend/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	/opt/compiler/glibc-oabi-toolchain-arm-generic/bin/arm-unknown-linux-gnu-gcc -I/home/pos/NEWPOS/sdk/include/fribidi -I"/home/pos/workspace/Demotwo/jsonfiles" -I"/home/pos/workspace/Demotwo/libseos/include" -I/home/pos/NEWPOS/sdk/include/directfb -I/home/pos/Downloads/NEW8210SEOS/sdk/include -I/home/pos/NEWPOS/FDx_SDK_PRO_LINUX_ARM11_OABI_3_7_1_REV922/include -I/opt/compiler/glibc-oabi-toolchain-arm-generic/include -I/opt/compiler/glibc-oabi-toolchain-arm-generic/arm-unknown-linux-gnu/sys-root/usr/include -include/home/pos/NEWPOS/FDx_SDK_PRO_LINUX_ARM11_OABI_3_7_1_REV922/include/sgfplib.h -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


