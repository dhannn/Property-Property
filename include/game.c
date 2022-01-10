#include "game.h"
#include <stdlib.h>
#include <time.h>


void initializeGame(Game *game){
    srand(1);

    game->dice = 0;
    game->inventory = 0;
    game->isBankrupt = 0;

    initializePlayers(&(game->players), MAX_PLAYERS);
    game->activePlayer = game->players;
}

void rollDice(int *dice){
    int diceValue = rand() % 6 + 1;
    *dice = diceValue;
}

void movePlayer(Player *activePlayer, int dice){
    int new = (getPosition(activePlayer) + dice) % 10;
    setPosition(activePlayer, new);
}

void getGameState(Game *game){
    Player *player = game->activePlayer;
    int inventory = game->inventory;

    int spaceState = getSpaceState(player, inventory);
    int playerState = getPlayerState(player, spaceState, inventory, game->dice);

    if(spaceState & IS_JAIL_TIME)
        game->state = GO_JAIL;

    else if(spaceState & IS_FEELIN_LUCKY)
        game->state = LUCKY;

    else if(spaceState & PROPERTY_BY_PLAYER && spaceState & PROPERTY_IS_RENOVATED)
        game->state = ALREADY_RENOVATED;

    else if(playerState & HAS_CASH){
        if(spaceState & PROPERTY_BY_BANK)
            game->state = CAN_BUY;

        if(spaceState & PROPERTY_BY_PLAYER && !(spaceState & PROPERTY_IS_RENOVATED))
            game->state = CAN_RENOVATE;

        if(spaceState & PROPERTY_BY_OTHER)
            game->state = CAN_PAY_RENT;
    } else {
        if(spaceState & PROPERTY_BY_BANK)
            game->state = CANNOT_BUY;

        if(spaceState & PROPERTY_BY_PLAYER && !(spaceState & PROPERTY_IS_RENOVATED))
            game->state = CANNOT_RENOVATE;

        if(spaceState & PROPERTY_BY_OTHER && spaceState & HAS_PROPERTY)
            game->state = CANNOT_PAY_RENT;

        if(spaceState & PROPERTY_BY_OTHER && !(spaceState & HAS_PROPERTY))
            game->state = BANKRUPT;
    }
}

void incrementTurn(Player *player[MAX_PLAYERS], Player **activePlayer){
    *activePlayer = nextPlayer(*activePlayer);
}

void enactTransaction(Game *game){
    Transaction transaction = game->transaction;
    Player *player = game->activePlayer;

    int position = getPosition(player);
    int *inventory = &(game->inventory);

    updateCash(player, transaction.amount, transaction.operation);
    updateInventory(inventory, position, transaction.newState);
}

enum transactionType getTransactionType(int state){
    switch(state){
        case CAN_BUY:
            return BUY_PROPERTY;
        case CAN_RENOVATE:
            return RENOVATE_PROPERTY;
        case CAN_PAY_RENT:
            return PAY_RENT;
        case CAN_PAY_RENT_RENOVATED:
            return PAY_RENT_RENOVATED;
    }

    return -1;
}

int getAmountFromTransactionType(TransactionType tr, int position, int dice){
    int buyingCost = 20 * (position % 7);
    int rentingCost = buyingCost / 5;

    if(position == ELECTRIC_COMPANY && tr == BUY_PROPERTY)
        return ELECTRIC_COMPANY_BUYING_COST * COST_MULTIPLIER;

    if(position == ELECTRIC_COMPANY && (tr == PAY_RENT || tr == PAY_RENT_RENOVATED))
        return 8 * dice * COST_MULTIPLIER;

    if(position == RAILROAD && tr == BUY_PROPERTY)
        return RAILROAD_BUYING_COST * COST_MULTIPLIER;

    if(position == ELECTRIC_COMPANY && (tr == PAY_RENT || tr == PAY_RENT_RENOVATED))
        return RAILROAD_RENTING_COST * COST_MULTIPLIER;

    switch(tr){
        case BUY_PROPERTY:
            return buyingCost;
        case RENOVATE_PROPERTY:
            return RENOVATION_COST * COST_MULTIPLIER;
        case PAY_RENT_RENOVATED:
            rentingCost = 1 + 2 * rentingCost;
        case PAY_RENT:
            return rentingCost;
    }

    // NULL_TRANSACTION,
    // GET_BANK_BONUS,
    // GET_FROM_BANK,
    // PAY_BANK,
    // BUY_PROPERTY,
    // RENOVATE_PROPERTY,
    // PAY_RENT,
    // PAY_RENT_RENOVATED,
    // SELL_PROPERTY
}
