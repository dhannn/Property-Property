/*
    Description         This file contains the function prototypes and other
                        structures involving standard transactions in the game
    Programmed by       Daniel L. Ramos III (S15A)
    Last modified       28-01-2022
    Version             3.0.0
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
enum spaceInfo {
    IS_GO                       =   0b0000001, // 1d
    IS_FEELIN_LUCKY             =   0b0000010, // 2d
    IS_JAIL_TIME                =   0b0000100, // 4d
    PROPERTY_BY_BANK            =   0b0001000, // 8d
    PROPERTY_BY_PLAYER          =   0b0010000, // 16d
    PROPERTY_BY_OTHER           =   0b0100000, // 32d
    PROPERTY_IS_RENOVATED       =   0b1000000, // 64d
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


// This enum is used to determine whether to add or deduct from one's cash
// and how much cash is added or deducted in a transaction (in getAmount()
// and getOperation())
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
    int operation;
    int newStatus;
    // TODO: refactor code to include inventory in transaction struct
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
    This function returns the operation needed for the transaction.

    @param  transactionType the type of transaction (e.g BUY, RENOVATE, PAY)
    @return                 1 if addition; -1 if subtraction
*/
int getOperation(TransactionType transactionType);

/**
    This function returns the amount needed for a transaction.

    @param  spaceInfo       a bitfield containing information about the current
                            space (i.e. who owns it and renovation status)
    @param  position        the current position of the player
    @param  inventory       the 9-digit integer containing ownership details
    @param  dice            the value of the dice in the game
    @return                 the amount in the transaction
*/
int getAmount(int spaceInfo, int position, int inventory, int dice);

/*
    This function performs the transaction in a turn

    @param  player          the pointer to the current player
    @param  transaction     structure containing transaction details
    @param  inventory       the 9-digit integer containing ownership details
    @return                 none
*/
void enactTransaction(Player *player, Transaction transaction, int *inventory);

#endif