################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../zint-master/backend/2of5.c \
../zint-master/backend/auspost.c \
../zint-master/backend/aztec.c \
../zint-master/backend/code.c \
../zint-master/backend/code1.c \
../zint-master/backend/code128.c \
../zint-master/backend/code16k.c \
../zint-master/backend/code49.c \
../zint-master/backend/common.c \
../zint-master/backend/composite.c \
../zint-master/backend/dllversion.c \
../zint-master/backend/dmatrix.c \
../zint-master/backend/gridmtx.c \
../zint-master/backend/gs1.c \
../zint-master/backend/imail.c \
../zint-master/backend/large.c \
../zint-master/backend/library.c \
../zint-master/backend/maxicode.c \
../zint-master/backend/medical.c \
../zint-master/backend/pdf417.c \
../zint-master/backend/plessey.c \
../zint-master/backend/png.c \
../zint-master/backend/postal.c \
../zint-master/backend/ps.c \
../zint-master/backend/qr.c \
../zint-master/backend/reedsol.c \
../zint-master/backend/render.c \
../zint-master/backend/rss.c \
../zint-master/backend/svg.c \
../zint-master/backend/telepen.c \
../zint-master/backend/upcean.c 

OBJS += \
./zint-master/backend/2of5.o \
./zint-master/backend/auspost.o \
./zint-master/backend/aztec.o \
./zint-master/backend/code.o \
./zint-master/backend/code1.o \
./zint-master/backend/code128.o \
./zint-master/backend/code16k.o \
./zint-master/backend/code49.o \
./zint-master/backend/common.o \
./zint-master/backend/composite.o \
./zint-master/backend/dllversion.o \
./zint-master/backend/dmatrix.o \
./zint-master/backend/gridmtx.o \
./zint-master/backend/gs1.o \
./zint-master/backend/imail.o \
./zint-master/backend/large.o \
./zint-master/backend/library.o \
./zint-master/backend/maxicode.o \
./zint-master/backend/medical.o \
./zint-master/backend/pdf417.o \
./zint-master/backend/plessey.o \
./zint-master/backend/png.o \
./zint-master/backend/postal.o \
./zint-master/backend/ps.o \
./zint-master/backend/qr.o \
./zint-master/backend/reedsol.o \
./zint-master/backend/render.o \
./zint-master/backend/rss.o \
./zint-master/backend/svg.o \
./zint-master/backend/telepen.o \
./zint-master/backend/upcean.o 

C_DEPS += \
./zint-master/backend/2of5.d \
./zint-master/backend/auspost.d \
./zint-master/backend/aztec.d \
./zint-master/backend/code.d \
./zint-master/backend/code1.d \
./zint-master/backend/code128.d \
./zint-master/backend/code16k.d \
./zint-master/backend/code49.d \
./zint-master/backend/common.d \
./zint-master/backend/composite.d \
./zint-master/backend/dllversion.d \
./zint-master/backend/dmatrix.d \
./zint-master/backend/gridmtx.d \
./zint-master/backend/gs1.d \
./zint-master/backend/imail.d \
./zint-master/backend/large.d \
./zint-master/backend/library.d \
./zint-master/backend/maxicode.d \
./zint-master/backend/medical.d \
./zint-master/backend/pdf417.d \
./zint-master/backend/plessey.d \
./zint-master/backend/png.d \
./zint-master/backend/postal.d \
./zint-master/backend/ps.d \
./zint-master/backend/qr.d \
./zint-master/backend/reedsol.d \
./zint-master/backend/render.d \
./zint-master/backend/rss.d \
./zint-master/backend/svg.d \
./zint-master/backend/telepen.d \
./zint-master/backend/upcean.d 


# Each subdirectory must supply rules for building sources it contributes
zint-master/backend/%.o: ../zint-master/backend/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	/opt/compiler/glibc-oabi-toolchain-arm-generic/bin/arm-unknown-linux-gnu-gcc -I/home/pos/Downloads/NEW8210SEOS/sdk/include -I/home/pos/NEWPOS/FDx_SDK_PRO_LINUX_ARM11_OABI_3_7_1_REV922/include -I/opt/compiler/glibc-oabi-toolchain-arm-generic/include -I/opt/compiler/glibc-oabi-toolchain-arm-generic/arm-unknown-linux-gnu/sys-root/usr/include -I/home/pos/NEWPOS/sdk/include/fribidi -I"/home/pos/workspace/Demotwo/jsonfiles" -I"/home/pos/workspace/Demotwo/libseos/include" -I/home/pos/NEWPOS/sdk/include/directfb -include/home/pos/NEWPOS/FDx_SDK_PRO_LINUX_ARM11_OABI_3_7_1_REV922/include/sgfplib.h -O0 -g3 -Wall -Wundef -Wstrict-prototypes -Werror-implicit-function-declaration -Wdeclaration-after-statement -fsigned-char -marm -mapcs -mno-sched-prolog -mabi=apcs-gnu -mlittle-endian -mno-thumb-interwork -msoft-float -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


