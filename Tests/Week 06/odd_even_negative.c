//
// Created by Andrew on 14/04/2018.
//

// Write a C program odd_even_negative.c which reads integers from standard input until it reads a negative integer. It should then print the odd numbers on one line then print the even numbers on one line.
// You may assume that the program's input will contain only integers, in other words you can assume scanf succeeeds.
//
// You can assume a negative integer will always be read.
//
// You can assume at most 1000 integers are read before a negative integer is read.

#include <stdio.h>
#define MAX_SIZE 1000

int main(void) {

    int arr[MAX_SIZE] = {'\0'};
    int i = 0;
    int v;
    // Loop until v is negative
    while (scanf("%d", &v) && v > 0) {
        arr[i] = v;
        i++;
    }

    // Print out the odd values
    // An odd number occurs when the modulo of n%2 is 1
    printf("Odd numbers were:");
    i = 0;
    while (arr[i] != '\0') {
        if (arr[i] % 2) printf(" %d", arr[i]);
        i++;
    }

    // Print out the even values
    // An odd number occurs when the modulo of n%2 is 0
    printf("\nEven numbers were:");
    i = 0;
    while (arr[i] != '\0') {
        if (arr[i] % 2 == 0) printf(" %d", arr[i]);
        i++;
    }

    printf("\n");


}