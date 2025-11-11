#ifndef __SLL_H 
#define __SLL_H 1234
#include<common.h>
#include<stdlib.h>
#include<stdio.h>
typedef struct _sll_$__s
{
void *ptr;
struct _sll_$__s  *next;
}SinglyLinkedListNode;
typedef struct _sll_$__ss
{
struct _sll_$__s  *start;
struct _sll_$__s  *end;
int size;
}SinglyLinkedList;
SinglyLinkedList *createSinglyLinkedList(bool *success);
int getSizeOfSinglyLinkedList(SinglyLinkedList *singlyLinkedList);
void destroySinglyLinkedList(SinglyLinkedList *singlyLinkedList);
void addToSinglyLinkedList(SinglyLinkedList *singlyLinkedList,void *ptr,bool *success);
void insertIntoSinglyLinkedList(SinglyLinkedList *singlyLinkedList,int index,void *ptr,bool *success);
void *removeFromSinglyLinkedList(SinglyLinkedList *singlyLinkedList,int index,bool *success);
void clearSinglyLinkedList(SinglyLinkedList *singlyLinkedList);
void appendToSinglyLinkedList(SinglyLinkedList *targetSinglyLinkedList,SinglyLinkedList *sourceSinglyLinkedList,bool *success);
void *getFromSinglyLinkedList(SinglyLinkedList *singlyLinkedList,int index,bool *success);
#endif