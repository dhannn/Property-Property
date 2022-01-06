/**********************************************************
*
*   Description:        This header file contains functions
*   Programmed by:      Daniel III L. Ramos
*   Last Modified:      12-26-2021
*   Version:            1.0
*
*   Acknowledgements:
*
**********************************************************/

#include "space.h"
#define ADD 1
#define SUBTRACT -1
#define MAX_NAME_CHAR 10

#ifndef PLAYER_H
#define PLAYER_H
enum playerState{
    HAS_CASH = 0b01,
    HAS_PROPERTY = 0b10
};

typedef struct position{
    int data;        // may be seen as the "top" of the stack
    struct position *previous; // pointer to the previous position
} Position;

typedef struct player Player;

#define INITIAL_CASH 400.0
#define BANK_BONUS 50.0
#define COST_MULTIPLIER 1
#endif

/**
 * This function initializes members of the Player structure.
 *
 * @param player        a pointer to the player being initialized
 * @param index         the index of the player in the game
 */
void initializePlayers(Player **player, int size);

/**
 * This function returns 1 if the player passes the "Go" space and 0 if otherwise.
 *
 * @param position      the position stack that contains the current and
 *                      previous positions
 * @return              boolean values
 */
int passesGo(Player *player);
int getPosition(Player *player);
int getIndex(Player *player);
int getCash(Player *player);
int getCanPlay(Player *player);
char *getName(Player *player);
void setPosition(Player *player, int newPosition);
void setCanPlay(Player *player, int canPlay);
void setName(Player *player, char *name);
Player *nextPlayer(Player *player);
int previousPosition(Player *player);


/**
 * This function updates cash by adding or subtracting a specified amount
 *
 * @param cash          a pointer to the cash to be updated
 * @param amount        the amount to be added or subtracted
 * @param operation     1 for adding or -1 for subtracting
 */
void updateCash(Player *player, int amount, int operation);

// The following deals with the stack data structure of position
/**
 * This function initializes the position stack
 *
 * @param new           the initialized value of the current position
 * @return Position*
 */
Position *initializeNewPosition(int new);
/**
 * This function pushes a new value to the position stack
 *
 * @param positionStack pointer to the pointer of the stack
 * @param newPosition   the value to be pushed into the top
 */
void pushPosition(Position **positionStack, int newPosition);
/**
 * This function recursively deallocates the memory of each element of
 * the stack until the previous member becomes null.
 *
 * @param position      pointer to the stack being deallocated
 */
void deallocatePositions(Position *position);

/**
 * This function returns 1 if the cash-in-hand is sufficient
 * for a transaction and 0 if otherwise.
 *
 * @param cash          current cash of the player
 * @param amount        amount needed for the transaction
 * @return int
 */
int isCashSufficient(int cash, int amount);
/**
 * This function returns 1 if the player has at least one property
 * and 0 if otherwise.
 *
 * @param inventory     inventory that contains ownership information
 * @param playerIndex   index of the player to be checked
 * @return int
 */
int hasProperty(int inventory, int playerIndex);
