//  Write a C program line_char.c which reads a line from its input then reads an integer n from its input.
//  It should write the character in position n from the line in the format given in the examples below.
//
//  Your program should then exit - it should not read more lines.

//  No error checking is necessary.

//  You can assume a line can be read.
//
//  You can assume the line will contain at most 256 characters.
//
//  You can assume a positive integer n can be read.
//
//  You can assume the line read has at least n characters.

#include <stdio.h>

#define MAX_CHARACTERS 256

int main(void) {
    // Store the user input into our character array
    char line[MAX_CHARACTERS] = {'\0'};
    fgets(line, MAX_CHARACTERS, stdin);

    // Get the input for the index of our string (remember, it's zero based)
    int pos;
    scanf("%d", &pos);

    printf("The character in position %d is '%c'\n", pos, line[pos]);
}