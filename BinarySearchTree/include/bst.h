#ifndef __BST_re 
#define __BST_re 1234
#include<common.h>
#include<stdlib.h>
#include<stdio.h>
#include<stack.h>
#include<queue.h>
typedef struct _bst_$__s
{
void *ptr;
struct _bst_$__s  *left;	
struct _bst_$__s  *right;
}BSTNode;
typedef struct _bst_$__ss
{
struct _bst_$__s  *root;
int size;
bool (*comparator)(void *,void *);
}BST;
typedef struct _bst_$__it
{
BSTNode *node;
Stack *stack;
}BSTInOrderIterator;

typedef struct _bst_$__pt
{
BSTNode *node;
Stack *stack;
}BSTPreOrderIterator;


typedef struct _bst_$__pot
{
BSTNode *node;
Stack *stack;
}BSTPostOrderIterator;

BSTPostOrderIterator getBSTPostOrderIterator(BST *bst,bool *success);
int hasMoreElementBSTPostOrder(BSTPostOrderIterator *iter);
void *getElementFromBSTPostOrderIterator(BSTPostOrderIterator *iter,bool *success);


BSTInOrderIterator getBSTInOrderIterator(BST *bst,bool *success);
int hasMoreElementBSTInOrder(BSTInOrderIterator *iter);
void *getElementFromBSTInOrderIterator(BSTInOrderIterator *iter,bool *success);

BSTPreOrderIterator getBSTPreOrderIterator(BST *bst,bool *success);
int hasMoreElementBSTPreOrder(BSTPreOrderIterator *iter);
void *getElementFromBSTPreOrderIterator(BSTPreOrderIterator *iter,bool *success);


BST *createBST(bool *success,bool (*comparator)(void *,void *));
int getSizeOfBST(BST *bst);
void destroyBST(BST *bst);
void insertIntoBST(BST *bst,int index,void *ptr,bool *success);
void removeFromBST(BST *bst,void *ptr,bool *success);
void clearBST(BST *bst);
#endif