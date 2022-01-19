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

int getPlayerState(Player *player, int inventory, Transaction transaction){
    int state = 0;
    int cash = getCash(player);
    int amount = transaction.amount;
    int index = getIndex(player);

    if(isCashSufficient(cash, amount))
        state = state | HAS_CASH;

    if(hasProperty(inventory, index))
        state = state | HAS_PROPERTY;

    return state;
}

TransactionType getTransactionType(int spaceState){
    if(spaceState & PROPERTY_BY_BANK)
        return BUY_PROPERTY;
    else if(spaceState & PROPERTY_BY_PLAYER)
        return RENOVATE_PROPERTY;
    else if(spaceState & PROPERTY_BY_OTHER)
        return PAY_RENT;

    return NULL_TRANSACTION;
}

int getNewState(Player *player, int inventory, TransactionType transactionType){
    return 2;
}

int getAmount(int state, int position, int inventory, int dice){
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

    return -1;
}

int getOwner(int inventory, int position){
    int property = extractDigit(inventory, position);

    if(!property)
        return -1;

    return (property + 1) % 2;
}

void enactTransaction(Player *player, Transaction transaction, int *inventory){
    int amount = transaction.amount;
    int operation = transaction.operation;
    int newStatus = transaction.newStatus;
    int position = getPosition(player);

    updateCash(player, amount, operation);
    updateInventory(inventory, position, newStatus);
}
