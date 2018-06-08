//
// Created by Andrew on 4/05/2018.
//

// Write a C program word_count.c which reads characters from its input until the end of input
// and then prints a count of the characters, words and lines it read.
// Assume the only non-word characters are space and newline.
//
// All other characters should be considered word characters.
//
// A word is defined as a maximal non-empty sequence of word characters.
//
// Multiple spaces or newline characters may separate words.

#include <stdio.h>

int main() {
    int c;

    int countCharacters = 0;
    int countLines = 0;
    int countWords = 0;

    int prevC = ' ';
    while ((c = getchar()) != EOF) {
        countCharacters++;
        if (c == '\n') countLines++;
        if ((c != ' ' && c != '\n') && (prevC == ' ' || prevC == '\n')) {
            countWords++;
        }

        prevC = c;
    }

    printf("%d lines %d words %d characters\n", countLines, countWords, countCharacters);
}

