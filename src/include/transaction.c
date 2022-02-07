/*

    Description         This file contains the implementation details of the
                        transaction.h module
    Programmed by       Daniel III L. Ramos (S15A)
    Last Modified       06-02-2022
    Version             3.5.0

*/

#include "transaction.h"
#include "player.h"
#include "helper.h"
#include <stdlib.h>


/* -------------------------------------------------------------------------- */
/*                  FUNCTIONS INVOLVING SPACE AND SPACE INFO                  */
/* -------------------------------------------------------------------------- */

int getSpaceInfo(Player *player, int inventory) {
    int position = getPosition(player);
    int index = getIndex(player);
    int spaceInfo = 0;

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
        spaceInfo = spaceInfo | PROPERTY_BY_PLAYER;
    else
        spaceInfo = spaceInfo | PROPERTY_BY_OTHER;

    if(isRenovated(inventory, position))
        spaceInfo = spaceInfo | PROPERTY_IS_RENOVATED;

    return spaceInfo;
}

int isRenovated(int inventory, int position) {
    int property = extractDigit(inventory, position);
    if(position == GO || position == JAIL_TIME || position == FEELIN_LUCKY)
        return 0;
    return property >= 3;
}

int isOwnedByBank(int inventory, int position) {
    int property = extractDigit(inventory, position);
    if(position == GO || position == JAIL_TIME || position == FEELIN_LUCKY)
        return 0;
    return property == 0;
}

int isOwnedByPlayer(int inventory, int position, int playerIndex) {
    int property = extractDigit(inventory, position);

    if(
        position == GO || position == JAIL_TIME ||
        position == FEELIN_LUCKY || !property
    )
        return 0;
    return (property + playerIndex) % 2;
}

/* -------------------------------------------------------------------------- */
/*                      FUNCTIONS INVOLVING THE INVENTORY                     */
/* -------------------------------------------------------------------------- */

void updateInventory(int *inventory, int position, int newStatus) {
    setDigit(inventory, position, newStatus);
}

int getOwner(int inventory, int position) {
    int property = extractDigit(inventory, position);

    if(!property)
        return -1;

    return (property + 1) % 2;
}

int hasProperty(int inventory, int playerIndex) {
    int flag = 0;
    int i;

    for(i = 0; i < 10 && !flag; i++)
        if(isOwnedByPlayer(inventory, i, playerIndex))
            flag = 1;

    return flag;
}

/* -------------------------------------------------------------------------- */
/*              MAJOR OPERATIONS INVOLVING TRANSACTION STRUCTURE              */
/* -------------------------------------------------------------------------- */

TransactionType getTransactionType(int spaceInfo) {
    if(spaceInfo & PROPERTY_BY_BANK)
        return BUY_PROPERTY;
    else if(spaceInfo & PROPERTY_BY_PLAYER)
        return RENOVATE_PROPERTY;
    else if(spaceInfo & PROPERTY_BY_OTHER)
        return PAY_RENT;

    return NULL_TRANSACTION;
}

int getNewDigit(Player *player, int inventory, TransactionType transactionType) {
    int position = getPosition(player);
    int index = getIndex(player);
    int status = extractDigit(inventory, position);

    switch(transactionType) {
        case BUY_PROPERTY:
            status = index + 1;
            break;
        case RENOVATE_PROPERTY:
            status += 2;
            break;
        case PAY_RENT:
        case NULL_TRANSACTION:
            break;
    }

    return status;
}

int getAmount(int spaceInfo, int position, int inventory, int dice, float mult) {
    int buyingCost = 20.0 * (position % 7);
    int rentingCost = (1.0/5.0) * buyingCost;


    if(spaceInfo & PROPERTY_BY_BANK) {
        if(position == ELECTRIC_COMPANY)
            return ELECTRIC_COMPANY_BUYING_COST * mult;
        if(position == RAILROAD)
            return RAILROAD_BUYING_COST * mult;

        return buyingCost * mult;
    }

    if(spaceInfo & PROPERTY_BY_PLAYER) {
        if(position == ELECTRIC_COMPANY || position == RAILROAD)
            return 0;
        return RENOVATION_COST * mult;
    }

    if(spaceInfo & PROPERTY_BY_OTHER) {
        if(position == ELECTRIC_COMPANY)
            return 8 * dice * mult;

        if(position == RAILROAD)
            return RAILROAD_RENTING_COST * mult;

        if(spaceInfo & PROPERTY_IS_RENOVATED)
            rentingCost = 1 + 2 * rentingCost;

        return rentingCost * mult;
    }

    if(spaceInfo & PROPERTY_TO_SELL) {
        if(position == ELECTRIC_COMPANY)
            return ELECTRIC_COMPANY_BUYING_COST * mult / 2;

        if(position == RAILROAD)
            return RAILROAD_BUYING_COST * mult / 2;

        return buyingCost * mult / 2;
    }

    return -1;
}

void enactTransaction(Player *player, Transaction transaction, int *inventory) {
    int amount = transaction.amount;
    int newStatus = transaction.newStatus;
    int position = getPosition(player);

    updateCash(player, amount, SUBTRACT);
    updateInventory(inventory, position, newStatus);

    // Pays the rent to the other player
    if(transaction.transactionType == PAY_RENT) {
        Player *rentee = nextPlayer(player);
        updateCash(rentee, amount, ADD);
    }
}
