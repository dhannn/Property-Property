#include "player.h"
#include "space.h"

#ifndef TRANSACTION_H
#define TRANSACTION_H

enum transactionType{
    NULL_TRANSACTION,
    BUY_PROPERTY,
    RENOVATE_PROPERTY,
    PAY_RENT
};

typedef enum transactionType TransactionType;

struct transaction{
    TransactionType transactionType;
    int amount;
    int operation;
    int newStatus;
};

typedef struct transaction Transaction;


#define RENOVATION_COST 50
#define ELECTRIC_COMPANY_BUYING_COST 150
#define RAILROAD_BUYING_COST 100
#define RAILROAD_RENTING_COST 35
#define GET_BANK_MAX 200
#define GET_BANK_MIN 100
#define GET_BANK_RANGE (GET_BANK_MAX - GET_BANK_MIN)
#define PAY_BANK_MAX 150
#define PAY_BANK_MIN 50
#define PAY_BANK_RANGE (PAY_BANK_MAX - PAY_BANK_MIN)

void updateInventory(int *inventory, int position, int newStatus);
int getOwner(int inventory, int position);

int getSpaceState(Player *player, int inventory);
int getPlayerState(Player *player, int inventory, Transaction transaction);

TransactionType getTransactionType(int spaceState);
int getNewState(Player *player, int inventory, TransactionType transactionType);
int getOperation(TransactionType transactionType);
int getAmount(int state, int position, int inventory, int dice);
void enactTransaction(Player *player, Transaction transaction, int *inventory);

int isInventoryValid(int inventory);

#endif
