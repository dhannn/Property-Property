// For 30 Dec
// Jail feature
// Feelin' Lucky Feature

// For 30 Dec - 31 Dec
// TODO: Finish the rent feature (when no more money)

// For 01 Jan - 03 Jan
// TODO: Refactor Refactor Refactor 
// TODO: Make function and file comments 
// TODO: Ask Ms. about future sessions
// TODO: Ask Ms. about ANSI

// For 04 Jan - 08 Jan 
// TODO: Bonus feature

// For 08 Jan - 10 Jan
// TODO: Refactor Refactor Refactor 

// For 10 Jan - 18 Jan
// TODO: Finish documentation 

#include "display.h"
#include "transaction.h"
#include "engine.h"
#include "player.h"
#include "space.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    char in;
    Game game;
    // Player player;
    // Point origin = {2, 5};
    // Card card;
    
    // int inventory = 103;
    
    clear();
    
    printTitle(0);
    printOpeningScreen();
    in = input("", 
            PLAY | EXIT | MENU, 
            0);
    
    handleInput(in, &game);
    // playGame(&game);
    clear();
    // printTitle(1);
    // printSpaces();
    // in = input("Something something.", DEFAULT, 0);

    // printf("Space State:\t%d\n", getSpaceState(player, inventory));
    // printf("Player State:\t%d\n", getPlayerState(player, inventory));
    return 0;
}
