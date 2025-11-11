#include<bst.h>
#include<stdio.h>
BST *createBST(bool *success,bool (*comparator)(void *,void *))
{
if(success) *success=false;
BST *bst;
bst=(BST *)malloc(sizeof(BST));
if(bst==NULL) return NULL;
bst->root=NULL;
bst->size=0;
bst->comparator=comparator;
if(success) *success=true;
return bst;
}
int getSizeOfBST(BST *bst)
{
if(bst==NULL || bst->root==NULL) return 0;
return bst->size;
}
void destroyBST(BST *bst)
{
if(bst==NULL) return;
//clearBST(bst);
//free(bst);
}
void insertIntoBST(BST *bst,int index,void *ptr,bool *success)
{
BSTNode *t;
if(success) *success=false;
if(bst==NULL) return;
if(bst->root==NULL)
{
t=(BSTNode *)malloc(sizeof(BSTNode));
if(t==NULL) return;
t->ptr=ptr;
t->left=NULL;
t->right=NULL;
bst->root=t;
if(success) *success=true;
bst->size++;
return;
}
BSTNode *j;
j=bst->root;
while(j!=NULL)
{
int res=bst->comparator(j->ptr,ptr);
if(res==0) return;
if(res==1)
{
if(j->left==NULL)
{
t=(BSTNode *)malloc(sizeof(BSTNode));
if(t==NULL) return;
t->ptr=ptr;
t->left=NULL;
t->right=NULL;
j->left=t;
break;
}
else j=j->left;
}
else
{
if(j->right==NULL)
{
t=(BSTNode *)malloc(sizeof(BSTNode));
if(t==NULL) return;
t->ptr=ptr;
t->left=NULL;
t->right=NULL;
j->right=t;
break;
}
else j=j->right;
}
}
if(success) *success=true;
bst->size++;
return;
}

/*
Stack *createStack(bool *success);
void pushOnStack(Stack *stack,void *ptr,bool *success);
void *popFromStack(Stack *stack,bool *success);
int getSizeOfStack(Stack *stack);
void *elementAtTopOfStack(Stack *stack,bool *success);
bool isStackEmpty(Stack *stack);
void clearStack(Stack *stack);
void destroyStack(Stack *stack);
void *removeFromBST(BST *bst,int index,bool *success,bool (*comparator)(void *,void *));
*/
BSTInOrderIterator getBSTInOrderIterator(BST *bst,bool *success)
{
bool succ;
if(success) *success=false;
BSTInOrderIterator iter;
iter.node=NULL;
iter.stack=NULL;
if(bst==NULL) return iter;
if(bst->root==NULL)
{
if(success) *success=true;
return iter;
}
iter.stack=createStack(&succ);
if(succ==false) return iter;
BSTNode *j;
j=bst->root;
while(j)
{
pushOnStack(iter.stack,j,&succ);
if(succ==false)
{
destroyStack(iter.stack);
iter.stack=NULL;
return iter;
}
j=j->left;
}
iter.node=popFromStack(iter.stack,&succ);
if(success) *success=true;
return iter;
}
int hasMoreElementBSTInOrder(BSTInOrderIterator *iter)
{
if(iter==NULL || iter->stack==NULL || iter->node==NULL) return false;
return true;
}
void *getElementFromBSTInOrderIterator(BSTInOrderIterator *iter,bool *success)
{
BSTNode *t,*j;
if(success) *success=false;
if(iter==NULL || iter->node==NULL) return NULL;
t=iter->node;
j=t->right;
bool succ;
BSTNode *node;
while(j)
{
pushOnStack(iter->stack,j,&succ);
if(succ==false)
{
destroyStack(iter->stack);
iter->stack=NULL;
iter->node=NULL;
if(success) *success=true;
return t->ptr;
}
j=j->left;
}
if(isStackEmpty(iter->stack)) 
{
destroyStack(iter->stack);
iter->node=NULL;
iter->stack=NULL;
}
else
{
iter->node=popFromStack(iter->stack,&succ);
}
if(success) *success=true;
return  t->ptr;
}

BSTPreOrderIterator getBSTPreOrderIterator(BST *bst,bool *success)
{
bool succ;
if(success) *success=false;
BSTPreOrderIterator iter;
iter.node=NULL;
iter.stack=NULL;
if(bst==NULL || bst->root==NULL) return iter;
if(bst->root==NULL)
{
if(success) *success=true;
return iter;
}
iter.stack=createStack(&succ);
if(succ==false) return iter;
iter.node=bst->root;
if(success) *success=true;
return iter;
}
int hasMoreElementBSTPreOrder(BSTPreOrderIterator *iter)
{
if(iter==NULL || iter->node==NULL || iter->stack==NULL) return false;
return true;
}
void *getElementFromBSTPreOrderIterator(BSTPreOrderIterator *iter,bool *success)
{
BSTNode *t,*j;
if(success) *success=false;
if(iter->node==NULL || iter==NULL) return NULL;
j=iter->node;
bool succ;
BSTNode *node;
if(j->right!=NULL)
{
pushOnStack(iter->stack,j->right,&succ);
if(succ==false)
{
destroyStack(iter->stack);
iter->stack=NULL;
iter->node=NULL;
if(success) *success=true;
return t->ptr;
}
}
if(j->left!=NULL)
{
pushOnStack(iter->stack,j->left,&succ);
if(succ==false)
{
destroyStack(iter->stack);
iter->stack=NULL;
iter->node=NULL;
if(success) *success=true;
return t->ptr;
}
}
if(isStackEmpty(iter->stack)) 
{
destroyStack(iter->stack);
iter->node=NULL;
iter->stack=NULL;
}
else
{
iter->node=popFromStack(iter->stack,&succ);
}
if(success) *success=true;
return  j->ptr;
}








