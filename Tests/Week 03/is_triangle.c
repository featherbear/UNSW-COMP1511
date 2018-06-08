#include <stdio.h>
int main(void) {
  float s1, s2, s3;
  printf("Please enter three numbers: ");
  scanf("%f %f %f", &s1, &s2, &s3);
  
  printf("%striangle\n", (s1+s2<=s3||s1+s3<=s2||s2+s3<=s1)? "not a " : "");
  return 0;
}