//
// Created by Andrew on 8/04/2018.
//

// Write a C program swap_case.c which reads characters from its input and writes the same characters to its
// output with lower case letters converted to upper case and upper case letters converted to lower case.
// Your program should stop only at the end of input.

// They might as well have given us a sPoNgEbOb TeXt AcTiViTy

#include <stdio.h>

int swapCase(char c);

int main(void) {
    int c;
    while ((c = getchar()) != EOF) {
        // Keep looping until we reach an EOF character
        putchar(swapCase(c));
    }
}

int swapCase(char c) {
    // The ASCII position of A is 65
    // The ASCII position of a is 97
    // So we can just add 32 to the character code position of any capital letter to get its lower-case

    if (c >= 'a' && c <= 'z') return c - 32;
    if (c >= 'A' && c <= 'Z') return c + 32;
    return c;
}