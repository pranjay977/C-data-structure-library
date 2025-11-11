#ifndef __ARRAY__$_
#define __ARRAY__$_ 3223
#include<stdlib.h>
#include<common.h>
typedef struct __array
{
void  ***x;
int rows;
int size;
}Array;
Array *createArray(bool *succ);
void *getElementFromArray(Array *array,int index);
void setElementIntoArray(Array *array,int index,void *elem);
int getSizeOfArray(Array *array);
void destroyArray(Array *array,bool *succ);
#endif

