#include <stdio.h>

int main(void) {
    int size;

    printf("Enter size: ");
    scanf("%d", &size);

    int row = 0;
    while (row < size) {
        /* Each row is an asterisk followed by a new line character */
        if (row == size - 1) {
            /* Except the last row!!!111oneoneone!!! */
            int repeater = 1;
            while (repeater < size) {
                printf("*");
                repeater++;
            }
        }
        printf("*\n");
        row++;
    }

    return 0;
}