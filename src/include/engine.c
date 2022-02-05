/*
    Description         This file contains the implementation details
                        of the engine.h module
    Programmed by       Daniel III L. Ramos (S15A)
    Last Modified       01-02-2022
    Version             3.1.0
*/

#include <stdio.h>
#include <stdlib.h>
#include "engine.h"
#include "helper.h"

void playGame(Game *game) {
    // sets up the game
    initializeGame(game);
    getPlayerName(game->players);
    clear();

    // actual game loop
    do{
        playTurn(game);
        updateState(game);
    } while(!game->isBankrupt);

    // cleanup
    if(game->isBankrupt != -1)
        displayWinner(game->activePlayer);

    delay(DEFAULT_DELAY);
    cleanGame(game);
}

void getPlayerName(Player *players) {
    int i;
    char temp[MAX_NAME_CHAR]; // acts as a buffer

    for(i = 0; i < MAX_PLAYERS; i++) {
        // displays prompt
        gotoInputStream();
        clearLine();
        printf("Player %d, please enter your name\n", i + 1);
        clearLine();
        printf(">> ");
        scanf("%s", temp);

        // checks whether name is beyond the allowed maximum characters
        while(setName(players, temp)) {
            gotoInputStream();
            clearLine();

            printf("Six-character names only. Nicknames are cool ;)\n");
            clearLine();
            printf(">> ");
            scanf("%s", temp);
        }

        players = nextPlayer(players);
    }
}

void playTurn(Game *game) {
    Player *activePlayer = game->activePlayer;
    int current = getPosition(activePlayer);
    int previous = previousPosition(activePlayer);
    int index = getIndex(activePlayer);
    char *in = &(game->input);

    // reprints everything
    clear();
    printSpaces();
    updateScreenElements(*game);

    if(getCanPlay(activePlayer)) {
        *in = input("Press R to roll the dice.", ROLL | DEFAULT);
        handleInput(game);

        if(*in != EXIT_KEY) {
            movePlayer(activePlayer, game->dice);
            current = getPosition(activePlayer);
            previous = previousPosition(activePlayer);
            displayPlayerMove(previous, current, index);

            updateState(game);
            handleState(game);
            handleInput(game);

            updateScreenElements(*game);
        }
    } else {
        setCanPlay(activePlayer, 1);
        output("Don't worry. You'll be released from prison next turn!");
    }

    incrementTurn(&(game->players), &(game->activePlayer));
}

void handleInput(Game *game) {
    char in = game->input;

    switch(in) {
        case PLAY_KEY:
            playGame(game);
            break;
        case ROLL_KEY:
            rollDice(&(game->dice));
            displayDiceRoll(game->dice);
            break;
        case BUY_KEY:
        case RENOVATE_KEY:
        case PAY_KEY:
            enactTransaction(
                game->activePlayer,
                game->transaction,
                &(game->inventory)
            );
            break;
        case X_KEY:
            break;
        case EXIT_KEY:
            game->isBankrupt = -1;
            break;
        case MENU_KEY:
            // printMenu();
            // TODO: finish menu
            break;
    }
}

