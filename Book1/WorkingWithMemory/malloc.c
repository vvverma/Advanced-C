/*
*FileName: malloc.c
*Author: Vishal Verma
*Purpose: This program demonstrates how to dynamically allocate memmory using malloc() and freed using free();
*         _ _LINE_ _ preprocessor directive is a defined constant.
*        When the program is compiled, it is replaced with the current
*	line number. Another popular preprocessor directive is _ _FILE_ _.
*	This constant is replaced by the current source file’s name.
*
*	DO check the return value from malloc() to ensure that memory was allocated.
*	DO avoid using malloc() for allocating small amounts of memory. Each
*	memory allocation made with malloc() contains some overhead—typically 16 bytes or more.
*	DON’T forget to free allocated memory with the free() function. If you
*	don’t free the memory, and the pointer to it goes out of scope, the memory
*	will be unavailable during the execution of the rest of the program.
*
*/

#include<stdio.h>
#include<stdlib.h>


int main(void){
int *arrElements;
int arrNum = 0;


while(arrNum<1 || arrNum>200000000){
printf("Enter the number of elements if array: ");
scanf("%d",&arrNum);
}

arrElements = malloc(sizeof(int)*arrNum);
if(arrElements == NULL){
printf( "\nError in line %3.3d: Could not allocate memory.",__LINE__);
exit(1);
}
//printf( "\nError in line %3.3d: Could not allocate memory.",__LINE__);
printf("The total size of the array reserved is : %ld\n", sizeof(int)*arrNum);

//populate the array;

for(int i = 0 ; i<arrNum; i++){
*(arrElements+i )=rand()%100+1;  
}


//print the array
for(int i = 0 ; i<arrNum; i++){
printf("%d\t", *(arrElements+i));
}
printf("\n");

//free the memory which was allocated
free(arrElements);
return 0;
}
