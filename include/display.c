#include "display.h"
#include "helper.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>

// https://en.cppreference.com/w/c/variadic

void printTitle(int y){
    int startRow = y;
    int startColumn = getCenterOrigin(TITLE_WIDTH);
    reposition(startRow, startColumn);

    printf("%s\n", TITLE_LINE_1);

    moveRight(startColumn - 1);
    printf("%s\n", TITLE_LINE_2);

    moveRight(startColumn - 1);
    printf("%s\n", TITLE_LINE_3);

    moveRight(startColumn - 1);
    printf("%s\n", TITLE_LINE_4);
}

void printOpeningScreen(){
    int startColumn = getCenterOrigin(TITLE_WIDTH);

    moveRight(startColumn - 1);
    printf("Welcome!\n");
    moveRight(startColumn - 1);
    printf("Press P to play the game\n");
    moveRight(startColumn - 1);
    printf("      E to exit or\n");
    moveRight(startColumn - 1);
    printf("      M to load menu\n\n");
}

void printSpaces(){
    Card card;
    int i, j;
    int originX;
    int originY;
    int numberOfProperties = 0;
    char names[2][10][LINE_LENGTH] = {{"GO", "TREE", "ELEC", "BEACH", "FARM", "JAIL", "IGLOO", "RAIL", "FEEL", "CASTLE"},
                        {"", "HOUSE", "CO.", "HOUSE", "HOUSE", "TIME", "", "ROAD", "LUCKY", ""}};

    for(i = 0; i < 3; i++){
        for(j = 0; j < 4; j++){
            if(!(i == 1 && j > 0 && j < 3)){
                originX = (CARD_WIDTH + 2) * j + 1;
                originY = (CARD_HEIGHT + 1) * i + 1;
                createCard(&card, originX, originY, names[0][numberOfProperties], names[1][numberOfProperties]);
                printSpaceCard(card);
                numberOfProperties++;
            }
        }
    }

    int titleOrigin = (CARD_HEIGHT + 1) * 2 - 7;
    printTitle(titleOrigin);
    reposition(titleOrigin + 4, (CARD_WIDTH + 2) * 2 + 2);
    printf("Press M for menu , E to exit");
}

void gotoInputStream(){
    reposition(INPUT_STREAM_POSITION, 1);
}

void printSpaceCard(Card card){
    Point origin = card.outerRectangle.origin;
    int width = card.outerRectangle.width;
    int height = card.outerRectangle.height;

    printRectangle(card.outerRectangle);
    printRectangle(card.innerRectangle);
    printSpaceText(card);
    reposition(origin.y + height, origin.x + width);
}

void displayDiceRoll(int dice){
    int delayNum;
    int previous;
    int randomDice;
    int i;

    printf("\x1B[?25l");

    // To give the illusion of rolling dice
    for(i = 0; i < 4; i++){
        // random delay from .25s to 0.50s
        // for ✨ s u s p e n s e ✨
        delayNum = rand() % 250 + 250;

        // makes sure that each random roll is unique
        do{
            randomDice = rand() % 6 + 1;
        } while(randomDice == previous);

        previous = randomDice;

        printDice(randomDice);
        delay(delayNum);
    }

    printDice(dice);
    printf("\x1B[?25h");
}

void printDice(int dice){
    int i;
    Point origin = {86, 20};

    // maps the composition of a dice given the number of dots
    char diceMatrix[6][3][14] = {{DICE_R1_NONE, DICE_R2_ONE, DICE_R3_NONE},
                            {DICE_R1_ONE, DICE_R2_NONE, DICE_R3_ONE},
                            {DICE_R1_ONE, DICE_R2_ONE, DICE_R3_ONE},
                            {DICE_R1_TWO, DICE_R2_NONE, DICE_R3_TWO},
                            {DICE_R1_TWO, DICE_R2_ONE, DICE_R3_TWO},
                            {DICE_R1_TWO, DICE_R2_TWO, DICE_R3_TWO}};
    reposition(origin.y, origin.x);
    printf(DICE_TOP);

    for(i = 1; i < 4; i++){
        reposition(origin.y + i, origin.x);
        printf(diceMatrix[dice - 1][i - 1]);
    }
}

void displayPlayerMove(int previousPosition, int currentPosition, int index){
    int positionDifference = currentPosition - previousPosition;
    int i;

    if(positionDifference < 0)
        positionDifference = 10 + currentPosition - previousPosition;

    for(i = 0; i < positionDifference; i++){
        printPlayer(previousPosition, index, 0);
        delay(500);
        printPlayer(previousPosition, index, 1);
        delay(250);
        previousPosition = (previousPosition + 1) % 10;
    }
    printPlayer(previousPosition, index, 0);
}