void handleState(Game *game) {
    Player *player = game->activePlayer;
    State state = game->state;
    Transaction *transaction = &(game->transaction);

    char *in = &(game->input);

    if(passesGo(player)) {
        getFromBank(game);
        output("You got %p from the bank!", BANK_BONUS);
        updateState(game);
        updateScreenElements(*game);
    }

    makeTransaction(game);

    switch(state) {
        // <---------- Non-Transaction states -------->
        case DO_NOTHING:
            output("Nothing to do here!");
            *in = 'X'; // reset input to do nothing
            break;
        case PLAY_BY_LUCK:
            output("You're feeling lucky, huh?");
            *in = input("Press R to roll the dice.", DEFAULT | ROLL);
            handleInput(game);

            switch(playByLuck(game)) {
                case LUCK_IS_JAIL:
                    output("Oh no... You lost your next turn.");
                    break;
                case LUCK_IS_GET_BANK:
                    output(
                        "Nice! You got %p from the bank.",
                        transaction->amount
                    );
                    break;
                case LUCK_IS_PAY_BANK:
                    output(
                        "Oof... You have to pay the bank %p.",
                        transaction->amount
                    );
                    break;
            }

            *in = 'X'; // reset input to do nothing
            break;
        case GO_TO_JAIL:
            output("Oh no... You lost your next turn.");

            goToJail(game);
            *in = 'X'; // reset input to do nothing
            break;

        // <---------- Transaction states -------->

        case CAN_BUY:
            output(
                "You can buy this property with a price of %p.",
                transaction->amount
            );

            *in = input(
                "Press B to buy this property or X to do nothing.",
                DEFAULT | BUY | X,
                transaction->amount
            );
            break;
        case CAN_RENOVATE:
            output(
                "You can renovate this property with a price of %p",
                transaction->amount
            );

            *in = input(
                "Press N to renovate your property or X to do nothing.",
                DEFAULT | RENOVATE | X);

            break;
        case CAN_PAY:
            makeTransaction(game);

            output("Oh no! You need to pay rent %p.", transaction->amount);
            *in = input("Press A to pay rent.", DEFAULT | PAY);
            break;
        case CANNOT_BUY:
            output(
                "You cannot buy this property! The price %p is too pricey.",
                transaction->amount
            );

            *in = 'X'; // resets input to do nothing
            break;
        case CANNOT_RENOVATE:
            output("You cannot renovate this property!");
            *in = 'X';  // resets input to do nothing
            break;
        case CANNOT_PAY:
            output(
            "Oh no! You don't have enough money to pay the rent %p",
                transaction->amount
            );

            handleInsufficientMoney(game);

            if(!game->isBankrupt) {
                *in = input("Press A to pay rent.", DEFAULT | PAY);
            }
            break;
    }
}

void handleInsufficientMoney(Game *game) {
    // I made a separate function to handle CANNOT_PAY state
    // since, unlike others, this has the most complicated logic

    Player *player = game->activePlayer;
    Transaction *transaction = &(game->transaction);
    int *inventory = &(game->inventory);
    char *in = &(game->input);
    int index = getIndex(player);
    int cash = getCash(player);
    int propertyToSell;
    int flag;

    do {
        *in = input(
            "Enter the position of the property chosen."
            "(ex: 1 for Treehouse, ..., 9 for Igloo)",
            DEFAULT | RANGE, 1, 9
        );

        propertyToSell = atoi(in);

        // validates if property is owned by player
        while(!isOwnedByPlayer(*inventory, propertyToSell, index)) {
            *in = input(
                "Please choose a property you own.",
                DEFAULT | RANGE,
                1, 9
            );
            propertyToSell = atoi(in);
        }

        // lets player confirm this transaction based on the price
        output(
            "This property costs %p!",
            getAmount(PROPERTY_TO_SELL, propertyToSell, *inventory, game->dice)
        );

        *in = input(
            "Press S to confirm selling or X if you want to choose another.",
            DEFAULT | SELL | X
        );

        // enacts the actual selling
        if(*in == 'S'){
            sellProperty(game, propertyToSell);
            updateScreenElements(*game);
        }

        // checks certain conditions that will terminate this loop
        cash = getCash(player);
        if(isCashSufficient(cash, transaction->amount))
            flag = 0;
        else if(!hasProperty(*inventory, index)) {
            game->isBankrupt = 1;
            flag = 0;
        }
    } while(flag);

    if(game->isBankrupt)
        output("Oh no! You've gone bankrupt :(");
}

