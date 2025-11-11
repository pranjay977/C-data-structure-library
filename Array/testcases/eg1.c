#include<array.h>
#include<stdio.h>
int main()
{
int succ;
Array *array=createArray(&succ);
int x=222;
setElementIntoArray(array,34,(void *)&x);
int y=333;
setElementIntoArray(array,44,(void *)&y);
int k=444;
setElementIntoArray(array,55,(void *)&k);
int z=343;
setElementIntoArray(array,66,(void *)&z);

int *j=(void *)getElementFromArray(array,34);
printf("%d\n",*j);
j=(void *)getElementFromArray(array,44);
printf("%d\n",*j);
j=(void *)getElementFromArray(array,55);
printf("%d\n",*j);
j=(void *)getElementFromArray(array,66);
printf("%d\n",*j);
return 0;
}