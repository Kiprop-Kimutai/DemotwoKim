################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../jsonfiles/arraylist.c \
../jsonfiles/debug.c \
../jsonfiles/json_object.c \
../jsonfiles/json_object_iterator.c \
../jsonfiles/json_tokener.c \
../jsonfiles/json_util.c \
../jsonfiles/linkhash.c \
../jsonfiles/printbuf.c 

OBJS += \
./jsonfiles/arraylist.o \
./jsonfiles/debug.o \
./jsonfiles/json_object.o \
./jsonfiles/json_object_iterator.o \
./jsonfiles/json_tokener.o \
./jsonfiles/json_util.o \
./jsonfiles/linkhash.o \
./jsonfiles/printbuf.o 

C_DEPS += \
./jsonfiles/arraylist.d \
./jsonfiles/debug.d \
./jsonfiles/json_object.d \
./jsonfiles/json_object_iterator.d \
./jsonfiles/json_tokener.d \
./jsonfiles/json_util.d \
./jsonfiles/linkhash.d \
./jsonfiles/printbuf.d 


# Each subdirectory must supply rules for building sources it contributes
jsonfiles/%.o: ../jsonfiles/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	/opt/compiler/glibc-oabi-toolchain-arm-generic/bin/arm-unknown-linux-gnu-gcc -I/home/pos/NEWPOS/sdk/include/fribidi -I"/home/pos/workspace/Demotwo/jsonfiles" -I"/home/pos/workspace/Demotwo/libseos/include" -I/home/pos/NEWPOS/sdk/include/directfb -I/home/pos/Downloads/NEW8210SEOS/sdk/include -I/home/pos/NEWPOS/FDx_SDK_PRO_LINUX_ARM11_OABI_3_7_1_REV922/include -I/opt/compiler/glibc-oabi-toolchain-arm-generic/include -I/opt/compiler/glibc-oabi-toolchain-arm-generic/arm-unknown-linux-gnu/sys-root/usr/include -include/home/pos/NEWPOS/FDx_SDK_PRO_LINUX_ARM11_OABI_3_7_1_REV922/include/sgfplib.h -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


