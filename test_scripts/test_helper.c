#include <stdio.h>
#include "..\include\helper.h"
#include "test_framework.h"

void test_extractDigit_1(){
    int number = 123;
    int place = 1;
    int expected = 3;
    int actual = extractDigit(number, place);

    assertEqualInt(expected, actual);
}

void test_extractDigit_2(){
    int number = 457;
    int place = 2;
    int expected = 5;
    int actual = extractDigit(number, place);

    assertEqualInt(expected, actual);
}

void test_extractDigit(){
    testcase_t testcase;

    addTestCase(&testcase, NULL, NULL, 2);
    addTest(&testcase, test_extractDigit_1);
    addTest(&testcase, test_extractDigit_2);
    runTestCase(testcase, "========== extractDigit() function ==========\n");
}

int main(){
    test_extractDigit();
    printf("done");
}
