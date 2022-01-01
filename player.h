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


/*
    I've been reading about data structures 
    for a while now and just recently, I learned 
    how to implement a linked list.

    And so, naturally, I wanted to try it in this 
    project. Luckily, there is a part in my program
    where I need to refer to previous position 
    which is a perfect fit for a stack data structure
    (I think).

    I know a simple "currentPosition" variable, a simple
    "previousPosition" variable and a swapping function
    can do the job just as easily but where's the fun
    in that? 😅
*/
typedef struct position{
    int current;        // may be seen as the "top" of the stack
    struct position *previous; // pointer to the previous position
} Position;

struct player{
    char name[MAX_NAME_CHAR];
    int index;
    float cash;
    Position *position;
    int canPlay;
};

typedef struct player Player;

#define INITIAL_CASH 400.0
#define BANK_BONUS 50.0
#define COST_MULTIPLIER 2.0
#endif

/**
 * This function initializes members of the Player structure.
 * 
 * @param player        a pointer to the player being initialized
 */
void initializePlayer(Player *player);

/**
 * This function returns 1 if the player passes the "Go" space and 0 if otherwise.
 * 
 * @param position      the position stack that contains the current and 
 *                      previous positions
 * @return              boolean values
 */
int passesGo(Position position);
int getPosition(Player player);

/**
 * This function updates cash by adding or subtracting a specified amount
 * 
 * @param cash          a pointer to the cash to be updated
 * @param amount        the amount to be added or subtracted
 * @param operation     1 for adding or -1 for subtracting
 */
void updateCash(float *cash, float amount, int operation);

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
int isCashSufficient(float cash, float amount);
/**
 * This function returns 1 if the player has at least one property 
 * and 0 if otherwise.
 * 
 * @param inventory     inventory that contains ownership information
 * @param playerIndex   index of the player to be checked
 * @return int 
 */
int hasProperty(int inventory, int playerIndex);


