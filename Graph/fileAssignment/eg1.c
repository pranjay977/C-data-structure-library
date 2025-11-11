#include<stdio.h>
#include<string.h>
int main()
{
char m,name[100];
printf("Enter data:");
fgets(name,100,stdin);
if(name[strlen(name)-1]!='\n')
{
while((m=getchar())!='\n');
}
name[strlen(name)-1]='\0';
FILE *f=fopen("graph.dat","wb");
int i;
for(i=0;i<strlen(name);i++)  fputc(name[i],f);
fclose(f);
return 0;
}