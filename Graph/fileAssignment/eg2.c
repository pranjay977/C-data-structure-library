#include<stdio.h>
#include<string.h>
int main()
{
int weight,vertex,adv,code;
char c1,c2,c3;
FILE *f=fopen("graph.dat","rb");
while(1)
{
code=0;
c1=fgetc(f);
if(feof(f)) break;
code=(code *10)+(c1-48);
while(1)
{
c1=fgetc(f);
if(c1==',' || c1=='#') break;
if(feof(f)) break;
code=(code *10)+(c1-48);
}
printf("\n%d\n",code);
if(feof(f)) break;
while(1)
{
adv=0;
c2=fgetc(f);
adv=(adv*10)+(c2-48);
while(1)
{
c2=fgetc(f);
if(feof(f) || c2==',') break;
adv=(adv *10)+(c2-48);
}
printf("%d ,",adv);
weight=0;
c3=fgetc(f);
weight=(weight*10)+(c3-48);
while(1)
{
c3=fgetc(f);
if(feof(f) || c3=='#' || c3==',') break;
weight=(weight*10)+(c3-48);
}
printf(" %d |",weight);
if(c3=='#') break;
}
if(feof(f)) break;
}
fclose(f);
return 0;
}