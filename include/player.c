#include "player.h"
#include <stdlib.h>
#include <string.h>

struct player{
    char *name;
    int index;
    int cash;
    Position *position;
    int canPlay;
};

/**********************************************************
 *              FUNCTIONS ABOUT THE PLAYERS
**********************************************************/

void initializePlayers(Player **player, int size){
    int i;

    *player = malloc(sizeof(Player) * size);

    // FIXME: second won't return a
    for(i = 0; i < size; i++){
        (*player)[i].canPlay = 1;
        (*player)[i].position = initializeNewPosition(0);
        (*player)[i].cash = INITIAL_CASH;
        (*player)[i].index = i;
    }
}

void updateCash(Player *player, int amount, int operation){
    // when operation is SUBTRACT (i.e. -1), the operation of
    // the equation turns to subtraction

    player->cash = player->cash + operation * amount;
}

int getPosition(Player *player){
    if(player == NULL || player->position == NULL)
        return 0;

    return player->position->data;
}

int getIndex(Player *player){
    if(player == NULL)
        return 0;
    return player->index;
}

int getCash(Player *player){
    if(player == NULL)
        return 0;
    return player->cash;
}

char *getName(Player *player){
    if(player == NULL)
        return 0;
    return player->name;
}

int getCanPlay(Player *player){
    if(player == NULL)
        return 0;
    return player->canPlay;
}

Player *player(Player *player){
    int currentIndex = getIndex(player);
    int newIndex = (currentIndex + 1) % 2;

    return &(player[newIndex]);
}

void setPosition(Player *player, int newPosition){
    pushPosition(&(player->position), newPosition);
}

void setIndex(Player *player, int index){
    player->index = index;
}

void setCash(Player *player, int cash){
    player->cash = cash;
}

void setCanPlay(Player *player, int canPlay){
    player->canPlay = canPlay;
}

void setName(Player *player, char *name){
    int src_length = strlen(name) + 1;
    player->name = malloc(src_length + 1);

    strncpy(player->name, name, src_length);
}

Player *nextPlayer(Player *player){
    int index = !(getIndex(player)) * 2 - 1;
    return player + index;
}

int previousPosition(Player *player){
    if(player->position->previous == NULL)
        return player->position->data;

    return player->position->previous->data;
}

int passesGo(Player *player){
    Position position = *(player->position);
    int current = position.data;
    int previous = position.previous->data;

    return current <= previous;
}

/**********************************************************
 *              FUNCTIONS ABOUT POSITION
**********************************************************/

Position *initializeNewPosition(int new){
    Position *position;
    position = malloc(sizeof(Position));
    position->data = new;
    position->previous = NULL;

    return position;
}

void pushPosition(Position **positions, int newPosition){
    Position *ptrNewPosition = initializeNewPosition(newPosition);

    // Move the pointer of the current position to the "previous" variable
    ptrNewPosition->previous = *positions;

    // Move the new position to the "top of the stack"
    *positions = ptrNewPosition;
}

void deallocatePositions(Position *position){

    // recursively goes to the previous members to deallocate each nodes
    if(position->previous != NULL){
        deallocatePositions(position->previous);
    }

    free(position);
}


/**********************************************************
 *              FUNCTIONS ABOUT PLAYER STATE
**********************************************************/
int isCashSufficient(int cash, int amount){
    return cash - amount >= 0;
}

int hasProperty(int inventory, int playerIndex){
    int flag = 0;
    int i;

    for(i = 0; i < 10 && !flag; i++){
        if(isOwnedByPlayer(inventory, i, playerIndex))
            flag = 1;
    }

    return flag;
}
