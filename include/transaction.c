#include "transaction.h"
#include "player.h"
#include "space.h"
#include "helper.h"
#include <stdlib.h>

void updateInventory(int *inventory, int position, int newStatus){
    setDigit(inventory, position, newStatus);
}

int getSpaceState(Player *player, int inventory){
    int position = getPosition(player);
    int index = getIndex(player);
    int state = 0;

    // Checks non-property spaces
    if(position == GO)
        return IS_GO;

    if(position == FEELIN_LUCKY)
        return IS_FEELIN_LUCKY;

    if(position == JAIL_TIME)
        return IS_JAIL_TIME;


    // Checks property spaces
    if(isOwnedByBank(inventory, position))
        return PROPERTY_BY_BANK;

    if(isOwnedByPlayer(inventory, position, index))
        state = state | PROPERTY_BY_PLAYER;
    else
        state = state | PROPERTY_BY_OTHER;

    if(isRenovated(inventory, position))
        state = state | PROPERTY_IS_RENOVATED;

    return state;
}

// enum transactionType getTransactionType(int gameState){
//     if(gameState & IS_GO)
//         return GET_BANK_BONUS;
//     if(gameState & PROPERTY_BY_BANK)
//         return GET_FROM_BANK;
//     if(gameState & PROPERTY_BY_PLAYER)
//         return RENOVATE_PROPERTY;
//     if(gameState & PROPERTY_BY_OTHER)
//         return PAY_RENT;
// }

int getAmount(enum spaceState state, int position, int inventory, int dice){
    int buyingCost = 20.0 * (position % 7) * COST_MULTIPLIER;
    int rentingCost = (1.0/5.0) * buyingCost * COST_MULTIPLIER;

    if(state & PROPERTY_BY_BANK){
        if(position == ELECTRIC_COMPANY)
            return ELECTRIC_COMPANY_BUYING_COST;
        if(position == RAILROAD)
            return RAILROAD_BUYING_COST;

        return buyingCost;
    }

    if(state & PROPERTY_BY_PLAYER)
        return RENOVATION_COST;

    if(state & PROPERTY_BY_OTHER){
        if(position == ELECTRIC_COMPANY)
            return 8 * dice;

        if(position == RAILROAD)
            return RAILROAD_RENTING_COST;

        if(state & PROPERTY_IS_RENOVATED)
            rentingCost = 1 + 2 * rentingCost;

        return rentingCost;
    }
}

int getOwner(int inventory, int position){
    int property = extractDigit(inventory, position);

    if(!property)
        return -1;

    return (property + 1) % 2;
}

int getPlayerState(Player *player, enum spaceState sState, int inventory){
    int position = getPosition(player);
    int cash = getCash(player);
    int playerState = 0;

    int cost = getAmount(position, inventory, sState, 0);

    if(hasProperty(inventory, getIndex(player)))
        playerState = playerState | HAS_PROPERTY;

    if(isCashSufficient(cash, cost))
        playerState = playerState | HAS_CASH;

    return playerState;
}

int getNewState(Player *player, int inventory,  enum transactionType tr){
    int propertyStatus = extractDigit(inventory, getPosition(player));
    int index = getIndex(player);

    switch(tr){
        case GET_BANK_BONUS:
        case GET_FROM_BANK:
        case PAY_BANK:
        case PAY_RENT:
            return propertyStatus;
        case BUY_PROPERTY:
            return index + 1;
        case RENOVATE_PROPERTY:
            return index + 3;
        case SELL_PROPERTY:
            return 0;
    }

    return -1;
}

int getOperation(enum transactionType tr){
    switch(tr){
        case GET_BANK_BONUS:
        case GET_FROM_BANK:
        case SELL_PROPERTY:
            return ADD;
        case PAY_BANK:
        case BUY_PROPERTY:
        case RENOVATE_PROPERTY:
        case PAY_RENT:
        case PAY_RENT_RENOVATED:
            return SUBTRACT;
    }

    return -1;
}
