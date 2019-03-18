################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src1/ContactSmartCard.c \
../src1/JSON_checker.c \
../src1/Z_report.c \
../src1/cJSON.c \
../src1/cardinfo.c \
../src1/cl_smartcard_demo.c \
../src1/configurations.c \
../src1/desfire_test.c \
../src1/display.c \
../src1/fp_test.c \
../src1/gprs_demo.c \
../src1/jsonread.c \
../src1/jsontest.c \
../src1/keyboart.c \
../src1/lcd.c \
../src1/magneticstrip_demo.c \
../src1/main.c \
../src1/menu_back_forth.c \
../src1/menu_hash.c \
../src1/modem_demo.c \
../src1/mutwol.c \
../src1/network_f.c \
../src1/postslib_extern.c \
../src1/printer_demo.c \
../src1/receipt.c \
../src1/socket_demo.c \
../src1/sql_functions.c \
../src1/string_convert.c \
../src1/touch.c \
../src1/touch_demo.c \
../src1/transaction.c \
../src1/uart_demo.c \
../src1/video.c \
../src1/visualstring.c 

OBJS += \
./src1/ContactSmartCard.o \
./src1/JSON_checker.o \
./src1/Z_report.o \
./src1/cJSON.o \
./src1/cardinfo.o \
./src1/cl_smartcard_demo.o \
./src1/configurations.o \
./src1/desfire_test.o \
./src1/display.o \
./src1/fp_test.o \
./src1/gprs_demo.o \
./src1/jsonread.o \
./src1/jsontest.o \
./src1/keyboart.o \
./src1/lcd.o \
./src1/magneticstrip_demo.o \
./src1/main.o \
./src1/menu_back_forth.o \
./src1/menu_hash.o \
./src1/modem_demo.o \
./src1/mutwol.o \
./src1/network_f.o \
./src1/postslib_extern.o \
./src1/printer_demo.o \
./src1/receipt.o \
./src1/socket_demo.o \
./src1/sql_functions.o \
./src1/string_convert.o \
./src1/touch.o \
./src1/touch_demo.o \
./src1/transaction.o \
./src1/uart_demo.o \
./src1/video.o \
./src1/visualstring.o 

C_DEPS += \
./src1/ContactSmartCard.d \
./src1/JSON_checker.d \
./src1/Z_report.d \
./src1/cJSON.d \
./src1/cardinfo.d \
./src1/cl_smartcard_demo.d \
./src1/configurations.d \
./src1/desfire_test.d \
./src1/display.d \
./src1/fp_test.d \
./src1/gprs_demo.d \
./src1/jsonread.d \
./src1/jsontest.d \
./src1/keyboart.d \
./src1/lcd.d \
./src1/magneticstrip_demo.d \
./src1/main.d \
./src1/menu_back_forth.d \
./src1/menu_hash.d \
./src1/modem_demo.d \
./src1/mutwol.d \
./src1/network_f.d \
./src1/postslib_extern.d \
./src1/printer_demo.d \
./src1/receipt.d \
./src1/socket_demo.d \
./src1/sql_functions.d \
./src1/string_convert.d \
./src1/touch.d \
./src1/touch_demo.d \
./src1/transaction.d \
./src1/uart_demo.d \
./src1/video.d \
./src1/visualstring.d 


# Each subdirectory must supply rules for building sources it contributes
src1/%.o: ../src1/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	/opt/compiler/glibc-oabi-toolchain-arm-generic/bin/arm-unknown-linux-gnu-gcc -I/home/pos/Downloads/NEW8210SEOS/sdk/include -I/home/pos/NEWPOS/FDx_SDK_PRO_LINUX_ARM11_OABI_3_7_1_REV922/include -I/opt/compiler/glibc-oabi-toolchain-arm-generic/include -I/opt/compiler/glibc-oabi-toolchain-arm-generic/arm-unknown-linux-gnu/sys-root/usr/include -I/home/pos/NEWPOS/sdk/include/fribidi -I"/home/pos/workspace/Demotwo/jsonfiles" -I"/home/pos/workspace/Demotwo/libseos/include" -I/home/pos/NEWPOS/sdk/include/directfb -include/home/pos/NEWPOS/FDx_SDK_PRO_LINUX_ARM11_OABI_3_7_1_REV922/include/sgfplib.h -O0 -g3 -Wall -Wundef -Wstrict-prototypes -Werror-implicit-function-declaration -Wdeclaration-after-statement -fsigned-char -marm -mapcs -mno-sched-prolog -mabi=apcs-gnu -mlittle-endian -mno-thumb-interwork -msoft-float -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


