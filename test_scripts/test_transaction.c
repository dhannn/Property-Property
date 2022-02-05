#include <stdio.h>
#include <stdlib.h>
#include "..\src\include\transaction.h"
#include "test_framework\test_framework.h"

/* -------------------------------------------------------------------------- */
/*                             getSpaceInfo() Test                            */
/* -------------------------------------------------------------------------- */

void test_getSpaceInfo_1() {
    Player *player;

    initializePlayers(&player, 1);
    setPosition(player, GO);

    assertEqualInt(IS_GO, getSpaceInfo(player, 0));

    cleanPlayers(player, 1);
}

void test_getSpaceInfo_2() {
    Player *player;

    initializePlayers(&player, 1);
    setPosition(player, FEELIN_LUCKY);

    assertEqualInt(IS_FEELIN_LUCKY, getSpaceInfo(player, 0));

    cleanPlayers(player, 1);
}

void test_getSpaceInfo_3() {
    Player *player;

    initializePlayers(&player, 1);
    setPosition(player, JAIL_TIME);

    assertEqualInt(IS_JAIL_TIME, getSpaceInfo(player, 0));

    cleanPlayers(player, 1);
}

void test_getSpaceInfo_4() {
    Player *player;
    int inventory = 142030021;

    initializePlayers(&player, 1);
    setPosition(player, 3);

    assertEqualInt(PROPERTY_BY_BANK, getSpaceInfo(player, inventory));

    cleanPlayers(player, 1);
}

void test_getSpaceInfo_5() {
    Player *players;
    Player *testPlayer;
    int inventory = 142030021;

    initializePlayers(&players, 2);

    testPlayer = nextPlayer(players);
    setPosition(testPlayer, 2);

    assertEqualInt(PROPERTY_BY_PLAYER, getSpaceInfo(testPlayer, inventory));

    cleanPlayers(players, 2);
}

void test_getSpaceInfo_6() {
    Player *players;
    Player *testPlayer;
    int inventory = 142030021;

    initializePlayers(&players, 2);

    testPlayer = nextPlayer(players);
    setPosition(testPlayer, 8);

    assertEqualInt(
        PROPERTY_BY_PLAYER | PROPERTY_IS_RENOVATED,
        getSpaceInfo(testPlayer, inventory)
    );

    cleanPlayers(players, 2);
}

void test_getSpaceInfo_7() {
    Player *players;
    Player *testPlayer;
    int inventory = 142030021;

    initializePlayers(&players, 2);

    testPlayer = nextPlayer(players);
    setPosition(testPlayer, 1);

    assertEqualInt(
        PROPERTY_BY_OTHER,
        getSpaceInfo(testPlayer, inventory)
    );

    cleanPlayers(players, 2);
}

void test_getSpaceInfo_8() {
    Player *players;
    Player *testPlayer;
    int inventory = 142030021;

    initializePlayers(&players, 2);

    testPlayer = nextPlayer(players);
    setPosition(testPlayer, 5);

    assertEqualInt(
        PROPERTY_BY_OTHER | PROPERTY_IS_RENOVATED,
        getSpaceInfo(testPlayer, inventory)
    );

    cleanPlayers(players, 2);
}

void test_getSpaceInfo() {
    testcase_t testcase;

    addTestCase(&testcase, NULL, NULL, 8);
    addTest(&testcase, test_getSpaceInfo_1);
    addTest(&testcase, test_getSpaceInfo_2);
    addTest(&testcase, test_getSpaceInfo_3);
    addTest(&testcase, test_getSpaceInfo_4);
    addTest(&testcase, test_getSpaceInfo_5);
    addTest(&testcase, test_getSpaceInfo_6);
    addTest(&testcase, test_getSpaceInfo_7);
    addTest(&testcase, test_getSpaceInfo_8);

    runTestCase(testcase, "getSpaceInfo()");
}

/* -------------------------------------------------------------------------- */
/*                             isRenovated() Test                             */
/* -------------------------------------------------------------------------- */

void test_isRenovated_1() {
    int inventory = 0;
    int position = GO;

    int expected = 0;
    int actual = isRenovated(inventory, position);

    assertEqualInt(expected, actual);
}

