# https://www.tutorialspoint.com/makefile/makefile_macros.htm
# https://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
# https://docs.microsoft.com/en-us/powershell/module/microsoft.powershell.archive/compress-archive?view=powershell-7.2

CFLAGS=-Wall
CFLAGS_TEST=-Wall -c
BIN="[CCPROG1] MP - Monopoly.exe"
INCLUDE_DIR=include
INCLUDES=$(wildcard $(INCLUDE_DIR)/*.c)
TEST_DIR=test_scripts
TEST_BINS=$(TEST_DIR)/test_player
TESTS=$(wildcard $(TEST_DIR)/*.c)
MAIN_SRC=main.c

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
