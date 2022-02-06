#include "include/display.h"
#include "include/transaction.h"
#include "include/engine.h"
#include "include/player.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    Game game;

    clear();

    printf("Protip: Maximize the terminal to see the full screen elements ;)");
    delay(DEFAULT_DELAY * 2);


    clear();

    printTitle((CARD_HEIGHT + 1) * 2 - 10);
    printOpeningScreen();

    do{
        game.input = input("", PLAY | EXIT | MENU);
        handleInput(&game);

        clear();

        printTitle((CARD_HEIGHT + 1) * 2 - 10);
        printOpeningScreen();
    } while(game.input == PLAY_KEY);

    clear();
    return 0;
}