void printPlayer(int position, int index, int isErase){
    Point origin = getOriginPlayerMarker(position);

    reposition(origin.y + index * 3, origin.x);
    if(isErase)
        printf("   ");
    else
        printf("[%d]", index + 1);

    reposition((CARD_HEIGHT + 1) * 3 + 1, 1);
}

Point getOriginPlayerMarker(int position){
    // returns the row and column on the grid
    int row = getRowFromSpace(position);
    int column = getColumnFromSpace(position, row);


    if(row == -1)
        printf("Error");
    if(column == -1)
        printf("Error");

    // int i;
    // Point originMatrix[10];
    Point origin;


    origin.x = CARD_WIDTH + (CARD_WIDTH + 2) * 2 * column + 1;
    origin.y = (CARD_HEIGHT + CARD_BORDER_SIZE - CARD_BOTTOM_BORDER) / 2
                + (CARD_HEIGHT + 1) * row;

    return origin;
}

int getRowFromSpace(int position){
    if(position >= 0 && position <= 3)
       return 0;
    else if(position == 9 || position == 4)
        return 1;
    else if(position >= 5 && position <= 8)
        return 2;

    return -1;
}

int getColumnFromSpace(int position, int row){
    switch(row){
        case 0:
            return position;
        case 1:
            if(position == 4)
                return 3;
            else if(position == 9)
                return 0;
        case 2:
            return 8 - position;
    }

    return -1;
}

void printCash(float cash, int index, char *name){
    Point origin = {80, 15};
    reposition(origin.y - 1, origin.x);
    printf("CASH");
    reposition(origin.y + index, origin.x);
    printf("%s\t\t₱%.2f", name, cash);

    // printf("%d\t\t₱%.2f", index + 1, cash);

    reposition((CARD_HEIGHT + 1) * 3 + 1, 1);
}

void printOwnership(int position, int index){
    Point origin = getOriginPropertyMarker(position);

    reposition(origin.y, origin.x + CARD_WIDTH * 2 - 2);
    printf("%d", index + 1);

    gotoInputStream();
}

void printRenovated(int position){
    Point origin = getOriginPropertyMarker(position);

    reposition(origin.y, origin.x);
    printf("*");

    gotoInputStream();
}

Point getOriginPropertyMarker(int position){
    int row = getRowFromSpace(position);
    int col = getColumnFromSpace(position, row);
    Point origin = {
        (CARD_WIDTH + 2) * 2 * col + 3,
        (CARD_HEIGHT + 1) * row + 2
    };

    return origin;
}

void createCard(Card *card, int x, int y, char line1[], char line2[]){
    Rectangle outer = {
        {x, y},
        CARD_WIDTH,
        CARD_HEIGHT
    };

    Rectangle inner = {
        {x + CARD_BORDER_SIZE, y + CARD_BORDER_SIZE},
        CARD_WIDTH - 2 * CARD_BORDER_SIZE,
        CARD_HEIGHT - CARD_BOTTOM_BORDER - 1
    };

    card->outerRectangle = outer;
    card->innerRectangle = inner;
    strcpy(card->text1, line1);
    strcpy(card->text2, line2);
}

void printSpaceText(Card card){
    char *line1 = card.text1;
    char *line2 = card.text2;
    int line1Width = strlen(line1);
    int line2Width = strlen(line2);
    int i;
    Point textOrigin = {
        card.innerRectangle.origin.x * 2,
        card.innerRectangle.origin.y + card.innerRectangle.height
    };
    Point line1Origin = {
        textOrigin.x + (LINE_LENGTH  - line1Width),
        textOrigin.y
    };
    Point line2Origin = {
        textOrigin.x + (LINE_LENGTH - line2Width),
        textOrigin.y + 1
    };

    reposition(line1Origin.y, line1Origin.x);
    for(i = 0; i < line1Width; i++)
        printf("%c ", line1[i]);

    reposition(line2Origin.y, line2Origin.x);
    for(i = 0; i < line2Width; i++)
        printf("%c ", line2[i]);

}

void printRectangle(Rectangle rect){
    int width = rect.width;
    int height = rect.height;
    Point origin = rect.origin;
    int columns = origin.x;
    int rows = origin.y;

    for(rows = origin.y; rows < height + origin.y; rows++){
        reposition(rows, (origin.x) * 2);

        for(columns = origin.x; columns < width + origin.x; columns++){
            // print line in the first row
            if(rows == origin.y){
                printf(" _");
            }
            // print the bottom left corner
            else if(columns == origin.x && rows == height + origin.y - 1){
                printf("|_");
            }
            // print the bottom right corner
            else if(columns == width + origin.x - 1 && rows == height + origin.y - 1){
                printf(" _|");
            }
            // print line the last row
            else if(rows == height + origin.y - 1){
                printf(" _");
            }
            // print the left side of the rect
            else if(columns == origin.x){
                printf("|");
            }
            // print the right side of the rect
            else if(columns == width + origin.x - 1){
                printf("   |");
            }
            // add the spaces between
            else {
                printf("  ");
            }
        }
    }
}

