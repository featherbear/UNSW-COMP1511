#include <stdio.h>
int main(void) {
  int i1, i2;
  scanf("%d %d", &i1, &i2);
  if (i1 == i2) {
    printf("equal");
  } else {
    printf("%d", i1 > i2 ? i1 - i2 : i2 - i1);  
  }
  printf("\n");
  return 0;
}