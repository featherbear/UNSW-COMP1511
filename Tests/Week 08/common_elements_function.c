//
// Created by Andrew on 29/04/2018.
//

// Write a C function that finds common elements between two arrays,and copies all of the values
// in the first source array which are also found in the second source array, into a third array.

// In other words, all of the elements that appear in both of the source arrays should be
// copied to the third destination array, in the order that they appear in the first array.


// You can assume the two source arrays contain only positive integers.
// You can assume that all three arrays are the same size (length) and length is > 0.
//
// You cannot assume anything about the number of common elements, i.e. there may not be any common elements between both arrays, or conversely, the entire contents of the first array may also be present in the second array.
//
// Your function should return a single integer.
//
// Your function should not change the array it is given.
//
// Your function should not call scanf (or getchar or fgets).
//
// Your function should not print anything. It should not call printf.
//
// Your submitted file may contain a main function. It will not be tested or marked.
//

int common_elements(int length, int source1[length], int source2[length], int destination[length]);

int isInArray(int needle, int *haystack, int haystackLength);


// Check if an integer is in an array
int isInArray(int needle, int *haystack, int haystackLength) {
    int i = 0;
    while (i < haystackLength) {
        if (haystack[i] == needle) { return 1; }
        i++;
    }
    return 0;
}

// Core
int common_elements(int length, int source1[length], int source2[length], int destination[length]) {
    int k = 0;
    int i = 0;

    while (i < length) {
        if (isInArray(source1[i], source2, length)) {
            destination[k] = source1[i];
            k++;
        }
        i++;
    }

    return k;

}