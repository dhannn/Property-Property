/*
    Description         This file contains the function prototypes and other
                        structures involving the player
    Programmed by       Daniel L. Ramos III (S15A)
    Last modified       26-01-2022
    Version             3.0.0

    Acknowledgements    Sorber, J. [Jacob Sorber]. (2021, April 06). Make
                        your Data Type more Abstract with Opaque Types in C
                        [Video]. YouTube.
                        https://www.youtube.com/watch?v=TsUOhPsZk6k

                        Helped me understand opaque types such as the FILE *
*/

#ifndef PLAYER_H
#define PLAYER_H

// I tried making this an opaque data type as an exercise
typedef struct player Player;

// See player.c for an author's note about this type
typedef struct position Position;

#define INITIAL_CASH 200
#define BANK_BONUS 50
#define COST_MULTIPLIER 2

#define ADD 1
#define SUBTRACT -1
#define MAX_NAME_CHAR 6
#define SET_NAME_SUCCESS 0
#define SET_NAME_FAILURE 1

/* -------------------------------------------------------------------------- */
/*               MAJOR OPERATIONS INVOLVING THE PLAYER STRUCTURE              */
/* -------------------------------------------------------------------------- */

/**
    This function dynamically allocates memory to a player pointer based
    on the size specified and sets its attributes to their initial values

    @param  player          the pointer to the player pointer
    @param  size            the number of players to be allocated
    @return                 none
*/
void initializePlayers(Player **player, int size);

/**
    This function updates the cash of the player based on the specified
    amount and operation

    Pre-condition:  operation is a macro-defined value of 1 for addition
                    or -1 for subtraction

    @param  player          the pointer to the player being updated
    @param  amount          the amount being added or deducted
    @param  operation       either ADD (1) or SUBTRACT (-1)
    @return                 none

*/
void updateCash(Player *player, int amount, int operation);

/**
    This function checks whether the player has enough cash left based
    on the amount given in a transaction

    @param  cash            the amount of cash a player has
    @param  amount          the amount being deducted in a transaction
    @return                 1 if player has sufficient cash; 0 if otherwise
*/
int isCashSufficient(int cash, int amount);

/**
    This function checks whether a player passes the 'Go' space

    @param  player          the pointer to the player being checked
    @return                 1 if the player passes Go; 0 if otherwise
*/
int passesGo(Player *player);

/**
    This function returns the player pointer of the next player

    @param  player          the pointer to the current player
    @return                 the pointer to the next player
*/
Player *nextPlayer(Player *player);

/**
    This function returns the previous position of the player.

    @param  player          the pointer to the current player
    @return                 the previous position of the player
*/
int previousPosition(Player *player);


/* -------------------------------------------------------------------------- */
/*                   GETTERS AND SETTERS OF PLAYER STRUCTURE                  */
/* -------------------------------------------------------------------------- */

/**
    This function gets the current position of the player

    @param  player          the pointer to the player being checked
    @return                 the current position of the player
*/
int getPosition(Player *player);

/**
    This function gets the index of the player in the game

    @param  player          the pointer to the player being checked
    @return                 the index of the player
*/
int getIndex(Player *player);

/**
    This function gets the current cash value of the player

    @param  player          the pointer to the player being checked
    @return                 the current cash value of the player
*/
int getCash(Player *player);

/**
    This function checks whether the player can play

    @param  player          the pointer to the player being checked
    @return                 1 if the player can play; 0 if otherwise
*/
int getCanPlay(Player *player);

/**
    This function gets the name set by the player

    @param  player          the pointer to the player being checked
    @return                 the name set by the player
*/
char *getName(Player *player);

/**
    This function sets the current position of the player

    @param  player          the pointer to the player being set
    @return                 none
*/
void setPosition(Player *player, int newPosition);

/**
    This function sets if the player can play or not

    @param  player          the pointer to the player being set
    @return                 none
*/
void setCanPlay(Player *player, int canPlay);

/**
    This function sets the name of the player

    @param  player          the pointer to the player being checked
    @return                 1 if failed (name is too large); 0 if otherwise
*/
int setName(Player *player, char *name);


/* -------------------------------------------------------------------------- */
/*                   FUNCTIONS INVOLVING THE POSITION STACK                   */
/* -------------------------------------------------------------------------- */

/**
    This function initializes the position stack by setting the top
    to a specified value

    @param  new             the initial value for the top of the stack
    @return                 a pointer to a stack structure containing position
*/
Position *initializeNewPosition(int new);

/**
    This function "pushes" a new value of the position to the top of the stack

    @param  positionStack   the stack structure containing position details
    @param  newPosition     the value to be "pushed" to the top
    @return                 none
*/
void pushPosition(Position **positionStack, int newPosition);

/**
    This function deallocates all the dynamically allocated memory
    done in the process of making the stack

    @param  positionStack   the stack structure containing position details
    @return                 none
*/
void deallocatePositions(Position *positionStack);

void cleanPlayers(Player *player, int size);


#endif
