#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test_framework.h"

#define TEST_LOG_FILE "test_log.txt"

void addTestCase(testcase_t *testcase, setup_t setup, destroy_t destroy, int numberOfTests, ...) {
    va_list args;
    va_start(args, numberOfTests);

    testcase->setup = setup;
    testcase->destroy = destroy;
    testcase->numTest = numberOfTests;
    testcase->test = malloc(sizeof(test_t) * numberOfTests);

    for(int i = 0; i < numberOfTests; i++)
        testcase->test[i] = NULL;
}

void addTest(testcase_t *testcase, test_t test) {
    int i = 0;
    while(testcase->test[i] != NULL) i++;

    testcase->test[i] = test;
}

void runTestCase(testcase_t testcase, char *title) {
    int i = 0;
    FILE *testLog;
    testLog = fopen(TEST_LOG_FILE, "a");

    printf("%10s%10s\n", " ", title);
    fprintf(testLog, "%10s%10s\n", " ", title);
    fclose(testLog);

    // HACK: the double open and close is needed because fprintf
    //          buffer works differently than printf

    for(i = 0; i < testcase.numTest; i++) {
        testLog = fopen(TEST_LOG_FILE, "a");

        printf("Test %d", i + 1);
        fprintf(testLog, "Test %d\n", i + 1);
        fclose(testLog);
        testcase.test[i]();
    }

    free(testcase.test);
}

void assertEqualInt(int expected, int actual) {
    char status = 'F';
    FILE *testLog = fopen(TEST_LOG_FILE, "a");

    if(expected == actual)
        status = 'P';

    printf("\n---------------------------------\n");
    printf("Expected:   %d\n", expected);
    printf("Actual:     %d\n", actual);
    printf("Status:     %c\n\n", status);

    fprintf(testLog, "\n---------------------------------\n");
    fprintf(testLog, "Expected:   %d\n", expected);
    fprintf(testLog, "Actual:     %d\n", actual);
    fprintf(testLog, "Status:     %c\n\n", status);

    fclose(testLog);
}

void assertEqualStr(char *expected, char *actual) {
    char status = 'F';
    FILE *testLog = fopen(TEST_LOG_FILE, "a");

    if(!strcmp(expected, actual))
        status = 'P';

    printf("\n---------------------------------\n");
    printf("Expected:   %d\n", expected);
    printf("Actual:     %d\n", actual);
    printf("Status:     %c\n\n", status);

    fprintf(testLog, "\n---------------------------------\n");
    fprintf(testLog, "Expected:   %s\n", expected);
    fprintf(testLog, "Actual:     %s\n", actual);
    fprintf(testLog, "Status:     %c\n\n", status);

    fclose(testLog);
}

void assertNull(void *ptr) {
    char status = 'F';
    FILE *testLog = fopen(TEST_LOG_FILE, "a");

    if(ptr == NULL)
        status = 'P';


    printf("\n---------------------------------\n");
    printf("Expected:   %p\n", 0x0);
    printf("Actual:     %p\n", ptr);
    printf("Status:     %c\n\n", status);

    fprintf(testLog, "\n---------------------------------\n");
    fprintf(testLog, "Expected:   %p\n", (void*)0x0);
    fprintf(testLog, "Actual:     %p\n", (void*)ptr);
    fprintf(testLog, "Status:     %c\n\n", status);

    fclose(testLog);
}

void assertNotNull(void *ptr) {
    char status = 'F';
    FILE *testLog = fopen(TEST_LOG_FILE, "a");

    if(ptr != NULL)
        status = 'P';


    printf("\n---------------------------------\n");
    printf("Expected:   Not %p\n", 0x0);
    printf("Actual:     %p\n", ptr);
    printf("Status:     %c\n\n", status);

    fprintf(testLog, "\n---------------------------------\n");
    fprintf(testLog, "Expected:   Not %p\n", 0x0);
    fprintf(testLog, "Actual:     %p\n", ptr);
    fprintf(testLog, "Status:     %c\n\n", status);

    fclose(testLog);
}
