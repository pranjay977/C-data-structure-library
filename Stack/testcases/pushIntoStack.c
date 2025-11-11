#include<stack.h>
#include<stdio.h>
int main()
{
int x=20;
int y=30;
int z=40;
bool success;
Stack *stck=createStack(&success);
if(success==false) 
{
printf("Unable to create doublyLinkedList\n");
return 0;
}
pushOnStack(stck,(void *)&x,&success);
if(success) printf("%d added\n",x);
pushOnStack(stck,(void *)&y,&success);
if(success) printf("%d added\n",y);
pushOnStack(stck,(void *)&z,&success);
if(success) printf("%d added\n",z);
int i;
int size=getSizeOfStack(stck);
printf("Size:%d\n",size);
return 0;
}