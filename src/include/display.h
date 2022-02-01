/*

    Description         This header file contains functions prototypes
                        responsible for printing and displaying screen
                        elements to the console.
    Programmed by       Daniel III L. Ramos
    Last Modified       01-02-2022
    Version             1.1.0


    Acknowledgements:
    Peterson, Christian. 3 Nov 2021. ANSI Escape Sequences. Github gists
    https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797
        This Github gist lays out all the ANSI escape sequences I used.

    Variadic functions. (n.d.). cppreferences.
    https://en.cppreference.com/w/c/variadic
        This documentation helped me understand variadic functions such as
        printf() so I can implement my own input() and output()
*/

#include <string.h>
#include <stdarg.h>

// These are macros that define the title screen.
#define TITLE_LINE_1 "█▀█ █▀█ █▀█ █▀█ █▀▀ █▀█ ▀█▀ █▄█  "
#define TITLE_LINE_2 "█▀▀ █▀▄ █▄█ █▀▀ ██▄ █▀▄  █   █  ▄"
#define TITLE_LINE_3 "█▀█ █▀█ █▀█ █▀█ █▀▀ █▀█ ▀█▀ █▄█  "
#define TITLE_LINE_4 "█▀▀ █▀▄ █▄█ █▀▀ ██▄ █▀▄  █   █   "


// These are macros that define composition of a dice
#define DICE_TOP        " _ _ _ _"
#define DICE_R1_NONE    "|       |"
#define DICE_R1_ONE     "| •     |"
#define DICE_R1_TWO     "| •   • |"
#define DICE_R2_NONE    "|       |"
#define DICE_R2_ONE     "|   •   |"
#define DICE_R2_TWO     "| •   • |"
#define DICE_R3_NONE    "|_ _ _ _|"
#define DICE_R3_ONE     "|_ _ _•_|"
#define DICE_R3_TWO     "|_•_ _•_|"

//These are macros that define valid keystrokes.
#define PLAY_KEY 'P'
#define MENU_KEY 'M'
#define EXIT_KEY 'E'
#define CONTINUE_KEY 'C'
#define BUY_KEY 'B'
#define RENOVATE_KEY 'N'
#define PAY_KEY 'A'
#define SELL_KEY 'S'
#define ROLL_KEY 'R'
#define X_KEY 'X'

// These are macros that define screen attributes.
#define SCREEN_WIDTH 74
#define TITLE_WIDTH 33
#define CARD_WIDTH 7
#define CARD_HEIGHT 10
#define CARD_BORDER_SIZE 1
#define CARD_BOTTOM_BORDER 2
#define LINE_LENGTH 6
#define INPUT_STREAM_POSITION ((CARD_HEIGHT + 1) * 3 + 1)


// These are macros that define ANSI escape sequences that help in displaying
// (both in cursor position and color)

// CURSOR POSITIONING
#define CLEAR "\033[2J"
#define CLEAR_LINE "\033[2K"
#define REPOSITION "\033[%d;%dH"
#define MOVE_UP "\033[%dA"
#define MOVE_DOWN "\033[%dB"
#define MOVE_RIGHT "\033[%dC"
#define MOVE_LEFT "\033[%dD"

#define DEFAULT_DELAY 2500

// COLORS
#define COLOR_TEMPLATE "\033[%d;%dm"
#define CYAN_FG 36
#define CYAN_BG 46
#define WHITE_FG 37
#define WHITE_BG 47

// These are some miscellaneous macros
#define MAX_SPACES 10
#define TO_UPPER_INCREMENT 32
#define LOWERCASE_START 97
#define PESO "₱"

#ifndef DISPLAY_H
#define DISPLAY_H

// This struct stores information about an element position in the terminal
struct point{
    int x;              // the column position in the terminal
    int y;              // the row position in the terminal
};

typedef struct point Point;

// This struct stores information about rectangles to be drawn in the terminal
struct rect{
    Point origin;       // the position where the terminal first prints
    int width;          // how wide the rectangle
    int height;         // how tall the rectangle
};

typedef struct rect Rectangle;

// This struct stores information about a "card" of a space (i.e. Go, ...)
struct card{
    Rectangle outerRectangle;   // rectangle of the whole card
    Rectangle innerRectangle;   // rectangle for the player markers
    char text1[LINE_LENGTH];    // line 1 of the card name
    char text2[LINE_LENGTH];    // line 2 of the card name
};

typedef struct card Card;