void test_isRenovated_2() {
    int inventory = 0;
    int position = FEELIN_LUCKY;

    int expected = 0;
    int actual = isRenovated(inventory, position);

    assertEqualInt(expected, actual);
}

void test_isRenovated_3() {
    int inventory = 0;
    int position = JAIL_TIME;

    int expected = 0;
    int actual = isRenovated(inventory, position);

    assertEqualInt(expected, actual);
}

void test_isRenovated_4() {
    int inventory = 124020013;
    int position = 3;

    int expected = 0;
    int actual = isRenovated(inventory, position);

    assertEqualInt(expected, actual);
}

void test_isRenovated_5() {
    int inventory = 124020013;
    int position = 2;

    int expected = 0;
    int actual = isRenovated(inventory, position);

    assertEqualInt(expected, actual);
}

void test_isRenovated_6() {
    int inventory = 124020013;
    int position = 7;

    int expected = 1;
    int actual = isRenovated(inventory, position);

    assertEqualInt(expected, actual);
}

void test_isRenovated() {
    testcase_t testcase;

    addTestCase(&testcase, NULL, NULL, 6);
    addTest(&testcase, test_isRenovated_1);
    addTest(&testcase, test_isRenovated_2);
    addTest(&testcase, test_isRenovated_3);
    addTest(&testcase, test_isRenovated_4);
    addTest(&testcase, test_isRenovated_5);
    addTest(&testcase, test_isRenovated_6);

    runTestCase(testcase, "isRenovated");
}

/* -------------------------------------------------------------------------- */
/*                            isOwnedByBank() Test                            */
/* -------------------------------------------------------------------------- */

void test_isOwnedByBank_1() {
    int inventory = 0;
    int position = GO;

    int expected = 0;
    int actual = isOwnedByBank(inventory, position);

    assertEqualInt(expected, actual);
}

void test_isOwnedByBank_2() {
    int inventory = 0;
    int position = FEELIN_LUCKY;

    int expected = 0;
    int actual = isOwnedByBank(inventory, position);

    assertEqualInt(expected, actual);
}

void test_isOwnedByBank_3() {
    int inventory = 0;
    int position = JAIL_TIME;

    int expected = 0;
    int actual = isOwnedByBank(inventory, position);

    assertEqualInt(expected, actual);
}

void test_isOwnedByBank_4() {
    int inventory = 312000304;
    int position = 2;

    int expected = 1;
    int actual = isOwnedByBank(inventory, position);

    assertEqualInt(expected, actual);
}

void test_isOwnedByBank_5() {
    int inventory = 312000304;
    int position = 7;

    int expected = 0;
    int actual = isOwnedByBank(inventory, position);

    assertEqualInt(expected, actual);
}

void test_isOwnedByBank() {
    testcase_t testcase;

    addTestCase(&testcase, NULL, NULL, 5);
    addTest(&testcase, test_isOwnedByBank_1);
    addTest(&testcase, test_isOwnedByBank_2);
    addTest(&testcase, test_isOwnedByBank_3);
    addTest(&testcase, test_isOwnedByBank_4);
    addTest(&testcase, test_isOwnedByBank_5);

    runTestCase(testcase, "isOwnedByBank()");
}

/* -------------------------------------------------------------------------- */
/*                           isOwnedByPlayer() Test                           */
/* -------------------------------------------------------------------------- */

void test_isOwnedByPlayer_1() {
    int inventory = 0;
    int position = GO;
    int index = 0;

    int expected = 0;
    int actual = isOwnedByPlayer(inventory, position, index);

    assertEqualInt(expected, actual);
}

void test_isOwnedByPlayer_2() {
    int inventory = 0;
    int position = FEELIN_LUCKY;
    int index = 0;

    int expected = 0;
    int actual = isOwnedByPlayer(inventory, position, index);

    assertEqualInt(expected, actual);
}

void test_isOwnedByPlayer_3() {
    int inventory = 0;
    int position = JAIL_TIME;
    int index = 0;

    int expected = 0;
    int actual = isOwnedByPlayer(inventory, position, index);

    assertEqualInt(expected, actual);
}

