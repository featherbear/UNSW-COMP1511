//Write a C program remove_repeated_lines.c which reads lines and prints them unless it has seen exactly the same line previously.
//In other words it doesn't print repeated lines. It prints our only the first occurance of any line.
//
//It should stop when it reaches the end of input.

//You can assume lines will contain at most 256 characters.
//You can assume lines are terminated with a newline ('\n') character,

#include <stdio.h>

#define MAX_CHARACTERS 256

int main(void) {
    char line[MAX_CHARACTERS] = {'\0'};

    int index = 0;
    
    int c;
    // Loop until we reach EOF
    while ((c = getchar()) != EOF) {

        if (c == '\n') {
            // If we've reached the end of the line, print all the characters backwards
            while (index > 0) {
                putchar(line[index - 1]);
                index--;
            }

            // Then print a new line
            putchar('\n');


        } else {
            // Not the end of the line, so add the character to our character array
            line[index] = c;
            index++;
        }
    }

}