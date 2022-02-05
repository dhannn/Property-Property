#include <stdio.h>
#include <stdlib.h>
#include "..\src\include\helper.h"
#include "test_framework\test_framework.h"

/* -------------------------------------------------------------------------- */
/*                             extractDigit() test                            */
/* -------------------------------------------------------------------------- */

void test_extractDigit_1() {
    int expected;
    int actual;

    int number = 0;
    int place = 2;

    expected = 0;
    actual = extractDigit(number, place);

    assertEqualInt(expected, actual);
}

void test_extractDigit_2() {
    int expected;
    int actual;

    int number = 13;
    int place = 0;

    expected = 0;
    actual = extractDigit(number, place);

    assertEqualInt(expected, actual);
}

void test_extractDigit_3() {
    int expected;
    int actual;

    int number = 104;
    int place = 1;

    expected = 4;
    actual = extractDigit(number, place);

    assertEqualInt(expected, actual);
}

void test_extractDigit_4() {
    int expected;
    int actual;

    int number = 93726;
    int place = 3;

    expected = 7;
    actual = extractDigit(number, place);

    assertEqualInt(expected, actual);
}

void test_extractDigit_5() {
    int expected;
    int actual;

    int number = 2048;
    int place = 4;

    expected = 2;
    actual = extractDigit(number, place);

    assertEqualInt(expected, actual);
}

void test_extractDigit_6() {
    int expected;
    int actual;

    int number = 732;
    int place = 6;

    expected = 0;
    actual = extractDigit(number, place);

    assertEqualInt(expected, actual);
}

void test_extractDigit() {
    testcase_t testcase;

    addTestCase(&testcase, NULL, NULL, 6);
    addTest(&testcase, test_extractDigit_1);
    addTest(&testcase, test_extractDigit_2);
    addTest(&testcase, test_extractDigit_3);
    addTest(&testcase, test_extractDigit_4);
    addTest(&testcase, test_extractDigit_5);
    addTest(&testcase, test_extractDigit_6);
    runTestCase(testcase, "extractDigit()");
}

/* -------------------------------------------------------------------------- */
/*                               setDigit() test                              */
/* -------------------------------------------------------------------------- */

void test_setDigit_1() {
    int *number = malloc(sizeof(int));
    int place;
    int newDigit;

    int expected;
    int actual;

    *number = 0;
    place = 2;
    newDigit = 3;

    expected = 30;
    setDigit(number, place, newDigit);
    actual = *number;

    assertEqualInt(expected, actual);
    free(number);
}

void test_setDigit_2() {
    int *number = malloc(sizeof(int));
    int place;
    int newDigit;

    int expected;
    int actual;

    *number = 13;
    place = 0;
    newDigit = 5;

    expected = 13;
    setDigit(number, place, newDigit);
    actual = *number;

    assertEqualInt(expected, actual);
    free(number);
}

void test_setDigit_3() {
    int *number = malloc(sizeof(int));
    int place;
    int newDigit;

    int expected;
    int actual;

    *number = 524;
    place = 3;
    newDigit = 0;

    expected = 24;
    setDigit(number, place, newDigit);
    actual = *number;

    assertEqualInt(expected, actual);
    free(number);
}

void test_setDigit_4() {
    int *number = malloc(sizeof(int));
    int place;
    int newDigit;

    int expected;
    int actual;

    *number = 104;
    place = 1;
    newDigit = 6;

    expected = 106;
    setDigit(number, place, newDigit);
    actual = *number;

    assertEqualInt(expected, actual);
    free(number);
}

void test_setDigit_5() {
    int *number = malloc(sizeof(int));
    int place;
    int newDigit;

    int expected;
    int actual;

    *number = 93726;
    place = 3;
    newDigit = 2;

    expected = 93226;
    setDigit(number, place, newDigit);
    actual = *number;

    assertEqualInt(expected, actual);
    free(number);
}

void test_setDigit_6() {
    int *number = malloc(sizeof(int));
    int place;
    int newDigit;

    int expected;
    int actual;

    *number = 2048;
    place = 4;
    newDigit = 5;

    expected = 5048;
    setDigit(number, place, newDigit);
    actual = *number;

    assertEqualInt(expected, actual);
    free(number);
}

void test_setDigit_7() {
    int *number = malloc(sizeof(int));
    int place;
    int newDigit;

    int expected;
    int actual;

    *number = 732;
    place = 6;
    newDigit = 1;

    expected = 100732;
    setDigit(number, place, newDigit);
    actual = *number;

    assertEqualInt(expected, actual);
    free(number);
}


void test_setDigit() {
    testcase_t testcase;

    addTestCase(&testcase, NULL, NULL, 7);
    addTest(&testcase, test_setDigit_1);
    addTest(&testcase, test_setDigit_2);
    addTest(&testcase, test_setDigit_3);
    addTest(&testcase, test_setDigit_4);
    addTest(&testcase, test_setDigit_5);
    addTest(&testcase, test_setDigit_6);
    addTest(&testcase, test_setDigit_7);
    runTestCase(testcase, "setDigit()");
}

/* -------------------------------------------------------------------------- */
/*                                power() Test                                */
/* -------------------------------------------------------------------------- */

