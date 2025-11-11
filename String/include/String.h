#ifndef __STRING__$_
#define __STRING__$_ 12323
#include<stdio.h>
typedef struct string$$__
{
int size;
char *ptr;  
}String;
void assignTo(String *ptr,char *str);
void addTo(String *ptr,char *str);
#endif  