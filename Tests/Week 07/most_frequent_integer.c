//
// Created by Andrew on 20/04/2018.
//

// Write a C program most_frequent_integer.c which reads integers from standard input until it reaches end-of-input.
// It should then print the most frequently occurring integer.
//
// If there is a tie for the most frequent integer, your program should print the largest integer that is tied for most frequent.

// You can assume the input will only only contain integers, one per line.

// You can assume each line will contain one and only one integer.
//
// You can assume your input contains at least one integer.
//
// You can assume your input contains no more than 100,000 integers.
//
// You are free to write this program in any way you wish: there is no specific function that you need to implement.
// Note that your program will need to have a `main` function.

#include <stdio.h>

int posOrNext(int needle, int haystack[]) {
    int i = 0;
    while (haystack[i] != 0) {
        if (haystack[i] == needle) return i;
        i++;
    }
    return i;
}

int main(void) {
    // https://stackoverflow.com/a/23509376
    int ints[100000] = {0};
    int intsC[100000] = {0};

    int v;
    while (scanf("%d", &v) != EOF) {
        int pos = posOrNext(v, ints);
        ints[pos] = v;
        intsC[pos]++;
    }

    int c = 0;

    int highestInt = -1;
    int highestC = -1;
    while (ints[c] != 0) {
        if (intsC[c] > highestC || (intsC[c] == highestC && ints[c] > highestInt)) {
            highestC = intsC[c];
            highestInt = ints[c];
        }
        c++;
    }
    printf("%d\n", highestInt);
}

