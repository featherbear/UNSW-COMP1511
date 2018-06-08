/*
 Matilda wants to buy some ice-cream, but she only has $10.
 Write a program so that she can input how many scoops of ice-cream she wants
 and how much each scoop costs and it will let her know if she has enough money.
*/

#include <stdio.h> // Get access to the `printf` and `scanf` functions

int main() {
    // Ask the person how many scoops they want, assume scoops are whole numbers.
    int num_scoops;
    printf("How many scoops? ");
    scanf("%i", &num_scoops);

    // Ask the person how much each scoop costs, assume that scoops are currency, and therefore have decimal places.
    double cost_scoops;
    printf("How many dollars does each scoop cost? ");
    scanf("%lf", &cost_scoops);

    // If the product of the two values is less than or equal to ten (the amount they have), then the person can buy!
    // Otherwise, rip.
    printf(num_scoops * cost_scoops <= 10 ? "You have enough money!" : "Oh no, you don't have enough money :(");
    printf("\n");
}
