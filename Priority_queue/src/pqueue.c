#include<pqueue.h>
#include<stdio.h>
#include<stdlib.h>
PQueue *createPQueue(bool *success,int  (*comparator)(void *,void *))
{
if(success) *success=false;
PQueue *pqueue;
Heap *heap;
bool succ;
heap=createHeap(&succ,comparator);
if(succ==false) return NULL;
pqueue=(PQueue *)malloc(sizeof(PQueue));
if(pqueue==NULL)
{
destroyHeap(heap,&succ);
return pqueue;
}
pqueue->heap=heap;
if(success) *success=true;
return pqueue;
}

void addToPQueue(PQueue *pqueue,void *ptr,bool *success)
{
bool succ;
if(success) *success=false;
if(pqueue==NULL || pqueue->heap==NULL) return ;
addToHeap(pqueue->heap,ptr,&succ);
if(succ==false) return;
if(success) *success=true;
return;
}
void *removeFromPQueue(PQueue *pqueue,bool *success)
{
void *ptr;
bool succ;
if(success) *success=false;
if(isPQueueEmpty(pqueue)) return NULL;
ptr=removeFromHeap(pqueue->heap,&succ);
if(succ==false) return NULL;
if(success) *success=true;
return ptr;
}
int getSizeOfPQueue(PQueue *pqueue)
{
if(pqueue==NULL || pqueue->heap==NULL) return 0;
return getSizeOfHeap(pqueue->heap);
}
void *elementAtTopOfPQueue(PQueue *pqueue,bool *success)
{
void *ptr;
if(success) *success=false;
bool succ;
if(isPQueueEmpty(pqueue)) return NULL;
ptr=elementAtTopOfHeap(pqueue->heap,&succ);
if(success) *success=false;
return ptr;
}
bool isPQueueEmpty(PQueue *pqueue)
{
if(pqueue==NULL) return true;
if(pqueue->heap==NULL) return true;
if(getSizeOfHeap(pqueue->heap)==0) return true;
return false;
}
void clearPQueue(PQueue *pqueue)
{
if(pqueue==NULL) return;
if(pqueue->heap==NULL) return;
destroyPQueue(pqueue);
}
void destroyPQueue(PQueue *pqueue)
{
if(pqueue==NULL) return;
if(pqueue->heap==NULL) return;
bool succ;
destroyHeap(pqueue->heap,&succ);
free(pqueue);
}
