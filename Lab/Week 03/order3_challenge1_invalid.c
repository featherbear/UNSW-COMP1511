// But violates the rule: You can use printf to print the value of an expression, in other words you can have an expression inside printf.

/*
// Code golf :)
#include <stdio.h>
int main(){int _,i,l;char* j="Enter integer: ";printf(j);scanf("%d",&_);printf(j);scanf("%d",&i);printf(j);scanf("%d",&l);printf("The integers in order are: ");(_<=i&&_<=l&&printf("%d",_))||(i<=_&&i<=l&&printf("%d",i))||(l<=_&&l<=i&&printf("%d",l));printf(" ");(i<=_&&_<=l&&printf("%d",_))||(l<=_&&_<=i&&printf("%d",_))||(_<=i&&i<=l&&printf("%d",i))||(i<=_&&l<=i&&printf("%d",i))||(_<=l&&l<=i&&printf("%d",l))||(i<=l&&l<=_&&printf("%d",l));printf(" ");(_>=i&&_>=l&&printf("%d",_))||(i>=_&&i>=l&&printf("%d",i))||(l>=_&&l>=i&&printf("%d",l));printf("\n");}
*/

#define badlyNamedQuestionVariable "Enter integer: " // We got lazy.

#include <stdio.h> // Include the library that contains the `printf` and `scanf` functions

int main() {
    // Define our variables, badly... :)
    int badlyNamedVariable1;
    int badlyNamedVariable2;
    int badlyNamedVariable3;

    // Ask for the three integers
    printf(badlyNamedQuestionVariable);
    scanf("%d", &badlyNamedVariable1);
    printf(badlyNamedQuestionVariable);
    scanf("%d", &badlyNamedVariable2);
    printf(badlyNamedQuestionVariable);
    scanf("%d", &badlyNamedVariable3);

    printf("The integers in order are: "); // Note that we don't put in '\n', because we don't want a new line

    /* first value */

    // cases for i: i <= j, and i <= k
    (badlyNamedVariable1 <= badlyNamedVariable2 && badlyNamedVariable1 <= badlyNamedVariable3 && printf("%d", badlyNamedVariable1)) ||
    (badlyNamedVariable2 <= badlyNamedVariable1 && badlyNamedVariable2 <= badlyNamedVariable3 && printf("%d", badlyNamedVariable2)) ||
    (badlyNamedVariable3 <= badlyNamedVariable1 && badlyNamedVariable3 <= badlyNamedVariable2 && printf("%d", badlyNamedVariable3));

    printf(" ");
    /* second value */

    // cases for j: i <= j <= k
    (badlyNamedVariable2 <= badlyNamedVariable1 && badlyNamedVariable1 <= badlyNamedVariable3 && printf("%d", badlyNamedVariable1)) || // b <= a <= c
    (badlyNamedVariable3 <= badlyNamedVariable1 && badlyNamedVariable1 <= badlyNamedVariable2 && printf("%d", badlyNamedVariable1)) || // c <= a <= b

    (badlyNamedVariable1 <= badlyNamedVariable2 && badlyNamedVariable2 <= badlyNamedVariable3 && printf("%d", badlyNamedVariable2)) || // a <= b <= c
    (badlyNamedVariable2 <= badlyNamedVariable1 && badlyNamedVariable3 <= badlyNamedVariable2 && printf("%d", badlyNamedVariable2)) || // c <= b <= a

    (badlyNamedVariable1 <= badlyNamedVariable3 && badlyNamedVariable3 <= badlyNamedVariable2 && printf("%d", badlyNamedVariable3)) || // a <= c <= b
    (badlyNamedVariable2 <= badlyNamedVariable3 && badlyNamedVariable3 <= badlyNamedVariable1 && printf("%d", badlyNamedVariable3)); // b <= c <= a


    printf(" ");
    /* third value */

    // cases for k: k >= j, and k => i
    (badlyNamedVariable1 >= badlyNamedVariable2 && badlyNamedVariable1 >= badlyNamedVariable3 && printf("%d", badlyNamedVariable1)) ||
    (badlyNamedVariable2 >= badlyNamedVariable1 && badlyNamedVariable2 >= badlyNamedVariable3 && printf("%d", badlyNamedVariable2)) ||
    (badlyNamedVariable3 >= badlyNamedVariable1 && badlyNamedVariable3 >= badlyNamedVariable2 && printf("%d", badlyNamedVariable3));

    printf("\n");
    return 0;

    /*
     * = What's going on???!??! =
     *  Recall how the `if` code structure works...
     *      if (condition1) {
     *         do stuff ...
     *      }
     * In order to 'do stuff', `condition1` must be evaluated to true...
     *
     * What if we had two conditions???
     *      if (condition1 && condition2) {
     *           do stuff ...
     *      }
     * This time, both `condition1` and `condition2` must both be evaluated to true...
     *
     * How about this?
     *      int returnTrue() {
     *          return 1;
     *      }
     *      if (condition1 && returnTrue()) {
     *          do stuff ...
     *      }
     * To 'do stuff', `condition1` and the value of `returnTrue()` must both be evaluated to true...
     *
     *
     * What if `condition1` was evaluated to be false?
     * The program won't bother to check what `returnTrue()` is, since both conditions need to be true,
     * (and the first condition was already found to be false)
     *
     *
     * In case you missed it, we just executed a function that is dependent on the previous condition.
     * We just cheated an `if` statement!
     *
     * condition && doSomething(); // doSomething() will occur if `condition` is true
     * ... and that's the same thing as:
     *   if (condition) {
     *      doSomething();
     *   }
     *
     *
     * Wait, wth?
     *
     * if (cond1 && cond2 && cond3) { doStuff(); }
     *    is the same thing as...
     * cond1 && cond2 && cond3 && doStuff();
     *
     * What?
     *    if `cond1` is true...
     *      if `cond2` is true...
     *        if `cond3` is true...
     *          if doStuff() is true...
     * Note that, though `doStuff()` is probably not going to be true, we've still executed it!
     */
}