void test_isOwnedByPlayer_4() {
    int inventory = 241010231;
    int position = 5;
    int index = 0;

    int expected = 1;
    int actual = isOwnedByPlayer(inventory, position, index);

    assertEqualInt(expected, actual);
}

void test_isOwnedByPlayer_5() {
    int inventory = 241010231;
    int position = 3;
    int index = 1;

    int expected = 1;
    int actual = isOwnedByPlayer(inventory, position, index);

    assertEqualInt(expected, actual);
}

void test_isOwnedByPlayer_6() {
    int inventory = 241010231;
    int position = 2;
    int index = 0;

    int expected = 1;
    int actual = isOwnedByPlayer(inventory, position, index);

    assertEqualInt(expected, actual);
}

void test_isOwnedByPlayer_7() {
    int inventory = 241010231;
    int position = 8;
    int index = 1;

    int expected = 1;
    int actual = isOwnedByPlayer(inventory, position, index);

    assertEqualInt(expected, actual);
}

void test_isOwnedByPlayer_8() {
    int inventory = 241010231;
    int position = 3;
    int index = 0;

    int expected = 0;
    int actual = isOwnedByPlayer(inventory, position, index);

    assertEqualInt(expected, actual);
}

void test_isOwnedByPlayer_9() {
    int inventory = 241010231;
    int position = 5;
    int index = 1;

    int expected = 0;
    int actual = isOwnedByPlayer(inventory, position, index);

    assertEqualInt(expected, actual);
}

void test_isOwnedByPlayer() {
    testcase_t testcase;

    addTestCase(&testcase, NULL, NULL, 9);
    addTest(&testcase, test_isOwnedByPlayer_1);
    addTest(&testcase, test_isOwnedByPlayer_2);
    addTest(&testcase, test_isOwnedByPlayer_3);
    addTest(&testcase, test_isOwnedByPlayer_4);
    addTest(&testcase, test_isOwnedByPlayer_5);
    addTest(&testcase, test_isOwnedByPlayer_6);
    addTest(&testcase, test_isOwnedByPlayer_7);
    addTest(&testcase, test_isOwnedByPlayer_8);
    addTest(&testcase, test_isOwnedByPlayer_9);

    runTestCase(testcase, "isOwnedByPlayer()");
}

/* -------------------------------------------------------------------------- */
/*                              updateCash() Test                             */
/* -------------------------------------------------------------------------- */

void test_updateInventory_1() {
    int position = 1;
    int inventory = 201;
    int newStatus = 3;

    int expected = 203;
    updateInventory(&inventory, position, newStatus);

    assertEqualInt(expected, inventory);
}

void test_updateInventory_2() {
    int position = 4;
    int inventory = 102;
    int newStatus = 2;

    int expected = 2102;
    updateInventory(&inventory, position, newStatus);

    assertEqualInt(expected, inventory);
}

void test_updateInventory_3() {
    int position = 9;
    int inventory = 14010321;
    int newStatus = 3;

    int expected = 314010321;
    updateInventory(&inventory, position, newStatus);

    assertEqualInt(expected, inventory);
}

void test_updateInventory_4() {
    int position = 3;
    int inventory = 14010321;
    int newStatus = 0;

    int expected = 14010021;
    updateInventory(&inventory, position, newStatus);

    assertEqualInt(expected, inventory);
}

void test_updateInventory_5() {
    int position = 2;
    int inventory = 14010321;
    int newStatus = 4;

    int expected = 14010341;
    updateInventory(&inventory, position, newStatus);

    assertEqualInt(expected, inventory);
}

void test_updateInventory() {
    testcase_t testcase;

    addTestCase(&testcase, NULL, NULL, 5);
    addTest(&testcase,  test_updateInventory_1);
    addTest(&testcase,  test_updateInventory_2);
    addTest(&testcase,  test_updateInventory_3);
    addTest(&testcase,  test_updateInventory_4);
    addTest(&testcase,  test_updateInventory_5);

    runTestCase(testcase, "updateInventory()");
}

/* -------------------------------------------------------------------------- */
/*                               getOwner() Test                              */
/* -------------------------------------------------------------------------- */

void test_getOwner_1() {
    int inventory = 0;
    int position = JAIL_TIME;

    int expected = -1;
    int actual = getOwner(inventory, position);

    assertEqualInt(expected, actual);
}

