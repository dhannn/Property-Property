/*

    Description         This file contains the function prototypes and other
                        structures involving standard transactions in the game
    Programmed by       Daniel III L. Ramos (S15A)
    Last Modified       06-02-2022
    Version             3.5.0

*/

#include "player.h"

#ifndef TRANSACTION_H
#define TRANSACTION_H

// constant costs
#define RENOVATION_COST 50
#define ELECTRIC_COMPANY_BUYING_COST 150
#define RAILROAD_BUYING_COST 100
#define RAILROAD_RENTING_COST 35

// variables used for the Feelin' Lucky Space
#define GET_BANK_MAX 200
#define GET_BANK_MIN 100
#define GET_BANK_RANGE (GET_BANK_MAX - GET_BANK_MIN)
#define PAY_BANK_MAX 150
#define PAY_BANK_MIN 50
#define PAY_BANK_RANGE (PAY_BANK_MAX - PAY_BANK_MIN)

// To represent the information about the currentspace, I decided to implement
// a bitmask for a) better readability and b) seamless operations.

// also good practice for CCICOMP 😅
enum spaceInfo {
    IS_GO                       =   0b00000001, // 1d
    IS_FEELIN_LUCKY             =   0b00000010, // 2d
    IS_JAIL_TIME                =   0b00000100, // 4d
    PROPERTY_BY_BANK            =   0b00001000, // 8d
    PROPERTY_BY_PLAYER          =   0b00010000, // 16d
    PROPERTY_BY_OTHER           =   0b00100000, // 32d
    PROPERTY_TO_SELL            =   0b01000000, // 64d
    PROPERTY_IS_RENOVATED       =   0b10000000, // 128d
};

enum space {
    GO,
    TREEHOUSE,
    ELECTRIC_COMPANY,
    BEACH_HOUSE,
    JAIL_TIME,
    CASTLE,
    FEELIN_LUCKY,
    RAILROAD,
    IGLOO,
    FARMHOUSE
};


// This enum is used to determine how much cash is
// added or deducted in a transaction (in getAmount())
enum transactionType{
    NULL_TRANSACTION,
    BUY_PROPERTY,
    RENOVATE_PROPERTY,
    PAY_RENT
};

typedef enum transactionType TransactionType;


// This enum contains all the necessary information in most transactions
// such as buying properties, renovating properties and paying rent.
struct transaction{
    TransactionType transactionType;
    int amount;
    int newStatus;
};

typedef struct transaction Transaction;

/* -------------------------------------------------------------------------- */
/*                  FUNCTIONS INVOLVING SPACE AND SPACE INFO                  */
/* -------------------------------------------------------------------------- */

/**
    This function returns a 7-bit integer containing details of the space
    (i.e. whether owned by player, owned by other, owned by bank and renovated)

    @param  player          the pointer to the current player
    @param  inventory       the 9-digit integer containing ownership details
    @return                 the 9-bit integer containing info about the space
*/
int getSpaceInfo(Player *player, int inventory);

/**
    This function checks whether the current space is renovated

    @param  inventory       the 9-digit integer containing ownership details
    @param  position        the position of the space being checked
    @return                 1 if renovated; 0 if otherwise or not a property
*/
int isRenovated(int inventory, int position);

/**
    This function checks whether the current space is owned by the bank

    @param  inventory       the 9-digit integer containing ownership details
    @param  position        the position of the space being checked
    @return                 1 if owned by bank; 0 if otherwise or not property
*/
int isOwnedByBank(int inventory, int position);

/**
    This function checks whether the current space is owned by the current
    player

    @param  inventory       the 9-digit integer containing ownership details
    @param  position        the position of the space being checked
    @param  playerIndex     the index of the player
    @return                 1 if owned by player; 0 if otherwise or
                            not a property
*/
int isOwnedByPlayer(int inventory, int position, int playerIndex);


/* -------------------------------------------------------------------------- */
/*                      FUNCTIONS INVOLVING THE INVENTORY                     */
/* -------------------------------------------------------------------------- */

/**
    This function updates the inventory based on the specified position
    and new status.

    Pre-condition           inventory is a 9-digit (or less) integer;
                            position is from 1 to 9 and a property space
                            newStatus is from 0 to 4

    @param  inventory       the 9-digit integer containing ownership details
    @param  position        the position of the space
    @param  newStatus       the new value of the digit specified
    @return                 none
*/
void updateInventory(int *inventory, int position, int newStatus);

/**
    This function returns the index of the player owning a property

    @param  inventory       the 9-digit integer containing ownership details
    @param  position        the position of the property being checked
    @return                 -1 if not a property; otherwise, the index
                            of the owner
*/
int getOwner(int inventory, int position);

/*
    This function checks whether a player has at least one property

    Pre-condition           playerIndex is 0 or 1;
                            inventory is a 9-digit integer

    @param  inventory       the 9-digit integer containing ownership details
    @param  playerIndex     the index of the player
    @return                 1 if the player has property; 0 if otherwise
*/
int hasProperty(int inventory, int playerIndex);

/* -------------------------------------------------------------------------- */
/*              MAJOR OPERATIONS INVOLVING TRANSACTION STRUCTURE              */
/* -------------------------------------------------------------------------- */

/**
    This function returns the transaction type given the space info

    @param  spaceInfo       a bitfield containing information about the current
                            space (i.e. who owns it and renovation status)
    @return                 the type of transaction (e.g. BUY, RENOVATE, PAY)
*/
TransactionType getTransactionType(int spaceInfo);

/**
    This function returns the new digit of the current position in the
    inventory based on the transaction type

    @param  player          the pointer to the current player
    @param  inventory       the 9-integer value containing ownership details
    @param  transactionType the type of transaction (e.g. BUY, RENOVATE, PAY)
    @return                 the new digit in the inventory
*/
int getNewDigit(Player *player, int inventory, TransactionType transactionType);

/**
    This function returns the amount needed for a transaction.

    @param  spaceInfo       a bitfield containing information about the current
                            space (i.e. who owns it and renovation status)
    @param  position        the current position of the player
    @param  inventory       the 9-digit integer containing ownership details
    @param  dice            the value of the dice in the game
    @return                 the amount in the transaction
*/
int getAmount(int spaceInfo, int position, int inventory, int dice, float mult);

/*
    This function performs the transaction in a turn

    @param  player          the pointer to the current player
    @param  transaction     structure containing transaction details
    @param  inventory       the 9-digit integer containing ownership details
    @return                 none
*/
void enactTransaction(Player *player, Transaction transaction, int *inventory);

#endif
