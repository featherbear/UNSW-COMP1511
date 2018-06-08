//
// Created by Andrew on 8/04/2018.
//

// Write a C program decode.c which decrypts text encrypted by substitution.c

#include <stdio.h>

char substitute(int c, char cipher[]);

int main(int argc, char *argv[]) {

    // We want to reverse the cipher
    char *oldCipher = argv[1];
    char cipher[26];

    int i = 0;
    int j;

    // for each letter a..z, find its position in the cipher and create a reverse cipher map
    while (i < 26) {
        j = 0;
        while (j < 26) {
            if ('a' + i == oldCipher[j]) {
                cipher[i] = 'a' + j;
            }
            j++;
        }
        i++;
    }

    char c;
    while ((c = getchar()) != EOF) {
        putchar(substitute(c, cipher));
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

        // Instead we substract 32 ASCII code positions, as we need to ensure that the character we return is capital.
        // The question spec states that the cipher will be in lowercase (aka 97..122) so we want it to be 65..90
        return cipher[c] - 32;
    }

    // If the character is neither an upper case or lower case letter, return it as-is.
    return c;
}