void test_getOwner_2() {
    int inventory = 30124;
    int position = 5;

    int expected = 0;
    int actual = getOwner(inventory, position);

    assertEqualInt(expected, actual);
}

void test_getOwner_3() {
    int inventory = 30124;
    int position = 3;

    int expected = 0;
    int actual = getOwner(inventory, position);

    assertEqualInt(expected, actual);
}

void test_getOwner_4() {
    int inventory = 30124;
    int position = 1;

    int expected = 1;
    int actual = getOwner(inventory, position);

    assertEqualInt(expected, actual);
}

void test_getOwner_5() {
    int inventory = 30124;
    int position = 2;

    int expected = 1;
    int actual = getOwner(inventory, position);

    assertEqualInt(expected, actual);
}

void test_getOwner() {
    testcase_t testcase;

    addTestCase(&testcase, NULL, NULL, 5);
    addTest(&testcase, test_getOwner_1);
    addTest(&testcase, test_getOwner_2);
    addTest(&testcase, test_getOwner_3);
    addTest(&testcase, test_getOwner_4);
    addTest(&testcase, test_getOwner_5);

    runTestCase(testcase, "getOwner()");
}

/* -------------------------------------------------------------------------- */
/*                             hasProperty() Test                             */
/* -------------------------------------------------------------------------- */

void test_hasProperty_1() {
    int inventory = 0;
    int index = 0;

    int expected = 0;
    int actual = hasProperty(inventory, index);

    assertEqualInt(expected, actual);
}

void test_hasProperty_2() {
    int inventory = 242020242;
    int index = 0;

    int expected = 0;
    int actual = hasProperty(inventory, index);

    assertEqualInt(expected, actual);
}

void test_hasProperty_3() {
    int inventory = 131010131;
    int index = 1;

    int expected = 0;
    int actual = hasProperty(inventory, index);

    assertEqualInt(expected, actual);
}

void test_hasProperty_4() {
    int inventory = 242010242;
    int index = 0;

    int expected = 1;
    int actual = hasProperty(inventory, index);

    assertEqualInt(expected, actual);
}

void test_hasProperty_5() {
    int inventory = 141010131;
    int index = 1;

    int expected = 1;
    int actual = hasProperty(inventory, index);

    assertEqualInt(expected, actual);
}

void test_hasProperty_6() {
    int inventory = 212010243;
    int index = 0;

    int expected = 1;
    int actual = hasProperty(inventory, index);

    assertEqualInt(expected, actual);
}

void test_hasProperty_7() {
    int inventory = 141020234;
    int index = 1;

    int expected = 1;
    int actual = hasProperty(inventory, index);

    assertEqualInt(expected, actual);
}

void test_hasProperty_8() {
    int inventory = 311030313;
    int index = 0;

    int expected = 1;
    int actual = hasProperty(inventory, index);

    assertEqualInt(expected, actual);
}

void test_hasProperty_9() {
    int inventory = 22404022;
    int index = 1;

    int expected = 1;
    int actual = hasProperty(inventory, index);

    assertEqualInt(expected, actual);
}

void test_hasProperty() {
    testcase_t testcase;

    addTestCase(&testcase, NULL, NULL, 9);
    addTest(&testcase, test_hasProperty_1);
    addTest(&testcase, test_hasProperty_2);
    addTest(&testcase, test_hasProperty_3);
    addTest(&testcase, test_hasProperty_4);
    addTest(&testcase, test_hasProperty_5);
    addTest(&testcase, test_hasProperty_6);
    addTest(&testcase, test_hasProperty_7);
    addTest(&testcase, test_hasProperty_8);
    addTest(&testcase, test_hasProperty_9);

    runTestCase(testcase, "hasProprty()");
}

/* -------------------------------------------------------------------------- */
/*                          getTransactionType() Test                         */
/* -------------------------------------------------------------------------- */

void test_getTransactionType_1() {
    int space = IS_GO;

    int expected = NULL_TRANSACTION;
    int actual = getTransactionType(space);

    assertEqualInt(expected, actual);
}

