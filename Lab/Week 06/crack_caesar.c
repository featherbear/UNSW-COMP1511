//
// Created by Andrew on 8/04/2018.
//

// Write a C program crack_caesar.c which decrypts text encrypted by an unknown Caesar cipher.
// Your program should make no assumptions about the language of the original text - don't assume its English.
//
// Your program will be given as a command-line argument the name of a file containing
// a large amount of unencrypted text in the same language as the encrypted text.
//
// For example your program might be given this file:
//        https://cgi.cse.unsw.edu.au/~cs1511/18s1/activities/crack_caesar/wiki_sentences.txt
//                containing 188k characters of English text
//
// Your program will be given the encrypted text on standard input.
// It should print its decryption
//
// You may assume the encrypted text contains at most 10000 characters.


#include <stdio.h>
#include <string.h>

// START CODE FROM caesar.c
int modulo(int x, int N) {
    return (x % N + N) % N;
}

int characterShift(char c, int offset) {
    if ('a' <= c && c <= 'z') return 'a' + modulo(c - 'a' + offset, 26);
    if ('A' <= c && c <= 'Z') return 'A' + modulo(c - 'A' + offset, 26);
    return c;
}
// END CODE FROM caesar.c

// START CODE FROM frequency_analysis.c
int toLowerCase(char c) {
    // Convert uppercase letters to their lowercase letter.
    // If the character is not an uppercase, return as-is.
    return ('A' <= c && c <= 'Z') ? c + 32 : c;
}

// END CODE FROM frequency_analysis.c
int isLetter(char c) {
    c = toLowerCase(c);
    return 'a' <= c && c <= 'z';
}

#define wordMatches 10

int main(int argc, char *argv[]) {

#define fileArrMAX 250000
#define inputArrMAX 10000

    char fileArr[fileArrMAX] = {'\0'};
    char inputArr[inputArrMAX] = {'\0'};

    int c;
    int i = 0;

    // Read file and keep only letters, space, new line and single quote
    FILE *stream = fopen(argv[1], "r");
    while ((c = fgetc(stream)) != EOF) {
        if (isLetter(c) || c == '\'' || c == ' ' || c == '\n') {
            if (c == ' ' && fileArr[i - 1] == ' ') continue;
            if (c == '\n') c = ' ';
            fileArr[i] = toLowerCase(c);
            i++;

        }
    }

    // Read input (Keeping this because we need to print out the input later)
    i = 0;
    while ((c = getchar()) != EOF) {
        inputArr[i] = c;
        i++;
    }

    // Sanitise the input array in the exact same way as our file sanitisation.
    char cleanInputArr[inputArrMAX] = {'\0'};
    i = 0;
    int j = 0;
    while ((c = inputArr[i]) != '\0') {
        if (isLetter(c) || c == '\'' || c == ' ' || c == '\n') {
            if (c == ' ' && cleanInputArr[j - 1] == ' ') {
                i++;
                continue;
            }
            if (c == '\n') c = ' ';
            cleanInputArr[j] = toLowerCase(c);
            j++;
        }
        i++;
    }

    char word[wordMatches][20] = {{'\0'}};
    int wc = 0;

    // Extract n words (n <= wordMatches)
    i = 0;
    j = 0;
    while (wc < wordMatches) {
        j = 0;
        while (cleanInputArr[i] != '\0') {
            if (cleanInputArr[i] == ' ') {
                break;
            }
            word[wc][j] = cleanInputArr[i];
            j++;
            i++;
        }
        i++;
        wc++;
    }

    char sWord[wordMatches][20] = {{'\0'}};
    int offset = 0;
    int offsetMatch[26] = {0};
    while (offset < 26) {
        int matchCount = 0;
        wc = 0;
        while (wc < wordMatches) {
            i = 0;
            // Shift each word's letters by the offset
            while (word[wc][i] != '\0') {
                sWord[wc][i] = characterShift(word[wc][i], offset);
                i++;
            }
            matchCount += strstr(fileArr, sWord[wc]) != NULL; // If a word matches, increase matchCount
            wc++; // Go to the next word
        }
        offsetMatch[offset] = matchCount; // Store the count
        offset++;
    }

    // Find the highest match count
    offset = 0;
    int highestOffset = 0;
    while (offset < 26) {
        if (offsetMatch[offset] > offsetMatch[highestOffset]) highestOffset = offset;
        offset++;
    }

    i = 0;
    while (inputArr[i] != '\0') {
        putchar(characterShift(inputArr[i], highestOffset));
        i++;
    }
}

