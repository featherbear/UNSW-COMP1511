//
// Created by Andrew on 13/03/2018.
//

#define badlyNamedQuestionVariable "Enter integer: " // We got lazy.

#include <stdio.h> // Include the library that contains the `printf` and `scanf` functions

int main() {
    // Define our variables, badly... :)
    int badlyNamedVariable1;
    int badlyNamedVariable2;
    int badlyNamedVariable3;

    // I got lazy
    int smol;
    int meed;
    int lergg;

    // Ask for the first integer
    printf(badlyNamedQuestionVariable);
    scanf("%d", &badlyNamedVariable1);
    smol = badlyNamedVariable1; // Set the variable smol to the first integer

    // Ask for the second integer
    printf(badlyNamedQuestionVariable);
    scanf("%d", &badlyNamedVariable2);

    /* START insertion sort */
    if (badlyNamedVariable2 <= smol) {
        meed = smol;
        smol = badlyNamedVariable2;
    } else {
        meed = badlyNamedVariable2;
    }
    /* END insertion sort */

    // ask for the third integer
    printf(badlyNamedQuestionVariable);
    scanf("%d", &badlyNamedVariable3);
    /* START insertion sort */
    if (badlyNamedVariable3 <= smol) {
        lergg = meed;
        meed = smol;
        smol = badlyNamedVariable3;
    } else if (badlyNamedVariable3 <= meed) {
        lergg = meed;
        meed = badlyNamedVariable3;
    } else {
        lergg = badlyNamedVariable3;
    }
    /* END insertion sort */

    printf("The integers in order are: %d %d %d\n", smol, meed, lergg);
    return 0;
}