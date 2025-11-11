#include<queue.h>
#include<stdio.h>
int main()
{
int x[10]={1,2,3,4,5,6,7,8,9,1};
bool success;
int i;
Queue *que=createQueue(&success);
if(success==false) 
{
printf("Unable to create doublyLinkedList\n");
return 0;
}
for(i=0;i<10;i++) addToQueue(que,(void *)&x[i],&success);
int size=getSizeOfQueue(que);
printf("Size:%d\n",size);
for(i=0;i<10;i++) printf(" |  %d  |\n",*((int *)removeFromQueue(que,&success)));
printf("  -----  \n");
return 0;
}
