#include "player.h"
#include <stdlib.h>

/**********************************************************
 *              FUNCTIONS ABOUT THE PLAYERS
**********************************************************/

void initializePlayer(Player *player){
    player->canPlay = 1;
    player->cash = 0;
    player->position = initializeNewPosition(0);
    player->cash = INITIAL_CASH;
    player->ownedProperties = malloc(sizeof(Property));
    player->ownedProperties[0] = NULL;
}

void updateCash(float *cash, float amount, int operation){
    *cash = *cash + operation * amount;
}


int passesGo(Position position){
    int current = position.current;
    int previous = position.previous->current;

    return current < previous;
}

/**********************************************************
 *              FUNCTIONS ABOUT POSITION
**********************************************************/

Position *initializeNewPosition(int new){
    Position *position;
    position = malloc(sizeof(Position));
    position->current = new;
    position->previous = NULL;

    return position;
}

void pushPosition(Position **positions, int newPosition){
    Position *ptrNewPosition = initializeNewPosition(newPosition);

    // Move the pointer of the current position 
    // to the "previous" variable 
    ptrNewPosition->previous = *positions;

    // Move the new position to the "top of the stack"
    *positions = ptrNewPosition;
}

void deallocatePositions(Position *position){
    if(position->previous != NULL){
        deallocatePositions(position->previous);
    }

    free(position);
}


/**********************************************************
 *              FUNCTIONS ABOUT PLAYER STATE
**********************************************************/
int isCashSufficient(float cash, float amount){
    return cash - amount >= 0;
}

int hasProperty(Property **ownedProperties){
    return ownedProperties[0] != NULL;
}
