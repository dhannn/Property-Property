#include "game.h"
#include "helper.h"
#include <stdlib.h>
#include <time.h>


void initializeGame(Game *game){
    srand(1);

    game->dice = 0;
    game->inventory = 0;
    game->isBankrupt = 0;

    initializePlayers(&(game->players), MAX_PLAYERS);
    game->activePlayer = game->players;
    game->transaction.transactionType = NULL_TRANSACTION;
    game->transaction.amount = 0;
    game->transaction.newStatus = 0;
    game->transaction.operation = ADD;
}

void rollDice(int *dice){
    int diceValue = rand() % 6 + 1;
    *dice = diceValue;
}

void movePlayer(Player *activePlayer, int dice){
    int new = (getPosition(activePlayer) + dice) % 10;
    setPosition(activePlayer, new);
}

void makeTransaction(Game *game){
    Player *player = game->activePlayer;
    int inventory = game->inventory;
    Transaction *transaction = &(game->transaction);
    int spaceState = getSpaceState(player, inventory);

    transaction->transactionType = getTransactionType(spaceState);
    transaction->newStatus = getNewState(player, inventory, transaction->transactionType);
    transaction->amount = getAmount(spaceState, getPosition(player), game->inventory, game->dice);
    transaction->operation = getOperation(transaction->transactionType);
}

void updateState(Game *game){
    Player *player = game->activePlayer;
    State *state = &(game->state);

    int position = getPosition(player);
    int inventory = game->inventory;
    int dice = game->dice;
    int spaceState = getSpaceState(player, inventory);
    int cash = getCash(player);
    int amount = getAmount(spaceState, position, inventory, dice);
    int hasCash = isCashSufficient(cash, amount);

    if(bitcmp(spaceState, IS_FEELIN_LUCKY))
        *state = PLAY_BY_LUCK;
    else if(bitcmp(spaceState, IS_JAIL_TIME))
        *state = GO_TO_JAIL;
    else if(bitcmp(spaceState, PROPERTY_BY_BANK) && hasCash)
        *state = CAN_BUY;
    else if(bitcmp(spaceState, PROPERTY_BY_BANK) && !hasCash)
        *state = CANNOT_BUY;
    else if(bitcmp(spaceState, PROPERTY_BY_PLAYER) && !bitcmp(spaceState, PROPERTY_IS_RENOVATED) && hasCash)
        *state = CAN_RENOVATE;
    else if(bitcmp(spaceState, PROPERTY_BY_PLAYER) && !bitcmp(spaceState, PROPERTY_IS_RENOVATED) && !hasCash)
        *state = CANNOT_RENOVATE;
    else if(bitcmp(spaceState, PROPERTY_BY_OTHER) && hasCash)
        *state = CAN_PAY;
    else if(bitcmp(spaceState, PROPERTY_BY_OTHER) && !hasCash)
        *state = CANNOT_PAY;
    else
        *state = DO_NOTHING;
}

void incrementTurn(Player *player[MAX_PLAYERS], Player **activePlayer){
    *activePlayer = nextPlayer(*activePlayer);
}

int playByLuck(Game *game){
    int dice = game->dice;
    Player *player = game->activePlayer;
    int amount;

    if(dice == 1){
        setCanPlay(player, 0);
        return LUCK_IS_JAIL;
    }

    if(isPrime(dice)){
        amount = rand() % GET_BANK_RANGE + GET_BANK_MIN;
        game->transaction.amount = amount;
        game->transaction.operation = ADD;

        return LUCK_IS_GET_BANK;
    } else{
        amount = rand() % PAY_BANK_RANGE + PAY_BANK_MIN;
        game->transaction.amount = amount;
        game->transaction.operation = SUBTRACT;

        return LUCK_IS_PAY_BANK;
    }
}

void goToJail(Game *game){
    Player *activePlayer = game->activePlayer;

    setCanPlay(activePlayer, 0);
}

void sellProperty(Game *game){
    int position = atoi(&(game->input));
    int *inventory = &(game->inventory);
    int state = game->state;
    int dice = game->dice;

    int amount = getAmount(state, position, *inventory, dice);
    Player *player = game->activePlayer;

    updateCash(player, amount, ADD);
    updateInventory(inventory, position, 0);
}
