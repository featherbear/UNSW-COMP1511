//Write a C program reverse_lines.c which reads lines and writes them out with the characters of each line in reverse order. It should stop when it reaches the end of input.
//
//

//You can assume lines will contain at most 256 characters.
//You assume at most 256 lines will be read before end-of-input.
//
//You can assume lines are terminated with a newline ('\n') character,

#include <stdio.h>
#include <string.h>

#define MAX_CHARACTERS 256
#define MAX_LINES 256


int isSeenLine(char *line, char seen[][MAX_CHARACTERS]);

// Checks if a line has been seen before
int isSeenLine(char *line, char seen[][MAX_CHARACTERS]) {
    int i = 0;

    // Repeat until we no longer have lines to compare to
    // Empty lines will have a length of zero, therefore loop UNTIL the length is zero
    while (strlen(seen[i]) != 0) {
        // If the strings match, then we've found a line that has been seen before
        if (strcmp(line, seen[i]) == 0) {
            return 1;
        }
        i++;
    }

    // N o p e
    return 0;
}

int main(void) {
    char lines[MAX_LINES][MAX_CHARACTERS] = {{'\0'}};
    char line[MAX_CHARACTERS] = {'\0'};

    int lineCounter = 0;
    // Repeat until EOF
    while (fgets(line, MAX_CHARACTERS, stdin)) {


        if (!isSeenLine(line, lines)) {
            printf("%s", line);

            strcpy(lines[lineCounter], line);
            lineCounter++;
        }

    }
}


