#include "player.h"
#include "space.h"

#ifndef TRANSACTION_H
#define TRANSACTION_H
enum transactionType{
    NULL_TRANSACTION,
    GET_BANK_BONUS,
    GET_FROM_BANK,
    PAY_BANK,
    BUY_PROPERTY,
    RENOVATE_PROPERTY,
    PAY_RENT,
    PAY_RENT_RENOVATED,
    SELL_PROPERTY
};

typedef enum transactionType TransactionType;

struct transaction{
    TransactionType transactionType;
    int amount;
    int operation;
    int newState;
};

#define DEFAULT_STATE -1

typedef struct transaction Transaction;
#endif

#define RENOVATION_COST 50.0
#define ELECTRIC_COMPANY_BUYING_COST 150.0
#define RAILROAD_BUYING_COST 100.0
#define RAILROAD_RENTING_COST 35.0
#define GET_BANK_MAX 200
#define GET_BANK_MIN 100
#define GET_BANK_RANGE (GET_BANK_MAX - GET_BANK_MIN)
#define PAY_BANK_MAX 150
#define PAY_BANK_MIN 50
#define PAY_BANK_RANGE (PAY_BANK_MAX - PAY_BANK_MIN)

/**
 * This function updates the current inventory by adding a new status to
 * a specified position
 *
 * @param inventory     the inventory that contains ownership details
 * @param position      position of the digit to be replaced
 * @param newStatus     the new digit that will replace the original digit
 */
void updateInventory(int *inventory, int position, int newStatus);
int getAmount(enum spaceState state, int position, int inventory, int dice);
int getNewState(Player *player, int inventory,  enum transactionType tr);
int getOperation(enum transactionType);

/**
 * This function returns the index of the player who owns the property
 * in a specified position.
 *
 * @param inventory     the inventory that contains ownership details
 * @param position      position of property to be checked
 * @return int
 */
int getOwner(int inventory, int position);


// The following functions are used to get states

/**
 * This function uses bitwise operation
 *
 * @param player
 * @param inventory
 * @return int
 */
int getSpaceState(Player *player, int inventory);
int getPlayerState(Player *player, enum spaceState sState, int inventory);


// The following function is used for input validation
int isInventoryValid(int inventory);
