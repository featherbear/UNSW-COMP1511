//
// Created by Andrew on 14/04/2018.
//

// Write a C program odd_even_ten.c which reads 10 integers from standard input, prints the odd numbers on one line, then prints the even numbers on one line.
// You may assume that the program's input will contain only positive integers and will contain at least 10 integers, in other words you can assume scanf succeeeds.

#include <stdio.h>
#define SIZE 10

int main(void) {
    int i = 0;

    // Read in the 10 values
    int arr[SIZE];
    while (i < SIZE) {
        scanf("%d", &arr[i]);
        i++;
    }

    // Print out the odd values
    // An odd number occurs when the modulo of n%2 is 1
    printf("Odd numbers were:");
    i = 0;
    while (i < SIZE) {
        if (arr[i] % 2) printf(" %d", arr[i]);
        i++;
    }

    // Print out the even values
    // An odd number occurs when the modulo of n%2 is 0
    printf("\nEven numbers were:");
    i = 0;
    while (i < SIZE) {
        if (arr[i] % 2 == 0) printf(" %d", arr[i]);
        i++;
    }

    printf("\n");


}