# Makefile for building devkit as a shared library.
#
# Targets:
#   all      Build libdevkit.so in the root directory (default)
#   clean    Remove build artifacts

NAME      := devkit
LIB       := lib$(NAME).so

SRC_DIR   := source
INC_DIR   := include
BUILD_DIR := build

CC        ?= cc
CFLAGS    ?= -O2
CFLAGS    += -Wall -Wextra -pedantic -fPIC
CPPFLAGS  += -I$(INC_DIR) -MMD -MP
LDFLAGS   += -shared
LDLIBS    += -lm

SRCS      := $(shell find $(SRC_DIR) -name '*.c')
OBJS      := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS      := $(OBJS:.o=.d)

.PHONY: all clean

all: $(LIB)

$(LIB): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(BUILD_DIR) $(LIB)

-include $(DEPS)
