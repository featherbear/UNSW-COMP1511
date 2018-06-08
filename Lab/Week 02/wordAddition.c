/*
  For this challenge you can only use the topics covered in the course so far:
    if, elseif, else, printf, scanf, int

  This program should ask for two integers using the message
    Please enter two integers:
  and then display the sum of the integers as n + n = sum.

  Any numbers that are between zero and ten should appear as words.
  This also applies to negative numbers between negative ten and zero.
  All other numbers should appear as decimal integers.
 */

#include <stdio.h>

int main() {
    // Grab the two integers, separated by a space
    int int1;
    int int2;
    printf("Please enter two integers: ");
    scanf("%d %d", &int1, &int2);

    // Work on the first integer
    if (-10 <= int1 && int1 < 0) printf("negative ");
    if (int1 == 0) printf("zero");
    else if (int1 == 1 || int1 == -1) printf("one");
    else if (int1 == 2 || int1 == -2) printf("two");
    else if (int1 == 3 || int1 == -3) printf("three");
    else if (int1 == 4 || int1 == -4) printf("four");
    else if (int1 == 5 || int1 == -5) printf("five");
    else if (int1 == 6 || int1 == -6) printf("six");
    else if (int1 == 7 || int1 == -7) printf("seven");
    else if (int1 == 8 || int1 == -8) printf("eight");
    else if (int1 == 9 || int1 == -9) printf("nine");
    else if (int1 == 10 || int1 == -10) printf("ten");
    else printf("%d", int1); // Print out the number if it was outside of -10 to 10

    printf(" + ");

    // Work on the second integer // too bad we can't use functions.
    if (-10 <= int2 && int2 < 0) printf("negative ");
    if (int2 == 0) printf("zero");
    else if (int2 == 1 || int2 == -1) printf("one");
    else if (int2 == 2 || int2 == -2) printf("two");
    else if (int2 == 3 || int2 == -3) printf("three");
    else if (int2 == 4 || int2 == -4) printf("four");
    else if (int2 == 5 || int2 == -5) printf("five");
    else if (int2 == 6 || int2 == -6) printf("six");
    else if (int2 == 7 || int2 == -7) printf("seven");
    else if (int2 == 8 || int2 == -8) printf("eight");
    else if (int2 == 9 || int2 == -9) printf("nine");
    else if (int2 == 10 || int2 == -10) printf("ten");
    else printf("%d", int2); // Print out the number if it was outside of -10 to 10

    printf(" = ");

    int sum = int1 + int2; // Now we can add the two integers together, and represent the sum as a string.
    // I mean, a char array of infinite length.

    // and now do the exact same thing, AGAIN.
    if (-10 <= sum && sum < 0) printf("negative ");
    if (sum == 0) printf("zero");
    else if (sum == 1 || sum == -1) printf("one");
    else if (sum == 2 || sum == -2) printf("two");
    else if (sum == 3 || sum == -3) printf("three");
    else if (sum == 4 || sum == -4) printf("four");
    else if (sum == 5 || sum == -5) printf("five");
    else if (sum == 6 || sum == -6) printf("six");
    else if (sum == 7 || sum == -7) printf("seven");
    else if (sum == 8 || sum == -8) printf("eight");
    else if (sum == 9 || sum == -9) printf("nine");
    else if (sum == 10 || sum == -10) printf("ten");
    else printf("%d", sum);

    printf("\n");
    return 0;
}
