#ifndef __$__STACK__
#define __$__STACK__ 1234
#include<sll.h>
typedef struct _$$__stack__
{
SinglyLinkedList *singlyLinkedList;
}Stack;
Stack *createStack(bool *success);
void pushOnStack(Stack *stack,void *ptr,bool *success);
void *popFromStack(Stack *stack,bool *success);
int getSizeOfStack(Stack *stack);
void *elementAtTopOfStack(Stack *stack,bool *success);
bool isStackEmpty(Stack *stack);
void clearStack(Stack *stack);
void destroyStack(Stack *stack);
#endif 
