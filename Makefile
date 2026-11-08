CC := gcc

CFLAGS := \
	-Wall \
	-Wextra \
	-pedantic \
	-std=c89 \
	-fPIC \
	-lm

LDFLAGS :=

INCLUDES := \
	-Iinclude \
	-Ithird_party/unity/src

BUILD_DIR := build

LIB_NAME := vasall
LIBRARY := $(BUILD_DIR)/lib$(LIB_NAME).so

UNITY_SRC := third_party/unity/src/unity.c

#
# Library sources
#

SRC := $(shell find source -type f -name '*.c')

OBJ := $(patsubst source/%.c,$(BUILD_DIR)/obj/%.o,$(SRC))

#
# Tests
#

TEST_SRC := $(shell find tests -type f -name '*.c')

TEST_BIN := \
	$(patsubst tests/%.c,$(BUILD_DIR)/tests/%,$(TEST_SRC))

#
# Default target
#

.PHONY: all
all: $(LIBRARY) $(TEST_BIN)

#
# Shared library
#

$(LIBRARY): $(OBJ)
	@mkdir -p $(dir $@)
	$(CC) -shared -o $@ $^

#
# Library object files
#

$(BUILD_DIR)/obj/%.o: source/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

#
# Test executables
#

$(BUILD_DIR)/tests/%: tests/%.c $(LIBRARY)
	@mkdir -p $(dir $@)

	$(CC) \
		$(CFLAGS) \
		$(INCLUDES) \
		$< \
		$(UNITY_SRC) \
		-L$(BUILD_DIR) \
		-l$(LIB_NAME) \
		-Wl,-rpath,'$$ORIGIN/../..' \
		-o $@

#
# Run all tests
#

.PHONY: test
test: $(TEST_BIN)
	@for test in $(TEST_BIN); do \
		echo ""; \
		echo "========================================"; \
		echo "Running $$test"; \
		echo "========================================"; \
		$$test || exit 1; \
	done

#
# Clean
#

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

#
# Show discovered files
#

.PHONY: info
info:
	@echo "Sources:"
	@printf "  %s\n" $(SRC)

	@echo ""
	@echo "Tests:"
	@printf "  %s\n" $(TEST_SRC)
