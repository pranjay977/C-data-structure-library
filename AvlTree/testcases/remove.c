#include<avl.h>
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
AVL *avl=createAVL(&succ);
if(succ==false)
{
printf("Unable to create avl\n");
return 0;
}
int elem,ch=1;
while(ch)
{
printf("Enter element to insert:");
scanf("%d",&elem);
int *x=(int *)malloc(sizeof(int));
*x=elem;
insertIntoAVL(avl,0,(void *)x,&succ,&IntCom);
printf("Want to insert more:");
scanf("%d",&ch);
levelOrderTraversal(avl);
}
printf("Size:%d\n",getSizeOfAVL(avl));
AVLInOrderIterator iter=getAVLInOrderIterator(avl,&succ);
if(succ)
{
while(hasMoreElementAVLInOrder(&iter))
{
printf("%d\n",*((int *)getElementFromAVLInOrderIterator(&iter,&succ)));
}
}
ch=1;
while(ch)
{
printf("Enter element to delete:");
scanf("%d",&elem);
int *x=(int *)malloc(sizeof(int));
*x=elem;
removeFromAVL(avl,(void *)x,&succ,&IntCom);
if(succ==false) printf("Unable to delete:%d\n",elem);
else printf("%d successfully deleted\n",elem);
printf("Want to delete more:");
scanf("%d",&ch);
}
printf("After deletion\n");
iter=getAVLInOrderIterator(avl,&succ);
if(succ)
{
while(hasMoreElementAVLInOrder(&iter))
{
printf("%d\n",*((int *)getElementFromAVLInOrderIterator(&iter,&succ)));
}
}
return 0;
}