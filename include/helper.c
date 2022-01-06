#include "helper.h"
#include <math.h>

int extractDigit(int number, int place){
    return number % power(10, place) / power(10, place - 1);
}

void setDigit(int *number, int place, int newStatus){
    // TODO: Fix terminologies
    int placeValue = power(10, place - 1);
    int value = extractDigit(*number, place);

    int oldFaceValue = value * placeValue;
    int newFaceValue = newStatus * placeValue;

    *number -= oldFaceValue;
    *number = *number + newFaceValue;
}

int power(int base, int exponent){
    int result = 1;
    int i;

    for(i = 0; i < exponent; i++)
        result *= base;
    
    return result;
}

int isPrime(int number){
    int flag = 1;
    int divisor = 2;

    if(number == 1)
        return -1;

    while(divisor <= sqrt(number)){
        if(number % divisor == 0)
            flag = 0;
        divisor++;
    }

    return flag;
}
