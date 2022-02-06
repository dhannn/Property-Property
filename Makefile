# https://www.tutorialspoint.com/makefile/makefile_macros.htm
# https://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
# https://docs.microsoft.com/en-us/powershell/module/microsoft.powershell.archive/compress-archive?view=powershell-7.2

CFLAGS=-Wall -g
CFLAGS_TEST=

BIN="[CCPROG1] MP - Monopoly.exe"
SRC_DIR=src
INCLUDE_DIR=include
INCLUDES=$(wildcard $(SRC_DIR)/$(INCLUDE_DIR)/*.c)

MAIN_SRC=$(SRC_DIR)/main.c

TEST_DIR=test_scripts
TESTS=$(wildcard $(TEST_DIR)/*.c)
TEST_BINS=$(patsubst $(TEST_DIR)/%.c,$(TEST_DIR)/%.exe,$(TESTS))
TEST_FRAMEWORK=$(wildcard $(TEST_DIR)/test_framework/*.c)

all: $(BIN)

demo: $(BIN)
	.\$(BIN)

$(BIN):
	gcc $(CFLAGS) $(INCLUDES) $(MAIN_SRC) -o $(BIN)

$(SRC_DIR)/%.exe: $(SRC_DIR)/%.c
	gcc $(CFLAGS_TEST) $(INCLUDES) $< $(TEST_FRAMEWORK) -o $@

clean: del_bin del_test

del_bin:
	del $(BIN)

del_test:
	$(foreach test, $(TEST_BINS), rm $(test);)

test: $(TEST_BINS)

$(TEST_DIR)/%.exe: $(TEST_DIR)/%.c
	gcc $(CFLAGS_TEST) $(INCLUDES) $< $(TEST_FRAMEWORK) -o $@
	.\$@
	echo "hi"
