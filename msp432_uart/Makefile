# Defines the part type that this project uses.
DEVICE=__MSP432P401R__

# The base directory for MSPWare.
ROOT=drivers/

# The compiler to be used.
ifndef CROSS
$(info Please set CROSS compiler, e.g. CROSS=1)
$(error unspecified compiler)
endif

ifeq ($(CROSS), 1)
# Include the common make definitions.
include Makefile.defs
endif


# Where to find header files that do not live in the source directory.
IPATH=drivers
IPATH+=drivers/inc/
IPATH+=drivers/inc/CMSIS/
IPATH+=drivers/driverlib/MSP432P4xx

SRC_C = \
	startup_msp432p401r_${COMPILER}.c \
	system_msp432p401r.c \
	uart.c \

#
# The default rule, which causes the firmware to be built.
#
all: ${COMPILER}
all: ${COMPILER}/firmware.axf

#
# The rule to clean out all the build products.
#
clean:
	@rm -rf ${COMPILER} ${wildcard *~}

#
# The rule to create the target directory.
#
${COMPILER}:
	@mkdir -p ${COMPILER}

#
# Rules for building the examples.
#
#${COMPILER}/firmware.axf: ${COMPILER}/startup_msp432p401r_${COMPILER}.o
#${COMPILER}/firmware.axf: ${COMPILER}/system_msp432p401r.o
#${COMPILER}/firmware.axf: ${COMPILER}/blink.o
${COMPILER}/firmware.axf: $(addprefix $(COMPILER)/, $(SRC_C:.c=.o))
${COMPILER}/firmware.axf: ${ROOT}/driverlib/MSP432P4xx/${COMPILER}/msp432p4xx_driverlib.a
${COMPILER}/firmware.axf: msp432p401r.ld
SCATTERgcc_firmware=msp432p401r.ld
ENTRY_firmware=resetISR
CFLAGSgcc=-DTARGET_IS_MSP432P4XX

#
# Include the automatically generated dependency files.
#
ifneq (${MAKECMDGOALS},clean)
-include ${wildcard ${COMPILER}/*.d} __dummy__
endif
