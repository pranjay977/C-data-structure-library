 #include<avl.h>
typedef struct _D
{
int cityCode;
char cityName[100];
}Data;
AVL *createAVL(bool *success)
{
if(success) *success=false;
AVL *avl;
avl=(AVL *)malloc(sizeof(AVL));
if(avl==NULL) return NULL;
avl->root=NULL;
avl->size=0;
if(success) *success=true;
return avl;
}
int getSizeOfAVL(AVL *avl)
{
if(avl==NULL || avl->root==NULL) return 0;
return avl->size;
}
void destroyAVL(AVL *avl)
{
if(avl==NULL) return;
//clearAVL(avl);
//free(avl);
}
void balanceAVL(AVL *avlTree,Stack *stack)
{
AVLNode **p2p;
AVLNode *lc,*rc,*lcrc,*rclc,*parent,*root;
int lh,rh;
int diff,succ;
if(stack==NULL) return;
if(isStackEmpty(stack)) return;
while(!isStackEmpty(stack))
{
root=popFromStack(stack,&succ);
lh=getHeightOfTree(root->left);
rh=getHeightOfTree(root->right);
diff=lh-rh;
if(diff>=-1 && diff<=1) continue;
if(isStackEmpty(stack))
{
p2p=&(avlTree->root);
}
else 
{
parent=elementAtTopOfStack(stack,&succ);
if(parent->left==root)
{
p2p=&(parent->left);
}
else
{
p2p=&(parent->right);
}
}
if(rh>lh)
{
rc=root->right;
if(getHeightOfTree(rc->left)>getHeightOfTree(rc->right))
{
rclc=rc->left;
rc->left=rclc->right;
rclc->right=rc;
root->right=rclc;
rc=root->right;
}
root->right=rc->left;
rc->left=root;
*p2p=rc;
}
else
{
lc=root->left;
if(getHeightOfTree(lc->right)>getHeightOfTree(lc->left))
{
lcrc=lc->right;
lc->right=lcrc->left;
lcrc->left=lc;
root->left=lcrc;
lc=root->left;
}
root->left=lc->right;
lc->right=root;
*p2p=lc;
}
}
destroyStack(stack);
}
void insertIntoAVL(AVL *avl,int index,void *ptr,bool *success,bool (*comparator)(void *,void *))
{
AVLNode *t;
if(success) *success=false;
if(avl==NULL) 
{
return;
}
if(avl->root==NULL)
{
t=(AVLNode *)malloc(sizeof(AVLNode));
if(t==NULL) 
{
return;
}
t->ptr=ptr;
t->left=NULL;
t->right=NULL;
avl->root=t;
if(success) *success=true;
avl->size++;
return;
}
AVLNode *j;
bool succ;
Stack *stack=createStack(&succ);
if(succ==false) return;
j=avl->root;
while(j!=NULL)
{
int res=comparator(j->ptr,ptr);
if(res==0) 
{
return;
}
pushOnStack(stack,j,&succ);
if(succ==false)
{
destroyStack(stack);
return;
}
if(res==1)
{
if(j->left==NULL)
{
t=(AVLNode *)malloc(sizeof(AVLNode));
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
t=(AVLNode *)malloc(sizeof(AVLNode));
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
balanceAVL(avl,stack);
if(success) *success=true;
avl->size++;
return;
}
AVLInOrderIterator getAVLInOrderIterator(AVL *avl,bool *success)
{
bool succ;
if(success) *success=false;
AVLInOrderIterator iter;
iter.node=NULL;
iter.stack=NULL;
if(avl==NULL) return iter;
if(avl->root==NULL)
{
if(success) *success=true;
return iter;
}
iter.stack=createStack(&succ);
if(succ==false) return iter;
AVLNode *j;
j=avl->root;
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
int hasMoreElementAVLInOrder(AVLInOrderIterator *iter)
{
if(iter==NULL || iter->stack==NULL || iter->node==NULL) return false;
return true;
}
void *getElementFromAVLInOrderIterator(AVLInOrderIterator *iter,bool *success)
{
AVLNode *t,*j;
if(success) *success=false;
if(iter==NULL || iter->node==NULL) return NULL;
t=iter->node;
j=t->right;
bool succ;
AVLNode *node;
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

AVLPreOrderIterator getAVLPreOrderIterator(AVL *avl,bool *success)
{
bool succ;
if(success) *success=false;
AVLPreOrderIterator iter;
iter.node=NULL;
iter.stack=NULL;
if(avl==NULL || avl->root==NULL) return iter;
if(avl->root==NULL)
{
if(success) *success=true;
return iter;
}
iter.stack=createStack(&succ);
if(succ==false) return iter;
iter.node=avl->root;
if(success) *success=true;
return iter;
}
void *searchIntoAvl(AVL *avl,void *ptr,int (*comparator)(void *,void *))
{
if(avl==NULL || avl->root==NULL) return 0;
AVLNode *t;
t=avl->root;
while(t!=NULL)
{
int res=comparator(t->ptr,ptr);
if(res==0) return t->ptr;
if(res==1) t=t->left;
else t=t->right;
}
return NULL;
}
int hasMoreElementAVLPreOrder(AVLPreOrderIterator *iter)
{
if(iter==NULL || iter->node==NULL || iter->stack==NULL) return false;
return true;
}
void *getElementFromAVLPreOrderIterator(AVLPreOrderIterator *iter,bool *success)
{
AVLNode *t,*j;
if(success) *success=false;
if(iter->node==NULL || iter==NULL) return NULL;
j=iter->node;
bool succ;
AVLNode *node;
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

int getHeightOfTree(AVLNode *avl)
{
int lh,rh;
if(avl==NULL) return 0;
lh=getHeightOfTree(avl->left);
rh=getHeightOfTree(avl->right);
if(lh>rh) return lh+1;
return rh+1;
}





//CHANGES BELOW
AVLPostOrderIterator getAVLPostOrderIterator(AVL *avl,bool *success)
{
bool succ;
if(success) *success=false;
AVLPostOrderIterator iter;
AVLNode *t;
iter.node=NULL;
iter.stack=NULL;
if(avl==NULL) return iter;
if(avl->root==NULL)
{
if(success) *success=true;
return iter;
}
iter.stack=createStack(&succ);
if(succ==false) return iter;
t=avl->root;
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
int hasMoreElementAVLPostOrder(AVLPostOrderIterator *iter)
{
if(iter==NULL || iter->node==NULL || iter->stack==NULL) return false;
return true;
}
void *getElementFromAVLPostOrderIterator(AVLPostOrderIterator *iter,bool *success)
{
bool succ;
AVLNode *t,*j;
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
void levelOrderTraversal(AVL *avl)
{
bool succ;
Queue *queue=createQueue(&succ);
AVLNode *t;
addToQueue(queue,avl->root,&succ);
int x,j,insertionCount=1;
while(!isQueueEmpty(queue))
{
x=0;
j=1;
while(j<=insertionCount)
{
t=removeFromQueue(queue,&succ);
int *z=(int *)t->ptr;
printf("%d\n",*z);
if(t->left)
{
addToQueue(queue,t->left,&succ);
x++;
}
if(t->right)
{
addToQueue(queue,t->right,&succ);
x++;
}
j++;
}
insertionCount=x;
}
}
void removeFromAVL(AVL *avl,void *ptr,bool *success,bool (*comparator)(void *,void *))
{
if(success) *success=false;
if(avl==NULL || avl->root==NULL) return;
AVLNode *j,*t,*e,*f,**p2p;
t=avl->root;
while(t!=NULL)
{
int res=comparator(t->ptr,ptr);
if(res==0) break;
j=t;
if(res==1) t=t->left;
else t=t->right;
}
if(t==NULL) return;
if(t==avl->root) p2p=&(avl->root);
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
avl->size--;
if(success) *success=true;
return;
}

