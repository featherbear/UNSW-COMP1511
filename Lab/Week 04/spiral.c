/*

Write a program called spiral.c that reads an integer n from standard input
and prints an nxn pattern of asterisks and dashes in the shape of a spiral.
You can assume n is odd and >= 5.

You are only permitted to use C language features covered in weeks 1-3 lectures.

// You are not permitted to use array(s).

*/

#include <stdio.h>

/*

*********
        *
******* *
*     * *
* *** * *
* *   * *
* ***** *
*       *
*********

*/

int main() {
    // Thank you code forums!
    // Dividing the spiral into four triangular quarters makes things much easier than how I did the boxes, because you
    // get access to more invisible boundary lines
    int size;
    printf("Enter size: ");
    scanf("%d", &size);
    if (size % 2 == 0 || size < 5) return -1;

    int midpoint = size / 2;

    int cursorY = 0;
    while (cursorY < size) {
        int cursorX = 0;
        while (cursorX < size) {
            int flag = 0; // Instead of going (A&&B&&C)||(B&&C&&(D||(E&&F&&G||(B+C<A+B-fizzbuzz))) we'll use a flag.

            if (cursorY % 2 == 0) {
                if (cursorY < midpoint && cursorX >= cursorY && cursorX < size - cursorY) {
                    // Top triangle
                    flag = 1;
                } else if (cursorY > midpoint && cursorX <= cursorY && cursorX >= size - cursorY) {
                    // Bottom triangle
                    flag = 1;
                }
            }

            if (cursorX % 2 == 0) {
                if (cursorX > midpoint && cursorY <= cursorX && cursorX >= size - cursorY) {
                    // Right triangle
                    flag = 1;
                } else if (cursorX <= midpoint && cursorY > cursorX + 1 && cursorX < size - cursorY) {
                    // Left triangle. Notice our second condition `cursorY > cursorX PLUS ONE`, which prevents the box
                    // from forming a square
                    flag = 1;
                }
            }
            if (cursorX % 2 && cursorY == cursorX + 1) {
                // Handle the joining pieces
                flag = 1;
            }

            // The centre flag alternates every second odd cycle.
            // size | 5 | 7 | 9 | 11 | 13 |
            // -----|---|---|---|----|----|
            // s%4  | 1 | 3 | 1 | 3  | 1  |
            // -----|---|---|---|----|----|
            // flag | y | n | y | n  | y  |

            if (size % 4 == 1 && cursorY == cursorX && cursorY == size / 2) { flag = 1; }


            printf(flag ? "*" : "-");
            cursorX++;
        }
        printf("\n");
        cursorY++;
    }
    return 0;
}
