/**************************************************************************************
*
*   Description:        This header file contains functions responsible
*                       for printing and displaying screen elements to the console.
*   Programmed by:      Daniel III L. Ramos
*   Last Modified:      12-26-2021
*   Version:            1.0
*
*
*   Acknowledgements:
*
*   Peterson, Christian. 3 Nov 2021. ANSI Escape Sequences.
*   https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797
*
*   This Github gist lays out all the ANSI escape sequences I used in the project.
*
**************************************************************************************/
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


// These are macros that define ANSI escape
// sequences that help in displaying (both
// in cursor position and color)

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

#define TO_UPPER_INCREMENT 32
#define LOWERCASE_START 97

#ifndef DISPLAY_H
#define DISPLAY_H
struct point{
    int x;
    int y;
};

typedef struct point Point;

struct rect{
    Point origin;
    int width;
    int height;
};

typedef struct rect Rectangle;

struct card{
    Rectangle outerRectangle;
    Rectangle innerRectangle;
    char text1[LINE_LENGTH];
    char text2[LINE_LENGTH];
};

typedef struct card Card;

enum input{
    PLAY        =   0b00000000001,
    MENU        =   0b00000000010,
    EXIT        =   0b00000000100,
    ROLL        =   0b00000001000,
    BUY         =   0b00000010000,
    X           =   0b00000100000,
    RENOVATE    =   0b00001000000,
    PAY         =   0b00010000000,
    SELL        =   0b00100000000,
    RANGE       =   0b01000000000,
    CONTINUE    =   0b10000000000,
    DEFAULT     =   MENU | EXIT
};

void printTitle(int y);
void printOpeningScreen();
void printSpaces();


/*********      FUNCTIONS PRINTING GAME ELEMENTS      *********/
void gotoInputStream();
/* ------ Spaces ------ */
void createCard(Card *card, int x, int y, char line1[], char line2[]);
void printRectangle(Rectangle rect);
void printSpaceCard(Card card);
void printSpaceText(Card card);

/* ------ Player ------ */
void printPlayer(int position, int index, int isErase);
void displayPlayerMove(int previousPosition, int currentPosition, int index);

Point getOriginPlayerMarker(int position);
int getRowFromSpace(int position);
int getColumnFromSpace(int position, int row);

/* ------ Dice ------ */
void printDice(int dice);
void displayDiceRoll(int dice);

/* ------ Player and Property Status ------ */
void printCash(float cash, int index, char *name);
void printOwnership(int position, int index);

Point getOriginPropertyMarker(int position);
void printRenovated(int position);


/*********      INPUT-HANDLING FUNCTIONS        *********/
// I made output() and input() variadic functions to accomodate
// formatted string like in the printf() function
void output(char *prompt, ...);
char input(char *prompt, int validInputs, ...);
void format(char *prompt, va_list args);
void validateInput(char *in, int validInputs, va_list args);
int isValidInput(char *in, int validInputs, va_list args);
void toUpper(char *in);


/*********          SCREEN FUNCTIONS            *********/
int getCenterOrigin(int width); // (screen width - text width) / 2
void delay(int millisecond);
void clear();
void clearLine();


/*********  FUNCTIONS ABOUT CURSOR POSITIONING  *********/
void reposition(int row, int column);
void moveUp(int rowDecrement);
void moveDown(int rowIncrement);
void moveLeft(int columnDecrement);
void moveRight(int columnIncrement);

/* FUNCTIONS ABOUT COLORING */
void color(int FG, int BG);
#endif
