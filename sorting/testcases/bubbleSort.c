#include<sortingAlgo.h>
#include<stdio.h>
int main()
{
char arr[10]={'a','c','d','z','a','e','h','q','r','v'};
Sort(arr,10,IntComparator);
for(i=0;i<10;i++) printf("%d ",*((int *)ptr[i]));
printf("\n");
gBubbleSort(ptr,10,CharComparator);
for(i=0;i<10;i++) printf("%c ",*((char *)ptr[i]));
return 0;
}