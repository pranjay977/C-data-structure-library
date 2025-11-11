#include<pqueue.h>
#include<stdio.h>
int comparator(void *a,void *b)
{
int *left=(int *)a;
int *right=(int *)b;
if(*left>*right) return 1;
return -1;
}
int main()
{
int x[10]={3,4,5,12,2,6,60,21,65,56};
bool success;
PQueue *pqueue=createPQueue(&success,comparator);
if(success==false) 
{
printf("Unable to create doublyLinkedList\n");
return 0;
}
int i;
for(i=0;i<10;i++) addToPQueue(pqueue,(void *)&x[i],&success);
int size=getSizeOfPQueue(pqueue);
printf("Size:%d\n",size);
while(!isPQueueEmpty(pqueue))
{
printf("%d\n",*((int *)elementAtTopOfPQueue(pqueue,&success)));
removeFromPQueue(pqueue,&success);
}
return 0;
}