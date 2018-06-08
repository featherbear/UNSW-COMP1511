/*

Write a program called decimal_spiral.c that reads an integer n from standard input
and prints an nxn pattern of decimal digits and dashes in the shape of a spiral.
You can assume n is odd and >= 5.

You are only permitted to use C language features covered in weeks 1-3 lectures.
// In particular, you are not permitted to use array(s).

*/

/*
./decimal_spiral
Enter size: 5
65432
----1
210-0
3---9
45678

5 + 4 + 4 + 2 + 2

./decimal_spiral
Enter size: 7
0987654
------3
87654-2
9---3-1
0-012-0
1-----9
2345678

7 + 6 + 6 + 4 + 4 + 2 + 2

./decimal_spiral
Enter size: 9
876543210
--------9
8765432-8
9-----1-7
0-210-0-6
1-3---9-5
2-45678-4
3-------3
456789012

9 + 8 + 8 + 6 + 6 + 4 + 4 + 2 + 2

./decimal_spiral
Enter size: 15
654321098765432
--------------1
2109876543210-0
3-----------9-9
4-210987654-8-8
5-3-------3-7-7
6-4-87654-2-6-6
7-5-9---3-1-5-5
8-6-0-012-0-4-4
9-7-1-----9-3-3
0-8-2345678-2-2
1-9---------1-1
2-01234567890-0
3-------------9
456789012345678

 */

#include <stdio.h>
int getNumber(int x, int y, int size, int sum);

int sumSize(int size);

int main() {

    int size;
    printf("Enter size: ");
    scanf("%d", &size);

    if (size % 2 == 0 || size < 5) return -1;

    int sum = sumSize(size);
    // printf("Sum: %d\n", sum);

    int midpoint = size / 2;

    int cursorY = 0;
    while (cursorY < size) {
        int cursorX = 0;
        while (cursorX < size) {
            int flag = 0; // Instead of going (A&&B&&C)||(B&&C&&(D||(E&&F&&G||(B+C<A+B-fizzbuzz))) we'll use a flag.

            if (cursorY % 2 == 0) {
                if (cursorY < midpoint && cursorX >= cursorY && cursorX < size - cursorY) {
                    // Top triangle
                    flag = 1;
                } else if (cursorY > midpoint && cursorX <= cursorY && cursorX >= size - cursorY) {
                    // Bottom triangle
                    flag = 1;
                }
            }

            if (cursorX % 2 == 0) {
                if (cursorX > midpoint && cursorY <= cursorX && cursorX >= size - cursorY) {
                    // Right triangle
                    flag = 1;
                } else if (cursorX <= midpoint && cursorY > cursorX + 1 && cursorX < size - cursorY) {
                    // Left triangle. Notice our second condition `cursorY > cursorX PLUS ONE`, which prevents the box
                    // from forming a square
                    flag = 1;
                }
            }
            if (cursorX % 2 && cursorY == cursorX + 1) {
                // Handle the joining pieces
                flag = 1;
            }

            // The centre flag alternates every second odd cycle.
            // size | 5 | 7 | 9 | 11 | 13 |
            // -----|---|---|---|----|----|
            // s%4  | 1 | 3 | 1 | 3  | 1  |
            // -----|---|---|---|----|----|
            // flag | y | n | y | n  | y  |

            if (size % 4 == 1 && cursorY == cursorX && cursorY == size / 2) { flag = 1; }


            if (flag) { printf("%d", getNumber(cursorX, cursorY, size, sum)); }
            else { printf("-"); }

            cursorX++;
        }
        printf("\n");
        cursorY++;
    }
    return 0;
}

