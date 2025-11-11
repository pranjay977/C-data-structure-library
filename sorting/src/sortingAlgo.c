#include<sortingAlgo.h>
// Define comparator for all primitive types
// If the user want to perform sorting into a non primitive type
// then he have to write its own comparator

void swap(void **a,void **b)
{
void *g=*a;
*a=*b;
*b=g;
}
int IntComparator(void *a,void *b)
{
int *k=(int *)a;
int *g=(int *)b;
return *k<*g;
}
int CharComparator(void *a,void *b)
{
char *k=(char *)a;
char *g=(char *)b;
return *k<*g;
}
int DoubleComparator(void *a,void *b)
{
double *k=(double *)a;
double *g=(double *)b;
return *k<*g;
}
int LongComparator(void *a,void *b)
{
long *k=(long *)a;
long *g=(long *)b;
return *k<*g;
}
int FloatComparator(void *a,void *b)
{
float *k=(float *)a;
float *g=(float *)b;
return *k<*g;
}
int ShortComparator(void *a,void *b)
{
short *k=(short *)a;
short *g=(short *)b;
return *k<*g;
}


void gBubbleSort(void **arr,int size,int (*comparator)(void *,void *))
{
int i,j;
for(i=0;i<size;i++)
{
for(j=0;j<size-1;j++)
{
if(comparator(arr[j+1],arr[j])) swap(&arr[j+1],&arr[j]);
}
}
}

void Sort(int *a,int size,int (*comparator)(void *,void *))
{

}
