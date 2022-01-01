#include "transaction.h"
#include "player.h"
#include "space.h"
#include "helper.h"
#include <stdlib.h>

void updateInventory(int *inventory, int position, int newStatus){
    setDigit(inventory, position, newStatus);
}

int getSpaceState(Player player, int inventory){
    int position = player.position->current;
    int index = player.index;
    int state = 0;

    // Checks non-property spaces
    if(position == GO) 
        return IS_GO;

    if(position == FEELIN_LUCKY)
        return IS_FEELIN_LUCKY;

    if(position == JAIL_TIME)
        return IS_JAIL_TIME;


    // Checks property spaces
    if(isOwnedByBank(inventory, position))
        return PROPERTY_BY_BANK;
    
    if(isOwnedByPlayer(inventory, position, index))
        state = state | PROPERTY_BY_PLAYER; 
    else 
        state = state | PROPERTY_BY_OTHER;
    
    if(isRenovated(inventory, position))
        state = state | PROPERTY_IS_RENOVATED;
    
    return state;
}

int *getOwnedProperty(Player player, int inventory){ 
    int *ownedProperties = malloc(sizeof(int));
    int numOfProperties = 0;
    int i = 0;

    for(; i < 10; i++){
        if(isOwnedByPlayer(inventory, i, player.index)){
            ownedProperties = realloc(ownedProperties, numOfProperties + 2);
            ownedProperties[numOfProperties] = i;

            numOfProperties++;
        }
    }

    ownedProperties = realloc(ownedProperties, numOfProperties + 1);
    ownedProperties[numOfProperties] = -1;

    return ownedProperties;
}

float getCost(int position, int inventory, int spaceState, int dice){
    float buyingCost = 20.0 * (position % 7) * COST_MULTIPLIER;
    float rentingCost = (1.0/5.0) * buyingCost * COST_MULTIPLIER;
    // float sellingCost = (1.0/2.0) * buyingCost;

    if((spaceState & IS_GO) || (spaceState & IS_JAIL_TIME))
        return 0;
    if((spaceState & IS_FEELIN_LUCKY) != 0){
        if(isPrime(dice) == -1)
            return 0;

        if(isPrime(dice))
            return rand() % (GET_BANK_RANGE + GET_BANK_MIN) * COST_MULTIPLIER;
        else
            return rand() % (PAY_BANK_RANGE + PAY_BANK_MIN) * COST_MULTIPLIER;
    }

    // Returns buying cost
    if((spaceState & PROPERTY_BY_BANK) != 0){
        if(position == ELECTRIC_COMPANY)
            return ELECTRIC_COMPANY_BUYING_COST * COST_MULTIPLIER;
        
        if(position == RAILROAD)
            return RAILROAD_BUYING_COST * COST_MULTIPLIER;
        
        return buyingCost;
    }
    
    // Returns renovation cost 
    if(((spaceState ^ PROPERTY_IS_RENOVATED) & PROPERTY_BY_PLAYER) == 
        PROPERTY_BY_PLAYER)
        return RENOVATION_COST;
    
    // Returns renting cost
    if((spaceState & PROPERTY_BY_OTHER) != 0){
        if(position == ELECTRIC_COMPANY)
            return dice * 8.0;
        
        if(position == RAILROAD)
            return RAILROAD_RENTING_COST;

        if((spaceState & PROPERTY_IS_RENOVATED) != 0)
            rentingCost = 1 + 2.0 * rentingCost;
        return rentingCost;
    }
    
    return -1;
}

int getOwner(int inventory, int position){
    int property = extractDigit(inventory, position);

    if(!property)
        return -1;
    
    return (property + 1) % 2;
}

int getPlayerState(Player player, int inventory){
    int position = player.position->current;
    int cash = player.cash;
    int playerState = 0;
    
    int spaceState = getSpaceState(player, inventory);
    int cost = getCost(position, inventory, spaceState, 0);

    if(cost == -1){
        // printf("Invalid space state");
        return -1;
    }

    if(hasProperty(inventory, player.index))
        playerState = playerState | HAS_PROPERTY;

    if(isCashSufficient(cash, cost))
        playerState = playerState | HAS_CASH;
    
    return playerState;
}
