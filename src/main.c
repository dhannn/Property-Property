/*

    Description         This file contains the main function that calls
                        the other module and serves as an entry point
    Programmed by       Daniel III L. Ramos (S15A)
    Last Modified       06-02-2022
    Version             3.5.0

*/

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

    game.input = input("", PLAY | EXIT | MENU);
    handleInput(&game);

    while(game.input != EXIT_KEY) {
        clear();

        printTitle((CARD_HEIGHT + 1) * 2 - 10);
        printOpeningScreen();
        game.input = input("", PLAY | EXIT | MENU);

        if(game.input != EXIT_KEY)
            handleInput(&game);
    }

    clear();
    return 0;
}