void test_getTransactionType_2() {
    int space = PROPERTY_BY_BANK;

    int expected = BUY_PROPERTY;
    int actual = getTransactionType(space);

    assertEqualInt(expected, actual);
}

void test_getTransactionType_3() {
    int space = PROPERTY_BY_PLAYER;

    int expected = RENOVATE_PROPERTY;
    int actual = getTransactionType(space);

    assertEqualInt(expected, actual);
}

void test_getTransactionType_4() {
    int space = PROPERTY_BY_OTHER;

    int expected = PAY_RENT;
    int actual = getTransactionType(space);

    assertEqualInt(expected, actual);
}

void test_getTransactionType() {
    testcase_t testcase;

    addTestCase(&testcase, NULL, NULL, 4);
    addTest(&testcase, test_getTransactionType_1);
    addTest(&testcase, test_getTransactionType_2);
    addTest(&testcase, test_getTransactionType_3);
    addTest(&testcase, test_getTransactionType_4);

    runTestCase(testcase, "getTransactionType()");
}

/* -------------------------------------------------------------------------- */
/*                             getNewDigit() Test                             */
/* -------------------------------------------------------------------------- */

void test_getNewDigit_1() {
    Player *players;
    Player *activePlayer;
    int inventory;
    TransactionType tr;

    int expected;
    int actual;

    initializePlayers(&players, 2);
    activePlayer = players;

    setPosition(activePlayer, 4);
    inventory = 114030102;
    tr = NULL_TRANSACTION;

    expected = 0;
    actual = getNewDigit(activePlayer, inventory, tr);

    assertEqualInt(expected, actual);

    cleanPlayers(players, 2);
}

void test_getNewDigit_2() {
    Player *players;
    Player *activePlayer;
    int inventory;
    TransactionType tr;

    int expected;
    int actual;

    initializePlayers(&players, 2);
    activePlayer = players;

    setPosition(activePlayer, 2);
    inventory = 114030102;
    tr = BUY_PROPERTY;

    expected = 1;
    actual = getNewDigit(activePlayer, inventory, tr);

    assertEqualInt(expected, actual);

    cleanPlayers(players, 2);
}

void test_getNewDigit_3() {
    Player *players;
    Player *activePlayer;
    int inventory;
    TransactionType tr;

    int expected;
    int actual;

    initializePlayers(&players, 2);
    activePlayer = nextPlayer(players);

    setPosition(activePlayer, 2);
    inventory = 114030102;
    tr = BUY_PROPERTY;

    expected = 2;
    actual = getNewDigit(activePlayer, inventory, tr);

    assertEqualInt(expected, actual);

    cleanPlayers(players, 2);
}

void test_getNewDigit_4() {
    Player *players;
    Player *activePlayer;
    int inventory;
    TransactionType tr;

    int expected;
    int actual;

    initializePlayers(&players, 2);
    activePlayer = players;

    setPosition(activePlayer, 3);
    inventory = 114030102;
    tr = RENOVATE_PROPERTY;

    expected = 3;
    actual = getNewDigit(activePlayer, inventory, tr);

    assertEqualInt(expected, actual);

    cleanPlayers(players, 2);
}

void test_getNewDigit_5() {
    Player *players;
    Player *activePlayer;
    int inventory;
    TransactionType tr;

    int expected;
    int actual;

    initializePlayers(&players, 2);
    activePlayer = nextPlayer(players);

    setPosition(activePlayer, 1);
    inventory = 114030102;
    tr = RENOVATE_PROPERTY;

    expected = 4;
    actual = getNewDigit(activePlayer, inventory, tr);

    assertEqualInt(expected, actual);

    cleanPlayers(players, 2);
}

void test_getNewDigit_6() {
    Player *players;
    Player *activePlayer;
    int inventory;
    TransactionType tr;

    int expected;
    int actual;

    initializePlayers(&players, 2);
    activePlayer = nextPlayer(players);

    setPosition(activePlayer, 5);
    inventory = 114030102;
    tr = PAY_RENT;

    expected = 3;
    actual = getNewDigit(activePlayer, inventory, tr);

    assertEqualInt(expected, actual);

    cleanPlayers(players, 2);
}

