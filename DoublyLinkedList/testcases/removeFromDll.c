#include<dll.h>
#include<stdio.h>
int main()
{
int x[10]={1,2,3,4,5,6,7,8,9,10};
int i;
bool success;
DoublyLinkedList *dll=createDoublyLinkedList(&success);
if(success==false) 
{
printf("Unable to create doublyLinkedList\n");
return 0;
}
for(i=0;i<10;i++)
{
addToDoublyLinkedList(dll,(void *)&x[i],&success);
if(success) printf("%d added\n",x[i]);
}
int size=getSizeOfDoublyLinkedList(dll);
printf("Size:%d\n",size);
for(i=0;i<size;i++)
{
int *j=(int *)getFromDoublyLinkedList(dll,i,&success);
printf("%d ->",*j);
}
printf("\n");
removeFromDoublyLinkedList(dll,5,&success);
printf("After Removal\n");
size=getSizeOfDoublyLinkedList(dll);
for(i=0;i<size;i++)
{
int *j=(int *)getFromDoublyLinkedList(dll,i,&success);
printf("%d ->",*j);
}
printf("\n");
return 0;
} 