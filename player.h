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
    which is a perfect fit for a stack data structure.

    I know a simple "currentPosition" variable, a simple
    "previousPosition" variable and a swapping function
    can do the job just as easily but where's the fun
    in that? 😅
*/
typedef struct position{
    int current;        // may be seen as the top of the stack
    struct position *previous; // pointer to the previous position
} Position;

struct player{
    char name[MAX_NAME_CHAR];
    int index;
    float cash;
    Position *position;
    int canPlay;
    Property **ownedProperties;
};

typedef struct player Player;

#define INITIAL_CASH 400.0
#define BANK_BONUS 50.0
#define COST_MULTIPLIER 2.0
#endif

void initializePlayer(Player *player);
int passesGo(Position position);
int getPosition(Player player);
void updateCash(float *cash, float amount, int operation);

// The following deals with the stack data structure of position
Position *initializeNewPosition(int new);
void pushPosition(Position **currentPosition, int newPosition);
void deallocatePositions(Position *position);

// The following are used for getting the player state
int isCashSufficient(float cash, float amount);
int hasProperty(Property **ownedProperties);


