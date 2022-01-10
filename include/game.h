/*
    Description:    Combines elements from player.h, space.h and transaction.h
                    to implement the main game features
    Programmed by:  Daniel III L. Ramos (S15A)
    Last Modified:  31 December 2021
    Version:        3.0.0
*/

#include "transaction.h"

#define MAX_PLAYERS 2

#ifndef GAME_H
#define GAME_H

enum gameState{
    GO_JAIL,
    LUCKY,
    CAN_BUY,
    CANNOT_BUY,
    CAN_RENOVATE,
    CANNOT_RENOVATE,
    ALREADY_RENOVATED,
    CAN_PAY_RENT,
    CAN_PAY_RENT_RENOVATED,
    CANNOT_PAY_RENT,
    BANKRUPT
};

typedef enum gameState GameState;

typedef struct {
    unsigned int spaceState: 6;
    unsigned int playerState: 2;
} State;

#define IS_GO                   0b000001 // 1
#define IS_FEELING_LUCKY        0b000010 // 2
#define PROPERTY_BY_BANK        0b000100 // 4
#define PROPERTY_BY_PLAYER      0b001000 // 8
#define PROPERTY_BY_OTHER       0b010000 // 16
#define PROPERTY_IS_RENOVATED   0b100000 // 32
#define HAS_CASH                0b01     // 1
#define HAS_PROPERTY            0b10     // 2

struct game{
    Player *players;                // the players
    Player *activePlayer;           // pointer to the current player
    int inventory;                  // contains ownership details
    int dice;                       // contains the current dice value
    int isBankrupt;                 // boolean
    GameState state;
    Transaction transaction;
    char input;
};

typedef struct game Game;


/**
 * This function initializes all values of the game structure
 *
 * @param game          the game structure to be initialized
 */
void initializeGame(Game *game);


/**
 * This function computes for a random dice value and stores it
 * to the dice variable
 *
 * @param dice          pointer to the dice member of the game
 */
void rollDice(int *dice);


/**
 * This function moves the player to the new position by adding
 * the current position to the dice.
 *
 * @param activePlayer  pointer to the active player to be moved
 * @param dice          dice value that dictates player movement
 */
void movePlayer(Player *activePlayer, int dice);


void enactTransaction(Game *game);

enum transactionType getTransactionType(int state);

int getAmountFromTransactionType(TransactionType tr, int position, int dice);
/**
 * This function gets the state of the game and assigns it to
 * the state member of the game structure.
 *
 * @param game          pointer to the game structure
 */
void getGameState(Game *game);


/**
 * This function decides
 *
 * @param player
 * @param activePlayer
 */
void incrementTurn(Player *player[MAX_PLAYERS], Player **activePlayer);

#endif
