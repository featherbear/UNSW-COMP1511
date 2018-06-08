//
// Created by Andrew on 20/04/2018.
//

// Write a C function that removes duplicate elements from an array,
// by copying the non-duplicate values to a second array
// i.e. only the first occurrence of any value should be copied.

// You can assume the source array only contains positive integers.
// You can assume the source array contains at least one integer.
//
// You can assume that the destination array will always be large enough to fit all of the copied values.
//
// You cannot assume anything about the number of duplicates,
// i.e. there may not be any duplicates, or conversely, the entire array may be duplicates.
//
// Your function should return a single integer.
//
// Your function should not change the array it is given.
//
// Your function should not call scanf (or getchar or fgets).
//
// Your function should not print anything. It should not call printf.
//
// Your submitted file may contain a main function. It will not be tested or marked. tested or marked.

// Function prototypes
int remove_duplicates(int length, int source[length], int destination[length]);
int intInArray(int length, int needle, int haystack[]);


// Check if an integer (needle) is in an array (haystack)
int intInArray(int length, int needle, int haystack[]) {
    int i = 0;
    while (i < length) {
        // If we found a matching needle in the haystack, return TRUE (aka 1)
        if (haystack[i] == needle) return 1;
        i++;
    }

    // No matches, return FALSE (aka 0)
    return 0;

}

int remove_duplicates(int length, int source[length], int destination[length]) {
    int i = 0; // Iterator
    int j = 0; // Unique counter
    while (i < length) {
        if (!intInArray(length, source[i], destination)) {
            destination[j] = source[i];
            j++;
        }
        i++;
    }
    return j;

}