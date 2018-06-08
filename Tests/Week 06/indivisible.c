//
// Created by Andrew on 14/04/2018.
//

// Write a C program indivisible.c which reads integers > 1 from standard input until it reaches end-of-input.
// It should then print the integers read which are not exactly divisible by any other of the integers read.
//
// In other words it should not print an integer if another integer that has been read is a factor of that number.
//
// You may assume that the program's input will contain only positive integers one per line.
//
// You may assume that all integers are > 1.
//
// You can assume at most 1000 integers will be read before end-of-input is reached.

#include <stdio.h>

#define MAX_INTEGERS 1000

int main() {

    // Read our numbers in until we receive an EOF (which is returned by scanf)
    int i = 0;
    int v;
    int numbers[MAX_INTEGERS] = {'\0'};
    while (scanf("%d", &v) != EOF) {
        numbers[i] = v;
        i++;
    }

    printf("Indivisible numbers:");

    i = 0;
    int j;
    int indivisible;

    // Step through each number and check if any of the other numbers are a factor
    // If so, then set indivisible to 0.
    // Otherwise, if no factor is found, print out the number
    // The index i cannot be the same as index j obviously!

    while (numbers[i] != '\0') {
        indivisible = 1;
        j = 0;
        while (numbers[j] != '\0') {
            if (i != j && numbers[i] % numbers[j] == 0) indivisible = 0;
            j++;
        }

        if (indivisible) printf(" %d", numbers[i]);
        i++;

    }
    printf("\n");
}
