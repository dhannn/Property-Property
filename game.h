#include "transaction.h"

#define MAX_PLAYERS 2

#ifndef GAME_H
#define GAME_H
struct game{
    Space spaces[MAX_SPACES];
    Player players[MAX_PLAYERS];
    Player *activePlayer;
    int inventory;
    int dice;
    int isBankrupt;
    int state;
};

typedef struct game Game;
#endif

void initializeGame(Game *game);
void rollDice(int *dice);
void movePlayer(Player *activePlayer, int dice);
void getGameState(Game *game);
void incrementTurn(Player player[MAX_PLAYERS], Player **activePlayer);
