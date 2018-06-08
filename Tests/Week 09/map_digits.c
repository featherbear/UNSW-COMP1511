//
// Created by Andrew on 4/05/2018.
//

// Write a C program map_digits.c which reads characters from its input and writes the characters to its output
// with digit ('0' .. '9') characters replaced by specified characters.
// The mapping for digits will be given to your program as a single command line argument.
//
// This command line argument will contain 10 characters. These are the characters the corresponding digit should be replaced with.
// For example, '0's should be replaced with the first character of the command line argument,
// '1' with the second character of the command line argument and so on.
//
// Characters other than digits should not be changed.

#include <stdio.h>

int main(int argc, char *argv[]) {
    int c;
    while ((c = getchar()) != EOF) {
        putchar(('0' <= c && c <= '9') ? argv[1][c - '0'] : c);
    }

}