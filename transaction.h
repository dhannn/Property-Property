#include "player.h"
#include "space.h"

#ifndef TRANSACTION_H
#define TRANSACTION_H
enum transactionType{
    GET_FROM_BANK, 
    PAY_BANK, 
    BUY_PROPERTY, 
    RENOVATE_PROPERTY, 
    PAY_RENT, 
    SELL_PROPERTY
};

struct transaction{
    float cost;
    int operation;
    int newState;
};

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

void enactTransaction(Player *player, int inventory, Transaction transactionType);
void updateInventory(int *inventory, int position, int newStatus);
float getCost(int position, int inventory, int spaceState, int dice);
int getOwner(int inventory, int position);
void getOwnedProperty(Player *player, int inventory);

// The following functions are used to get states
int getSpaceState(Player player, int inventory);
int getPlayerState(Player player, int inventory);

// The following function is used for input validation
int isInventoryValid(int inventory);
