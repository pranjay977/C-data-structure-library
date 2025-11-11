#ifndef __$__QUEUE__
#define __$__QUEUE__ 1234
#include<heap.h>
typedef struct _$$__pqueue__
{
Heap *heap;
}PQueue;
PQueue *createPQueue(bool *success,int  (*comparator)(void *,void *));
void addToPQueue(PQueue *pqueue,void *ptr,bool *success);
void *removeFromPQueue(PQueue *pqueue,bool *success);
int getSizeOfPQueue(PQueue *pqueue);
void *elementAtTopOfPQueue(PQueue *pqueue,bool *success);
bool isPQueueEmpty(PQueue *pqueue);
void clearPQueue(PQueue *pqueue);
void destroyPQueue(PQueue *pqueue);
#endif 
