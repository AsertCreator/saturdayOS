TARGET_EXEC := satkrnl
BUILD_DIR := $(BUILD_DIR)/$(TARGET_EXEC)
CPPFLAGS := $(INC_FLAGS) -MMD -MP -Wall -Wextra -Werror -fms-extensions -nostdlib -ffreestanding -mgeneral-regs-only -mno-red-zone -O0
LDFLAGS := -T $(SDK)/kernel.ld -shared -ffreestanding -nostdlib -lgcc -O0
OUTTARGET := /sys/core

-include $(ENGINE)
-include $(DEPS)