#include <stdio.h>
int main(){int i,I,l;char*j="Enter integer: ";printf(j);scanf("%d",&i);printf(j);scanf("%d",&I);printf(j);scanf("%d",&l);(l<I)&&(l+=I)&&(I=l-I)&&(l-=I);(I<i)&&(I+=i)&&(i=I-i)&&(I-=i);(l<I)&&(l+=I)&&(I=l-I)&&(l-=I);printf("The integers in order are: %d %d %d",i,I,l);}