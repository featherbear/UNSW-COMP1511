/*

In this task, you will create a program called danish_flag.c which will
read in a size and display a Danish Flag of that size using the following algorithm and the # character.

The Danish Flag is made up of 6 blocks. It is 3 blocks wide, and 2 blocks high.
To display it using empty spaces and the character '#'
We will read in a value called `size`.
Each block will be 3 times size wide, and 2 times size high.

In the top left block, the right column and bottom row will be empty spaces.
In the top middle block, the left column and bottom row will be empty spaces.
In the top right block, the bottom row will be empty spaces.
In the bottom left block, the right column and top row will be empty spaces.
In the bottom middle block, the left column and top row will be empty spaces.
In the bottom right block, the top row will be empty spaces.
Every other position will be the # character.

*/

#include <stdio.h>
int main() {
    int size;
    printf("Enter the flag size: ");
    scanf("%d", &size);

    int segmentsX = size * 3 * 3;
    int segmentsY = size * 2 * 2;

    // if segmentsY = 4; middle is 2,3

    int whiteY = segmentsY / 2;
    int whiteX = segmentsX / 3;

    // if segmentsX = 9; middle is 3,4
    // if segmentsX = 18; middle is 6,7
    // if segmentsX = 27; middle is 9,10

    int cursorY = 1;
    int cursorX;

    while (cursorY <= segmentsY) {
        cursorX = 1;
        while (cursorX <= segmentsX) {
            printf(cursorY == whiteY || cursorY == whiteY + 1 || cursorX == whiteX || cursorX == whiteX + 1? " " : "#");
            cursorX++;
        }
        printf("\n");
        cursorY++;
    }
}





/*
// I got baited. The white section of the flag doesn't scale ...

int main() {
    int size = 1;
//  printf ("Enter the flag size: ");
//  scanf ("%d", &size);

    int segmentsX = size * 3 * 3;
    int segmentsY = size * 2 * 2;
    printf("\n\nGrid is %dx%d\n", segmentsX, segmentsY);
    int cursorX;
    int cursorY = 0;

    while (cursorY < segmentsY) {
        cursorX = 0;
        while (cursorX < segmentsX) {
            int blockPosX = (cursorX - cursorX % 3) / (size * 3);
            int blockPosY = (cursorY - cursorY % 2) / (size * 2);
            int internalPosX = (cursorX / size) % 3;
            int internalPosY = (cursorY / size) % 2;
            printf( (blockPosY==1 && (internalPosY == 0 || (blockPosX==0 && internalPosX == 2) || (blockPosX == 1 && internalPosX == 0))) || (blockPosY == 0 && (internalPosY==1 || (blockPosX == 1 && internalPosX == 0) || (blockPosX == 0 && internalPosX == 2)))? " ": "#");
            cursorX++;

        }
        printf("\n");
        cursorY++;
    }

    return 0;
}
*/