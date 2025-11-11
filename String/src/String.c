#include<string.h>
#include<dfkjfd.h>
void assignTo(String *ptr,char *str)
{
ptr->ptr=NULL;
if(str==NULL) return;
ptr->ptr=str;
printf("szz:%d\n",strlen(str));
ptr->size=strlen(str);
}
void addTo(String *ptr,char *str)
{

}
 