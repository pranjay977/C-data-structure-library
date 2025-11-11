#include<dll.h>
#include<stdlib.h>
DoublyLinkedList *createDoublyLinkedList(bool *success)
{
if(success) *success=false;
DoublyLinkedList *dll;
dll=(DoublyLinkedList *)malloc(sizeof(DoublyLinkedList));
if(dll==NULL) return NULL;
dll->start=NULL;
dll->end=NULL;
dll->size=0;
if(success) *success=true;
return dll;
}
void clearDoublyLinkedList(DoublyLinkedList *dll)
{
DoublyLinkedListNode *node;
if(dll==NULL) return;
node=dll->start;
while(dll->start!=NULL)
{
node=dll->start;
dll->start=dll->start->next;
free(node);
}
dll->size=0;
}
int getSizeOfDoublyLinkedList(DoublyLinkedList *dll)
{
if(dll==NULL) return 0;
return dll->size;
}
void destroyDoublyLinkedList(DoublyLinkedList *dll)
{
if(dll==NULL) return;
clearDoublyLinkedList(dll);
free(dll);
}
void addToDoublyLinkedList(DoublyLinkedList *dll,void *ptr,bool *success)
{
DoublyLinkedListNode *node;
if(success) *success=false;
if(dll==NULL) return;
node=(DoublyLinkedListNode *)malloc(sizeof(DoublyLinkedListNode));
if(node==NULL) return;
node->ptr=ptr;
node->next=NULL;
node->previous=NULL;
if(dll->start==NULL)
{
dll->start=node;
dll->end=node;
}
else
{
dll->end->next=node;
node->previous=dll->end;
dll->end=node;
}
dll->size++;
if(success) *success=true;
}
void insertIntoDoublyLinkedList(DoublyLinkedList *dll,int index,void *ptr,bool *success)
{
if(success) *success=false;
if(dll==NULL) return;
if(index<0 || index>dll->size) return;
if(index==dll->size)
{
addToDoublyLinkedList(dll,ptr,success);
return;
}
DoublyLinkedListNode *node;
node=(DoublyLinkedListNode *)malloc(sizeof(DoublyLinkedListNode));
if(node==NULL) return;
node->ptr=ptr;
node->next=NULL;
node->previous=NULL;
if(index==0)
{
node->next=dll->start;
dll->start->previous=node;
dll->start=node;
dll->size++;
if(success) *success=true;
return;
}
DoublyLinkedListNode *p1,*p2;
p1=dll->start;
int x=0;
while(x<index)
{
p2=p1;
p1=p1->next;
x++;
}
node->next=p1;
p1->previous=node;
node->previous=p2;
p2->next=node;
dll->size++;
if(success) *success=true;
}
void *removeFromDoublyLinkedList(DoublyLinkedList *dll,int index,bool *success)
{
void *ptr;
DoublyLinkedListNode *p1,*p2;
int x;
if(success) *success=false;
if(dll==NULL) return NULL;
if(index<0 || index>=dll->size) return NULL;
p1=dll->start;
x=0;
while(x<index)
{
p2=p1;
p1=p1->next;
x++;
}
ptr=p1->ptr;
if(dll->start==p1 && dll->end==p1)
{
dll->start=NULL;
dll->end=NULL;
}else if(dll->start==p1)
{
dll->start=dll->start->next;
dll->start->previous=NULL;
}else if(dll->end==p1)
{
dll->end=p2;
dll->end->next=NULL;
}
else
{
p2->next=p1->next;
p1->next->previous=p2;
}
free(p1);
dll->size--;
if(success) *success=true;
return ptr;
}
void appendToDoublyLinkedList(DoublyLinkedList *targetSll,DoublyLinkedList *sourceSll,bool *success)
{
if(targetSll==NULL || sourceSll==NULL) return;
targetSll->end->next=sourceSll->start;
sourceSll->start->previous=targetSll->end;
targetSll->size=targetSll->size+sourceSll->size;
return;
}
void *getFromDoublyLinkedList(DoublyLinkedList *dll,int index,bool *success)
{
void *ptr;
DoublyLinkedListNode *node;
int x;
if(success) *success=false;
if(dll==NULL) return NULL;
if(index<0 || index>=dll->size) return NULL;
node=dll->start;
x=0;
while(x<index)
{
node=node->next;
x++;
}
if(success) *success=true;
return node->ptr;
}

