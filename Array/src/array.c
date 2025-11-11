#include<array.h>
#include<stdio.h> 
Array *createArray(int *succ)
{
if(succ) *succ=false;
Array *arr=(Array *)malloc(sizeof(Array));
arr->x=NULL;
arr->rows=0;
arr->size=0;
if(succ) *succ=true;
return arr;
}
void *getElementFromArray(Array *array,int index)
{
if(index<0 || index>=array->size) return NULL;
int rowIndex,columnIndex,sp,ep,i;
rowIndex=index/10;
if(rowIndex>=array->rows) return NULL;
if(array->x[rowIndex]==NULL) return NULL;
columnIndex=index%10;
return array->x[rowIndex][columnIndex];
}

void setElementIntoArray(Array *array,int index,void *elem)
{
if(index<0) return;
int rowIndex,columnIndex,sp,ep,i;
rowIndex=index/10;
columnIndex=index%10;
void ***tmp;
if(rowIndex>=array->rows)
{
void ***tmp = (void ***)calloc(rowIndex + 1, sizeof(void **));
for (int i = 0; i < array->rows; i++) tmp[i] = array->x[i];
free(array->x);
array->x = tmp;
array->rows = rowIndex + 1;
}
if(array->x[rowIndex]==NULL)
{
array->x[rowIndex]=(void **)calloc(10,sizeof(void *));
}
array->x[rowIndex][columnIndex]=elem;
if(index>=array->size) array->size=index+1;
}
int getSizeOfArray(Array *array)
{
return array->size;
}
void destroyArray(Array *array,bool *success)
{
if(array==NULL) return;
if(success) *success=false;
int i;
for(i=0;i<array->rows;i++) free(array->x[i]);
free(array->x);
if(success) *success=true;
return;
}
