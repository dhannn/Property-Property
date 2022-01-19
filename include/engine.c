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
            enactTransaction(game->activePlayer, game->transaction, &(game->inventory));
            break;
        case X_KEY:
            break;
        case EXIT_KEY:
            game->isBankrupt = -1;
            break;
    }
}

void handleState(Game *game){
    Player *player = game->activePlayer;
    // Player *otherPlayer = nextPlayer(player);
    State state = game->state;
    Transaction *transaction = &(game->transaction);

    char *in = &(game->input);

    if(passesGo(player)){

    }

    switch(state){
        case DO_NOTHING:
            output("Nothing to do here!");
            break;
        case PLAY_BY_LUCK:
            output("You're feeling lucky, huh?");
            *in = input("Press R to roll the dice.", DEFAULT | ROLL);
            handleInput(*in, game);

            switch(playByLuck(game)){
                case LUCK_IS_JAIL:
                    output("Oh no... You lost your next turn.");
                    break;
                case LUCK_IS_GET_BANK:
                    output("Nice! You got %p from the bank.", transaction->amount);
                    enactTransaction(player, *transaction, &(game->inventory));
                    break;
                case LUCK_IS_PAY_BANK:
                    output("Oof... You have to pay the bank %p.", transaction->amount);
                    enactTransaction(player, *transaction, &(game->inventory));
                    break;
            }

            *in = 'X'; // reset input to do nothing
            break;
        case GO_TO_JAIL:
            output("Oh no... You lost your next turn.");

            goToJail(game);
            break;
        case CAN_BUY:
            output("You can buy this property with a price of %p.", transaction->amount);
            *in = input("Press B to buy this property or X to do nothing.", DEFAULT | BUY | X, transaction->amount);
            break;
        case CANNOT_BUY:
            output("You cannot buy this property! The price %p is too pricey.", transaction->amount);
            break;
        case CAN_RENOVATE:
            output("You can renovate this property with a price of %p", transaction->amount);
            *in = input("Press N to renovate your property or X to do nothing.", DEFAULT | RENOVATE | X);
            break;
        case CANNOT_RENOVATE:
            output("You cannot renovate this property!");
            break;
        case CAN_PAY:
            output("Oh no! You need to pay rent %p.", transaction->amount);
            *in = input("Press A to pay rent.", DEFAULT | PAY_KEY);
            break;
        case CANNOT_PAY:

            // TODO: make sell property function in game module
            break;
    }
}

void playGame(Game *game){
    initializeGame(game);
    getPlayerName(game->players);
    clear();

    do{
        playTurn(game);
        updateState(game);
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
    char *in = &(game->input);

    clear();
    printSpaces();
    updateScreenElements(*game);

    if(getCanPlay(activePlayer)){
        *in = input("Press R to roll the dice.", ROLL | DEFAULT);
        handleInput(*in, game);

        movePlayer(activePlayer, game->dice);

        current = getPosition(activePlayer);
        previous = previousPosition(activePlayer);
        displayPlayerMove(previous, current, index);

        updateState(game);
        handleState(game);
        handleInput(*in, game);
        updateScreenElements(*game);
    } else {
        setCanPlay(activePlayer, 1);
        output("Don't worry. You'll be released from prison next turn!");
    }

    incrementTurn(&(game->players), &(game->activePlayer));
}

void getPlayerName(Player *players){
    int i;
    char temp[MAX_NAME_CHAR];
    for(i = 0; i < MAX_PLAYERS; i++){
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
