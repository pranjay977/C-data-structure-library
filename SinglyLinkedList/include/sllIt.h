#ifndef __SLL_ITERATOR_
#define __SLL_ITERATOR_ 124
#include<sll.h>
typedef struct __$_sll_iterator
{
SinglyLinkedListNode *node;
}SinglyLinkedListIterator;
SinglyLinkedListIterator getSinglyLinkedListIterator(SinglyLinkedList *sll,bool *success);
bool hasNextInSinglyLinkedList(SinglyLinkedListIterator *sllIt);
void *getNextElementFromSinglyLinkedList(SinglyLinkedListIterator *sllIt,bool *success);
#endif