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
struct game{
    Player players[MAX_PLAYERS];    // the players
    Player *activePlayer;           // pointer to the current player
    int inventory;                  // contains ownership details
    int dice;                       // contains the current dice value
    int isBankrupt;                 // boolean 
    int state;                      // a bitfield  
};

typedef struct game Game;
#endif

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
void incrementTurn(Player player[MAX_PLAYERS], Player **activePlayer);
