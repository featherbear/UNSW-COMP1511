/*

Write a program perfect.c that reads a positive integer n from standard input
and prints all the factors of n, their sum and if indicates if n is a perfect number.

*/

#include <stdio.h>

int main(void) {
    // Ask for the number
    int number;
    printf("Enter number: ");
    scanf("%d", &number);

    printf("The factors of %d are: \n", number);

    int counter = 1, sum = 0;
    while (counter <= number) {
        // For each integer less than `number`, check to see if it is a factor (ie remainder of zero)

        // Cheating without `if` statements again
        // Blame the challenge from wk3 that said no if statements.

        // If a number is not a factor, then the modulo will be non-zero - 1/'true' result
        // If a number is a factor, then the modulo will be zero - 0/'false' result
        // We can exploit this true/false value with the OR operator (||)
        //     The OR operator evaluates each expression from left to right
        //     If the first expression of an OR statement is true, the rest of the expressions will not be evaluated.
        //     If the first expression of an OR statement is false, the next expression will be evaluated.
        //   This exploit functions works by considering if `counter` is a factor,
        //   aka if the modulo is zero aka false, then we can use the OR operator chain expressions and functions.

        (number % counter) || printf("%d\n", counter) && (sum += counter);
        // (number % counter) || printf("%d\n", counter) && (sum += counter);
        //     IS THE SAME AS
        // if (number % counter) == 0 {
        //   printf(...);
        //   sum = sum + counter;
        // }

        counter++;
    }

    printf("Sum of factors = %d\n", sum);

    printf("%d is %sa perfect number\n", number, sum % number ? "not " : "");

    // We're using a ternary if statement - (condition) ? (resultIfTrue) : (resultIfFalse)
    //  sum % number ? "not " : ""
    //      IS THE SAME AS
    // char* isNumber(char* string) {
    //   if (sum % number) {
    //     return "not ";
    //   } else {
    //     return "";
    //   }
    // }

    //    printf("%d is %sa perfect number", number, sum % number ? "not " : "");
    //      (number) is %sa perfect number
    //      (number) is a perfect number || (number) is not a perfect number

    return 0;
}
