#include<queue.h>
#include<stdio.h>
int main()
{
int x=20;
int y=30;
int z=40;
bool success;
Queue *stck=createQueue(&success);
if(success==false) 
{
printf("Unable to create doublyLinkedList\n");
return 0;
}
addToQueue(stck,(void *)&x,&success);
if(success) printf("%d added\n",x);
addToQueue(stck,(void *)&y,&success);
if(success) printf("%d added\n",y);
addToQueue(stck,(void *)&z,&success);
if(success) printf("%d added\n",z);
int i;
int size=getSizeOfQueue(stck);
printf("Size:%d\n",size);
return 0;
}