//
// Created by Andrew on 6/04/2018.
//

// Write a C program count_up.c that reads 2 positive integers and prints the integers between them, one per line.

#include <stdio.h>
int main() {
    // Ask for lower and upper numbers
    int lb, ub;
    printf("Enter lower: ");
    scanf("%d", &lb);
    printf("Enter upper: ");
    scanf("%d", &ub);

    while (lb < ub - 1) {
        // Print every single number from (lb+1)..(ub-1) inclusive
        lb++;
        printf("%d\n", lb);
    }
    return 0;
};