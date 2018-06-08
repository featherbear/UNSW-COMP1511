//
// Created by Andrew on 4/05/2018.
//

// Write a C program digit_filter.c which reads characters from its input and writes character to its output.
// Digits ('0' .. '9'), spaces and newline characters should be written unchanged.
//
// All other characters should be replaced with a '.' character.

#include <stdio.h>

int main() {
    int c;
    while ((c = getchar()) != EOF) {
        putchar((('0' <= c && c <= '9') || c == ' ' || c == '\n') ? c : '.');
    }
}
