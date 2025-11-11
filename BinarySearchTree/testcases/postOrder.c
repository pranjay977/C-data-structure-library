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
BST *bst=createBST(&succ);
if(succ==false)
{
printf("Unable to create bst\n");
return 0;
}
int elem,ch=1;
while(ch)
{
printf("Enter element to insert:");
scanf("%d",&elem);
int *x=(int *)malloc(sizeof(int));
*x=elem;
insertIntoBST(bst,0,(void *)x,&succ,&IntCom);
printf("Want to insert more:");
scanf("%d",&ch);
}
printf("Size:%d\n",getSizeOfBST(bst));
BSTPostOrderIterator iter=getBSTPostOrderIterator(bst,&succ);
if(succ)
{
while(hasMoreElementBSTPostOrder(&iter))
{
printf("%d\n",*((int *)getElementFromBSTPostOrderIterator(&iter,&succ)));
}
}
return 0;
}