// This enum is used in input() function to indicate valid inputs
// It's a nifty way to show valid inputs esp. when used with bitwise operators
enum input{
    PLAY        =   0b00000000001,
    MENU        =   0b00000000010,
    EXIT        =   0b00000000100,
    ROLL        =   0b00000001000,
    BUY         =   0b00000010000,
    X           =   0b00000100000,  // to do nothing
    RENOVATE    =   0b00001000000,
    PAY         =   0b00010000000,
    SELL        =   0b00100000000,
    RANGE       =   0b01000000000,  // indicates numerical value within a range
    CONTINUE    =   0b10000000000,
    DEFAULT     =   MENU | EXIT     // to access menu and exit any time
};


/* -------------------------------------------------------------------------- */
/*                      FUNCTIONS PRINTING GAME ELEMENTS                      */
/* -------------------------------------------------------------------------- */

/**
    This function prints the title "Property Property"

    @param y            row number to be printed on
    @return             none
*/
void printTitle(int y);

/*
    This function prints the opening screen and the menu
*/
void printOpeningScreen();

/*
    This function prints the spaces (i.e. Go, Treehouse, ...)
*/
void printSpaces();


/* --------------------------------- Spaces --------------------------------- */
/**
    This function initializes a card structure by providing the member values

    @param  card        pointer to the card being initialized
    @param  x           column position of the card origin
    @param  y           row position of the card origin
    @param  line1       first line of the name
    @param  line2       second line of the name
    @return             none
*/
void createCard(Card *card, int x, int y, char line1[], char line2[]);

/**
    This function prints a space card

    @param  card        the card structure to be printed
    @return             none
*/
void printSpaceCard(Card card);

/**
    This function prints the name of the card

    @param  card        the card structure of the name to be printed
    @return             none
*/
void printSpaceText(Card card);

/**
    This function prints a rectangle

    @param  rect        the rectangle structure to be printed
*/
void printRectangle(Rectangle rect);


/* --------------------------------- Player --------------------------------- */
/**
    This function prints a player marker based on player status

    Pre-condition           position is an integer from 0 to 9,
                            index is either 0 or 1 and isErase is either 1 or 0
    @param  position        indicates player position
    @param  index           index of the player; 0 for Player 1 and 1 for Player 2
    @param  isErase         indicates whether to print or erase the player
                            (used for displaying player move)
    @return                 none
*/
void printPlayer(int position, int index, int isErase);

/**
    This function displays the player "moving" across the board

    Pre-condition           previousPosition and currentPosition
                            are integers between 0 to 9;
                            index is either 1 or 0
    @param previousPosition previous position of the player
    @param currentPosition  current position of the player
    @param index            player index
    @return                 none

*/
void displayPlayerMove(int previousPosition, int currentPosition, int index);

/**
    This function gets the origin of the player marker

    Pre-condition           position is an integer from 0 to 9
    @param  position        current position of the player
    @return                 the point of origin for the player marker
*/
Point getOriginPlayerMarker(int position);

/**
    This function converts the space position to the row in the space grid

    Pre-condition           position is an integer from 0 to 9
    @param  position        current position of the player
    @return                 row indicating position in a grid (0, 1, 2)
*/
int getRowFromSpace(int position);

/**
    This function converts the space position to the colum in the space grid

    Pre-condition           position is an integer from 0 to 9; row is
                            an integer from 0 to 2
    @param  position        current position of the player
    @param  row             row of the indicated space in the space grid
    @return                 column indicating position in a grid (0, 1, 2, 3)
*/
int getColumnFromSpace(int position, int row);

/* ---------------------------------- Dice ---------------------------------- */

/**
    This function displays a "rolling" dice

    Pre-condition           dice value is from 1 to 6
    @param  dice            the value of the dice on a turn
    @return                 none
*/
void displayDiceRoll(int dice);

/**
    This function displays a static dice

    Pre-condition           dice value is from 1 to 6
    @param  dice            the value of the dice on a turn
    @return                 none
*/
void printDice(int dice);


/* ----------------------- Player and Property Status ----------------------- */

/**
    This function prints the cash statistics of a player

    Pre-condition           name contains at most 6 digits characters;
                            index is 0 or 1
    @param  cash            the cash to be displayed
    @param  index           the index of the player
    @param  name            the name of the player
    @return                 none
*/
void printCash(float cash, int index, char *name);

