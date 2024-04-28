CXX := i686-elf-gcc
CC := i686-elf-gcc
NATIVECC := gcc
ASM := nasm
BUILD_DIR := $(shell pwd)/build
OUT_DIR := $(shell pwd)/final
SDK := $(shell pwd)/sdk
SRC := $(shell pwd)/src
BOOT := $(SRC)/boot
ENGINE := $(SDK)/engine.mk

OUTS := $(addprefix $(OUT_DIR)/,$(shell cat $(SDK)/system.txt))

export CXX
export CC
export ASM
export SRC # SRC and SRCS are not the same!!!
export SDK
export BUILD_DIR
export OUT_DIR
export BOOT
export ENGINE
export NATIVECC

.SILENT:
all: 
	mkdir -p final/
	mkdir -p build/
	mkdir -p $(OUTS)
	$(MAKE) -C $(SRC)/core
	$(MAKE) -f $(SDK)/cd.mk
	$(MAKE) -C $(SRC)/boot
	echo
	echo successfuly built!
	
.SILENT:
clean:
	rm -rf ./build ./final