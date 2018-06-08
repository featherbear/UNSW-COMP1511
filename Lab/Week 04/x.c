/*

Write a program called x.c that reads an integer n from standard input,
and prints an nxn pattern of asterisks and dashes in the shape of an "X".
You can assume n is odd and >= 5.

// You are not permitted to use an array in this exercise.
*/

#include <stdio.h>

int main(void) {
    int size;
    printf("Enter size: ");
    scanf("%d", &size);

    int row = 0;
    while (row < size) {
        int column = 0;
        while (column < size) {
            // Rather than comparing each line, if we take a step back we realise
            // that the X falls on co-ordinates that are (x,x), or (n-x, x)
            printf(column == row || size - column - 1 == row ? "*" : "-");
            column++;
        }
        row++;
        printf("\n");
    }

    return 0;
}
