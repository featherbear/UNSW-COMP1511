//
// Created by Andrew on 14/04/2018.
//

// Write a program, punctuated_palindrome.c, which reads a string and tests if it is a palindrome.
// Characters which are not letters should be ignored.
// Differences between upper case and lower case are ignored.


int toLowerCase(char c) {
    return ('A' <= c && c <= 'Z') ? c + 32 : c;
}

int isAlpha(char c) {
    c = toLowerCase(c);
    return 'a' <= c && c <= 'z';
}


#include <stdio.h>

#define MAX_LENGTH 4096

int main() {
    printf("Enter a string: ");

    char string[MAX_LENGTH];
    fgets(string, MAX_LENGTH, stdin);


    // Find the position of the last character before the '\n'
    // Or should we be using string.h functions?
    int lastPos = 0;
    while (lastPos < MAX_LENGTH && string[lastPos + 1] != '\n') {
        lastPos++;
    }

    // Strip all non letters of string up to `lastPos`, and store it into `sanitisedString`
    int i = 0;
    int offset = 0;
    char santitisedString[MAX_LENGTH];
    while (i + offset < lastPos + 1) {
        int pos = i + offset;
        if (isAlpha(string[pos])) {
            santitisedString[i] = toLowerCase(string[pos]);
            i++;
        } else {
            offset++;
        }
    }
    i--; // 0 based indexing!

    // Same palindrome logic as palindrome.c
    int isPalindrome = 1;
    int j = 0;
    while (j < i / 2 + 1) {
        if (santitisedString[j] != santitisedString[i - j]) isPalindrome = 0;
        j++;
    }

    printf("String is %sa palindrome\n", isPalindrome ? "" : "not ");
}
