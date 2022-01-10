// For 01 Jan - 03 Jan
// TODO: Refactor Refactor Refactor
// TODO: Make function and file comments
// TODO: Ask Ms. about future sessions
// Ask Ms. about ANSI

// For 04 Jan - 08 Jan
// TODO: Bonus feature

// For 08 Jan - 10 Jan
// TODO: Refactor Refactor Refactor

// For 10 Jan - 18 Jan
// TODO: Finish documentation

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
