// For 30 Dec
// Jail feature
// Feelin' Lucky Feature

// For 30 Dec - 31 Dec
// TODO: Finish the rent feature (when no more money)

// Good day po, Ms.! 

// I was wondering if by "Note that your implementation is text-based...," you mean strictly no image po ba? Or that we're just using the command line interface which means it's okay to display at least ASCII images?
// Also, will I be graded solely by the MP demo or will the program be run on your device po? I have a feature po kasi that might work only to some terminals/operating system
// I sent you po a private message containing some implementation details for some additional context. Thank you po!

// Good day po, Ms.! 

// Like I mentioned po sa MP discussion board, I was thinking to display some images onto the console but when I reviewed the specs, I remember the "text-based" restriction.
// Attached is the implementation of this feature. I was wondering if this implemention violates the specs or not.

// To display rin po the images, I had to think of ways on how to move the cursor of the terminal. I came across the idea of ANSI escape sequences https://en.wikipedia.org/wiki/ANSI_escape_code https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797
// But I figured out that not all terminals can read this. In fact, I tried it in the command prompt; it didn't work po even until I adjust the settings.

// It worked naman po sa IDE. That's why I asked whether will we be graded solely by how it works in the demo or do I have to think of device compatibility.

// Thank you po! 

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
    
    clear();

    printf("Protip: Maximize the terminal to see the full screen elements ;)");
    delay(DEFAULT_DELAY * 2);
    
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
