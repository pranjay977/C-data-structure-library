#include<heap.h>
#include<stdio.h>
int comparator(void *a,void *b)
{
int *left=(int *)a;
int *right=(int *)b;
if(*left<*right) return -1;
return 1; 
}
int main()
{
bool succ;
int i;
Heap *heap=createHeap(&succ,comparator);
if(succ==false) printf("Failed to allocate heap\n");
int x[10]={10,32,43,2,1,4,23,6,31,22};
for(i=0;i<10;i++) addToHeap(heap,(void *)&x[i],&succ);
int k=888;
updateElementInHeap(heap,8,(void *)&k,&succ);
if(succ) printf("Element updated\n");
for(i=0;i<10;i++)
{
int *j=(int *)removeFromHeap(heap,&succ);
printf("%d\n",*j);
}
destroyHeap(heap,&succ);
return 0;
}