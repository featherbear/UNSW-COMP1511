// Hillary you're a thief.
// But you're also a genius =)
#include <stdio.h>

int main(void) {
    int box;
    printf("How many boxes: ");
    scanf("%d", &box);

    int dimension = (4 * box) - 1;
    int row = 0;
    while (row < dimension) {
        int column = 0;
        while (column < dimension) {
            if (row % 2 == 0 && row < dimension / 2 && column >= row && column < dimension - row) {
                printf("#");
            } else if (row % 2 == 0 && row > dimension / 2 && column <= row && column >= dimension - row) {
                printf("#");
            } else if (column % 2 == 0 && column < dimension / 2 && row >= column && column < dimension - row) {
                printf("#");
            } else if (column % 2 == 0 && column > dimension / 2 && row <= column && column >= dimension - row) {
                printf("#");
            } else {
                printf(" ");
            }
            column++;
        }
        printf("\n");
        row++;
    }
    return 0;
}