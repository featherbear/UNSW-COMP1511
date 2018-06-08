//
// Created by Andrew on 20/04/2018.
//

// Write a C function which returns the number of even values in an array.
// Place your answer in a file named count_even_function.c
// Your function should return a single integer: the number of even values in the array.

// An even number is divisible by 2.
// Your function should return a single integer.
//
// Your function should not change the array it is given.
//
// Your function should not call scanf (or getchar or fgets).
//
// You can assume the array only contains positive integers.
//
// You can assume the array contains at least one integer.
//
// Your function should not print anything. It should not call printf.
//
// Your submitted file may contain a main function. It will not be tested or marked.

#include <stdio.h>
#include <stdlib.h>

// return the number of even values in an array.
int count_even(int length, int array[]) {
    int evenNumbers = 0;
    int i = 0;
    while (i < length) {
        if (array[i] % 2 == 0 ) evenNumbers++;
        i++;
    }
    return evenNumbers;
}

// This is a simple main function which could be used
// to test your count_even function.
// It will not be marked.
// Only your count_even function will be marked.

# define TEST_ARRAY_SIZE 8

int main(void) {
    int test_array[TEST_ARRAY_SIZE] = {16, 7, 8, 12, 13, 19, 21, 12};

    int result = count_even(TEST_ARRAY_SIZE, test_array);

    printf("%d\n", result);
    return 0;
}