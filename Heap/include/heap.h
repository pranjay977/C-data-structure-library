#ifndef __HEAP__$__
#define __HEAP__$__ 3432
#include<array.h>
typedef struct _heap
{
Array *array;
int (*comparator)(void *,void *);
int size;
}Heap;
Heap *createHeap(int *succ,int  (*comparator)(void *,void *));
void addToHeap(Heap *heap,void *elem,int *succ);
void *removeFromHeap(Heap *heap,int *succ);
void *elementAtTopOfHeap(Heap *heap,int *succ);
int getSizeOfHeap(Heap *heap);
void destroyHeap(Heap *heap,int *succ);
void updateElementInHeap(Heap *heap,int index,void *elem,int *succ);
#endif

