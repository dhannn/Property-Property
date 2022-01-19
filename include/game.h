/*
    Description:    Combines elements from player.h, space.h and transaction.h
                    to implement the main game features
    Programmed by:  Daniel III L. Ramos (S15A)
    Last Modified:  31 December 2021
    Version:        3.0.0
*/

#include "transaction.h"

#define MAX_PLAYERS 2
#define LUCK_IS_JAIL 0
#define LUCK_IS_GET_BANK 1
#define LUCK_IS_PAY_BANK 2

#ifndef GAME_H
#define GAME_H

typedef enum {
    DO_NOTHING,
    PLAY_BY_LUCK,
    GO_TO_JAIL,
    CAN_BUY,
    CANNOT_BUY,
    CAN_RENOVATE,
    CANNOT_RENOVATE,
    CAN_PAY,
    CANNOT_PAY
} State;

struct game{
    Player *players;                // the players
    Player *activePlayer;           // pointer to the current player
    int inventory;                  // contains ownership details
    int isBankrupt;                 // boolean
    State state;                    //
    Transaction transaction;        // contains details of transaction each round
    int dice;                       // contains the current dice value
    char input;                     // shows the input from user
};

typedef struct game Game;


void initializeGame(Game *game);
void rollDice(int *dice);
void movePlayer(Player *activePlayer, int dice);
void updateState(Game *game);
void makeTransaction(Game *game);
void incrementTurn(Player *player[MAX_PLAYERS], Player **activePlayer);

int playByLuck(Game *game);
void goToJail(Game *game);
void sellProperty(Game *game);

#endif
