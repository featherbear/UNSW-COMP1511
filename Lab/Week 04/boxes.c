/*

For this challenge, make a program called boxes.c which reads in a number
and then draws that many square boxes inside each other using the character #

// Doesn't say you can't use arrays :)

*/


#include <stdio.h>

// This code could be a lot more succinct, but it does the job.

int main() {
    int size;
    printf("How many boxes: ");
    scanf("%d", &size);
    if (size > 0) {
        // If we want one box then we need a 3x3
        // If we want two boxes then we need a 7x7
        // If we want three boxes then we need an 11x11
        // ...
        // If we want five boxes then we need a 19x19

        // General formula: 4x - 1
        int segments = size * 4 - 1;

        int middle = segments / 2;

        int cursorY = 0;
        int cursorX;

        int padding = 0;
        int _padding;

        //
        while (cursorY < middle) {
            if (cursorY % 2) padding++;
            _padding = 0;
            while (_padding < padding) {
                printf("%s", _padding != padding ? "# " : "#");
                _padding++;
            }
            int _size = 0;
            while (_size < segments - 4 * padding) {
                printf((cursorY + (cursorY > middle)) % 2 ? " " : "#");
                _size++;
            }
            _padding = 0;
            while (_padding < padding) {
                printf("%s", _padding != padding ? " #" : "#");
                _padding++;
            }
            cursorY++;
            printf("\n");
        }

        // cheat the middle case
        printf("#");
        int i = 0;
        while (i < size * 2 - 1) {
            printf(" #");
            i++;
        }

        //

        while (cursorY < segments - 1) {
            printf("\n");
            _padding = 0;
            while (_padding < padding) {
                printf("%s", _padding != padding ? "# " : "#");
                _padding++;
            }
            int _size = 0;
            while (_size < segments - 4 * padding) {
                printf(cursorY % 2 ? "#" : " ");
                _size++;
            }
            _padding = 0;
            while (_padding < padding) {
                printf("%s", _padding != padding ? " #" : "#");
                _padding++;
            }
            if (cursorY % 2 == 0) padding--;
            cursorY++;

        }
    printf("\n");
    }
    // EDIT: Sometime (yester[ester][ester][ester])today the autotest changed to not expect a new line character when the box size is zero
    // printf("\n");
}


