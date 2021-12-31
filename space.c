#include "space.h"
#include <math.h>


int isRenovated(int inventory, int position){
    int property = extractDigit(inventory, position);
    if(position == GO || position == JAIL_TIME || position == FEELIN_LUCKY)
        return 0;
    return property >= 3;
}

int isOwnedByBank(int inventory, int position){
    int property = extractDigit(inventory, position);
    if(position == GO || position == JAIL_TIME || position == FEELIN_LUCKY)
        return 0;
    return property == 0;
}

int isOwnedByPlayer(int inventory, int position, int playerIndex){
    int property = extractDigit(inventory, position);
    if(position == GO || position == JAIL_TIME || position == FEELIN_LUCKY || !property)
        return 0;
    return (property + playerIndex) % 2;
}