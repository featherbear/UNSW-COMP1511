//
// Created by Andrew on 14/04/2018.
//

// Write a program, last_lines.c, which given a filename as argument prints the last 10 lines of the file.
// If the file has less than 10 lines the entire file should be printed.
// You can assume lines have at most 1024 characters, but you can not make any assumption about how many lines are in the file.
//
// You can not read the entire file into an array.

#include <stdio.h>

int main(int argc, char *argv[]) {
    char lines[10][1024] = {'\0'};

    // Open our file with the read bit
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror(argv[1]);
        return -2;
    }

    int lineCount = 0;
    int c;

    // Iterate each line in our file, overwriting our ten lines in `lines`
    int i = 0;
    while ((c = fgetc(file)) != EOF) {
        // Modify `lines` index 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9

        lines[lineCount % 10][i] = c;
        i++;

        if (c == '\n') {
            lineCount++; // New line? Increase the line counter to modify which index we're modifying in `lines`
            i = 0; // Also reset our linear cursor
        }
    }

    // Now that we've stored the last ten lines, grab those ten lines, starting from the next index
    // that is, if we just modified index 8, print values from index 9 0 1 2 3 4 5 6 7 8
    i = 0;
    while (i < 10) {
        printf("%s", lines[(lineCount + i) % 10]);
        i++;
    }
}