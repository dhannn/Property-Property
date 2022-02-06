/*
    Description         This file contains the implementation of functions
                        in the game.h module
    Programmed by       Daniel III L. Ramos (S15A)
    Last Modified       05-02-2022
    Version             3.1.0
*/

#include "game.h"
#include "helper.h"
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

uint32_t initializeSeed() {
    uint32_t rand1 = time(NULL) ^ 2;
    uint32_t rand2 = rand1 + time(NULL) / 10;
    uint32_t key = time(NULL);

    rand1 = rand1 - rand2;
    rand1 = rand1 - key;
    rand1 = rand1 ^ (key >> 13);

    rand2 = rand2 - key;
    rand2 = rand2 - rand1;
    rand2 = rand2 ^ (rand1 << 8);

    key = key - rand1;
    key = key - rand2;
    key = key ^ (rand2 >> 13);

    rand1 = rand1 - rand2;
    rand1 = rand1 - key;
    rand1 = rand1 ^ (key >> 12);

    rand2 = rand2 - key;
    rand2 = rand2 - rand1;
    rand2 = rand2 ^ (rand1 << 16);

    key = key - rand1;
    key = key - rand2;
    key = key ^ (rand2 >> 5);

    rand1 = rand1 - rand2;
    rand1 = rand1 - key;
    rand1 = rand1 ^ (key >> 3);

    rand2 = rand2 - key;
    rand2 = rand2 - rand1;
    rand2 = rand2 ^ (rand1 << 10);

    key = key - rand1;
    key = key - rand2;
    key = key ^ (rand2 >> 15);

    return key;
}

/* -------------------------------------------------------------------------- */
/*                            MAIN GAME OPERATIONS                            */
/* -------------------------------------------------------------------------- */
/* The following functions are always called in every turn                    */
/* as they are constants in the main game loop                                */

void initializeGame(Game *game) {

    game->id = initializeSeed();
    srand(game->id);

    game->dice = 0;
    game->inventory = 0;
    game->isBankrupt = 0;

    initializePlayers(&(game->players), MAX_PLAYERS);

    // calling the players pointer returns the pointer of first player
    game->activePlayer = game->players;

    game->transaction.transactionType = NULL_TRANSACTION;
    game->transaction.amount = 0;
    game->transaction.newStatus = 0;
}

void rollDice(int *dice) {
    // rand() % 6 returns 0 - 5; adding 1 will normalize the value
    int diceValue = rand() % 6 + 1;
    *dice = diceValue;
}

void movePlayer(Player *activePlayer, int dice) {
    int new = (getPosition(activePlayer) + dice) % 10;
    setPosition(activePlayer, new);
}

void updateState(Game *game) {
    Player *player = game->activePlayer;
    State *state = &(game->state);

    int position = getPosition(player);
    int inventory = game->inventory;
    int dice = game->dice;

    int spaceInfo = getSpaceInfo(player, inventory);

    int amount = getAmount(spaceInfo, position, inventory, dice);
    int cash = getCash(player);
    int hasCash = isCashSufficient(cash, amount);


    // The following checks certain conditions and assigns a state
    // once certain conditions are met (e.g. can renovate only if
    // 1) the property is owned by the player, 2) the property is
    // not renovated and 3) the player has sufficient cash)

    if(bitcmp(spaceInfo, IS_FEELIN_LUCKY))
        *state = PLAY_BY_LUCK;
    else if(bitcmp(spaceInfo, IS_JAIL_TIME))
        *state = GO_TO_JAIL;
    else if(bitcmp(spaceInfo, PROPERTY_BY_BANK) && hasCash)
        *state = CAN_BUY;
    else if(bitcmp(spaceInfo, PROPERTY_BY_BANK) && !hasCash)
        *state = CANNOT_BUY;
    else if(bitcmp(spaceInfo, PROPERTY_BY_PLAYER) &&
            !bitcmp(spaceInfo, PROPERTY_IS_RENOVATED) &&
            hasCash && position != ELECTRIC_COMPANY &&
            position != RAILROAD)
        *state = CAN_RENOVATE;
    else if(bitcmp(spaceInfo, PROPERTY_BY_PLAYER) &&
            !bitcmp(spaceInfo, PROPERTY_IS_RENOVATED) &&
            !hasCash)
        *state = CANNOT_RENOVATE;
    else if(bitcmp(spaceInfo, PROPERTY_BY_OTHER) && hasCash)
        *state = CAN_PAY;
    else if(bitcmp(spaceInfo, PROPERTY_BY_OTHER) && !hasCash)
        *state = CANNOT_PAY;
    else
        *state = DO_NOTHING;
}

void makeTransaction(Game *game) {
    Player *player = game->activePlayer;
    int inventory = game->inventory;
    Transaction *transaction = &(game->transaction);
    int spaceInfo = getSpaceInfo(player, inventory);

    transaction->transactionType = getTransactionType(spaceInfo);
    transaction->newStatus = getNewDigit(
        player,
        inventory,
        transaction->transactionType
        );
    transaction->amount = getAmount(
        spaceInfo,
        getPosition(player),
        game->inventory,
        game->dice
    );
}

void incrementTurn(Player *player[MAX_PLAYERS], Player **activePlayer) {
    *activePlayer = nextPlayer(*activePlayer);
}

void cleanGame(Game *game) {
    int i;

    for(i = 0; i < MAX_PLAYERS; i++)
        cleanPlayers(game->players, MAX_PLAYERS);
}


/* -------------------------------------------------------------------------- */
/*                             MINOR GAME BRANCHES                            */
/* -------------------------------------------------------------------------- */
/* The following functions are called only in some turns                      */
/* as they are outcomes that depend on specific positions (e.g. jail)         */

void getFromBank(Game *game) {
    updateCash(game->activePlayer, BANK_BONUS, ADD);
}

int _rand(){
    return 150;
}

int playByLuck(Game *game) {
    int dice = game->dice;
    Player *player = game->activePlayer;
    int amount;

    if(dice == 1) {
        setCanPlay(player, 0);
        setPosition(player, JAIL_TIME);
        return LUCK_IS_JAIL;
    }

    if(isPrime(dice)) {
        amount = rand() % GET_BANK_RANGE + GET_BANK_MIN;
        game->transaction.amount = amount;

        updateCash(player, amount, ADD);
        return LUCK_IS_GET_BANK;
    }

    // if not prime
    amount = rand() % PAY_BANK_RANGE + PAY_BANK_MIN;
    game->transaction.amount = amount;

    if(!isCashSufficient(getCash(player), amount))
        return LUCK_IS_PAY_BANK_NO_CASH;

    updateCash(player, amount, SUBTRACT);
    return LUCK_IS_PAY_BANK;
}

void goToJail(Game *game) {
    Player *activePlayer = game->activePlayer;

    setCanPlay(activePlayer, 0);
}

void sellProperty(Game *game, int propertyToSell) {
    Player *player = game->activePlayer;
    int *inventory = &(game->inventory);
    int dice = game->dice;
    int amount = getAmount(
        PROPERTY_TO_SELL, propertyToSell, *inventory, dice
    );


    updateCash(player, amount, ADD);
    updateInventory(inventory, propertyToSell, 0);
}
