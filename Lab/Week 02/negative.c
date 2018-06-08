/*
Write a program that uses scanf to get a number from a user and prints "Don't be so negative!" if they entered a negative number.
If the number is positive, the program should print "You have entered a positive number."
If the user enters the number 0, the program should print "You have entered zero."
*/

#include <stdio.h>

int main() {
    // Grab the number from the input.. although don't prompt the user to enter a number.......
    int number;
    scanf("%d", &number);

    // Value checking time!
    if (number < 0) {
        printf("Don't be so negative!");
    } else if (number == 0) {
        printf("You have entered zero.");
    } else {
        // If the value is not less than zero, and it is also not zero, then it must be a positive number!
        printf("You have entered a positive number.");
    }

    printf("\n");
    return 0;
}
