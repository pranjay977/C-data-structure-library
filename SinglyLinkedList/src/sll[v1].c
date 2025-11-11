#include<sll.h>
#include<stdlib.h>
SinglyLinkedList *createSinglyLinkedList(bool *success)
{
if(success) *success=false;
SinglyLinkedList *sll;
sll=(SinglyLinkedList *)malloc(sizeof(SinglyLinkedList));
if(sll==NULL) return NULL;
sll->start=NULL;
sll->end=NULL;
sll->size=0;
if(success) *success=true;
return sll;
}
void clearSinglyLinkedList(SinglyLinkedList *sll)
{
SinglyLinkedListNode *node;
if(sll==NULL) return;
node=sll->start;
while(sll->start!=NULL)
{
node=sll->start;
sll->start=sll->start->next;
free(node);
}
sll->size=0;
}
int getSizeOfSinglyLinkedList(SinglyLinkedList *sll)
{
if(sll==NULL) return 0;
return sll->size;
}
void destroySinglyLinkedList(SinglyLinkedList *sll)
{
if(sll==NULL) return;
clearSinglyLinkedList(sll);
free(sll);
}
void addToSinglyLinkedList(SinglyLinkedList *sll,void *ptr,bool *success)
{
SinglyLinkedListNode *node;
if(success) *success=false;
if(sll==NULL) return;
node=(SinglyLinkedListNode *)malloc(sizeof(SinglyLinkedListNode));
if(node==NULL) return;
node->ptr=ptr;
node->next=NULL;
if(sll->start==NULL)
{
sll->start=node;
sll->end=node;
}
else
{
sll->end->next=node;
sll->end=node;
}
sll->size++;
if(success) *success=true;
}
void insertIntoSinglyLinkedList(SinglyLinkedList *sll,int index,void *ptr,bool *success)
{
if(success) *success=false;
if(sll==NULL) return;
if(index<0 || index>sll->size) return;
if(index==sll->size)
{
addToSinglyLinkedList(sll,ptr,success);
return;
}
SinglyLinkedListNode *node;
node=(SinglyLinkedListNode *)malloc(sizeof(SinglyLinkedListNode));
if(node==NULL) return;
node->ptr=ptr;
node->next=NULL;
if(index==0)
{
node->next=sll->start;
sll->start=node;
sll->size++;
if(success) *success=true;
return;
}
SinglyLinkedListNode *p1,*p2;
p1=sll->start;
int x=0;
while(x<index)
{
p2=p1;
p1=p1->next;
x++;
}
node->next=p1;
p2->next=node;
sll->size++;
if(success) *success=true;
}
void *removeFromSinglyLinkedList(SinglyLinkedList *sll,int index,bool *success)
{
void *ptr;
SinglyLinkedListNode *p1,*p2;
int x;
if(success) *success=false;
if(sll==NULL) return NULL;
if(index<0 || index>=sll->size) return NULL;
p1=sll->start;
x=0;
while(x<index)
{
p2=p1;
p1=p1->next;
x++;
}
ptr=p1->ptr;
if(sll->start==p1 && sll->end==p1)
{
sll->start=NULL;
sll->end=NULL;
}else if(sll->start==p1)
{
sll->start=sll->start->next;
}else if(sll->end==p1)
{
sll->end=p2;
sll->end->next=NULL;
}
else
{
p2->next=p1->next;
}
free(p1);
sll->size--;
if(success) *success=true;
return ptr;
}
void appendToSinglyLinkedList(SinglyLinkedList *targetSll,SinglyLinkedList *sourceSll,bool *success)
{
if(targetSll==NULL || sourceSll==NULL) return;
targetSll->end->next=sourceSll->start;
return;
}
void *getFromSinglyLinkedList(SinglyLinkedList *sll,int index,bool *success)
{
void *ptr;
SinglyLinkedListNode *node;
int x;
if(success) *success=false;
if(sll==NULL) return NULL;
if(index<0 || index>=sll->size) return NULL;
node=sll->start;
x=0;
while(x<index)
{
node=node->next;
x++;
}
if(success) *success=true;
return node->ptr;
}