void test_getNewDigit() {
    testcase_t testcase;

    addTestCase(&testcase, NULL, NULL, 6);
    addTest(&testcase, test_getNewDigit_1);
    addTest(&testcase, test_getNewDigit_2);
    addTest(&testcase, test_getNewDigit_3);
    addTest(&testcase, test_getNewDigit_4);
    addTest(&testcase, test_getNewDigit_5);
    addTest(&testcase, test_getNewDigit_6);

    runTestCase(testcase, "getNewDigit()");
}

/* -------------------------------------------------------------------------- */
/*                              getAmount() Test                              */
/* -------------------------------------------------------------------------- */

void test_getAmount_1() {
    int spaceInfo = PROPERTY_BY_BANK;
    int position = ELECTRIC_COMPANY;
    int inventory = 0;
    int dice = 1;

    int expected = 150;
    int actual = getAmount(spaceInfo, position, inventory, dice);

    assertEqualInt(expected, actual);
}

void test_getAmount_2() {
    int spaceInfo = PROPERTY_BY_BANK;
    int position = RAILROAD;
    int inventory = 0;
    int dice = 1;

    int expected = 100;
    int actual = getAmount(spaceInfo, position, inventory, dice);

    assertEqualInt(expected, actual);
}

void test_getAmount_3() {
    int spaceInfo = PROPERTY_BY_BANK;
    int position = TREEHOUSE;
    int inventory = 0;
    int dice = 1;

    int expected = 20;
    int actual = getAmount(spaceInfo, position, inventory, dice);

    assertEqualInt(expected, actual);
}

void test_getAmount_4() {
    int spaceInfo = PROPERTY_BY_BANK;
    int position = CASTLE;
    int inventory = 0;
    int dice = 1;

    int expected = 100;
    int actual = getAmount(spaceInfo, position, inventory, dice);

    assertEqualInt(expected, actual);
}

void test_getAmount_5() {
    int spaceInfo = PROPERTY_BY_BANK;
    int position = FARMHOUSE;
    int inventory = 0;
    int dice = 1;

    int expected = 40;
    int actual = getAmount(spaceInfo, position, inventory, dice);

    assertEqualInt(expected, actual);
}

void test_getAmount_6() {
    int spaceInfo = PROPERTY_BY_PLAYER;
    int position = ELECTRIC_COMPANY;
    int inventory = 0;
    int dice = 1;

    int expected = 0;
    int actual = getAmount(spaceInfo, position, inventory, dice);

    assertEqualInt(expected, actual);
}

void test_getAmount_7() {
    int spaceInfo = PROPERTY_BY_PLAYER;
    int position = RAILROAD;
    int inventory = 0;
    int dice = 1;

    int expected = 0;
    int actual = getAmount(spaceInfo, position, inventory, dice);

    assertEqualInt(expected, actual);
}

void test_getAmount_8() {
    int spaceInfo = PROPERTY_BY_PLAYER;
    int position = TREEHOUSE;
    int inventory = 0;
    int dice = 1;

    int expected = 50;
    int actual = getAmount(spaceInfo, position, inventory, dice);

    assertEqualInt(expected, actual);
}

void test_getAmount_9() {
    int spaceInfo = PROPERTY_BY_PLAYER;
    int position = CASTLE;
    int inventory = 0;
    int dice = 1;

    int expected = 50;
    int actual = getAmount(spaceInfo, position, inventory, dice);

    assertEqualInt(expected, actual);
}

void test_getAmount_10() {
    int spaceInfo = PROPERTY_BY_PLAYER;
    int position = FARMHOUSE;
    int inventory = 0;
    int dice = 1;

    int expected = 50;
    int actual = getAmount(spaceInfo, position, inventory, dice);

    assertEqualInt(expected, actual);
}

void test_getAmount_11() {
    int spaceInfo = PROPERTY_BY_OTHER;
    int position = ELECTRIC_COMPANY;
    int inventory = 0;
    int dice = 6;

    int expected = 48;
    int actual = getAmount(spaceInfo, position, inventory, dice);

    assertEqualInt(expected, actual);
}

void test_getAmount_12() {
    int spaceInfo = PROPERTY_BY_OTHER;
    int position = RAILROAD;
    int inventory = 0;
    int dice = 1;

    int expected = 35;
    int actual = getAmount(spaceInfo, position, inventory, dice);

    assertEqualInt(expected, actual);
}

