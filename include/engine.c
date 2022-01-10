#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include "engine.h"
#include "helper.h"

void updateScreenElements(Game game){
    int inventory = game.inventory;
    int owner;
    int i;
    int position;
    int cash;
    char *name;
    Player *players = game.players;

    for(i = 1; i <= MAX_SPACES; i++){
        owner = getOwner(inventory, i);

        if(owner != -1)
            printOwnership(i, owner);

        if(isRenovated(inventory, i) == 1)
            printRenovated(i);
    }

    for(i = 0; i < MAX_PLAYERS; i++){
        position = getPosition(players);
        cash = getCash(players);
        name = getName(players);

        printPlayer(position, i, 0);
        printCash(cash, i, name);

        players = nextPlayer(players);
    }
}

void handleInput(char in, Game *game, ...){
    // int cost = 0;
    va_list args;
    va_start(args, game);

    switch(in){
        case PLAY_KEY:
            playGame(game);
            break;
        case ROLL_KEY:
            rollDice(&(game->dice));
            displayDiceRoll(game->dice);
            break;
        case BUY_KEY:
        case RENOVATE_KEY:
        case SELL_KEY:
        case PAY_KEY:
            enactTransaction(game);
        case X_KEY:
            break;
        case EXIT_KEY:
            game->isBankrupt = -1;
            break;
    }
}

void handleState(Game *game){
    Player *player = game->activePlayer;
    GameState state = game->state;

    Transaction *transaction = &(game->transaction);

    char *in = &(game->input);

    switch(state){
        // Transaction States
        case CAN_BUY:
        case CAN_RENOVATE:
        case CAN_PAY_RENT:
        case CAN_PAY_RENT_RENOVATED:
            transaction->transactionType = getTransactionType(state);
            transaction->amount = getAmountFromTransactionType(transaction->transactionType,
                                                                getPosition(player), game->dice);
            transaction->newState = getNewState(player, game->inventory, transaction->transactionType);
            transaction->operation = getOperation(transaction->transactionType);
            handleInput(*in, game);
            break;

        // Non-Transaction States
        case GO_JAIL:
            setCanPlay(player, 1);
            break;
        case LUCKY:
            if(game->dice == 1){
                setCanPlay(player, 1);
            } else if(isPrime(game->dice)){
                transaction->transactionType = GET_FROM_BANK;
                transaction->amount = rand() % GET_BANK_RANGE + GET_BANK_MIN;
                transaction->operation = ADD;

                output("Congrats! The bank is giving you P%d", transaction->amount);
                enactTransaction(game);
            } else {
                transaction->amount = getAmountFromTransactionType(transaction->transactionType,
                                                                    getPosition(player), game->dice);
                transaction->transactionType = PAY_BANK;
                transaction->amount = rand() % PAY_BANK_RANGE + PAY_BANK_MIN;
                transaction->operation = SUBTRACT;

                output("Awwwww... You owe the bank P%d.", transaction->amount);
                enactTransaction(game);
            }
            break;
        case CANNOT_BUY:
            break;
        case CANNOT_RENOVATE:
            break;
        case ALREADY_RENOVATED:
            break;
        case CANNOT_PAY_RENT:
            break;
        case BANKRUPT:
            game->isBankrupt = 1;
            break;
    }

    // displayStateOutput(game);
    updateScreenElements(*game);
}

void playGame(Game *game){
    initializeGame(game);
    getPlayerName(game->players);
    clear();

    do{
        playTurn(game);
        getGameState(game);
    } while(!game->isBankrupt);

    if(game->isBankrupt != -1)
        displayWinner(game->activePlayer);

    delay(DEFAULT_DELAY);
}

void playTurn(Game *game){
    Player *activePlayer = game->activePlayer;
    int current = getPosition(activePlayer);
    int previous = previousPosition(activePlayer);
    int index = getIndex(activePlayer);
    char in;

    clear();
    printSpaces();
    updateScreenElements(*game);

    if(getCanPlay(activePlayer)){
        in = input("Press R to roll the dice.", ROLL | DEFAULT);
        handleInput(in, game);

        movePlayer(activePlayer, game->dice);

        current = getPosition(activePlayer);
        previous = previousPosition(activePlayer);
        // TODO: change function signature for displaye player move
        displayPlayerMove(previous, current, index);

        getGameState(game);
        displayStateOutput(game);
        handleState(game);
    } else {
        setCanPlay(activePlayer, 1);
    }

    incrementTurn(&(game->players), &(game->activePlayer));
}

void getPlayerName(Player *players){
    int i;
    char temp[MAX_NAME_CHAR];
    for(i = 0; i < MAX_PLAYERS; i++){
        moveUp(2);
        printf("Player %d, please enter your name\n>> ", i + 1);
        scanf("%s", temp);

        setName(players, temp);
        players = nextPlayer(players);
    }
}

void displayWinner(Player *player){
    clear();
    printf("Congrats, %s! You won.", getName(player));
}

void displayStateOutput(Game *game){
    GameState state = game->state;

    char *in = &(game->input);
    *in = 'X';

    switch(state){
        case GO_JAIL:
            output("Oof... you landed on jail. You lose a turn.");
            break;
        case LUCKY:
            output("Oooo... You're feeling lucky today, huh?");

            *in = input("Press R to roll the dice.", DEFAULT | ROLL);
            break;
        case CAN_BUY:
            output("You can buy this property with a price of ₱%d", game->transaction.amount);
            *in = input("Press B to buy or X if not", DEFAULT | BUY | X);
            break;
        case CANNOT_BUY:
            output("Awww... You cannot buy this property.");
            break;
        case CAN_RENOVATE:
            output("You can upgrade this property with a price of ₱%d", game->transaction.amount);
            *in = input("Press N to renovate or X if not", DEFAULT | RENOVATE | X);
            break;
        case CANNOT_RENOVATE:
            output("You don't have enough money to renovate.");
            break;
        case ALREADY_RENOVATED:
            output("You already renovated this property!");
            break;
        case CAN_PAY_RENT:
            output("Oh no... You landed on %d's property. Pay up ₱%d!", game->transaction.amount);
            *in = input("Press A to pay rent.", DEFAULT | PAY);
            break;
        case CANNOT_PAY_RENT:
            output("Looks like you don't have any money. You need to sell one of your property to pay rent.");
            *in = input("Press the position of your chosen property (1 - Treehouse, ..., 9 - Farmhouse).",
                       DEFAULT | RANGE, 1, MAX_SPACES);
            break;
        case BANKRUPT:
            output("Oh no! You're bankrupt.");
            break;
    }
}
