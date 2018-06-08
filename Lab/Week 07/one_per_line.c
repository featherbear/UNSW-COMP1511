//
// Created by Andrew on 14/04/2018.
//

// Write a C program, one_per_line.c, which reads in a line from standard input and writes out the characters one_per_line per line.
// Do not write a line for the new line character

#include <stdio.h>

#define MAX_LENGTH 4096

int main() {
    printf("Enter a string: ");

    char string[MAX_LENGTH];
    fgets(string, MAX_LENGTH, stdin);

    int i = 0;
    while (i < MAX_LENGTH && string[i] != '\n') {
        printf("%c\n", string[i]);
        i++;
    }
}
