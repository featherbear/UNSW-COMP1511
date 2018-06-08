//
// Created by Andrew on 8/04/2018.
//

/*

Write a C program devowel.c which reads characters from its input and writes the same characters to its output,
except it does not write lower case vowels ('a', 'e','i', 'o', 'u').

Your program should stop only at the end of input.

*/

#include <stdio.h>

int is_vowel(int character);

int main(void) {
    int c;
    while ((c = getchar()) != EOF) {
        // Keep looping until we reach an EOF character
        if (!is_vowel(c)) putchar(c);
    }
}

int is_vowel(int character) {
    // Check if the supplied character is a lower-case vowel
    if (character == 'a' || character == 'e' || character == 'i' || character == 'o' || character == 'u') return 1;
    return 0;
}