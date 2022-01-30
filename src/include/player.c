/*
    Description         This file contains the implementation details of the
                        player.h module
    Programmed by       Daniel L. Ramos III (S15A)
    Last modified       26-01-2022
    Version             3.0.0
*/

#include "player.h"
#include "error.h"
#include <stdlib.h>
#include <string.h>

/*
    NOTE: I was reading about linked list the other day and decided to try
    implementing it.

    I got so excited when I was successful so I decided to incorporate it
    in my MP.

    So I implemented a linked-list version of a stack especially since
    there are moments in the game where I have to compare the current
    position to the previous position.

    I know this is easily doable by making "previousPosition" and
    "currentPosition" variables but it isn't as fun and challenging 😅

    (And by "not as challenging", I meant there wasn't enough segfaults
    to make my hair split 😂)
*/

struct position {
    int data;                   // may be seen as the "top" of the stack
    struct position *previous;  // pointer to the previous position
};

struct player {
    char *name;
    int index;
    int cash;
    Position *position;
    int canPlay;
};

/* -------------------------------------------------------------------------- */
/*               MAJOR OPERATIONS INVOLVING THE PLAYER STRUCTURE              */
/* -------------------------------------------------------------------------- */

void initializePlayers(Player **player, int size) {
    int i;

    *player = malloc(sizeof(Player) * size);

    if(*player == NULL) {
        raiseNullPointerError(
            "Malloc of player pointer variable failed.",
            __FILE__, __func__, __LINE__
        );
    }

    for(i = 0; i < size; i++) {
        (*player)[i].canPlay = 1;
        (*player)[i].position = initializeNewPosition(0);
        (*player)[i].cash = INITIAL_CASH;
        (*player)[i].index = i;
    }
}

void updateCash(Player *player, int amount, int operation) {
    if(player == NULL) {
        raiseNullPointerError(
            "Player variable should not be null",
            __FILE__, __func__, __LINE__
        );
    }

    // when operation is SUBTRACT (i.e. -1), the operation of
    // the equation turns to subtraction

    player->cash = player->cash + operation * amount;
}

int isCashSufficient(int cash, int amount) {
    return cash - amount >= 0;
}

int passesGo(Player *player) {
    Position position;
    int current;
    int previous;

    position = *(player->position);
    current = position.data;
    previous = position.previous->data;

    return current <= previous;
}

Player *nextPlayer(Player *player) {
    int index;

    index = !(getIndex(player)) * 2 - 1;
    return player + index;
}

int previousPosition(Player *player) {
    if(player == NULL) {
        raiseNullPointerError(
            "Player variable should not be null",
            __FILE__, __func__, __LINE__
        );
    }

    if(player->position == NULL) {
        raiseNullPointerError(
            "Position variable should not be null at this point",
            __FILE__, __func__, __LINE__
        );
    }

    // this is if the game just started; therefore, not having previous
    if(player->position->previous == NULL)
        return player->position->data;

    return player->position->previous->data;
}

void cleanPlayer(Player *player) {
    deallocatePositions(player->position);
    free(player->name);
    free(player);
}

/* -------------------------------------------------------------------------- */
/*                   GETTERS AND SETTERS OF PLAYER STRUCTURE                  */
/* -------------------------------------------------------------------------- */

int getPosition(Player *player) {
    if(player == NULL) {
        raiseNullPointerError(
            "Player variable should not be null",
            __FILE__, __func__, __LINE__
        );
    }

    if(player->position == NULL) {
        raiseNullPointerError(
            "Position variable should not be null at this point",
            __FILE__, __func__, __LINE__
        );
    }

    return player->position->data;
}

int getIndex(Player *player) {
    if(player == NULL) {
        raiseNullPointerError(
            "Player variable should not be null",
            __FILE__, __func__, __LINE__
        );
    }

    return player->index;
}

int getCash(Player *player) {
    if(player->position == NULL) {
        raiseNullPointerError(
            "Player variable should not be null",
            __FILE__, __func__, __LINE__
        );
    }

    return player->cash;
}

int getCanPlay(Player *player) {
    if(player->position == NULL) {
        raiseNullPointerError(
            "Player variable should not be null",
            __FILE__, __func__, __LINE__
        );
    }

    return player->canPlay;
}

char *getName(Player *player) {
    if(player->position == NULL) {
        raiseNullPointerError(
            "Player variable should not be null",
            __FILE__, __func__, __LINE__
        );
    }

    return player->name;
}

void setPosition(Player *player, int newPosition) {
    if(player == NULL) {
        raiseNullPointerError(
            "Player variable should not be null",
            __FILE__, __func__, __LINE__
        );
    }

    if(player->position == NULL) {
        raiseNullPointerError(
            "Position variable should not be null at this point",
            __FILE__, __func__, __LINE__
        );
    }

    pushPosition(&(player->position), newPosition);
}

void setCanPlay(Player *player, int canPlay) {
    if(player == NULL) {
        raiseNullPointerError(
            "Player variable should not be null",
            __FILE__, __func__, __LINE__
        );
    }

    player->canPlay = canPlay;
}

int setName(Player *player, char *name) {
    int src_length = strlen(name);

    if(player == NULL) {
        raiseNullPointerError(
            "Player variable should not be null",
            __FILE__, __func__, __LINE__
        );
    }

    if(src_length > MAX_NAME_CHAR)
        return SET_NAME_FAILURE;

    player->name = malloc(src_length + 1);

    strncpy(player->name, name, src_length + 1);

    return SET_NAME_SUCCESS;
}

void setIndex(Player *player, int index) {
    if(player == NULL) {
        raiseNullPointerError(
            "Player variable should not be null",
            __FILE__, __func__, __LINE__
        );
    }

    player->index = index;
}

void setCash(Player *player, int cash) {
    if(player == NULL) {
        raiseNullPointerError(
            "Player variable should not be null",
            __FILE__, __func__, __LINE__
        );
    }

    player->cash = cash;
}


/* -------------------------------------------------------------------------- */
/*                   FUNCTIONS INVOLVING THE POSITION STACK                   */
/* -------------------------------------------------------------------------- */

Position *initializeNewPosition(int new) {
    Position *position;
    position = malloc(sizeof(Position));
    position->data = new;
    position->previous = NULL;

    return position;
}

void pushPosition(Position **positions, int newPosition) {
    Position *ptrNewPosition = initializeNewPosition(newPosition);

    // Move the pointer of the current position to the "previous" variable
    ptrNewPosition->previous = *positions;

    // Move the new position to the "top of the stack"
    *positions = ptrNewPosition;
}

void deallocatePositions(Position *positionStack) {

    // recursively goes to the previous members to deallocate each nodes
    if(positionStack->previous != NULL) {
        deallocatePositions(positionStack->previous);
    }

    free(positionStack);
}
