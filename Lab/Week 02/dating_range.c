/*

A popular rule for dating is that you should not date anyone younger than half your age + 7. COMP1511 does not endorse this rule and is not responsible if it leads to you having a bad date.
Write a C program dating_range.c that reads a person's age and calculates the upper and lower age limits of people they should date according to this rule.

Hint: you'll need to use symmetry to calculate the upper bound.

Hint: you only need to use the int type.

*/

#include <stdio.h>

int main() {

    // Get the person's age
    int age;
    printf("Enter your age: ");
    scanf("%d", &age);

    // Get the lower age limit
    int lb = age / 2 + 7;

    // If the lower limit is larger than your actual age, then... yeah... uhm... you're abit young
    // For example, if you're six years old. 6 / 2 + 7 = 10... six year old dating a ten year old??!?!?!
    if (age < lb) {
      printf("You are too young to be dating.\n");
      return -1;
    }

    // Then get the upper age limit
    int ub = (age - 7) * 2;

    printf("Your dating range is %d to %d years old.\n", lb, ub);
    
    return 0;
}
