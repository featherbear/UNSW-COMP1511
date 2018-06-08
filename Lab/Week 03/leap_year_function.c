//
// Created by Andrew on 13/03/2018.
//

#include <stdio.h>

// Prototype to tell the compiler that the function `isLeapYear` exists!
int isLeapYear(int year);

int main() {
    // Prompt the user for the year
    int year;
    printf("Enter year: ");
    scanf("%d", &year);

    // More one-line if statements :)
    // if `isLeapYear(year)` is 1, then print "YEAR is a leap year."
    // otherwise, print "YEAR is not a leap year."
    printf("%d %s\n", year, isLeapYear(year) ? "is a leap year." : "is not a leap year.");
}

int isLeapYear(int year) {
    // Adapted from https://en.wikipedia.org/wiki/Leap_year#Algorithm
    if (year % 4 != 0) return 0;
    if (year % 100 != 0) return 1;
    else if (year % 400 != 0) return 0;
    return 1;
}

