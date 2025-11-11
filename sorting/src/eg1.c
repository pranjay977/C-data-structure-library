#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// IN THIS CODE OTHER THAN SWAPPING EVERYTHING WORKS FINE AND GOOD
int comp(void *a,void *b)
{
char *aa=(char *)a;
char *bb=(char *)b;  
printf("comparator called\t for (%s) , (%s)\n",aa,bb);
if(strcmp(aa,bb)>0) return 1;
return 0;
}
void swap(void *a,void *b)
{
// memcpy vala concept

}
void sort(void **arr,int size,int (*comparator)(void *,void *),void (*comparatorSwap)(void *,void *))
{
char g[24];
for(int i=0;i<size;i++)
{
int k=1;
for(int j=0;j<size-1;j++,k++) 
{
if(comparator(arr[j],arr[k])>0)
{
comparatorSwap(arr[j],arr[k]);
}
}
}
}
int main()
{
char *arr[10];
for(int i=0;i<10;i++)
{
arr[i]=(char *)malloc(sizeof(char *)*24);
fgets(arr[i],24,stdin);
arr[i][strlen(arr[i])-1]='\0';
}
sort((void *)&arr,10,comp,swap);
printf("***********************\n");
for(int i=0;i<10;i++)  printf("%s\n",arr[i]);
return 0;
}