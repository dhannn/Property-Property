#include "game.h"
#include "display.h"
#include <stdarg.h>

/**
 * This function
 *
 * @param game
 */
void playGame(Game *game);

/**
 * This function follows one turn in a game.
 *
 * @param game
 */
void playTurn(Game *game);
void updateScreenElements(Game game);
void displayWinner(Player *winner);
void getPlayerName(Player *players);

/**
 * This function does necessary operation based on the input by the user
 *
 * @param in
 * @param game
 * @param ...
 */
void handleInput(char in, Game *game, ...);
void displayStateOutput(Game *game);


/**
 * This function does necessary operation based on the state of the game
 *
 * @param game
 */
void handleState(Game *game);
