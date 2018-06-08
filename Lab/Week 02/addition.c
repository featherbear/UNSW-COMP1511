/*
 This program should ask for two integers using the message:
   Please enter two integers:
 and then display the sum of the integers as n + n = sum.
*/

#include <stdio.h>

int main() {

    // Define the variable that we will later store into with `scanf`
    int int1;
    int int2;

    // Display text that asks for user input
    printf("Please enter two integers: "); // Note that we don't add a new line (\n)

    // User input
    scanf("%d %d", &int1, &int2);

    // Print the equation and the sum
    printf("%d + %d = %d\n", int1, int2, int1 + int2);
    return 0;
}
