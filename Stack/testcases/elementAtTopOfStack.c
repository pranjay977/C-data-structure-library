#include<stack.h>
#include<stdio.h>
int main()
{
int x[10]={1,2,3,4,5,6,7,8,9,1};
bool success;
int i;
Stack *stck=createStack(&success);
if(success==false) 
{
printf("Unable to create doublyLinkedList\n");
return 0;
}
for(i=0;i<10;i++) pushOnStack(stck,(void *)&x[i],&success);
printf("> %d\n",*((int *)elementAtTopOfStack(stck,&success)));
popFromStack(stck,&success);
printf("> %d\n",*((int *)elementAtTopOfStack(stck,&success)));
popFromStack(stck,&success);
printf("> %d\n",*((int *)elementAtTopOfStack(stck,&success)));
popFromStack(stck,&success);
printf("> %d\n",*((int *)elementAtTopOfStack(stck,&success)));
popFromStack(stck,&success);
return 0;
}
