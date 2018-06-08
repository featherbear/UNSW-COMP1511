//
// Created by Andrew on 8/04/2018.
//

// Write a C program substitution.c which reads characters from its input
// and writes the characters to its output encrypted with a Substitution cipher.
//
// The mapping will be given to your program as a single command line argument.
// This command line argument will contain 26 characters: an ordering of the letters 'a'..'z'.
//
// Characters other than letters should not be encrypted.
//
// Your program should stop only at the end of input.
//
// Your program should contain at least one function other than main.

// A good programmer would check the command line argument is present and appropriate.
// Oh well.

#include <stdio.h>

char substitute(int c, char cipher[]);

int main(int argc, char *argv[]) {
    char c;
    while ((c = getchar()) != EOF) {
        putchar(substitute(c, argv[1]));
    }
    return 0;
}

char substitute(int c, char cipher[]) {
    if (c >= 'a' && c <= 'z') {
        // if 'a' <= c <= 'z', then bring it into the range of 'A' <= c <= 'Z"
        // aka subtract 32 ASCII code positions
        c -= 32;

        // The letter A is given the ASCII code 65, and the letter Z is given the ASCII code 90
        // We want to change the range from 65 <= c <= 90 to 0 <= c <= 90
        // aka subtract 65 (equivalent to 'A') ASCII code positions
        c -= 'A';

        // Now that we have a number in the range of 0..25, we can use this number as the index of our cipher!
        return cipher[c];
    }

    if (c >= 'A' && c <= 'Z') {
        // Doing the same thing as above, except since we're already using capital letters, we don't need to subtract 32
        c -= 'A';

        // Instead we subtract 32 ASCII code positions, as we need to ensure that the character we return is capital.
        // The question spec states that the cipher will be in lowercase (aka 97..122) so we want it to be 65..90
        return cipher[c] - 32;
    }

    // If the character is neither an upper case or lower case letter, return it as-is.
    return c;
}