void test_power_1() {
    int base;
    int exponent;

    int expected;
    int actual;

    base = 0;
    exponent = 4;

    expected = 0;
    actual = power(base, exponent);

    assertEqualInt(expected, actual);
}

void test_power_2() {
    int base;
    int exponent;

    int expected;
    int actual;

    base = 3;
    exponent = 0;

    expected = 1;
    actual = power(base, exponent);

    assertEqualInt(expected, actual);
}

void test_power_3() {
    int base;
    int exponent;

    int expected;
    int actual;

    base = 1;
    exponent = 4;

    expected = 1;
    actual = power(base, exponent);

    assertEqualInt(expected, actual);
}

void test_power_4() {
    int base;
    int exponent;

    int expected;
    int actual;

    base = 3;
    exponent = 1;

    expected = 3;
    actual = power(base, exponent);

    assertEqualInt(expected, actual);
}

void test_power_5() {
    int base;
    int exponent;

    int expected;
    int actual;

    base = 4;
    exponent = 2;

    expected = 16;
    actual = power(base, exponent);

    assertEqualInt(expected, actual);
}

void test_power_6() {
    int base;
    int exponent;

    int expected;
    int actual;

    base = 3;
    exponent = 3;

    expected = 27;
    actual = power(base, exponent);

    assertEqualInt(expected, actual);
}

void test_power_7() {
    int base;
    int exponent;

    int expected;
    int actual;

    base = 10;
    exponent = 5;

    expected = 100000;
    actual = power(base, exponent);

    assertEqualInt(expected, actual);
}

void test_power() {
    testcase_t testcase;

    addTestCase(&testcase, NULL, NULL, 7);
    addTest(&testcase, test_power_1);
    addTest(&testcase, test_power_2);
    addTest(&testcase, test_power_3);
    addTest(&testcase, test_power_4);
    addTest(&testcase, test_power_5);
    addTest(&testcase, test_power_6);
    addTest(&testcase, test_power_7);
    runTestCase(testcase, "power()");
}

/* -------------------------------------------------------------------------- */
/*                               isPrime() Test                               */
/* -------------------------------------------------------------------------- */
void test_isPrime_1() {
    int number;

    int expected;
    int actual;

    number = 1;

    expected = -1;
    actual = isPrime(number);

    assertEqualInt(expected, actual);
}

void test_isPrime_2() {
    int number;

    int expected;
    int actual;

    number = 2;

    expected = 1;
    actual = isPrime(number);

    assertEqualInt(expected, actual);
}

void test_isPrime_3() {
    int number;

    int expected;
    int actual;

    number = 5;

    expected = 1;
    actual = isPrime(number);

    assertEqualInt(expected, actual);
}

void test_isPrime_4() {
    int number;

    int expected;
    int actual;

    number = 15;

    expected = 0;
    actual = isPrime(number);

    assertEqualInt(expected, actual);
}

void test_isPrime() {
    testcase_t testcase;

    addTestCase(&testcase, NULL, NULL, 4);
    addTest(&testcase, test_isPrime_1);
    addTest(&testcase, test_isPrime_2);
    addTest(&testcase, test_isPrime_3);
    addTest(&testcase, test_isPrime_4);
    runTestCase(testcase, "isPrime()");
}

/* -------------------------------------------------------------------------- */
/*                                bitcmp() Test                               */
/* -------------------------------------------------------------------------- */

void test_bitcmp_1() {
    int bitfield;
    int flag;

    int expected;
    int actual;

    bitfield = 0b1;
    flag = 0b1;

    expected = 1;
    actual = bitcmp(bitfield, flag);

    assertEqualInt(expected, actual);
}

void test_bitcmp_2() {
    int bitfield;
    int flag;

    int expected;
    int actual;

    bitfield = 0b0;
    flag = 0b1;

    expected = 0;
    actual = bitcmp(bitfield, flag);

    assertEqualInt(expected, actual);
}

void test_bitcmp_3() {
    int bitfield;
    int flag;

    int expected;
    int actual;

    bitfield = 0b11011;
    flag = 0b10000;

    expected = 1;
    actual = bitcmp(bitfield, flag);

    assertEqualInt(expected, actual);
}

void test_bitcmp_4() {
    int bitfield;
    int flag;

    int expected;
    int actual;

    bitfield = 0b1011;
    flag = 0b0100;

    expected = 0;
    actual = bitcmp(bitfield, flag);

    assertEqualInt(expected, actual);
}

void test_bitcmp_5() {
    int bitfield;
    int flag;

    int expected;
    int actual;

    bitfield = 0b000;
    flag = 0b000;

    expected = 0;
    actual = bitcmp(bitfield, flag);

    assertEqualInt(expected, actual);
}

void test_bitcmp() {
    testcase_t testcase;

    addTestCase(&testcase, NULL, NULL, 5);
    addTest(&testcase, test_bitcmp_1);
    addTest(&testcase, test_bitcmp_2);
    addTest(&testcase, test_bitcmp_3);
    addTest(&testcase, test_bitcmp_4);
    addTest(&testcase, test_bitcmp_5);
    runTestCase(testcase, "bitcmp()");
}


int main(){
    test_extractDigit();
    test_setDigit();
    test_power();
    test_isPrime();
    test_bitcmp();
    printf("done");
}
