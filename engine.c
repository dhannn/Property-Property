#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include "engine.h"
#include "helper.h"

void display(Game game){
    int inventory = game.inventory;
    // int property;
    int owner;
    int i;

    for(i = 1; i <= MAX_SPACES; i++){
        // property = extractDigit(inventory, i);
        owner = getOwner(inventory, i);

        if(owner != -1)
            printOwnership(i, owner); 

        if(isRenovated(inventory, i) == 1)
            printRenovated(i);
    }
}

void handleInput(char in, Game *game, ...){
    va_list args;
    va_start(args, game);
    int cost = 0;
    float *cash = &(game->activePlayer->cash);
    int *inventory = &(game->inventory);
    int *position = &(game->activePlayer->position->current);
    int index = game->activePlayer->index;
    Player *otherPlayer = &(game->players[(index + 1) % 2]);

    switch(in){
        case PLAY_KEY:
            playGame(game);
            break;
        case ROLL_KEY: 
            rollDice(&(game->dice));
            displayDiceRoll(game->dice);
            break;
        case BUY_KEY:
            cost = va_arg(args, double);
            updateCash(cash, cost, SUBTRACT);
            updateInventory(inventory, *position, index + 1);
            printCash(*cash, index, game->activePlayer->name);
            printOwnership(*position, index);
            break; 
        case RENOVATE_KEY:
            cost = va_arg(args, double);
            updateCash(cash, cost, SUBTRACT);
            updateInventory(inventory, *position, index + 3);
            printRenovated(*position);
            break;
        case SELL_KEY:
            cost = va_arg(args, double);
            updateCash(&(game->activePlayer->cash), cost, ADD);
            updateInventory(&(game->inventory), va_arg(args, int), 0);
            printCash(*cash, index, game->activePlayer->name);
            display(*game);
            break;
        case PAY_KEY:
            cost = va_arg(args, double);
            updateCash(cash, cost, SUBTRACT);
            updateCash(&(otherPlayer->cash), cost, ADD);
        case X_KEY:
            break;
        case EXIT_KEY:
            game->dice = 0;
            game->isBankrupt = -1;
            break;
    }
}

void handleState(Game *game){
    int state = game->state;
    int position = game->activePlayer->position->current;
    int inventory = game->inventory;
    int *dice = &(game->dice);
    float cost = getCost(position, inventory, state, *dice);
    int temp;
    char in;

    if(passesGo(*(game->activePlayer->position))){
        updateCash(&(game->activePlayer->cash), BANK_BONUS, ADD);
        printCash(game->activePlayer->cash, game->activePlayer->index, game->activePlayer->name);
        output("You can claim ₱%f from the bank!", BANK_BONUS);
        getGameState(game);
    }

    if((state & IS_JAIL_TIME)){
        game->activePlayer->canPlay = 0;
        output("Oof... you landed on jail. You lose a turn.");
    }

    if(state & IS_FEELIN_LUCKY){
        output("Oooo... You're feeling lucky today, huh?");
        in = input("Press R to roll the dice.", DEFAULT | ROLL);

        handleInput(in, game);
        gotoInputStream();

        cost = getCost(position, inventory, state, *dice);

        if(cost == 0){
            game->activePlayer->canPlay = 0;
        } else if(isPrime(*dice)){
            updateCash(&(game->activePlayer->cash), cost, ADD);
            output("Congrats! The bank gave you Php%f", cost);
        } else{
            updateCash(&(game->activePlayer->cash), cost, SUBTRACT);
            output("Awww... You owe the bank Php%f", cost);
        }
    }
    
    if((state & PROPERTY_BY_BANK) != 0){
        if((state & HAS_CASH) != 0){
            output("You can buy this property with a price of ₱%f", cost);
            in = input("Press B to buy or X if not.", DEFAULT | BUY | X);

            handleInput(in, game, cost);
        } else {
            output("Awww... You cannot buy this property.");
        }
    } else if((state & PROPERTY_BY_PLAYER) && !(state & PROPERTY_IS_RENOVATED)){
        if((state & HAS_CASH) != 0){
            output("You can upgrade this property with a price of ₱%f", RENOVATION_COST);
            in = input("Press N to renovate or X if not", DEFAULT | RENOVATE | X);

            handleInput(in, game, RENOVATION_COST);
        } else {
            output("You don't have enough money to renovate.");
        }
    } else if((state & PROPERTY_BY_OTHER)){
        output("Oh no... You landed on %s's property. Pay up ₱%f!", game->players[!(game->activePlayer->index)].name, cost);
        
        if((state & HAS_CASH) != 0){
            in = input("Press A to pay rent.", DEFAULT | PAY);

            handleInput(in, game);
        } else if(state & HAS_PROPERTY){
            output("You have no money left! You have to sell your property to pay rent.");
            in = input("Press the position of your chosen property (1 - Treehouse, ..., 9 - Farmhouse).", DEFAULT | RANGE, 1, MAX_SPACES); 
            
            while(!isOwnedByPlayer(inventory, atoi(&in), game->activePlayer->index)){
                in = input("Please select a property you own.", DEFAULT | RANGE, 1, MAX_SPACES);
            }

            cost = getCost(atoi(&in), inventory, PROPERTY_BY_BANK, *dice) / 5.0;
            temp = atoi(&in);

            output("The property costs ₱%f.", cost); 

            in = input("Press S to sell this property or X if you want to choose other!", DEFAULT | SELL | X);
            handleInput(in, game, cost, temp);

            getGameState(game);
            handleState(game);
        } else {
            output("Oh no! You're bankrupt.");
            game->isBankrupt = 1;
        }
    }
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
        displayWinner(*(game->activePlayer));

    delay(DEFAULT_DELAY);
}

void playTurn(Game *game){
    Player *activePlayer;
    activePlayer = game->activePlayer;
    char in;

    clear();
    printSpaces();
    printPlayer(game->players[0].position->current, 0, 0);
    printPlayer(game->players[1].position->current, 1, 0);
    printCash(game->players[0].cash, 0, game->players[0].name);
    printCash(game->players[1].cash, 1, game->players[1].name);
    display(*game);

    if(activePlayer->canPlay){
        in = input("Press R to roll the dice.", ROLL | DEFAULT);
        handleInput(in, game);
        
        movePlayer(activePlayer, game->dice);
        displayPlayerMove(activePlayer->position->previous->current, 
                            activePlayer->position->current, 
                            activePlayer->index);
        
        getGameState(game);
        handleState(game);

    } else {
        activePlayer->canPlay = 1;
    }

    incrementTurn(game->players, &(game->activePlayer));
}

void getPlayerName(Player players[MAX_PLAYERS]){
    int i;
    for(i = 0; i < MAX_PLAYERS; i++){
        moveUp(2);
        printf("Player %d, please enter your name\n>> ", i + 1);
        scanf("%s", players[i].name);
    }
}

void displayWinner(Player player){
    clear();
    printf("Congrats, %s! You won.", player.name);

    // https://www.asciiart.eu/holiday-and-events/fireworks
}
