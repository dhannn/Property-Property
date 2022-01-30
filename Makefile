# https://www.tutorialspoint.com/makefile/makefile_macros.htm
# https://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
# https://docs.microsoft.com/en-us/powershell/module/microsoft.powershell.archive/compress-archive?view=powershell-7.2

CFLAGS=-Wall -g
CFLAGS_TEST=-Wall -c
BIN="[CCPROG1] MP - Monopoly.exe"
SRC_DIR=src
INCLUDE_DIR=include
INCLUDES=$(wildcard $(SRC_DIR)/$(INCLUDE_DIR)/*.c)
MAIN_SRC=$(SRC_DIR)/main.c
TEST_DIR=test_scripts
TEST_BINS=$(TEST_DIR)/test_player
TESTS=$(wildcard $(TEST_DIR)/*.c)

all: $(BIN)

demo: $(BIN)
	.\$(BIN)

$(BIN): $(INCLUDES)
	gcc $(CFLAGS) $(INCLUDES) $(MAIN_SRC) -o $(BIN)

clean:
	del $(BIN)

test: $(TEST_BINS)

$(TEST_BINS): $(INCLUDES)
	gcc $(CFLAGS_TEST) $^
