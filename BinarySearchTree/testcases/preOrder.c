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
int x[7]={100,50,200,150,250,40,75};
BST *bst=createBST(&succ);
if(succ==false)
{
printf("Unable to create bst\n");
return 0;
}
for(int i=0;i<7;i++) insertIntoBST(bst,0,(void *)&x[i],&succ,&IntCom);
printf("Size:%d\n",getSizeOfBST(bst));
BSTPreOrderIterator iter=getBSTPreOrderIterator(bst,&succ);
if(succ)
{
while(hasMoreElementBSTPreOrder(&iter))
{
printf("%d\n",*((int *)getElementFromBSTPreOrderIterator(&iter,&succ)));
}
}
return 0;
}