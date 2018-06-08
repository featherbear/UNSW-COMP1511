// Write a C program frequency_analysis.c which reads characters from its input until end of input.
// It should then print the occurance frequency for each of the 26 letters 'a'..'z'.
//
// The frequency should be printed as a decimal value and an absolute number in exactly the format below.
//
// Note upper and lower case letters are counted together.

#include <stdio.h>

int toLowerCase(char c) {
    // Convert uppercase letters to their lowercase letter.
    // If the character is not an uppercase, return as-is.
    return ('A' <= c && c <= 'Z') ? c + 32 : c;
}

int main() {

    int total = 0;
    int characterCount[26] = {0};

    int c;
    while ((c = getchar()) != EOF) {

        // Convert uppercase letters to their lowercase letter.
        // If the character is not an uppercase, return as-is.
        c = toLowerCase(c);

        // Check if the character `c` is in a..z
        if (c >= 'a' && c <= 'z') {
            characterCount[c - 'a']++;
            total++;
        }
    }

    int i = 0;
    while (i < 26) {
        printf("'%c' %lf %d\n", 'a' + i, characterCount[i] * 1.0 / total, characterCount[i]);
        i++;
    }

    return 0;
}
