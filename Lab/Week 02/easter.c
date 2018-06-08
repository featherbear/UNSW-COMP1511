/*
  Write a program easter.c which allows the user to enter a year, then calculates the date of Easter Sunday for that year.
  Use the formula developed in 1876 by Samuel Butcher, Bishop of Meath.
*/


#include <stdio.h>

int main() {
    int year;
    printf("Enter Year: ");
    scanf("%d", &year);

    // hash tag copyright
    // Source: drupal.org/node/1180480
    // Literally just adapt the formula to C
    int a=year%19;
    int b=year/100;
    int c=year%100;
    int d=b/4;
    int e=b%4;
    int f=(b+8)/25;
    int g=(b-f+1)/3;
    int h=(19*a+b-d-g+15)%30;
    int i=c/4;
    int k=c%4;
    int l=(32+2*e+2*i-h-k)%7;
    int m=(a+11*h+22*l)/451;
    int MONTH_FROM1 =(h+l-7*m+114)/31;
    int p =(h+l-7*m+114)%31;
    int DATE_FROM1=p+1;


    // And then print out the output
    printf("Easter is %s %d in %d.\n", (MONTH_FROM1 == 3 ? "March" : "April"), DATE_FROM1, year);
    /*
     * (MONTH_FROM1 == 3 ? "March" : "April")
     * Ternary Condition! Following the syntax of < condition ? valueIfTrue : valueIfFalse >
     * If month number is 3, then it's March, otherwise it's April (Lazy way, because Easter is always either in March or April)
     *
     */
    return 0;
}
