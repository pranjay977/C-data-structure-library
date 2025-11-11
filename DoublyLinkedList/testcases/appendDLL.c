#include<dll.h>
#include<stdio.h>
int main()
{
int x[10]={1,2,3,4,5,6,7,8,9,10};
int y[10]={11,20,30,40,50,60,70,80,90,100};
int i;
bool success;
DoublyLinkedList *dll1=createDoublyLinkedList(&success);
DoublyLinkedList *dll2=createDoublyLinkedList(&success);
for(i=0;i<10;i++) addToDoublyLinkedList(dll1,(void *)&x[i],&success);
for(i=0;i<10;i++) addToDoublyLinkedList(dll2,(void *)&y[i],&success);
appendToDoublyLinkedList(dll1,dll2,&success);
int size=getSizeOfDoublyLinkedList(dll1);
printf("Size:%d\n",size);
for(i=0;i<size;i++)
{
int *j=(int *)getFromDoublyLinkedList(dll1,i,&success);
printf("%d ->",*j);
}
printf("NULL\n");
return 0;
} 