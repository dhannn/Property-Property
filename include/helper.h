/*
    Description:    This header file contains all the function prototypes
                    of helper functions used in other modules.
    Programmed by:  Daniel L. Ramos III (S15A)
    Last modified:  19 January 2022
    Version:        3.0.0
*/

#define NUM_IS_ONE -1

/**
    This function returns the digit of a number based on the specified place.
    If place is more than that of the number, the place value of the number
    will extend until the specified place.

    @param      number      the number to be extracted upon
    @param      place       the place of the digit to be extracted
    @return                 the digit on the specified place
*/
int extractDigit(int number, int place);

/**
    This function changes the digit of a number based on the specified place

    @param      number      the pointer of the number to be changed
    @param      place       the place of the digit to be changed
    @param      newDigit    the digit that replaces the original digit
    @return                 none
*/
void setDigit(int *number, int place, int newDigit);

/**
    This function computes the value of an exponent with a non-negative power.
    Pre-condition: the exponent (or power) is non-negative

    @param      base        the number to be multiplied
    @param      exponent    the number of times the base is multiplied
    @return                 the value of the exponent
*/
int power(int base, int exponent);

/**
    This function identifies whether or not a number is prime

    @param      number      the number to be examined
    @return                 1 if prime; 0 if not prime; -1 if number is one
*/
int isPrime(int number);

/**
    This function checks if the bitfield contains the flag specified

    @param      bitfield    the bitfield to be checked
    @param      flag        the flag to be checked
    @return                 1 if the bitfield contains the flag;
                            0 if otherwise
*/
int bitcmp(int bitfield, int flag);
