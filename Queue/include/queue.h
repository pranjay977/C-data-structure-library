#ifndef __$__QUEUE__
#define __$__QUEUE__ 1234
#include<sll.h>
typedef struct _$$__queue__
{
SinglyLinkedList *singlyLinkedList;
}Queue;
Queue *createQueue(bool *success);
void addToQueue(Queue *queue,void *ptr,bool *success);
void *removeFromQueue(Queue *queue,bool *success);
int getSizeOfQueue(Queue *queue);
void *elementAtTopOfQueue(Queue *queue,bool *success);
bool isQueueEmpty(Queue *queue);
void clearQueue(Queue *queue);
void destroyQueue(Queue *queue);
#endif 
