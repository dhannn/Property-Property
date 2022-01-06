#include "game.h"
#include <stdlib.h>
#include <time.h>


void initializeGame(Game *game){
    int i;
    srand(13);

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
    int playerState = getPlayerState(player, spaceState, inventory);

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
    int turn = (getIndex(*activePlayer) + 1) % MAX_PLAYERS;
    *activePlayer = nextPlayer(*activePlayer);
}

void enactTransaction(Game *game, enum transactionType tr){
    Transaction transaction;
    Player *player = game->activePlayer;

    int state = game->state;
    int position = getPosition(player);
    int dice = game->dice;
    int *inventory = &(game->inventory);

    transaction.amount = getAmount(state, position, *inventory, dice);
    transaction.newState = getNewState(player, *inventory, tr);
    transaction.operation = getOperation(tr);

    updateCash(player, transaction.amount, transaction.operation);
    updateInventory(inventory, position, transaction.newState);
}

enum transactionType getTransactionType(int state){
    if(state & PROPERTY_BY_BANK && state & HAS_CASH)
        return BUY_PROPERTY;

    if(state & PROPERTY_BY_PLAYER && !(state & PROPERTY_IS_RENOVATED))
        return RENOVATE_PROPERTY;

    if(state & PROPERTY_BY_OTHER && !(state & PROPERTY_IS_RENOVATED))
        return PAY_RENT;

    if(state & PROPERTY_BY_OTHER && state & PROPERTY_IS_RENOVATED)
        return PAY_RENT_RENOVATED;

    return NULL_TRANSACTION;
}
