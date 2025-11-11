#include<stdio.h>
#include<sll.h>
#include<sllIt.h>
SinglyLinkedListIterator getSinglyLinkedListIterator(SinglyLinkedList *sll,bool *success)
{
SinglyLinkedListIterator sllIt;
if(success) *success=false;
if(sll==NULL) return sllIt;
if(sll->start==NULL)
{
if(success) *success=true;
return sllIt;
}
if(success) *success=true;
sllIt.node=sll->start;
return sllIt;
}
bool hasNextInSinglyLinkedList(SinglyLinkedListIterator *sllIt)
{
if(sllIt==NULL) return false;
if(sllIt->node==NULL) return false;
return true;
}
void *getNextElementFromSinglyLinkedList(SinglyLinkedListIterator *sllIt,bool *success)
{
void *ptr=NULL;
if(success) *success=false;
if(sllIt==NULL || sllIt->node==NULL) return ptr;
ptr=sllIt->node->ptr;
sllIt->node=sllIt->node->next;
if(success) *success=true;
return ptr;
}
