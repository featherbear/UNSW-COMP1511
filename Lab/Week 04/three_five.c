/*

Write a program that three_five.c that reads a positive integer n
and print all the positive integers < n divisible by 3 or 5.

*/

#include <stdio.h>

int main(void) {
    // Ask for the number
    printf("Enter number: ");
    int number;
    scanf("%d", &number);

    int counter = 1;
    while (counter < number) {
        if (counter % 3 == 0 || counter % 5 == 0) printf("%d\n", counter); // If counter is divisible by 3 or 5, printf.
        counter++;
    }
}