/**
    This function prints the marker for ownership status

    Pre-condition           position is from 0 to 9;
                            index is 0 or 1
    @param  position        position of the owned property
    @param  index           index of the player who owns the property
    @return                 none
*/
void printOwnership(int position, int index);

/*
    This function prints the marker for renovated properties

    Pre-condition           position is from 0 to 9
    @param  position        position of the renovated property
    @return                 none
*/
void printRenovated(int position);

/*
    This function returns the origin of the property marker (ownership or
    renovated)

    Pre-condition           position is from 0 to 9
    @param  position        position of the renovated property
    @return                 none
*/
Point getOriginPropertyMarker(int position);


/* -------------------------------------------------------------------------- */
/*                          INPUT-HANDLING FUNCTIONS                          */
/* -------------------------------------------------------------------------- */
/*
    This function repositions the terminal cursor to the designated
    input area
*/
void gotoInputStream();

/*
    This function prints a prompt without asking any user input
*/
void output(char *prompt, ...);

/**
    Similar to Python's input() function, this function prints a prompt,
    asks for an input and returns the input if valid.

    Pre-condition           validInputs should correspond to one or
                            a combination of the input enumeration
    @param  prompt          the prompt being displayed to the player
    @param  validInputs     a bitfield containing all the valid inputs
*/                  // also one of my favorite functions i ever made 😅
char input(char *prompt, int validInputs, ...);

/**
    This function formats the prompt if custom format specifier is present

    Pre-condition           args has been passed to the va_start macro
                            either by the input() or the output() function
    @param  prompt          the prompt being displayed to the player
    @param  args            a va_list of values to be printed in format
*/
void format(char *prompt, va_list args);

/**
    This function loops until the input by the user matches one
    of the valid inputs set by the input() function

    Pre-condition           validInputs should correspond to one or
                            a combination of the input enumeration;
                            args has been passed to the va_start macro
                            either by the input() or the output() function
    @param  prompt          the prompt being displayed to the player
    @param  in              the input of the user
    @param  validInputs     a bitfield containing all the valid inputs
    @param  args            a va_list of values to be printed in format
*/
void validateInput(char *prompt, char *in, int validInputs, va_list args);

/**
    This function checks whether an input is valid.

    @param  in              the input of the user
    @param  validInputs     a bitfield containing all the valid inputs
    @param  args            a va_list of values in case RANGE is chosen
    @return                 1 if valid; 0 if otherwise
*/
int isValidInput(char *in, int validInputs, va_list args);

/**
    This function converts lowercase characters to uppercase

    @param  in              the user input
    @return                 none
*/
void toUpper(char *in);


/* -------------------------------------------------------------------------- */
/*                              SCREEN FUNCTIONS                              */
/* -------------------------------------------------------------------------- */
/**
    This function returns the center of the screen width

    Pre-condition       width is a non-negative integer
    @param  width       the screen width
    @return             the center of the width
*/
int getCenterOrigin(int width);

/**
    This function delays the flow of the program

    Pre-condition       millisecond is a non-negative integer
    @param millisecond  the amount of delay in ms
    @return             none
*/
void delay(int millisecond);

/*
    This function clears the terminal
*/
void clear();

/*
    This function clears a specific line in the terminal
*/
void clearLine();

/* -------------------------------------------------------------------------- */
/*                     FUNCTIONS ABOUT CURSOR POSITIONING                     */
/* -------------------------------------------------------------------------- */

/*
    This function repositions the cursor to a specific cell in the terminal

    Pre-condition       variables row and column are non-negative integers
    @param  row         the row of the destination cell
    @param  column      the column of the destination cell
*/
void reposition(int row, int column);

/*
    This function moves the cursor up a certain number of rows

    Pre-condition       rowDecrement is a non-negative integer
    @param rowDecrement the number of rows from the current cell to destination
*/
void moveUp(int rowDecrement);

/*
    This function moves the cursor down a certain number of rows

    Pre-condition       rowIncrement is a non-negative integer
    @param rowDecrement the number of rows from the current cell to destination
*/
void moveDown(int rowIncrement);

/*
    This function moves the cursor left a certain number of columns

    Pre-condition           columnDecrement is a non-negative integer
    @param columnDecrement  the number of columns from the current cell to dest
*/
void moveLeft(int columnDecrement);

/*
    This function moves the cursor right a certain number of columns

    Pre-condition           columnIncrement is a non-negative integer
    @param columnDecrement  the number of columns from the current cell to dest
*/
void moveRight(int columnIncrement);
#endif