void test_getAmount_13() {
    int spaceInfo = PROPERTY_BY_OTHER;
    int position = TREEHOUSE;
    int inventory = 0;
    int dice = 1;

    int expected = 4;
    int actual = getAmount(spaceInfo, position, inventory, dice);

    assertEqualInt(expected, actual);
}

void test_getAmount_14() {
    int spaceInfo = PROPERTY_BY_OTHER | PROPERTY_IS_RENOVATED;
    int position = CASTLE;
    int inventory = 0;
    int dice = 1;

    int expected = 41;
    int actual = getAmount(spaceInfo, position, inventory, dice);

    assertEqualInt(expected, actual);
}

void test_getAmount_15() {
    int spaceInfo = PROPERTY_BY_OTHER;
    int position = FARMHOUSE;
    int inventory = 0;
    int dice = 1;

    int expected = 8;
    int actual = getAmount(spaceInfo, position, inventory, dice);

    assertEqualInt(expected, actual);
}

void test_getAmount_16() {
    int spaceInfo = PROPERTY_TO_SELL;
    int position = ELECTRIC_COMPANY;
    int inventory = 0;
    int dice = 1;

    int expected = 75;
    int actual = getAmount(spaceInfo, position, inventory, dice);

    assertEqualInt(expected, actual);
}

void test_getAmount_17() {
    int spaceInfo = PROPERTY_TO_SELL;
    int position = RAILROAD;
    int inventory = 0;
    int dice = 1;

    int expected = 50;
    int actual = getAmount(spaceInfo, position, inventory, dice);

    assertEqualInt(expected, actual);
}

void test_getAmount_18() {
    int spaceInfo = PROPERTY_TO_SELL;
    int position = TREEHOUSE;
    int inventory = 0;
    int dice = 1;

    int expected = 10;
    int actual = getAmount(spaceInfo, position, inventory, dice);

    assertEqualInt(expected, actual);
}

void test_getAmount_19() {
    int spaceInfo = PROPERTY_TO_SELL;
    int position = CASTLE;
    int inventory = 0;
    int dice = 1;

    int expected = 50;
    int actual = getAmount(spaceInfo, position, inventory, dice);

    assertEqualInt(expected, actual);
}

void test_getAmount_20() {
    int spaceInfo = PROPERTY_TO_SELL;
    int position = FARMHOUSE;
    int inventory = 0;
    int dice = 1;

    int expected = 20;
    int actual = getAmount(spaceInfo, position, inventory, dice);

    assertEqualInt(expected, actual);
}

void test_getAmount() {
    testcase_t testcase;

    addTestCase(&testcase, NULL, NULL, 20);
    addTest(&testcase, test_getAmount_1);
    addTest(&testcase, test_getAmount_2);
    addTest(&testcase, test_getAmount_3);
    addTest(&testcase, test_getAmount_4);
    addTest(&testcase, test_getAmount_5);
    addTest(&testcase, test_getAmount_6);
    addTest(&testcase, test_getAmount_7);
    addTest(&testcase, test_getAmount_8);
    addTest(&testcase, test_getAmount_9);
    addTest(&testcase, test_getAmount_10);
    addTest(&testcase, test_getAmount_11);
    addTest(&testcase, test_getAmount_12);
    addTest(&testcase, test_getAmount_13);
    addTest(&testcase, test_getAmount_14);
    addTest(&testcase, test_getAmount_15);
    addTest(&testcase, test_getAmount_16);
    addTest(&testcase, test_getAmount_17);
    addTest(&testcase, test_getAmount_18);
    addTest(&testcase, test_getAmount_19);
    addTest(&testcase, test_getAmount_20);

    runTestCase(testcase, "getAmount()");
}

void test_enactTransaction_1() {
    Player *player;
    Transaction *transaction;
}

int main() {
    test_getSpaceInfo();
    test_isRenovated();
    test_isOwnedByBank();
    test_isOwnedByPlayer();
    test_updateInventory();
    test_getOwner();
    test_hasProperty();
    test_getTransactionType();
    test_getNewDigit();
    test_getAmount();
    return 0;
}
