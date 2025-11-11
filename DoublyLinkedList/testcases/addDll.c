#include<dll.h>
#include<stdio.h>
int main()
{
int x=20;
int y=30;
int z=40;
bool success;
DoublyLinkedList *dll=createDoublyLinkedList(&success);
if(success==false) 
{
printf("Unable to create doublyLinkedList\n");
return 0;
}
addToDoublyLinkedList(dll,(void *)&x,&success);
if(success) printf("%d added\n",x);
addToDoublyLinkedList(dll,(void *)&y,&success);
if(success) printf("%d added\n",y);
addToDoublyLinkedList(dll,(void *)&z,&success);
if(success) printf("%d added\n",z);
int i;
int size=getSizeOfDoublyLinkedList(dll);
printf("Size:%d\n",size);
for(i=0;i<size;i++)
{
int *x=(int *)getFromDoublyLinkedList(dll,i,&success);
printf("%d \n",*x);
}
return 0;
}