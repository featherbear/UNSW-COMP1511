//
// Created by Andrew on 14/04/2018.
//

// A palindrome is a sequence which is the same forwards as backwards.
// Write a program, palindrome.c, which reads a string and tests if it is a palindrome.

#include <stdio.h>

#define MAX_LENGTH 4096

int main() {
    printf("Enter a string: ");

    char string[MAX_LENGTH];
    fgets(string, MAX_LENGTH, stdin);

    // Get the position of the last letter
    int lastPos = 0;
    while (lastPos < MAX_LENGTH && string[lastPos] != '\n') {
        lastPos++;
    }
    lastPos--;

    int isPalindrome = 1;
    if (lastPos == -1) {
        isPalindrome = 1;
    } else {
        // Check for palindromic-activity... :)
        int i = 0;
        while (i < lastPos / 2 + 1) {
            if (string[i] != string[lastPos - i]) isPalindrome = 0;
            /*
             * n[0] ?= n[max-0]
             * n[1] ?= n[max-1]
             * n[2] ?= n[max-2]
             * ... etc ...
             */
            i++;
        }
    }
    printf("String is %sa palindrome\n", isPalindrome ? "" : "not ");
}
