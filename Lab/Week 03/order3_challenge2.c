// TODO code-golf me

#define badlyNamedQuestionVariable "Enter integer: " // We got lazy.

#include <stdio.h> // Include the library that contains the `printf` and `scanf` functions

int main() {
    // Define our variables, badly... :)
    int badlyNamedVariable1;
    int badlyNamedVariable2;
    int badlyNamedVariable3;

    // Ask for the three integers
    printf(badlyNamedQuestionVariable);
    scanf("%d", &badlyNamedVariable1);

    printf(badlyNamedQuestionVariable);
    scanf("%d", &badlyNamedVariable2);

    printf(badlyNamedQuestionVariable);
    scanf("%d", &badlyNamedVariable3);

    // Bubble sorting from the right
    /* switch 2 and 3 */ (badlyNamedVariable3 < badlyNamedVariable2) && (badlyNamedVariable3 += badlyNamedVariable2) && (badlyNamedVariable2=badlyNamedVariable3-badlyNamedVariable2) && (badlyNamedVariable3-=badlyNamedVariable2);
    /* switch 1 and 2 */ (badlyNamedVariable2 < badlyNamedVariable1) && (badlyNamedVariable2 += badlyNamedVariable1) && (badlyNamedVariable1=badlyNamedVariable2-badlyNamedVariable1) && (badlyNamedVariable2-=badlyNamedVariable1);
    /* switch 2 and 3 */ (badlyNamedVariable3 < badlyNamedVariable2) && (badlyNamedVariable3 += badlyNamedVariable2) && (badlyNamedVariable2=badlyNamedVariable3-badlyNamedVariable2) && (badlyNamedVariable3-=badlyNamedVariable2);

    printf("The integers in order are: %d %d %d\n", badlyNamedVariable1,badlyNamedVariable2,badlyNamedVariable3);
    return 0;
}