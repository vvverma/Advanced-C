/*
*FileName: variablesizes.c
*Author: Vishal Verma
*Purpose: This program is used to check the memory used by each datatype in C language
*         Datatype -- char,int,float,long,short, double, struct 
*         New FUnction learnt -- sizeof();
*/

#include<stdio.h>

int main(void){


char *ptrChar;
int  *ptrInt;
short *ptrShort;
long  *ptrLong;
float *ptrFloat;
double *ptrDouble;

struct testTag{
	char a;
	int  b;
}test;


printf("DataType\tSizes\n");
printf("================\n");
printf("Character\t %ld \n",sizeof(char));
printf("Integer\t %ld \n",sizeof(int));
printf("Short\t%ld\n",sizeof(short));
printf("Long\t%ld\n",sizeof(long));
printf("Float\t%ld\n",sizeof(float));
printf("Double\t%ld\n",sizeof(double));
printf("Char ptr\t%ld\n",sizeof(ptrChar));
printf("Integer ptr\t%ld\n",sizeof(ptrInt));
printf("Short ptr\t%ld\n",sizeof(ptrShort));
printf("Long ptr\t%ld\n",sizeof(ptrLong));
printf("Float ptr\t%ld\n",sizeof(ptrFloat));
printf("Double ptr\t%ld\n",sizeof(ptrDouble));
printf("Structure \t%ld\n",sizeof(test));

return 0;
}

