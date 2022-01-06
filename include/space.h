#include <stdint.h>
#define MAX_CHAR 10
#define MAX_SPACES 9

#ifndef SPACE_H
#define SPACE_H
/**
 * To represent the state of the space, 
 * I decided to implement a bitmask for a)
 * better readability and b) easy operations.
 */
enum spaceState {
    IS_GO                       =   0b000000100, // 4d
    IS_FEELIN_LUCKY             =   0b000001000, // 8d
    IS_JAIL_TIME                =   0b000010000, // 16d
    PROPERTY_BY_BANK            =   0b000100000, // 32d
    PROPERTY_BY_PLAYER          =   0b001000000, // 64d
    PROPERTY_BY_OTHER           =   0b010000000, // 128d
    PROPERTY_IS_RENOVATED       =   0b100000000, // 256d
};

#define GO                  0
#define TREEHOUSE           1
#define ELECTRIC_COMPANY    2
#define BEACH_HOUSE         3
#define JAIL_TIME           4
#define CASTLE              5
#define FEELIN_LUCKY        6
#define RAILROAD            7
#define IGLOO               8
#define FARMHOUSE           9
#endif

// void initializeSpace(Space *space);
// char *getSpaceName(Space space);

// The following functions are used for getting the state
int isRenovated(int inventory, int position);
int isOwnedByBank(int inventory, int position);
int isOwnedByPlayer(int inventory, int position, int playerIndex);

// The following functions are used for validating inputs
int isProperty(int position);
int isWithinRange(int position);
