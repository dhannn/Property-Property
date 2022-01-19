#include "include/display.h"
#include "include/transaction.h"
#include "include/engine.h"
#include "include/player.h"
#include "include/space.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    char in;
    Game game;

    clear();

    printf("Protip: Maximize the terminal to see the full screen elements ;)");
    // delay(DEFAULT_DELAY * 2);

    clear();

    printTitle((CARD_HEIGHT + 1) * 2 - 10);
    printOpeningScreen();
    in = input("", PLAY | EXIT | MENU, 0);

    do{
        handleInput(in, &game);

        in = input("Press C if you want to continue playing or E to exit.", CONTINUE | EXIT);
    } while(in == CONTINUE_KEY);

    clear();
    return 0;
}