void output(char *prompt, ...){
    va_list args;

    va_start(args, prompt);

    gotoInputStream();
    clearLine();
    moveDown(1);
    clearLine();
    gotoInputStream();

    format(prompt, args);

    gotoInputStream();
    printf("\n");

    delay(DEFAULT_DELAY);

    va_end(args);
}

char input(char *prompt, int validInputs, ...){
    char in;
    va_list args;

    va_start(args, validInputs);

    gotoInputStream();
    clearLine();
    format(prompt, args);

    moveDown(1);
    moveLeft(strlen(prompt));
    clearLine();

    printf(">> ");
    scanf(" %c", &in);

    toUpper(&in);
    validateInput(prompt, &in, validInputs, args);

    va_end(args);
    return in;
}

void format(char *prompt, va_list args){
    int i = 0;
    int flag = 0; // a flag if the current char is a specifier
    char current;

    do{
        current = *(prompt + i);

        if(current == '%')
            flag = 1;

        // custom format specifiers
        if(flag){
            switch(current){
                // price types
                case 'p':
                    printf("%s%d", PESO, va_arg(args, int));
                    flag = 0;
                    break;
                // other integer types
                case 'd':
                    printf("%d", va_arg(args, int));
                    flag = 0;
                    break;
                // char types
                case 'c':
                    // XXX: va_arg takes the type 'int' because C promotes char (and other smaller integral values) to int
                    printf("%c", va_arg(args, int));
                    flag = 0;
                    break;
                // string types
                case 's':
                    printf("%s", va_arg(args, char*));
                    flag = 0;
                    break;
            }

        } else {
            putchar(current);
        }

        i++;
    } while(*(prompt + i) != '\0');

}

void validateInput(char *prompt, char *in, int validInputs, va_list args){
    while(!isValidInput(in, validInputs, args)){
        moveUp(2);
        *in = input("Wrong input! Try again.", validInputs, 0);
    }
}

int isValidInput(char *in, int validInputs, va_list args){
    /**
     * The following boolean values have two parts:
     * *in == <KEY> and validInputs & <BITMASK> != 0.
     *
     * The first part checks whether the user input
     * (i.e. *in) matches the keystroke defined for
     * each commands (i.e. <KEY>).
     *
     * The second part checks whether the command
     * (i.e. <BITMASK>) is in the valid inputs
     * (i.e. validInputs) and this is done through
     * bitwise operation.
     *
     * Bitwise AND
     */

    int i;
    int flag;
    int bitMask;
    char keys[] = {PLAY_KEY, MENU_KEY, EXIT_KEY, ROLL_KEY, BUY_KEY, X_KEY,
                    RENOVATE_KEY, PAY_KEY, SELL_KEY, SELL_KEY, CONTINUE_KEY};

    // variables for range
    int min, max;
    int isWithinRange;
    int isNumeric;

    min = va_arg(args, int);
    max = va_arg(args, int);
    isNumeric = atoi(in) != 0;
    isWithinRange = atoi(in) >= min && atoi(in) <= max;

    for(i = 0; i < 11; i++){
        if(isNumeric && isWithinRange && (validInputs & RANGE)){
            min = va_arg(args, int);
            max = va_arg(args, int);

            return 1;
        }

        bitMask = power(2, i);
        flag = *in == keys[i] && (validInputs & bitMask);

        if(flag)
            return 1;
    }

    return 0;
}

void toUpper(char *in){
    if(*in >= LOWERCASE_START)
        *in = *in - TO_UPPER_INCREMENT;
}

int getCenterOrigin(int width){
    return (SCREEN_WIDTH - width) / 2;
}

void delay(int millisecond){
    long pause;
    clock_t now, then;

    pause = millisecond * (CLOCKS_PER_SEC / 1000);
    now = then = clock();

    while((now - then) < pause)
        now = clock();
}

void reposition(int row, int column){
    printf(REPOSITION, row, column);
}

void clear(){
    puts(CLEAR);
    reposition(1, 1);
}

void clearLine(){
    puts(CLEAR_LINE);
    moveUp(1);
}

void moveUp(int rowDecrement){
    int i, j;
    printf(MOVE_UP, rowDecrement);
    for(i = 0; i < rowDecrement; i++){
        for(j = 0; j < SCREEN_WIDTH; j++)
            printf(" ");
        printf("\n");
    }
    printf(MOVE_UP, rowDecrement);
}

void moveDown(int rowIncrement){
    printf(MOVE_DOWN, rowIncrement);
}

void moveLeft(int columnDecrement){
    printf(MOVE_LEFT, columnDecrement);
}

void moveRight(int columnIncrement){
    printf(MOVE_RIGHT, columnIncrement);
}
