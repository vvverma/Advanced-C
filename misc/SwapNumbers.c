/*
In this program we are going to swap the content of the variables without using temp variable

@author: Vishal Verma
*/
#include<stdio.h>

int main(void){
int val1,val2;
printf("Enter the first number: ");
scanf("%d",&val1);
printf("Enter the second number: ");
scanf("%d",&val2);
printf("val1:%d\t val2:%d\t\n",val1,val2);
val1 = val1+val2;
val2 = val1-val2;
val1 = val1-val2;
printf("After Swapping\n");
printf("val1:%d\t val2:%d\t\n",val1,val2);
return 0;
}
