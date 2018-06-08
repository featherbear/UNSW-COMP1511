//
// Created by Andrew on 6/04/2018.
//

// Write a C program product_odd.c that reads 2 positive integers and calculates the product of the odd integers between the first and second integers.
// For example, if the two integers entered are 10 and 16 then 2145 should be printed because 11 * 13 * 15 = 2145.
// If there are no odd integers between the first and second integers, your program should print 1.

#include <stdio.h>
int main() {
    int product = 1;

    // Ask for lower and upper numbers
    int lb, ub;
    printf("Enter lower: ");
    scanf("%d", &lb);
    printf("Enter upper: ");
    scanf("%d", &ub);

    while (lb < ub - 1) {
        // From lb..(ub-1), if `lb` is not divisible by two (aka remainder > 0), set `product` to `product * lb`
        lb++;
        if (lb % 2) {
            product *= lb;
        }
    }
    printf("%d\n", product);
    return 0;
};

