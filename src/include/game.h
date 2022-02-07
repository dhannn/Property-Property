/*

    Description         This file contains the function prototypes and other
                        structures involving the game itself
    Programmed by       Daniel III L. Ramos (S15A)
    Last Modified       06-02-2022
    Version             3.5.0

*/

#include "transaction.h"
#include <stdint.h>

#define MAX_PLAYERS 2
#define LUCK_IS_JAIL 0
#define LUCK_IS_GET_BANK 1
#define LUCK_IS_PAY_BANK 2
#define LUCK_IS_PAY_BANK_NO_CASH 3

#define CONFIG_FILE "config"

#ifndef GAME_H
#define GAME_H


// The game states dictate the possible outcomes in a turn
typedef enum {
    DO_NOTHING,             // when game has no possible outcome in the turn
    PLAY_BY_LUCK,           // landed on the Feelin Lucky space
    GO_TO_JAIL,             // landed on jail
    CAN_BUY,                // landed on unowned property and has enough money
    CANNOT_BUY,             // landed on unowned property and not enough money
    CAN_RENOVATE,           // landed on their property and has enough money
    CANNOT_RENOVATE,        // landed on their property and not enough money
    CAN_PAY,                // landed on other's property and has enough money
    CANNOT_PAY              // landed on other's property and not enough money
} State;


// The config structure deals with the settings of the game
struct config {
    float initialCash;
    float costMultiplier;
    float hasInflation;
};

typedef struct config Config;


// The game structure contains all the information related to the game
struct game{
    Player *players;                // pointer to the players
    Player *activePlayer;           // pointer to the current player
    Transaction transaction;        // contains transaction details each round
    State state;                    // shows the state of the game
    int inventory;                  // contains ownership details
    int isBankrupt;                 // boolean
    int dice;                       // contains the current dice value
    char input;                     // shows the input from user
    Config config;
    long id;                        // the seed that represents the game
};

typedef struct game Game;

/* -------------------------------------------------------------------------- */
/*                            MAIN GAME OPERATIONS                            */
/* -------------------------------------------------------------------------- */
/* The following functions are always called in every turn                    */
/* as they are constants in the main game loop                                */


/**
    This function uses a hash function to create a random seed

    @return             a 32-bit random integer used as seed for RNG
*/
uint32_t initializeSeed();

/**
    This function sets initial values to the members of the game structure

    @param  game        the pointer to the game structure
    @return             none
*/
void initializeGame(Game *game);

/**
    This function sets a random value from 1 to 6 and assigns it to the dice

    @param  dice        the pointer to the dice
    @return             none
*/
void rollDice(int *dice);

/**
    This function adds the dice value to the current position of active player
    and sets it as the new position of the player

    @param activePlayer the pointer to current player
    @param dice         the current dice value
    @return             none
*/
void movePlayer(Player *activePlayer, int dice);

/**
    This function updates the game state

    @param  game        the pointer to the game structure
    @return             none
*/
void updateState(Game *game);

/**
    This function sets the values of the transaction structure members

    @param  game        the pointer to the game structure
    @return             none
*/
void makeTransaction(Game *game);

/**
    This function replaces the current active player pointer to the next player

    @param player       the pointer to the players of the game
    @param activePlayer the pointer to the pointer of the current player
    @return             none
*/
void incrementTurn(Player *player[MAX_PLAYERS], Player **activePlayer);

void initiateInflation(Game *game);

/**
    This function deallocates dynamically-allocated memory set in
    the previous functions

    @param  game        the pointer to the game structure
    @return             none
*/
void cleanGame(Game *game);

/* -------------------------------------------------------------------------- */
/*                             MINOR GAME BRANCHES                            */
/* -------------------------------------------------------------------------- */
/* The following functions are called only in some turns                      */
/* as they are outcomes that depend on specific positions (e.g. jail)         */

/**
    This function adds the bank bonus to the player every time they pass go

    @param  game        the pointer to the game structure
    @return             none
*/
void getFromBank(Game *game);

/**
    This function dictates the outcome of the Feelin' Lucky space based on
    the dice value and returns an integer value about the outcome

    @param  game        the pointer to the game structure
    @return             0 if go to jail; 1 if get from bank; 2 if pay the bank,
                        has enough cash; 3 if pay the bank, not enough cash
*/
int playByLuck(Game *game);

/**
    This function sets the canPlay variable of the active player to 0

    @param  game        the pointer to the game structure
    @return             none
*/
void goToJail(Game *game);

/**
    This function allows player to sell their properties by updating
    the inventory and adding to their cash

    Pre-condition       The input member of the game structure
                        is a valid property owned by a player

    @param  game        the pointer to the game structure
    @return             none
*/
void sellProperty(Game *game, int propertyToSell);

#endif
