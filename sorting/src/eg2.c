#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// IN THIS CODE OTHER THAN SWAPPING EVERYTHING WORKS WELL AND GOOD
int comp(void *a,void *b)
{
int *aa=(int *)&a;
int *bb=(int *)&b;  
printf("comparator called\t for (%d) , (%d)\n",*aa,*bb);
if(*aa>*bb) return 1;
return 0;
}
void swap(void *a,void *b)
{
// memcpy vala concept

}
void sort(void **arr,int size,int (*comparator)(void *,void *),void (*comparatorSwap)(void *,void *))
{
for(int i=0;i<size;i++)
{
int k=1;
for(int j=0;j<size-1;j++,k++)  if(comparator(arr[j],arr[j+1])>0) comparatorSwap(arr[j],arr[k]);
}
}
// Accepted 
// (!)
int main()
{
int arr[10];
for(int i=0;i<10;i++) scanf("%d",&arr[i]);
sort((void **)&arr,10,comp,swap);
printf("***********************\n");
for(int i=0;i<10;i++)  printf("%d\n",arr[i]);
return 0;
}