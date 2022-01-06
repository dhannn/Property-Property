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
        // name = getName(player);

        printPlayer(position, i, 0);
        printCash(cash, i, name);

        players = nextPlayer(players);
    }
}

void handleInput(char in, Game *game, ...){
    // int cost = 0;
    Player *player = game->activePlayer;
    Player *otherPlayer = nextPlayer(player);
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
            enactTransaction(game, BUY_PROPERTY);
            break;
        case RENOVATE_KEY:
            enactTransaction(game, RENOVATE_PROPERTY);
            break;
        case SELL_KEY:
            enactTransaction(game, SELL_PROPERTY);
            break;
        case PAY_KEY:
            enactTransaction(game, PAY_RENT);
        case X_KEY:
            break;
        case EXIT_KEY:
            game->dice = 0;
            game->isBankrupt = -1;
            break;
    }
}

void handleState(Game *game){
    Player *player = game->activePlayer;
    GameState state = game->state;

    char *in = &(game->input);
    *in = 'X';


    switch(state){
        case GO_JAIL:
            output("Oof... you landed on jail. You lose a turn.");

            setCanPlay(player, 0);
            break;
        case LUCKY:
            output("Oooo... You're feeling lucky today, huh?");

            *in = input("Press R to roll the dice.", DEFAULT | ROLL);

            if(*in == 1)
                setCanPlay(player, 0);
            else if(isPrime(atoi(in))){
                enactTransaction(game, GET_FROM_BANK);
            } else {
                enactTransaction(game, PAY_BANK);
            }
            break;
        case CAN_BUY:
            output("You can buy this property with a price of ₱%f");
            *in = input("Press B to renovate or X if not", DEFAULT | BUY | X);
            break;
        case CANNOT_BUY:
            output("Awww... You cannot buy this property.");
            break;
        case CAN_RENOVATE:
            output("You can upgrade this property with a price of ₱%f", RENOVATION_COST);
            *in = input("Press N to renovate or X if not", DEFAULT | RENOVATE | X);
            break;
        case CANNOT_RENOVATE:
            output("You don't have enough money to renovate.");
            break;
        case ALREADY_RENOVATED:
            output("You already renovated this property!");
            break;
        case CAN_PAY_RENT:
            output("Oh no... You landed on %d's property. Pay up ₱%f!");
            *in = input("Press A to pay rent.", DEFAULT | PAY);
            break;
        case CANNOT_PAY_RENT:
            output("Oh no... You landed on %d's property. Pay up ₱%f!");
            *in = input("Press the position of your chosen property (1 - Treehouse, ..., 9 - Farmhouse).",
                       DEFAULT | RANGE, 1, MAX_SPACES);
            break;
        case BANKRUPT:
            output("Oh no! You're bankrupt.");
            break;
    }

    // displayStateOutput(game);
    handleInput(*in, game);
    updateScreenElements(*game);
}

void playGame(Game *game){
    initializeGame(game);
    // getPlayerName(game->players);
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
        displayPlayerMove(previous, current, index);

        getGameState(game);
        handleState(game);

    } else {
        setCanPlay(activePlayer, 1);
    }

    incrementTurn(&(game->players), &(game->activePlayer));
}

void getPlayerName(Player *players){
    int i;
    char *temp = malloc(sizeof(char) * MAX_NAME_CHAR);
    for(i = 0; i < MAX_PLAYERS; i++){
        moveUp(2);
        printf("Player %d, please enter your name\n>> ", i + 1);
        scanf("%s", temp);

        setName(players, temp);
        players = nextPlayer(players);
    }

    free(temp);
}

void displayWinner(Player *player){
    clear();
    // printf("Congrats, %s! You won.", getName(player));
}

void displayStateOutput(Game *game){
    GameState state = game->state;
    char *in = &(game->input);

    switch(state){
        case GO_JAIL:
            output("Oof... you landed on jail. You lose a turn.");
            break;
        case LUCKY:
            output("Oooo... You're feeling lucky today, huh?");

            *in = input("Press R to roll the dice.", DEFAULT | ROLL);
            break;
        case CAN_BUY:
            output("You can buy this property with a price of ₱%f");
            *in = input("Press B to renovate or X if not", DEFAULT | BUY | X);
            break;
        case CANNOT_BUY:
            output("Awww... You cannot buy this property.");
            break;
        case CAN_RENOVATE:
            output("You can upgrade this property with a price of ₱%f", RENOVATION_COST);
            *in = input("Press N to renovate or X if not", DEFAULT | RENOVATE | X);
            break;
        case CANNOT_RENOVATE:
            output("You don't have enough money to renovate.");
            break;
        case ALREADY_RENOVATED:
            output("You already renovated this property!");
            break;
        case CAN_PAY_RENT:
            output("Oh no... You landed on %d's property. Pay up ₱%f!");
            *in = input("Press A to pay rent.", DEFAULT | PAY);
            break;
        case CANNOT_PAY_RENT:
            output("Oh no... You landed on %d's property. Pay up ₱%f!");
            *in = input("Press the position of your chosen property (1 - Treehouse, ..., 9 - Farmhouse).",
                       DEFAULT | RANGE, 1, MAX_SPACES);
            break;
        case BANKRUPT:
            output("Oh no! You're bankrupt.");
            break;
    }
}
