#define question "Enter integer: "

#include <stdio.h>

int main(void) {
    // Get the integers
    int A;
    printf(question);
    scanf("%d", &A);

    int B;
    printf(question);
    scanf("%d", &B);

    int C;
    printf(question);
    scanf("%d", &C);


    // Printing time!
    printf("Middle: ");

        // Check if A is the middle number
    if ((B <= A && A <= C) || (C <= A && A <= B)) printf("%d", A);
        // Check if B is the middle number
    else if ((A <= B && B <= C) || (C <= B && B <= A)) printf("%d", B);
        // Check if C is the middle number
    else if ((B <= C && C <= A) || (A <= C && C <= B)) printf("%d", C);

    printf("\n"); // End the line with a new line character
    return 0;
}
