//
// Created by Andrew on 14/04/2018.
//

// Write a program, first_lines.c, which given a filename as argument prints the first 10 lines of the file.
// If the file has less than 10 lines the entire file should be printed.
// Note this program does not create any files. Its just prints part of the contents of a file to standard output.

// It should also be possible to specify that a different number of lines be printed.
// This will be done by passing the string "-n" as the first argument to the program
// The second argument will be the the number of lines to be printed.
// The file will now be the third argument to the program.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

    // Your program should print a suitable error message if given the wrong number of arguments or if the file can not be created.
    if (argc != 1 + 1 && argc != 3 + 1) {
        printf("Invalid number of arguments!\nUsage: %s [-n (lines)] file\n", argv[0]);
        return -1;
    }

    int linesToRead = 10;
    char *filePath = argv[1];
    if (argc == 3 + 1 && strcmp(argv[1], "-n") == 0) {
        linesToRead = atoi(argv[2]);
        filePath = argv[3];
        // Could also do an additional check to check that if `-n` is specified, the next argument is of an int type.
    }

    // Open our file with the read bit
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        perror(argv[3]);
        return -2;
    }


    int lineCount = 0;
    int c;

    // Print out each character until we reach `linesToRead` lines
    while (lineCount < linesToRead && (c = fgetc(file)) != EOF) {
        if (c == '\n') lineCount++;
        fputc(c, stdout); // putchar(c); // ???
    }

    fclose(file);

}