//CHANGES BELOW
BSTPostOrderIterator getBSTPostOrderIterator(BST *bst,bool *success)
{
bool succ;
if(success) *success=false;
BSTPostOrderIterator iter;
BSTNode *t;
iter.node=NULL;
iter.stack=NULL;
if(bst==NULL) return iter;
if(bst->root==NULL)
{
if(success) *success=true;
return iter;
}
iter.stack=createStack(&succ);
if(succ==false) return iter;
t=bst->root;
while(1)
{
while(t!=NULL)
{
if(t->right!=NULL) 
{
//PUSH ON STACK
pushOnStack(iter.stack,t->right,&succ);
if(succ==false)
{
destroyStack(iter.stack);
iter.stack=NULL;
iter.node=NULL;
if(success) *success=true;
return iter;
}
}
pushOnStack(iter.stack,t,&succ);
if(succ==false)
{
destroyStack(iter.stack);
iter.stack=NULL;
iter.node=NULL;
if(success) *success=true;
return iter;
}
//PUSH ON STACK
t=t->left;
}
t=popFromStack(iter.stack,&succ);
if(!isStackEmpty(iter.stack) && t->right!=NULL && t->right==elementAtTopOfStack(iter.stack,&succ))
{
popFromStack(iter.stack,&succ);
//PUSH ON STACK
pushOnStack(iter.stack,t,&succ);
if(succ==false)
{
destroyStack(iter.stack);
iter.stack=NULL;
iter.node=NULL;
if(success) *success=true;
return iter;
}
t=t->right;
}
else break;
}
iter.node=t;
if(success) *success=true;
return iter;
}
int hasMoreElementBSTPostOrder(BSTPostOrderIterator *iter)
{
if(iter==NULL || iter->node==NULL || iter->stack==NULL) return false;
return true;
}
void *getElementFromBSTPostOrderIterator(BSTPostOrderIterator *iter,bool *success)
{
bool succ;
BSTNode *t,*j;
if(success) *success=false;
j=iter->node;
if(isStackEmpty(iter->stack)) 
{
destroyStack(iter->stack);
iter->node=NULL;
iter->stack=NULL;
if(success==false) *success=true;
return j->ptr;
}
t=NULL;
while(1)
{
while(t!=NULL)
{
if(t->right!=NULL) 
{
//PUSH ON STACK
pushOnStack(iter->stack,t->right,&succ);
if(succ==false)
{
destroyStack(iter->stack);
iter->stack=NULL;
iter->node=NULL;
if(success) *success=true;
return NULL;
}
}
pushOnStack(iter->stack,t,&succ);
if(succ==false)
{
destroyStack(iter->stack);
iter->stack=NULL;
iter->node=NULL;
if(success) *success=true;
return NULL;
}
//PUSH ON STACK
t=t->left;
}
t=popFromStack(iter->stack,&succ);
if(!isStackEmpty(iter->stack) && t->right!=NULL && t->right==elementAtTopOfStack(iter->stack,&succ))
{
popFromStack(iter->stack,&succ);
//PUSH ON STACK
pushOnStack(iter->stack,t,&succ);
if(succ==false)
{
destroyStack(iter->stack);
iter->stack=NULL;
iter->node=NULL;
if(success) *success=true;
return NULL;
}
t=t->right;
}
else break;
}
iter->node=t;
if(success) *success=true;
return j->ptr;
}

void removeFromBST(BST *bst,void *ptr,bool *success)
{
if(success) *success=false;
if(bst==NULL || bst->root==NULL) return;
BSTNode *j,*t,*e,*f,**p2p;
t=bst->root;
while(t!=NULL)
{
int res=bst->comparator(t->ptr,ptr);
if(res==0) break;
j=t;
if(res==1) t=t->left;
else t=t->right;
}
if(t==NULL) return;
if(t==bst->root) p2p=&(bst->root);
else if(j->left==t) p2p=&(j->left);
else p2p=&(j->right);
if(t->left==NULL && t->right==NULL)
{
*p2p=NULL;
}
else 
{
if(t->right!=NULL)
{
for(e=t->right;e->left;e=e->left)  f=e;
if(t->right==e)
{
e->left=t->left;
}
else
{
e->left=t->left;
e->right=t->right;
f->left=NULL;
}
*p2p=e;
}
else
{
for(e=t->left;e->right;e=e->right)  f=e;
if(t->left==e)
{
e->right=t->right;
}
else
{
e->left=t->left;
e->right=t->right;
f->right=NULL;
}
*p2p=e;
}
}
free(t);
bst->size--;
if(success) *success=true;
return;
}
