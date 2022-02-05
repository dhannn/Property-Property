#include <stdio.h>
#include <stdlib.h>
#include "..\src\include\player.h"
#include "..\src\include\error.h"
#include "test_framework\test_framework.h"

/* -------------------------------------------------------------------------- */
/*                          initializePlayers() Test                          */
/* -------------------------------------------------------------------------- */

void test_initializePlayers_1() {
    Player *player = NULL;

    initializePlayers(&player, 0);
    assertNull(player);
}

void test_initializePlayers_2() {
    Player *player = NULL;

    initializePlayers(&player, 1);
    assertNotNull(&player);

    cleanPlayers(player, 1);
}

void test_initializePlayers_3() {
    Player *player = NULL;

    initializePlayers(&player, 2);
    assertNotNull(&player);
    assertNotNull(nextPlayer(player));

    cleanPlayers(player, 2);
}

void test_initializePlayers_4() {
    Player *player = NULL;
    Player *temp;
    int i;

    initializePlayers(&player, 6);
    temp = player;
    assertNotNull(player);

    for(i = 0; i < 5; i++) {
        temp = nextPlayer(temp);
        assertNotNull(temp);
    }

    cleanPlayers(player, 6);
}

void test_initializePlayers() {
    testcase_t testcase;

    addTestCase(&testcase, NULL, NULL, 4);
    addTest(&testcase, test_initializePlayers_1);
    addTest(&testcase, test_initializePlayers_2);
    addTest(&testcase, test_initializePlayers_3);
    addTest(&testcase, test_initializePlayers_4);

    runTestCase(testcase, "initializePlayers()");
}


/* -------------------------------------------------------------------------- */
/*                              updateCash() Test                             */
/* -------------------------------------------------------------------------- */

void test_updateCash_1() {
    Player *player;
    initializePlayers(&player, 1);

    updateCash(player, 100, ADD);
    assertEqualInt(300, getCash(player));

    free(player);
}

void test_updateCash_2() {
    Player *player;
    initializePlayers(&player, 1);

    updateCash(player, 50, SUBTRACT);
    assertEqualInt(150, getCash(player));

    free(player);
}

void test_updateCash_3() {
    Player *player;

    initializePlayers(&player, 1);

    updateCash(player, 300, SUBTRACT);
    assertEqualInt(-100, getCash(player));

    free(player);
}

void test_updateCash() {
    testcase_t testcase;

    addTestCase(&testcase, NULL, NULL, 3);
    addTest(&testcase, test_updateCash_1);
    addTest(&testcase, test_updateCash_2);
    addTest(&testcase, test_updateCash_3);
    runTestCase(testcase, "updateCash()");
}

/* -------------------------------------------------------------------------- */
/*                           isCashSufficient() Test                          */
/* -------------------------------------------------------------------------- */

void test_isCashSufficient_1() {
    Player *player;
    int expected;
    int actual;

    initializePlayers(&player, 1);

    expected = 1;
    actual = isCashSufficient(getCash(player), 20);

    assertEqualInt(expected, actual);

    free(player);
}

void test_isCashSufficient_2() {
    Player *player;
    int expected;
    int actual;

    initializePlayers(&player, 1);

    expected = 0;
    actual = isCashSufficient(getCash(player), 300);

    assertEqualInt(expected, actual);

    free(player);
}

void test_isCashSufficient_3() {
    Player *player;
    int expected;
    int actual;

    initializePlayers(&player, 1);

    expected = 1;
    actual = isCashSufficient(getCash(player), 200);

    assertEqualInt(expected, actual);

    free(player);
}

void test_isCashSufficient() {
    testcase_t testcase;

    addTestCase(&testcase, NULL, NULL, 3);
    addTest(&testcase, test_isCashSufficient_1);
    addTest(&testcase, test_isCashSufficient_2);
    addTest(&testcase, test_isCashSufficient_3);
    runTestCase(testcase, "isCashSufficient()");
}

/* -------------------------------------------------------------------------- */
/*                               passesGo() Test                              */
/* -------------------------------------------------------------------------- */

void test_passesGo_1() {
    Player *player;
    int expected;
    int actual;

    initializePlayers(&player, 1);
    setPosition(player, 5);
    setPosition(player, 0);

    expected = 1;
    actual = passesGo(player);


    assertEqualInt(expected, actual);
    cleanPlayers(player, 1);
}

void test_passesGo_2() {
    Player *player;
    int expected;
    int actual;

    initializePlayers(&player, 1);
    setPosition(player, 7);
    setPosition(player, 1);

    expected = 1;
    actual = passesGo(player);

    assertEqualInt(expected, actual);

    cleanPlayers(player, 1);
}

void test_passesGo_3() {
    Player *player;
    int expected;
    int actual;

    initializePlayers(&player, 1);
    setPosition(player, 3);
    setPosition(player, 8);

    expected = 0;
    actual = passesGo(player);

    assertEqualInt(expected, actual);

    cleanPlayers(player, 1);
}

void test_passesGo() {
    testcase_t testcase;

    addTestCase(&testcase, NULL, NULL, 3);
    addTest(&testcase, test_passesGo_1);
    addTest(&testcase, test_passesGo_2);
    addTest(&testcase, test_passesGo_3);
    runTestCase(testcase, "passesGo()");
}

/* -------------------------------------------------------------------------- */
/*                               setName() Test                               */
/* -------------------------------------------------------------------------- */

void test_setName_1() {
    Player *player;
    char *sExpected = "d";
    char *sActual;

    int nExpected;
    int nActual;

    initializePlayers(&player, 1);

    nExpected = 0;
    nActual = setName(player, sExpected);
    sActual = getName(player);
    assertEqualStr(sExpected, sActual);
    assertEqualInt(nExpected, nActual);

    free(player);
}

void test_setName_2() {
    Player *player;
    char *name = "dan";

    int nExpected;
    int nActual;

    initializePlayers(&player, 1);
    nExpected = 0;
    nActual = setName(player, name);
    assertEqualStr(name, getName(player));
    assertEqualInt(nExpected, nActual);

    free(player);
}

void test_setName_3() {
    Player *player;
    char *name = "daniel";

    int nExpected;
    int nActual;

    initializePlayers(&player, 1);
    nExpected = 0;
    nActual = setName(player, name);
    assertEqualStr(name, getName(player));
    assertEqualInt(nExpected, nActual);

    free(player);
}

void test_setName_4() {
    Player *player;
    char *name = "danielramos";

    int nExpected;
    int nActual;

    initializePlayers(&player, 1);
    nExpected = 1;
    nActual = setName(player, name);
    assertNull(getName(player));
    assertEqualInt(nExpected, nActual);

    free(player);
}

void test_setName() {
    testcase_t testcase;

    addTestCase(&testcase, NULL, NULL, 4);
    addTest(&testcase, test_setName_1);
    addTest(&testcase, test_setName_2);
    addTest(&testcase, test_setName_3);
    addTest(&testcase, test_setName_4);

    runTestCase(testcase, "setName()");
}

int main() {
    test_initializePlayers();
    test_updateCash();
    test_isCashSufficient();
    test_passesGo();
    test_setName();
    printf("Done");
}
