#include <stdio.h>

int main(void) {
    int size;
    printf("Enter size: ");
    scanf("%d", &size);

    int row = 0;
    while (row < size) {
        if (0 < row && row < size - 1) {
            /* For every row that is not the first or last, print a * followed by an amount of spaces */
            printf("*");
            int repeater = 1;
            while (repeater < row) {
                printf(" ");
                repeater++;
            }
        } else if (row == size - 1) {
            /* On the last line, print out row-1 asterisks */
            int repeater = 1;
            while (repeater < size) {
                printf("*");
                repeater++;
            }
        }

        printf("*\n"); // Print the final asterisk and new line character
        row++;
    }

    return 0;
}