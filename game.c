#include "game.h"
#include <stdlib.h>
#include <time.h>


void initializeGame(Game *game){
    int i;
    srand(13);

    game->dice = 0;
    game->inventory = 0;
    game->isBankrupt = 0;
    game->activePlayer = &(game->players[0]);
    // getGameState(game);

    for(i = 0; i < MAX_PLAYERS; i++){
        initializePlayer(&(game->players[i]));
        game->players[i].index = i;
    }
}

void rollDice(int *dice){
    int diceValue = rand() % 6 + 1;
    *dice = diceValue;
}

void movePlayer(Player *activePlayer, int dice){
    int new = (activePlayer->position->current + dice) % 10;
    pushPosition(&(activePlayer->position), new);
}

void getGameState(Game *game){
    Player player = *(game->activePlayer);
    int inventory = game->inventory;

    int spaceState = getSpaceState(player, inventory);
    int playerState = getPlayerState(player, inventory);

    game->state = spaceState | playerState;
}

void incrementTurn(Player player[MAX_PLAYERS], Player **activePlayer){
    int turn = ((*activePlayer)->index + 1) % MAX_PLAYERS;
    *activePlayer = &(player[turn]);
}
