/*

    Description         This file contains the function prototypes where
                        game and display modules are combined
    Programmed by       Daniel III L. Ramos (S15A)
    Last Modified       06-02-2022
    Version             3.5.0

*/

#include "game.h"
#include "display.h"


/**
    This function prints the current seed of the RNG for testing purposes

    @param  seed        the seed of the random number generator of the game
*/
void printSeed(unsigned long seed);


/**
    This function loads the configurations in the config file if there are any.
    If a setting is not found, the default setting will be loaded

    @param  game        the pointer to the game structure
*/
void loadConfig(Game *game);

/**
    This function initializes the game, starts the game loop, displays
    the winner and cleans up the dynamically-allocated variables

    @param  game        the pointer to the game structure
    @return             none
*/
void playGame(Game *game);

/**
    This function asks the users for their name and sets it to the players name

    @param  players     the pointer to the players
    @return             none
*/
void getPlayerName(Player *players);

/**
    This function carries out a single turn of a player

    @param  game        the pointer to the game structure
    @return             none
*/
void playTurn(Game *game);

/**
    This function carries out the necessary outcomes based on the game state

    @param  game        the pointer to the game structure
    @return             none
*/
void handleState(Game *game);

/*
    This function handles the event that a player has insifficient cash

    @param  game        the pointer to the game structure
    @return             none
*/
void handleInsufficientMoney(Game *game);

/**
    This function calls necessary functions based on user input

    @param  game        the pointer to the game structure
    @return             none
*/
void handleInput(Game *game);

/**
    This function updates screen elements based on game properties

    @param  game        the pointer to the game structure
    @return             none
*/
void updateScreenElements(Game game);

/**
    This function displays the winner

    @param  winner      the pointer to the winning player
    @return             none
*/
void displayWinner(Player *winner);


/* -------------------------------------------------------------------------- */
/*                               MENU FUNCTIONS                               */
/* -------------------------------------------------------------------------- */


/**
    This function prints the menu and prompts the user to pick one
    of the following settings: Initial Cash, Cost Multiplier, Inflation and
    Set Back to Default.

    @param  game        the pointer to the game structure
*/
void printMenu(Game *game);

/**
    This function changes the setting once the user tries to change it

    @param game         the pointer to the game structure
    @param setting      an integer index referring to a setting
    @param settingValue the value of the setting
*/
void changeSetting(Game *game, int setting, float settingValue);