// Keeping old (not working) code just because it looks somewhat interesting
/*
int getNumber(int x, int y, int size, int sum) {
    // Idea 1, this implementation failed. Keeping it though because it looks nice? ish.

    int midpoint = size / 2;
    if (size % 4 == 1) {
        if (x == midpoint && y == midpoint) return 0;

    } else if (size % 4 == 3) {
        if (x == midpoint - 1 && y == midpoint + 1) return 0;
        // zero at (midpoint-1, midpoint+1)
    }

    // if (x==0 && y == 0) return (sum-1) % 10;
    if (y == 0) return (sum - x - 1) % 10;

    if (x == size - 1) return (sum - size - y) % 10;                // - y
    if (y == size - 1) return (sum - 2 * size - 7 + x) % 10;        // + x

    if (x == 0) return (sum - 2 * size + 3 + x + y    + 2) % 10;           // + x + y
    if (y == 2) return (sum - 2 * size + 3 - x + y    + 2) % 10;           // - x + y

    if (x == size - 3) return (sum - 2 * size + 7 - x - y  + 2) % 10;    // - x - x
    if (y == size - 3) return (sum - 2 * size + 3 + x - y  + 4) % 10;    // + x - y
    if (x == 2) return (sum - 2 * size - 1 + x + y         - 4) % 10;           // + x + y
    if (y == 4) return (sum - 2 * size - 7 - x + y         + 6) % 10;           // - x + y

    if (x == size - 5) return (sum - 2 * size - 9 - x - y) % 10;    // - x - y
    if (y == size - 5) return (sum - 2 * size - 9 + x - y) % 10;    // + x - y
    if (x == 4) return (sum - 2 * size - 9 + x + y) % 10;          // + x + y
    if (y == 6) return (sum - 2 * size - 11 - x + y) % 10;         // - x + y

    if (x == size - 7) return (sum - 2 * size - 9 - x - y) % 10;    // - x - y
    return -1;

}
*/

int getNumber(int targetX, int targetY, int size, int sum) {
    // Step through with a while loop
    // keep going until we hit a return..?

    // Hello over-the-top looping!


//    printf("getNumber function called with args %d,%d,%d,%d\n", targetX, targetY, size, sum);
    int counter = 0;
    int cursorY = 0;
    int cursorX = 0;

    int turns = 0;
    int pad = 0;

    /*
     * = turns % 4 =
     * 0 - right
     * 1 - down
     * 2 - left
     * 3 - up
     */

    while (cursorX != targetX || cursorY != targetY) {
        int direction = turns % 4;

        if (direction == 0) {
            // Move the cursor right until we reach the boundary
            cursorX++;
            if (cursorX == size - pad - 1) {
                turns++;
            }
        } else if (direction == 1) {
            // Move the cursor down until we reach the boundary
            cursorY++;
            if (cursorY == size - pad - 1) {
                turns++;
            }
        } else if (direction == 2) {
            // Move the cursor left until we reach the boundary
            cursorX--;
            if (cursorX == pad) {
                turns++;
                pad += 2;
            }
        } else if (direction == 3) {
            // Move the cursor up until we reach the boundary
            cursorY--;
            if (cursorY == pad) {
                turns++;
            }
        }
        counter++;
    }

    // printf("Found co-ordinates %d,%d with total counter = %d\n\n", cursorX, cursorY, counter);
    return (sum - counter - 1) % 10; // Grab the last digit of the number only
}

int sumSize(int size) {
    // To find the number of asterisks, all of the spirals follow the pattern
    // Where n is an odd number... sum = n + n-1 + n-1 + n-3 + n-3 + n-5 + n-5 + ... + n-x + n-x ... where n-x == 2
    // For example if the size was 5: sum = 5 + 4 + 4 + 2 + 2 = 17
    // For example if the size was 7: sum = 7 + 6 + 6 + 4 + 4 + 2 + 2 = 31
    // For example if the size was 9: sum = 9 + 8 + 8 + 6 + 6 + 4 + 4 + 2 + 2 = 49

    int sum = size;
    size -= 1;
    while (size > 0) {
        sum += 2 * size;
        size -= 2;
    }
    return sum;
}