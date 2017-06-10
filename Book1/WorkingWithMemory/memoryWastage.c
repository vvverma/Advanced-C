/*
*FileName: memoryWastage.c
*Author: Vishal Verma
*Purpose: This program demonstrates how memory is wasted during array initialization and decalration 
*         Change the value of MAX to 1000000 then the segmantation fault occurs.
*/

#include<stdio.h>
#define MAX  10000

int main(void){
long x;
char studentNames[MAX][1];


for(x=0 ; x<MAX;x++){
printf("StudentName %.5ld", x+1);
gets(studentNames[x]);
printf("%s\n",studentNames[x]);
if(studentNames[x][0]== '\0')
x=MAX;
}
printf("\n\nYou entered the following:\n");
//PRINT NAMES;
for( x=0 ; studentNames[x][0] !='\0' && x<MAX; x++){
printf("StudentName %.5ld", x+1);
printf("%s\n",studentNames[x]);
}

return 0;
}
