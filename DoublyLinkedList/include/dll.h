#ifndef __DLL_H 
#define __DLL_H 1234
#include<stdlib.h>
#include<stdio.h>
#define bool int
#define True 1
#define true 1
#define TRUE 1
#define False 0
#define false 0
#define FALSE 0
typedef struct _DLL_$__s
{
void *ptr;
struct _DLL_$__s *next;
struct _DLL_$__s *previous;
}DoublyLinkedListNode;
typedef struct _DLL_$__ss
{
struct _DLL_$__s *start;
struct _DLL_$__s *end;
int size;
}DoublyLinkedList;
DoublyLinkedList *createDoublyLinkedList(bool *success);
int getSizeOfDoublyLinkedList(DoublyLinkedList *DoublyLinkedList);
void destroydDoublyLinkedList(DoublyLinkedList *DoublyLinkedList);
void addToDoublyLinkedList(DoublyLinkedList *DoublyLinkedList,void *ptr,bool *success);
void insertIntoDoublyLinkedList(DoublyLinkedList *DoublyLinkedList,int index,void *ptr,bool *success);
void *removeFromDoublyLinkedList(DoublyLinkedList *DoublyLinkedList,int index,bool *success);
void clearDoublyLinkedList(DoublyLinkedList *DoublyLinkedList);
void appendToDoublyLinkedList(DoublyLinkedList *targetDoublyLinkedList,DoublyLinkedList *sourceDoublyLinkedList,bool *success);
void *getFromDoublyLinkedList(DoublyLinkedList *DoublyLinkedList,int index,bool *success);
#endif