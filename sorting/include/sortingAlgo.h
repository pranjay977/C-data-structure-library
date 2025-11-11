#ifndef __SORTING__ 
#define __SORTING__ 43


void swap(void **a,void **b);
int IntComparator(void *a,void *b);
int CharComparator(void *a,void *b);
int DoubleComparator(void *a,void *b);
int FloatComparator(void *a,void *b);
int StringComparator(void *a,void *b);
int LongComparator(void *a,void *b);
int ShortComparator(void *a,void *b);
int CharComparator(void *a,void *b);
void Sort(int *a,int size,int (*comparator)(void *,void *));
void Sort(char*a,int size,int (*comparator)(void *,void *));
void Sort(double *a,int size,int (*comparator)(void *,void *));
void Sort(long *a,int size,int (*comparator)(void *,void *));
void Sort(short *a,int size,int (*comparator)(void *,void *));





void gBubbleSort(void **arr,int size,int (*comparator)(void *,void *));
#endif