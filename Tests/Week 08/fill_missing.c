//
// Created by Andrew on 29/04/2018.
//

// Write a C program fill_missing.c which reads integers from standard input until it reaches end-of-input.
// It should then print the missing integers.
//
// The missing integers should be all positive integers which did not appear in the program's input
// and which are smaller than the largest integer which did appear in the program's input.
//
// The missing integers should be printed in increasing order on a single line.

#include <stdio.h>
int isInArray(int needle, int *haystack, int haystackLength);

int isInArray(int needle, int *haystack, int haystackLength) {
    int i = 0;
    while (i < haystackLength) {
        if (haystack[i] == needle) { return 1; }
        i++;
    }
    return 0;
}

int main() {
    int highest = 0;

    int store[10000] = {0};
    int i = 0;

    int v;
    while (scanf("%d", &v) != EOF) {
        // Update the highest integer
        if (v > highest) {
            highest = v;
        }

        // Store the integer in the array `store`
        store[i] = v;
        i++;
    }

    int firstTime = 0; // Print looping, separated by spaces.

    i = 1;
    while (i < highest) {
        if (!isInArray(i, store, 10000)) {
            printf("%s%d", !firstTime++ ? "" : " ", i);
        }
        i++;
    }

    printf("\n");
}