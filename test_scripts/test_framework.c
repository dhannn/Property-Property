#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "test_framework.h"
#include "..\include\helper.h"

void addTestCase(testcase_t *testcase, setup_t setup, destroy_t destroy, int numberOfTests){

    testcase->setup = setup;
    testcase->destroy = destroy;
    testcase->numTest = numberOfTests;
    testcase->test = malloc(sizeof(test_t) * numberOfTests);

    for(int i = 0; i < numberOfTests; i++)
        testcase->test[i] = NULL;
}

void addTest(testcase_t *testcase, test_t test){
    int i = 0;
    while(testcase->test[i] != NULL) i++;

    testcase->test[i] = test;
}

void runTestCase(testcase_t testcase, char *title){
    int i = 0;

    printf(title);

    for(i = 0; i < testcase.numTest; i++){
        printf("Test %d\n", i + 1);
        testcase.test[i](NULL);
    }
}

int assertEqualInt(int expected, int actual){
    char status = 'F';

    if(expected == actual)
        status = 'P';

    printf("\n---------------------------------\n");
    printf("Expected:   %d\n", expected);
    printf("Actual:     %d\n", actual);
    printf("Status:     %c\n\n", status);
}
