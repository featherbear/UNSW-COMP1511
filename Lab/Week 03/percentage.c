//
// Created by Andrew on 13/03/2018.
//

// Generic code template
#include <stdio.h>

int main() {
    // Get the total marks
    int totalMarks;
    printf("Enter the total number of marks in the exam: ");
    scanf("%d", &totalMarks);

    // Get the scored marks
    double scoredMarks;
    printf("Enter the number of marks the student was awarded: ");
    scanf("%lf", &scoredMarks);

    // Show the percentage, as score*100 / total
    printf("The student scored %.0f%% in this exam.\n", scoredMarks * 100 / totalMarks);
}