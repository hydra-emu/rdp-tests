BUILD_DIR=build
SOURCE_DIR=.
ROM_NAME=joined_primitives
N64_ROM_TITLE="Joined primitives"

include $(N64_INST)/include/n64.mk
N64_CXXFLAGS += -I../../include -std=c++14

all: $(ROM_NAME).z64

OBJS = $(BUILD_DIR)/$(ROM_NAME).o

$(BUILD_DIR)/$(ROM_NAME).elf: $(OBJS)

clean:
	rm -rf $(BUILD_DIR) $(ROM_NAME).z64

-include $(wildcard $(BUILD_DIR)/*.d)

.PHONY: all clean
