#include <stdio.h>
#include <stdlib.h>

#define LOG_FILE "log.txt"

void printGeneralError() {
    printf("Oops, this shouldn't have happened. 😅\n");
    printf("Please contact the author to report this bug:\n");
}

void raiseNullPointerError(char *message, char *file, const char *func, int line) {
    FILE *logFile = fopen(LOG_FILE, "a");

    // printGeneralError();
    // fprintf(stderr, message);

    if(logFile != NULL)
        fprintf(logFile, "In file %s, function %s, ln %d - Accessing a null pointer\n", file, func, line);
    // fprintf(stderr, "\nIn file %s, function %s, ln %d - Accessing a null pointer\n", file, func, line);

    fclose(logFile);
}
