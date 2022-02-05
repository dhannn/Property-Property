#include <stdio.h>
#include <stdlib.h>
#include "..\src\include\game.h"
#include "test_framework\test_framework.h"

/* -------------------------------------------------------------------------- */
/*                              movePlayer() Test                             */
/* -------------------------------------------------------------------------- */

void test_updateMovePlayer_1() {
    Player *player;
    int dice;

    initializePlayers(&player, 1);

    setPosition(player, 0);
    dice = 1;

    movePlayer(player, dice);

    assertEqualInt(1, getPosition(player));

    cleanPlayers(player, 1);
}

void test_updateMovePlayer_2() {
    Player *player;
    int dice;

    initializePlayers(&player, 1);

    setPosition(player, 4);
    dice = 3;

    movePlayer(player, dice);

    assertEqualInt(7, getPosition(player));

    cleanPlayers(player, 1);
}

void test_updateMovePlayer_3() {
    Player *player;
    int dice;

    initializePlayers(&player, 1);

    setPosition(player, 2);
    dice = 6;

    movePlayer(player, dice);

    assertEqualInt(8, getPosition(player));

    cleanPlayers(player, 1);
}

void test_updateMovePlayer_4() {
    Player *player;
    int dice;

    initializePlayers(&player, 1);

    setPosition(player, 7);
    dice = 4;

    movePlayer(player, dice);

    assertEqualInt(1, getPosition(player));

    cleanPlayers(player, 1);
}

void test_updateMovePlayer() {
    testcase_t testcase;

    addTestCase(&testcase, NULL, NULL, 4);
    addTest(&testcase, test_updateMovePlayer_1);
    addTest(&testcase, test_updateMovePlayer_2);
    addTest(&testcase, test_updateMovePlayer_3);
    addTest(&testcase, test_updateMovePlayer_4);

    runTestCase(testcase, "updateMovePlayer()");
}

void test_playByLuck_1() {
    Game game;
    int expectedPosition;
    int actualPosition;
    int expectedCanPlay;
    int actualCanPlay;
    int actualReturn;
    int expectedReturn;

    initializeGame(&game);
    game.dice = 1;
    setPosition(game.activePlayer, 6);

    expectedReturn = 0;
    expectedCanPlay = 0;
    expectedPosition = 4;
    actualReturn = playByLuck(&game);
    actualCanPlay = getCanPlay(game.activePlayer);
    actualPosition = getPosition(game.activePlayer);

    assertEqualInt(expectedPosition, actualPosition);
    assertEqualInt(expectedCanPlay, actualCanPlay);
    assertEqualInt(expectedReturn, actualReturn);
}

void test_playByLuck_2() {
    Game game;
    int expectedCash;
    int actualCash;
    int actualReturn;
    int expectedReturn;

    initializeGame(&game);
    game.dice = 2;
    setPosition(game.activePlayer, 6);

    expectedReturn = 1;
    expectedCash = 350;
    actualReturn = playByLuck(&game);
    actualCash = getCash(game.activePlayer);

    assertEqualInt(expectedCash, actualCash);
    assertEqualInt(expectedReturn, actualReturn);
}

void test_playByLuck_3() {
    Game game;
    int expectedCash;
    int actualCash;
    int actualReturn;
    int expectedReturn;

    initializeGame(&game);
    game.dice = 4;
    setPosition(game.activePlayer, 6);

    expectedReturn = 2;
    expectedCash = 100;
    actualReturn = playByLuck(&game);
    actualCash = getCash(game.activePlayer);

    assertEqualInt(expectedCash, actualCash);
    assertEqualInt(expectedReturn, actualReturn);
}

void test_playByLuck() {
    testcase_t testcase;

    addTestCase(&testcase, NULL, NULL, 3);
    addTest(&testcase, test_playByLuck_1);
    addTest(&testcase, test_playByLuck_2);
    addTest(&testcase, test_playByLuck_3);

    runTestCase(testcase, "playByLuck()");
}

int main() {
    test_updateMovePlayer();
    test_playByLuck();
    return 0;
}
