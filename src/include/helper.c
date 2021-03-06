/*

    Description         This header file contains all the function prototypes
                        of helper functions used in other modules.
    Programmed by       Daniel III L. Ramos (S15A)
    Last Modified       06-02-2022
    Version             3.5.0

*/

#include "helper.h"
#include <math.h>

int extractDigit(int number, int place) {
    return number % power(10, place) / power(10, place - 1);
}

void setDigit(int *number, int place, int newDigit) {
    int unitPlaceValue = power(10, place - 1);
    int oldDigit = extractDigit(*number, place);

    int oldPlaceValue = oldDigit * unitPlaceValue;
    int newPlaceValue = newDigit * unitPlaceValue;

    if(place != 0) {
        // replaces the old place value with the new place value
        *number -= oldPlaceValue;
        *number += newPlaceValue;
    }
}

int power(int base, int exponent) {
    int result = 1;
    int i;

    for(i = 0; i < exponent; i++)
        result *= base;

    return result;
}

int isPrime(int number) {
    // Implementation of a crude version of the trial division method
    // for primality test
    // https://primes.utm.edu/glossary/page.php?sort=TrialDivision

    int divisor = 2;
    int flag = 1;       // to determine if prime
    int isDone = 0;   // to stop the loop without using return

    if(number == 1)
        return NUM_IS_ONE;

    // we only check divisors less than the square root of a number
    // since any factors above the square root has corresponding factor-pair
    // below the square root; thus checking below the root is sufficient
    while(divisor <= sqrt(number) && !isDone) {
        if(number % divisor == 0){
            flag = 0; // means there exists a divisible number other than 1 or itself
            isDone = 1;
        }

        divisor++;
    }

    return flag;
}

int bitcmp(int bitfield, int flag) {
    // this uses bitwise AND to query the status of the bit
    // and compare it to the flag

    // e.g. (111 & 101) == 101  ->  (101) == 101  ->   1
    // e.g. (110 & 011) == 011  ->  (010) == 101  ->   0
    if(flag != 0)
        return (bitfield & flag) == flag;

    return 0;
}
