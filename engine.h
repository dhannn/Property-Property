#include "game.h"
#include "display.h"
#include <stdarg.h>

void playGame(Game *gane);
void playTurn(Game *game);
void display(Game game);
void displayWinner(Player winner);
void getPlayerName(Player players[MAX_PLAYERS]);
void handleInput(char in, Game *game, ...);
void handleState(Game *game);
