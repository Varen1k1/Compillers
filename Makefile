# Makefile for the Kotlin validator built with Flex + Bison.
#
# Common targets:
#   make            - build build/kotlin_parser
#   make test       - build and run all tests/*.kt files
#   make clean      - remove generated files in build/
#   make rebuild    - clean + build
#
# Usage examples:
#   ./build/kotlin_parser tests/test_basic.kt
#   make test

CC      := gcc
BISON   := bison
FLEX    := flex
CFLAGS  := -O2 -Wall -Wno-unused-function

SRC_DIR   := src
BUILD_DIR := build
TESTS_DIR := tests

PARSER_Y  := $(SRC_DIR)/parser.y
LEXER_L   := $(SRC_DIR)/lexer.l

PARSER_C  := $(BUILD_DIR)/parser.tab.c
PARSER_H  := $(BUILD_DIR)/parser.tab.h
LEXER_C   := $(BUILD_DIR)/lex.yy.c

BIN       := $(BUILD_DIR)/kotlin_parser

.PHONY: all clean rebuild test test-quiet

all: $(BIN)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(PARSER_C) $(PARSER_H): $(PARSER_Y) | $(BUILD_DIR)
	cd $(BUILD_DIR) && $(BISON) -d -o parser.tab.c ../$(PARSER_Y)

$(LEXER_C): $(LEXER_L) $(PARSER_H) | $(BUILD_DIR)
	cd $(BUILD_DIR) && $(FLEX) -o lex.yy.c ../$(LEXER_L)

$(BIN): $(PARSER_C) $(LEXER_C)
	$(CC) $(CFLAGS) -o $(BIN) $(PARSER_C) $(LEXER_C)

clean:
	rm -f $(BUILD_DIR)/*.c $(BUILD_DIR)/*.h $(BUILD_DIR)/*.output $(BIN)

rebuild: clean all

# Run all tests/*.kt files, summarise pass/fail.
test: $(BIN)
	@echo "Running test suite..."
	@echo "----------------------------------------"
	@pass=0; fail=0; \
	for f in $(TESTS_DIR)/*.kt; do \
	    result=$$($(BIN) "$$f" 2>&1 | grep -E "^Result:" | head -1); \
	    name=$$(basename "$$f"); \
	    printf "%-28s %s\n" "$$name" "$$result"; \
	    if echo "$$result" | grep -q SUCCESS; then pass=$$((pass+1)); else fail=$$((fail+1)); fi; \
	done; \
	echo "----------------------------------------"; \
	echo "pass=$$pass fail=$$fail"; \
	echo ""; \
	echo "Note: tests/test_errors.kt is INTENTIONALLY broken - failure is the expected outcome."

# Less noisy variant: only summary, no per-file lines.
test-quiet: $(BIN)
	@for f in $(TESTS_DIR)/*.kt; do \
	    $(BIN) "$$f" >/dev/null 2>&1; \
	    rc=$$?; name=$$(basename "$$f"); \
	    if [ $$rc -eq 0 ]; then echo "OK   $$name"; else echo "FAIL $$name"; fi; \
	done
