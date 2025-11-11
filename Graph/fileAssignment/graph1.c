#include<stdio.h>
#include<avl.h>
#include<string.h>
typedef struct _H
{
int recordCount;
int lastGeneratedCode;
}Header;
typedef struct _D
{
int cityCode;
char cityName[100];
}Data;
AVL *cityNames;
AVL *cityCodes;
Header metaBlock;
int stringComparator(void *a,void *b)
{
Data *l=(Data *)a;
Data *r=(Data *)b;
int res=stricmp(l->cityName,r->cityName);
if(res==0) return 0;
if(res>0) return 1;
return -1;
}
int IntComparator(void *a,void *b)
{
Data *l=(Data *)a;
Data *r=(Data *)b;
if(l->cityCode==r->cityCode) return 0;
if(l->cityCode>r->cityCode) return 1;
return -1;
}
AVL *populateAvlTree(int (*cmp)(void *, void *)) {
int succ;
AVL *avl = createAVL(&succ);
if (succ == false) return NULL;
FILE *f = fopen("city.dat", "rb+");
if(f==NULL)
{
FILE *z = fopen("city.dat", "wb+");
metaBlock.lastGeneratedCode=1;
metaBlock.recordCount=0;
fwrite(&metaBlock,sizeof(Header),1,z);
fclose(z);
return avl;
}
fread(&metaBlock,sizeof(Header),1,f);
while (1) {
Data *d=(Data *)malloc(sizeof(Data));
fread(d, sizeof(Data), 1, f);
if(feof(f)) break;
insertIntoAVL(avl,0,(void *)d,&succ,cmp);
if(succ == false){
fclose(f);
return NULL;
}
}
fclose(f);
return avl;
}
void showMenu1()
{
printf("1.CITY MASTER\n");
printf("2.CITY ROUTE\n");
printf("3.EXIT\n");
}
void showMenu2()
{
printf("1.ADD\n");
printf("2.EDIT\n");
printf("3.SEARCH\n");
printf("4.DELETE\n");
printf("5.SHOW ROUTE\n");
printf("6.DISPLAY\n");
printf("7.EXIT\n");
}
Data *search(char *name)
{
Data *d=(Data *)malloc(sizeof(Data));;
int i;
strcpy(d->cityName,name);
d->cityCode=-1;
void *found=searchIntoAvl(cityNames,(void *)d,stringComparator);
if(found==NULL) return found;
return (Data *)found;
}
void add(char *name)
{
int succ;
if(name==NULL) return;
int i;
Data *presentOrNot=search(name);
printf("presentOrOrNot:%d\n",presentOrNot);
if(presentOrNot!=NULL) return;
FILE *f=fopen("city.dat","rb+");
fread(&metaBlock,sizeof(Header),1,f);
printf("lC:%d , RC:%d\n",metaBlock.lastGeneratedCode,metaBlock.recordCount);
Data *d=(Data *)malloc(sizeof(Data));;
d->cityCode=metaBlock.lastGeneratedCode;
strcpy(d->cityName,name);
fseek(f,0,SEEK_END);
fwrite(d,sizeof(Data),1,f);
fseek(f,0,SEEK_SET);
metaBlock.recordCount++;
metaBlock.lastGeneratedCode++;
fwrite(&metaBlock,sizeof(Header),1,f);
fclose(f);
insertIntoAVL(cityNames,0,(void *)d,&succ,stringComparator);
if(succ=false)
{
printf("Unable to add data\n");
return;
}
insertIntoAVL(cityCodes,0,(void *)d,&succ,stringComparator);
if(succ=false)
{
printf("Unable to add data\n");
return;
}
printf("Data successfully added\n");
return;
}
void edit(char *name)
{
FILE *f;
char m,nn[31];
int flg,succ,pos;
if(name==NULL) return;
Data *presentOrNot=search(name);
if(presentOrNot==NULL) 
{
printf("Invalid record to edit\n");
return;
}
printf("Enter new name to Edit:");
fgets(nn,31,stdin);
if(nn[strlen(nn)-1]!='\n')
{
while((m=getchar())!='\n');
}
nn[strlen(nn)-1]='\0';
void *check=search(nn);
if(check!=NULL) 
{
printf("Record alreadly present\n");
return;
}
printf("Are you sure(1/0):");
scanf("%d",&flg);
if(flg==0) return;
f=fopen("city.dat","rb+");
if(f==NULL) return;
Data d,*k;
fread(&metaBlock,sizeof(Header),1,f);
while(1)
{
pos=ftell(f);
fread(&d,sizeof(Data),1,f);
if(feof(f)) break;
if(stricmp(d.cityName,name)==0)
{
k=(Data *)malloc(sizeof(Data));
fseek(f,pos,SEEK_SET);
strcpy(k->cityName,nn);
k->cityCode=presentOrNot->cityCode;
printf("k->Name:%s\n",k->cityName);
fwrite(k,sizeof(Data),1,f);
break;
}
}
removeFromAVL(cityNames,(void *)presentOrNot,&succ,stringComparator);
removeFromAVL(cityCodes,(void *)presentOrNot,&succ,IntComparator);
insertIntoAVL(cityNames,0,(void *)k,&succ,stringComparator);
insertIntoAVL(cityCodes,0,(void *)k,&succ,IntComparator);
printf("Record succesfully edited\n");
fclose(f);
return;
}
int delete(char *name)
{
FILE *f,*temp;
char m;
int flg,succ,pos;
if(name==NULL) return 0;
Data d;
Data *presentOrNot=search(name);
if(presentOrNot==NULL) 
{
printf("Invalid record to edit\n");
return 0;
}
printf("Are you sure(1/0):");
scanf("%d",&flg);
if(flg==0) return 0;
f=fopen("city.dat","rb");
temp=fopen("temp.dat","wb");
fread(&metaBlock,sizeof(Header),1,f);
while(1)
{
fread(&d,sizeof(Data),1,f);
if(feof(f)) break;
if(stricmp(name,d.cityName)==0) continue;
fwrite(&d,sizeof(Data),1,temp);
}
fclose(f);
fclose(temp);
f=fopen("city.dat","wb");
temp=fopen("temp.dat","rb");
metaBlock.recordCount--;
fwrite(&metaBlock,sizeof(Header),1,f);
while(1)
{
fread(&d,sizeof(Data),1,temp);
if(feof(temp)) break;
fwrite(&d,sizeof(Data),1,f);
}
fclose(f);
fclose(temp);
f=fopen("temp.dat","wb");
fclose(f);
removeFromAVL(cityNames,(void *)presentOrNot,&succ,stringComparator);
removeFromAVL(cityCodes,(void *)presentOrNot,&succ,IntComparator);
printf("Record deleted successfully\n");
return 1;
}
void line(char c,int e)
{
int i;
for(i=0;i<e;i++) printf("%c",c);
printf("\n");
}
void display()
{
int sz=getSizeOfAVL(cityNames);
if(cityNames==NULL || sz==0) return;
int menu=1;
int cnt=0;
int succ; 
char m;
AVLInOrderIterator iter=getAVLInOrderIterator(cityNames,&succ);
if(succ)
{
while(hasMoreElementAVLInOrder(&iter))
{
if(menu) 
{
line('-',50);
printf("   SNO       NAME \n");
line('-',50);
menu=!menu;
}
Data *x=(Data *)getElementFromAVLInOrderIterator(&iter,&succ);
printf("%5d %-10s\n",x->cityCode,x->cityName);
cnt++;
if(cnt%5==0 || cnt==sz)
{
line('-',50);
if(cnt<sz) printf("please Enter to continue ....");
m=getchar();
menu=!menu;
}
}
}
}
int main()
{
int succ;
cityNames=populateAvlTree(stringComparator);
cityCodes=populateAvlTree(IntComparator);
int ch1,ch2;
char m,name[100];
while(1)
{
showMenu1();
printf("Enter choice:");
scanf("%d",&ch1);
while((m=getchar())!='\n');
if(ch1==1) 
{
while(1)
{
showMenu2();
printf("Enter choice:");
scanf("%d",&ch2);
while((m=getchar())!='\n');
if(ch2==1) 
{
printf("Enter name to insert:");
fgets(name,100,stdin);
if(name[strlen(name)-1]!='\n')
{
while((m=getchar())!='\n');
}
name[strlen(name)-1]='\0';
add(name);
}
if(ch2==2)
{
printf("Enter name to edit:");
fgets(name,23,stdin);
if(name[strlen(name)-1]!='\n')
{
while((m=getchar())!='\n');
}
name[strlen(name)-1]='\0';
edit(name);
}
if(ch2==3)
{
printf("Enter name to search:");
fgets(name,23,stdin);
if(name[strlen(name)-1]!='\n')
{
while((m=getchar())!='\n');
}
name[strlen(name)-1]='\0';
Data *d=search(name);
if(d) printf("Record is present into file\n");
else printf("Record is not present into file\n");
}
if(ch2==4)
{
printf("Enter name to delete:");
fgets(name,23,stdin);
if(name[strlen(name)-1]!='\n')
{
while((m=getchar())!='\n');
}
name[strlen(name)-1]='\0';
int i=delete(name);
if(i) printf("Record Deleted\n");
else printf("Record Not Deleted\n");
}
//if(ch2==5) showRoute();
if(ch2==6) display();
if(ch2==7) break;
}
}
if(ch1==3) break;
}
return 0;
 }