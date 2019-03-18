################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include zint-master/frontend/subdir.mk
-include zint-master/backend/subdir.mk
-include src1/subdir.mk
-include jsonfiles/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: Demotwo

# Tool invocations
Demotwo: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross GCC Linker'
	/opt/compiler/glibc-oabi-toolchain-arm-generic/bin/arm-unknown-linux-gnu-gcc -L/home/pos/NEWPOS/sdk/lib -L/home/pos/NEWPOS/FDx_SDK_PRO_LINUX_ARM11_OABI_3_7_1_REV922/lib/arm11_oabi -L"/home/pos/workspace/Demotwo/libseos/lib" -marm -mapcs -mno-sched-prolog -mabi=apcs-gnu -mlittle-endian -mno-thumb-interwork -msoft-float -Wl,-Map,"/home/pos/workspace/Demotwo/Debug/Demotwo.map" -o "Demotwo" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) Demotwo
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
