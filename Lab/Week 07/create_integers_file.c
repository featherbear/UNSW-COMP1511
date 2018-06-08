//
// Created by Andrew on 14/04/2018.
//

// Write a C program, create_integer_file.c which takes 3 arguments.
// The first & second arguments will specify a range of integers.
//
// The third argument will specify a filename.
//
// Your program should create a file of this name containing the specified integers.

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    // Your program should print a suitable error message if given the wrong number of arguments or if the file can not be created.
    if (argc != 3 + 1) {
        printf("Invalid number of arguments!\nUsage: %s (start) (end) (file)\n", argv[0]);
        return -1;
    }

    // Open our file with the write bit
    FILE *file = fopen(argv[3], "w");
    if (file == NULL) {
        perror(argv[3]);  // prints why the open failed
        return -2;
    }

    // Convert and store our first and second program arguments (aka lower and upper number bounds)
    int lower = atoi(argv[1]);
    int upper = atoi(argv[2]);

    // Write each increment from `lower` to `upper` to our file
    while (lower <= upper) {
        fprintf(file, "%d\n", lower);
        lower++;
    }


    fclose(file);

}