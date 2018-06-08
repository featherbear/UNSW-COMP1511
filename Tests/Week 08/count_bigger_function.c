//
// Created by Andrew on 29/04/2018.
//

// Write a C function which returns the number of values in the array which are larger than 99, or smaller than -99.

// Your function should return a single integer.
// Your function should not change the array it is given.
//
// Your function should not call scanf (or getchar or fgets).
//
// You can assume the array contains at least one integer.
//
// Your function should not print anything. It should not call printf.
//
// Your submitted file may contain a main function. It will not be tested or marked.

int count_bigger(int length, int array[length]);

int count_bigger(int length, int array[length]) {
    int count = 0;
    int i = 0;

    while (i < length) {
        if (array[i] < -99 || 99 < array[i]) {
            count++;
        }
        i++;
    }

    return count;
}