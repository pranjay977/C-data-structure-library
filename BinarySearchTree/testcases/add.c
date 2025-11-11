#include<bst.h>
int IntCom(void *a,void *b)
{
if(*((int *)a)==*((int *)b)) return 0;
if(*((int *)a)>*((int *)b)) return 1;
return -1;
}
int main()
{
bool succ;
int i;
BST *bst=createBST(&succ,IntCom);
if(succ==false)
{
printf("Unable to create bst\n");
return 0;
}
int *x;
for(int i=0;i<10;i++) 
{
x=(int *)malloc(sizeof(int));
printf("Enter no to insert:");
scanf("%d",x);
insertIntoBST(bst,0,(void *)x,&succ);
}
printf("Size:%d\n",getSizeOfBST(bst));
BSTInOrderIterator iter=getBSTInOrderIterator(bst,&succ);
if(succ)
{
while(hasMoreElementBSTInOrder(&iter))
{
printf("%d\n",*((int *)getElementFromBSTInOrderIterator(&iter,&succ)));
}
}
int *e,ch=1;
while(ch)
{
e=(int *)malloc(sizeof(int));
printf("Enter no to insert:");
scanf("%d",e);
insertIntoBST(bst,0,(void *)e,&succ);
scanf("%d",&ch);
}
iter=getBSTInOrderIterator(bst,&succ);
if(succ)
{
while(hasMoreElementBSTInOrder(&iter))
{
printf("%d\n",*((int *)getElementFromBSTInOrderIterator(&iter,&succ)));
}
}
return 0;
}