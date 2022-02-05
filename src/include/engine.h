/*
    Description         This file contains the function prototypes where
                        game and display modules are combined
    Programmed by       Daniel III L. Ramos (S15A)
    Last Modified       29-01-2022
    Version             3.0.0
*/

#include "game.h"
#include "display.h"
#define CONFIG_FILE "config"

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
    This function handles
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

void printMenu();