void updateScreenElements(Game game) {
    int inventory = game.inventory;
    int owner;
    int i;
    int position;
    int cash;
    char *name;
    Player *players = game.players;

    // Prints the spaces and other attributes (ownership and if renovated)
    for(i = 1; i <= MAX_SPACES; i++) {
        owner = getOwner(inventory, i);

        if(owner != -1)
            printOwnership(i, owner);

        if(isRenovated(inventory, i))
            printRenovated(i);
    }

    // Prints the cash of the two players
    for(i = 0; i < MAX_PLAYERS; i++) {
        position = getPosition(players);
        cash = getCash(players);
        name = getName(players);

        printPlayer(position, i, 0);
        printCash(cash, i, name);

        players = nextPlayer(players);
    }
}

void displayWinner(Player *player) {
    clear();
    printf("Congrats, %s! You won.", getName(player));
}

// void printMenu(Game *game) {
//     clear();

//     printf("Press the key of your choice\n");
//     printf("\tSe[T]tings\n");
//     printf("\t[E]xit\n");
//     printf("\tBa[C]k\n");

//     game->input = input("", SETTINGS | EXIT);
//     handleInput(game);
// }

// void printSettings(Game *game) {
//     char *in = &game->input;
//     int setting;

//     clear();
//     printf("Press the number of the setting you want to change\n");
//     printf("\t[1] Initial Cash\n");
//     printf("\t[2] Cost Multiplier\n");
//     printf("\t[3] Inflation?\n");
//     printf("\t[4] Back\n");

//     *in = input("", RANGE, 1, 4);
//     clear();

//     while(*in != 4) {
//         if(*in == '1') {

//             printf(
//                 "Initial cash allows you to change how much money"
//                 "the players have at the start of the game\n\n"
//             );

//             printf("Enter the inital cash you want.\n\t>> ");
//             do
//                 scanf("%d", &setting);
//             while(setting <= 0);
//         } else if(*in == '2') {
//             printf(
//                 "Cost multipliers raise the prices in the game"
//                 "for ya'll who want to experience ✨l u x u r y✨"
//             );

//             printf("Enter cost multiplier you want.\n\t>> ");

//             do
//                 scanf("%d", &setting);
//             while(setting <= 0);
//         } else if(*in == '3') {
//             printf(
//                 "Want the realistic experience? Setting the inflation ON"
//                 "will increase prices in every player's turn!"
//             );

//             printf("Enter 1 if you want inflation or 0 if not\n\t>> ");

//             do
//                 scanf("%d", &setting);
//             while(setting != 1 && setting != 0);
//         }

//         changeSetting(game, atoi(in), setting);
//     }

//     printMenu(game);
// }

// void changeSetting(Game *game, int setting, int settingValue) {
//     FILE *configFile = fopen(CONFIG_FILE, "r+");
//     int tempSetting;
//     int tempSettingValue;
//     int flag = 1;

//     while(fscanf(configFile, "%d %d", &tempSetting, &tempSettingValue) != EOF) {

//         if(tempSetting == setting) {
//             fseek(configFile, -1, SEEK_CUR);
//             fprintf(configFile, "%d=%d", setting);
//             flag = 0;
//         }
//     }

//     // if the current setting is not seen in the file
//     // (meaning the setting is originally set config by default)
//     if(flag) {
//         fprintf(configFile, "%d=%d", setting, settingValue);
//     }

//     fclose(configFile);
// }

// void loadConfig(Game *game) {
//     FILE *configFile = open(CONFIG_FILE, "r");
//     int setting;
//     int settingValue;
//     int i;

//     game->config.initialCash = -1;
//     game->config.costMultiplier = -1;
//     game->config.hasInflation = -1;
//     int *settingArr[3] = {
//         &game->config.initialCash,
//         &game->config.costMultiplier,
//         &game->config.hasInflation
//     };

//     int defValues[3] = {
//         INITIAL_CASH,
//         COST_MULTIPLIER,
//         0
//     };

//     while(fscanf(configFile, "%d %d", &setting, &settingValue) != EOF) {
//         *settingArr[setting] = settingValue;
//     }

//     fclose(configFile);

//     for(i = 0; i < 3; i++) {
//         if(*settingArr[i] == -1) {
//             *settingArr[i] = defValues[i];
//         }
//     }
// }
