SRCS := $(shell find $(SRC_DIRS) -name '*.c' -or -name '*.asm')
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)
INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

.SILENT:
$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	echo [$(TARGET_EXEC)] linking $@...
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)
	echo [$(TARGET_EXEC)] adding $@...
	cp $@ $(addprefix $(OUT_DIR)/,$(OUTTARGET))

.SILENT:
$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	echo [$(TARGET_EXEC)] building $@...
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

.SILENT:
$(BUILD_DIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	echo [$(TARGET_EXEC)] building $@...
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

.SILENT:
$(BUILD_DIR)/%.asm.o: %.asm
	mkdir -p $(dir $@)
	echo [$(TARGET_EXEC)] building $@...
	$(ASM) $< -felf32 -o $@
