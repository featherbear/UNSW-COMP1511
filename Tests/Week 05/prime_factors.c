//
// Created by Andrew on 6/04/2018.
//

// Write a program called prime_factors.c that reads a integer n from standard input and prints the decomposition of n into prime factors.
// If n is prime it should instead print "n is prime" (where n is the integer).

//  the heck is a prime factor

#include <stdio.h>

int isPrime(int i) {
    // A prime number is a number that does not have any factors other than itself and 1
    // This function recurses from 2..i to ensure that there are no divisible numbers.
    int counter = 2;
    int result = 1;
    while (counter < i) {
        if (i % counter == 0) {
            result = 0;
        }
        counter++;
    }
    return result; // TRUE if 1, FALSE if 0
}

int main() {
    int number;
    printf("Enter number: ");
    scanf("%d", &number);

    int _number = number; // Duplicate the value of `number`, as we are manipulating its value later

    int counter = 2;
    int printAsterisk = 0; // First-match flag, as well as if there was a match at all

    while (counter < _number + 1) {
        // Check if the `counter` is a prime number,
        // as well as a factor of `_number`,
        // as well as that `counter` is not the same as the original number - a number will always be a factor of itself
        if (isPrime(counter) && _number % counter == 0 && counter != number) {
            if (!printAsterisk) {
                // For the first match, print the information line, and don't print any separating asterisks
                printAsterisk = 1;
                printf("The prime factorization of %d is:\n", number);
            } else { printf(" * "); } // Every other match should be separated with ' * '

            printf("%d", counter); // Print out the actual number
            _number /= counter; // Modify `_number` to be the resultant of the division by `counter`
        } else {
            // We only want to increase the counter if `counter` is not able to be divisible anymore.
            counter++;
        }
    }
    if (printAsterisk) {
        // That means that at least one match was found
        printf(" = %d\n", number);
    } else {
        // Number didn't match, therefore it's a prime!
        printf("%d is prime\n", number);
    }

    return 0;
}
