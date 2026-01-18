BUILD_DIR ?= build
BIN_DIR   ?= bin
SRC_DIR   ?= src

$(BUILD_DIR)/liblogga.a: $(BUILD_DIR)/logga.o | $(BUILD_DIR)
	ar rcs $@ $^

$(BUILD_DIR)/logga.o: $(SRC_DIR)/logga.c | $(BUILD_DIR)
	clang -c -O3 -Iinclude -Wall -Wextra -pedantic -o $@ $<

$(BIN_DIR)/test: $(BUILD_DIR)/test.o $(BUILD_DIR)/liblogga.a | $(BIN_DIR)
	clang -L$(BUILD_DIR) -llogga -Wall -Wextra -pedantic -o $@ $<

$(BUILD_DIR)/test.o: $(SRC_DIR)/test.c | $(BUILD_DIR)
	clang -c -Iinclude -Wall -Wextra -pedantic -o $@ $<

.PHONY: all lib test clean

all: lib test

lib: $(BUILD_DIR)/liblogga.a

test: $(BIN_DIR)/test

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

$(BUILD_DIR):
	mkdir -p $@

$(BIN_DIR):
	mkdir -p $@
