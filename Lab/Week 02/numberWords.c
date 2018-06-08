/*
  Make a program called numberWords.c.
  This program will ask for a number with the message Please enter an integer: .
    For numbers between 1 and 5, display the number as a word in the message You entered number.
    For numbers less than 1, display the message You entered a number less than one.
    For numbers greater than 5, display the message You entered a number greater than five.
*/

#include <stdio.h>

// Making a function to replicate an unsightly amount of `if ... elseif ... elseif ... elseif [...] else` statements.
char* lazy(int i) { // because C doesn't have strings, jUsT cHaRs Of InFiNiTe LeNgTh
    if (i > 5) return "a number greater than five"; // If the value is greater than five, then return said string.
    switch (i) {
        case 1: // if i == 1
            return "one";
        case 2: // if i == 2
            return "two";
        case 3: // if i == 3
            return "three";
        case 4: // if i == 4
            return "four";
        case 5: // if i == 5
            return "five";
        default: // if i =/= 1,2,3,4,5 and i is not greater than 5, hence zero or a negative number.
            return "a number less than one";
    }
}
int main() {
    // Get the input from the person
    int int1;
    printf("Please enter an integer: ");
    scanf("%d", &int1);

    printf("You entered %s.", lazy(int1)); // Passing the value of int1 into the function we created
    printf("\n");
    return 0;
}
