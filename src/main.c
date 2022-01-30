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


    do{
        clear();

        printTitle((CARD_HEIGHT + 1) * 2 - 10);
        printOpeningScreen();
        game.input = input("", PLAY | EXIT | MENU, 0);
        handleInput(&game);
    } while(game.input == PLAY);

    clear();
    return 0;
}
