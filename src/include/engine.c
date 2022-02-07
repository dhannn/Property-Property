/*

    Description         This file contains the implementation details
                        of the engine.h module
    Programmed by       Daniel III L. Ramos (S15A)
    Last Modified       06-02-2022
    Version             3.5.0

*/

#include <stdio.h>
#include <stdlib.h>
#include "engine.h"
#include "helper.h"

void printSeed(unsigned long seed) {
    FILE *file = fopen("seed", "a");

    fprintf(file, "%lu\n", seed);

    fclose(file);
}

void loadConfig(Game *game) {
    FILE *configFile = fopen(CONFIG_FILE, "r");
    int setting;
    float settingValue;
    int i;

    // initialize to -1 so that we know what values are missing later
    game->config.initialCash = -1;
    game->config.costMultiplier = -1;
    game->config.hasInflation = -1;

    float *settingArr[3] = {
        &game->config.initialCash,
        &game->config.costMultiplier,
        &game->config.hasInflation
    };


    // XXX: While every setting in the game is actually an int, I decided
    //      to make the configurations a float for the cost multiplier.
    float defaultValues[3] = {
        INITIAL_CASH,
        COST_MULTIPLIER,
        0
    };

    // reading the config file to set into the game configuration
    while(fscanf(configFile, "%d %f", &setting, &settingValue) != EOF) {
        *settingArr[setting - 1] = settingValue;
    }

    fclose(configFile);

    // missing values are replaced with default values
    for(i = 0; i < 3; i++) {
        if(*settingArr[i] == -1) {
            *settingArr[i] = defaultValues[i];
        }
    }
}

void playGame(Game *game) {
    // sets up the game
    loadConfig(game);
    initializeGame(game);

    // prints seed for testing
    printSeed(game->id);

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

    // only active if not in jail
    if(getCanPlay(activePlayer)) {
        *in = input("Press R to roll the dice.", ROLL | DEFAULT);
        handleInput(game);

        // only true uf the user didn't attempt to exit
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
        // outcome when in jail
        setCanPlay(activePlayer, 1);
        output("Don't worry. You'll be released from prison next turn!");
    }

    incrementTurn(&(game->players), &(game->activePlayer));

    if(game->config.hasInflation && getIndex(activePlayer))
        initiateInflation(game);
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
            printMenu(game);
            break;
        case SETTINGS_KEY:
            break;
        case BACK_KEY:
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
        output(
            "You got %p from the bank!",
            BANK_BONUS * (game->config.costMultiplier * 0.5)
        );

        updateState(game);
        updateScreenElements(*game);
    }

    makeTransaction(game);

    switch(state) {
        /* -------------------- NON-TRANSACTION STATES -------------------- */
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
                case LUCK_IS_PAY_BANK_NO_CASH:
                    output(
                        "Oh no! You have no cash to pay the bank."
                    );

                    handleInsufficientMoney(game);
                    updateCash(player, transaction->amount, SUBTRACT);
            }

            *in = 'X'; // reset input to do nothing
            break;
        case GO_TO_JAIL:
            output("Oh no... You lost your next turn.");

            goToJail(game);
            *in = 'X'; // reset input to do nothing
            break;

        /* --------------------- TRANSACTION STATES ---------------------- */

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
    int flag = 1;

    do {
        *in = input(
            "Enter the position of the property chosen "
            "(1 for Treehouse, 2 for Electric Company, ..., 9 for Farmhouse).",
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
            getAmount(
                PROPERTY_TO_SELL, propertyToSell, *inventory,
                game->dice, game->config.costMultiplier
            )
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

    delay(DEFAULT_DELAY);
}

/* -------------------------------------------------------------------------- */
/*                               MENU FUNCTIONS                               */
/* -------------------------------------------------------------------------- */

void printMenu(Game *game) {
    char *in = &game->input;
    float setting;

    while(*in != '5') {
        clear();
        // middle of the screen
        reposition((CARD_HEIGHT + GRID_GAP_Y) * 2 - 7, 1);

        printf("Press the number of the setting you want to change\n");
        printf("  [1] Initial Cash\n");
        printf("  [2] Cost Multiplier\n");
        printf("  [3] Inflation?\n");
        printf("  [4] Switch to default\n");
        printf("  [5] Back\n");

        *in = input("", RANGE, 1, 5);
        clear();

        // middle of the screen
        reposition((CARD_HEIGHT + GRID_GAP_Y) * 2 - 7, 1);

        if(*in == '1') {

            printf(
                "Initial cash allows you to change how much money "
                "the players have at the start of the game\n\n"
            );

            printf("Enter the inital cash you want.\n  >> ");
            do
                scanf("%f", &setting);
            while(setting <= 0);
        } else if(*in == '2') {
            printf(
                "Cost multipliers raise the prices in the game "
                "for ya'll who want to experience ✨l u x u r y✨\n\n"
            );

            printf("Enter cost multiplier you want.\n  >> ");

            do
                scanf("%f", &setting);
            while(setting <= 0);
        } else if(*in == '3') {
            printf(
                "Want the realistic experience? Setting the inflation ON "
                "will increase prices in every player's turn!\n\n"
            );

            printf("Enter 1 if you want inflation or 0 if not\n  >> ");

            do
                scanf("%f", &setting);
            while(setting != 1 && setting != 0);
        }

        if(*in == '4')
            remove(CONFIG_FILE);
        else if(*in != '5')
            changeSetting(game, atoi(in), setting);
    }
}

void changeSetting(Game *game, int setting, float settingValue) {
    FILE *configFile = fopen(CONFIG_FILE, "r");
    FILE *temp = fopen("temp", "w");

    int tempSetting;
    float tempSettingValue;
    int flag = 1;

    while(fscanf(configFile, "%d %f", &tempSetting, &tempSettingValue) != EOF) {
        if(tempSetting == setting) {
            fprintf(temp, "%d\t%f\n", setting, settingValue);
            flag = 0;
        } else {
            fprintf(temp, "%d\t%f\n", tempSetting, tempSettingValue);
        }
    }

    // if the current setting is not seen in the file
    // (meaning the setting is originally set config by default)
    if(flag) {
        fprintf(temp, "%d\t%f\n", setting, settingValue);
    }

    fclose(configFile);
    fclose(temp);

    remove(CONFIG_FILE);
    rename("temp", CONFIG_FILE);
}
