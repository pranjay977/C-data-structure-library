#ifndef __AVL_H 
#define __AVL_H 1234
#include<common.h>
#include<stdlib.h>
#include<stdio.h>
#include<stack.h>
#include<queue.h>
typedef struct _avl_$__s
{
void *ptr;
struct _avl_$__s  *left;	
struct _avl_$__s  *right;
}AVLNode;
typedef struct _avl_$__ss
{
struct _avl_$__s  *root;
int size;
}AVL;
typedef struct _avl_$__it
{
AVLNode *node;
Stack *stack;
}AVLInOrderIterator;

typedef struct _avl_$__pt
{
AVLNode *node;
Stack *stack;
}AVLPreOrderIterator;


typedef struct _avl_$__pot
{
AVLNode *node;
Stack *stack;
}AVLPostOrderIterator;

AVLPostOrderIterator getAVLPostOrderIterator(AVL *avl,bool *success);
int hasMoreElementAVLPostOrder(AVLPostOrderIterator *iter);
void *getElementFromAVLPostOrderIterator(AVLPostOrderIterator *iter,bool *success);


AVLInOrderIterator getAVLInOrderIterator(AVL *avl,bool *success);
int hasMoreElementAVLInOrder(AVLInOrderIterator *iter);
void *getElementFromAVLInOrderIterator(AVLInOrderIterator *iter,bool *success);

AVLPreOrderIterator getAVLPreOrderIterator(AVL *avl,bool *success);
int hasMoreElementAVLPreOrder(AVLPreOrderIterator *iter);
void *getElementFromAVLPreOrderIterator(AVLPreOrderIterator *iter,bool *success);

AVL *createAVL(bool *success);
int getSizeOfAVL(AVL *avl);
void destroyAVL(AVL *avl);
void insertIntoAVL(AVL *avl,int index,void *ptr,bool *success,bool (*comparator)(void *,void *));
void removeFromAVL(AVL *avl,void *ptr,bool *success,bool (*comparator)(void *,void *));
void clearAVL(AVL *avl);
void balanceAvlTree(AVL *avlTree,Stack *stack);
void levelOrderTraversal(AVL *avl);
void *searchIntoAvl(AVL *avl,void *ptr,int (*cmp)(void *,void *));

int getHeightOfTree(AVLNode *avl);
#endif