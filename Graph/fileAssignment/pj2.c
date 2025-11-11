#include<stdio.h>
#include<avl.h>
#include<pair.h>
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
AVL *graph;
int chinku=0;
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
int vertexComparator(void *a,void *b)
{
Pair *left=(Pair *)a;
Pair *right=(Pair *)b;
return stringComparator(left->first,right->first);
}
int adjacentVertexComparator(void *a,void *b)
{
Pair *left=(Pair *)a;
Pair *right=(Pair *)b;
return stringComparator(left->first,right->first);
}
void populateGraph()
{
if(getSizeOfAVL(cityNames)<=0) return;
int code,acode,weight,*edgeWeight,succ,success;
Data c,*city,*advCity;
FILE *graphFile;	
AVL *advTree;
char m;
Pair *p1,*p2;
graph=createAVL(&succ);
graphFile=fopen("graph.dat","r");
if(graphFile==NULL) return;
while(1)
{
code=0;
m=fgetc(graphFile);
if(feof(graphFile)) break;
code=m-48;
while(1)
{
m=fgetc(graphFile);
if(m==',') break;
code=code*10+(m-48);
}
c.cityCode=code;
chinku=1;
city=(Data *)searchIntoAvl(cityCodes,(void *)&c,IntComparator);
p1=(Pair *)malloc(sizeof(Pair));
p1->first=(void *)city;
advTree=createAVL(&succ);
p1->second=(void *)advTree;
while(1)
{
acode=0;
while(1)
{
m=fgetc(graphFile);
if(m==',') break;
acode=acode*10+(m-48);
}
weight=0;
while(1)
{
m=fgetc(graphFile);
if(m==',' || m=='#') break;
weight=weight*10+(m-48);
}
c.cityCode=acode;
advCity=(Data *)searchIntoAvl(cityCodes,(void *)&c,IntComparator);
p2=(Pair *)malloc(sizeof(Pair));
p2->first=(void *)advCity;
edgeWeight=(int *)malloc(sizeof(int));
*edgeWeight=weight;
p2->second=(void *)edgeWeight;
insertIntoAVL(advTree,0,p2,&success,adjacentVertexComparator);
if(m=='#') break;
}
insertIntoAVL(graph,0,p1,&succ,vertexComparator);
}
fclose(graphFile);
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
printf("7.ADD ADJACENT VERTEX\n");
printf("8.REMOVE ADJACENT VERTEX\n");
printf("9.EDIT ADJACENT VERTEX\n");
printf("10.EXIT\n");
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
void addAdjacentVertex()
{
char name[100],advName[100],m;
Data d,*city,advC,*advCity;
AVL *advTree;
Pair gPair,*graphPair,*advPair;
FILE *graphFile;
int cityCode,flg,shouldAppend,advCode,weight,succ,*wgt;
printf("Enter city against you want to add adjacent cities:");
fgets(name,100,stdin);
if(name[strlen(name)-1]!='\n')
{
while((m=getchar())!='\n');
}
name[strlen(name)-1]='\0';
strcpy(d.cityName,name);
city=(Data *)searchIntoAvl(cityNames,(void *)&d,stringComparator);
if(city==NULL) 
{
printf("%s city does not exists\n");
return;
}
Pair *e;
Data *f;
Pair z;
z.first=(void *)city;
Pair *temp=(Pair *)searchIntoAvl(graph,(void *)&z,vertexComparator);
if(temp!=NULL)
{
AVL *av=(AVL *)temp->second;
printf("SIZE OF BANGLORE TREE:%d\n",getSizeOfAVL(av));
AVLInOrderIterator iter=getAVLInOrderIterator(av,&succ);
if(succ)
{
while(hasMoreElementAVLInOrder(&iter))
{
e=(Pair *)getElementFromAVLInOrderIterator(&iter,&succ);
f=(Data *)e->first;
int *distance=(int *)e->second;
printf("city :%s , Distance :%d \n",f->cityName,*distance);
}
}
}
cityCode=city->cityCode;
gPair.first=(void *)city;
graphPair=(Pair *)searchIntoAvl(graph,(void *)&gPair,vertexComparator);
shouldAppend=0;
if(graphPair==NULL) 
{
graphPair=NULL;
shouldAppend=1;
}
while(1)
{
printf("Enter Adjacent vertex to %s:",name);
fgets(advName,100,stdin);
if(advName[strlen(advName)-1]!='\n')
{
while((m=getchar())!='\n');
}
advName[strlen(advName)-1]='\0';
strcpy(advC.cityName,advName);
advCity=(Data *)searchIntoAvl(cityNames,(void *)&advC,stringComparator);
if(advCity==NULL)
{
printf("%s city does not exists\n",advName);
printf("Want to enter more city(0/1):");
scanf("%d",&flg);
while((m=getchar())!='\n');
if(flg!=1) break;
continue;
}
advCode=advCity->cityCode;
printf("Enter weight from %s to %s:",name,advName);
scanf("%d",&weight);
while((m=getchar())!='\n');
if(weight<=0)
{
printf("Invalid weight\n");
printf("Want to enter more weight(0/1):");
scanf("%d",&flg);
while((m=getchar())!='\n');
if(flg!=1) break;
continue;
}
printf("Save(0/1):");
scanf("%d",&flg);
while((m=getchar())!='\n');
if(flg!=1) break;
if(graphPair==NULL)
{
graphPair=(Pair *)malloc(sizeof(Pair));
graphPair->first=(void *)city;
advTree=createAVL(&succ);
graphPair->second=(void *)advTree;
advPair=(Pair *)malloc(sizeof(Pair));
advPair->first=(void *)advCity;
wgt=(int *)malloc(sizeof(int));
*wgt=weight;
advPair->second=(void *)wgt;
insertIntoAVL(advTree,0,advPair,&succ,adjacentVertexComparator);
insertIntoAVL(graph,0,graphPair,&succ,vertexComparator);
graphFile=fopen("graph.dat","a");
fprintf(graphFile,"%d,%d,%d#",cityCode,advCode,weight);
fclose(graphFile);
}
else if(shouldAppend==1)
{
graphFile=fopen("graph.dat","r+");
fseek(graphFile,-1,SEEK_END);
fprintf(graphFile,",%d,%d#",advCode,weight);
fclose(graphFile);
advPair=(Pair *)malloc(sizeof(Pair));
wgt=(int *)malloc(sizeof(int));
*wgt=weight;
advPair->second=(void *)wgt;
insertIntoAVL(advTree,0,advPair,&succ,adjacentVertexComparator);
}
else
{
//MARKER
AVL *temp=(AVL *)graphPair->second;
Data dt;
strcpy(dt.cityName,advName);
Pair *sdf=(Pair *)malloc(sizeof(Pair));
sdf->first=(void *)&dt;
Pair *ekd=(Pair *)searchIntoAvl(temp,(void *)sdf,adjacentVertexComparator);
if(ekd!=NULL) 
{
printf("City %s is already exists as the adjacent city to %s\n",advCity->cityName,name);
printf("Want to enter another city(0/1):");
scanf("%d",&flg);
while((m=getchar())!='\n');
if(flg!=1) break;
continue;
}
Pair *p=(Pair *)malloc(sizeof(Pair));
p->first=(void *)advCity;
wgt=(int *)malloc(sizeof(int));
*wgt=weight;
p->second=(void *)wgt;
insertIntoAVL(temp,0,(void *)p,&succ,adjacentVertexComparator);
AVLInOrderIterator iter=getAVLInOrderIterator(graph,&succ);
FILE *f=fopen("graph.dat","wb");
int suc;
if(succ)
{
while(hasMoreElementAVLInOrder(&iter))
{
Pair *dfs=(Pair *)getElementFromAVLInOrderIterator(&iter,&succ);
Data *ds=(Data *)dfs->first;
fprintf(f,"%d,",ds->cityCode);
AVL *e=(AVL *)dfs->second;
AVLInOrderIterator it=getAVLInOrderIterator(e,&suc);
if(suc)
{
while(hasMoreElementAVLInOrder(&it))
{
Pair *kfs=(Pair *)getElementFromAVLInOrderIterator(&it,&suc);
Data *gd=(Data *)kfs->first;
int *dd=(int  *)kfs->second;
if(hasMoreElementAVLInOrder(&it)) fprintf(f,"%d,%d,",gd->cityCode,*dd);
else fprintf(f,"%d,%d#",gd->cityCode,*dd);
}
}
}
}
fclose(f);
}
cityCode=city->cityCode;
gPair.first=(void *)city;
graphPair=(Pair *)searchIntoAvl(graph,(void *)&gPair,vertexComparator);
shouldAppend=0;
if(graphPair==NULL) 
{
printf("Want to enter more adjacent city to %s(0/1):",name);
scanf("%d",&flg);
while((m=getchar())!='\n');
if(flg!=1) break;
}
printf("Want to enter more adjacent city to %s(0/1):",name);
scanf("%d",&flg);
while((m=getchar())!='\n');
if(flg!=1) break;
} 
}

//MARKER
void removeAdjacentVertex()
{
char name[100],advName[100],m;
Data d,*city,advC,*advCity;
AVL *advTree;
Pair gPair,*graphPair,*advP,p;
FILE *graphFile;
int cityCode,flg,shouldAppend,advCode,weight,succ,*wgt;
printf("Enter city against you want to remove adjacent cities:");
fgets(name,100,stdin);
if(name[strlen(name)-1]!='\n')
{
while((m=getchar())!='\n');
}
name[strlen(name)-1]='\0';
strcpy(d.cityName,name);
city=(Data *)searchIntoAvl(cityNames,(void *)&d,stringComparator);
if(city==NULL) 
{
printf("%s city does not exists\n");
return;
}
Pair *e;
Data *f;
Pair z;
z.first=(void *)city;
Pair *temp=(Pair *)searchIntoAvl(graph,(void *)&z,vertexComparator);
if(temp!=NULL)
{
AVL *av=(AVL *)temp->second;
printf("Adjacent cities against %s city\n",name);
AVLInOrderIterator iter=getAVLInOrderIterator(av,&succ);
if(succ)
{
while(hasMoreElementAVLInOrder(&iter))
{
e=(Pair *)getElementFromAVLInOrderIterator(&iter,&succ);
f=(Data *)e->first;
int *distance=(int *)e->second;
printf("city :%s , Distance :%d \n",f->cityName,*distance);
}
}
}
cityCode=city->cityCode;
gPair.first=(void *)city;
graphPair=(Pair *)searchIntoAvl(graph,(void *)&gPair,vertexComparator);
advTree=(AVL *)graphPair->second;
while(1)
{
printf("Enter Adjacent city u want remove from %s:",name);
fgets(advName,100,stdin);
if(advName[strlen(advName)-1]!='\n')
{
while((m=getchar())!='\n');
}
advName[strlen(advName)-1]='\0';
strcpy(advC.cityName,advName);
p.first=(void *)&advC;
advP=(Pair *)searchIntoAvl(advTree,(void *)&p,adjacentVertexComparator);
if(advP==NULL) 
{
printf("%s city is does not exists as adjacent city to %s\n",advName,name);
printf("Want to delete another city to %s(0/1):",name);
scanf("%d",&flg);
while((m=getchar())!='\n');
if(flg!=1) break;
continue;
}
removeFromAVL(advTree,(void *)&p,&succ,adjacentVertexComparator);
AVLInOrderIterator iter=getAVLInOrderIterator(graph,&succ);
FILE *f=fopen("graph.dat","wb");
int suc;
if(succ)
{
while(hasMoreElementAVLInOrder(&iter))
{
Pair *dfs=(Pair *)getElementFromAVLInOrderIterator(&iter,&succ);
Data *ds=(Data *)dfs->first;
fprintf(f,"%d,",ds->cityCode);
AVL *e=(AVL *)dfs->second;
AVLInOrderIterator it=getAVLInOrderIterator(e,&suc);
if(suc)
{
while(hasMoreElementAVLInOrder(&it))
{
Pair *kfs=(Pair *)getElementFromAVLInOrderIterator(&it,&suc);
Data *gd=(Data *)kfs->first;
int *dd=(int  *)kfs->second;
if(hasMoreElementAVLInOrder(&it)) fprintf(f,"%d,%d,",gd->cityCode,*dd);
else fprintf(f,"%d,%d#",gd->cityCode,*dd);
}
}
}
fclose(f);
}
printf("%s city is successfully deleted from adjacent city to %s\n",advName,name);
printf("Want to delete another city to %s(0/1):",name);
scanf("%d",&flg);
while((m=getchar())!='\n');
if(flg!=1) break;
continue;
}
}
void editAdjacentVertex()
{
char name[100],advName[100],newName[100],m;
Data d,*city,advC,*advCity;
AVL *advTree;
Pair gPair,*graphPair,*advP,p;
FILE *graphFile;
int cityCode,flg,shouldAppend,advCode,weight,succ,*wgt;
printf("Enter city against you want to update adjacent cities:");
fgets(name,100,stdin);
if(name[strlen(name)-1]!='\n')
{
while((m=getchar())!='\n');
}
name[strlen(name)-1]='\0';
strcpy(d.cityName,name);
city=(Data *)searchIntoAvl(cityNames,(void *)&d,stringComparator);
if(city==NULL) 
{
printf("%s city does not exists\n");
return;
}
Pair *e;
Data *f;
Pair z;
z.first=(void *)city;
Pair *temp=(Pair *)searchIntoAvl(graph,(void *)&z,vertexComparator);
if(temp!=NULL)
{
AVL *av=(AVL *)temp->second;
printf("Adjacent cities against %s city\n",name);
AVLInOrderIterator iter=getAVLInOrderIterator(av,&succ);
if(succ)
{
while(hasMoreElementAVLInOrder(&iter))
{
e=(Pair *)getElementFromAVLInOrderIterator(&iter,&succ);
f=(Data *)e->first;
int *distance=(int *)e->second;
printf("city :%s , Distance :%d \n",f->cityName,*distance);
}
}
}
cityCode=city->cityCode;
gPair.first=(void *)city;
graphPair=(Pair *)searchIntoAvl(graph,(void *)&gPair,vertexComparator);
advTree=(AVL *)graphPair->second;
while(1)
{
printf("Enter Adjacent city u want update from %s:",name);
fgets(advName,100,stdin);
if(advName[strlen(advName)-1]!='\n')
{
while((m=getchar())!='\n');
}
advName[strlen(advName)-1]='\0';
strcpy(advC.cityName,advName);
p.first=(void *)&advC;
advP=(Pair *)searchIntoAvl(advTree,(void *)&p,adjacentVertexComparator);
if(advP==NULL) 
{
printf("%s city is does not exists as adjacent city to %s\n",advName,name);
printf("Want to update another city to %s(0/1):",name);
scanf("%d",&flg);
while((m=getchar())!='\n');
if(flg!=1) break;
continue;
}
printf("Enter new city name:");
fgets(newName,100,stdin);
if(newName[strlen(newName)-1]!='\n')
{
while((m=getchar())!='\n');
}
newName[strlen(newName)-1]='\0';
strcpy(d.cityName,newName);
advCity=(Data *)searchIntoAvl(cityNames,(void *)&d,stringComparator);
if(advCity==NULL)
{
printf("%s is a invalid city",newName);
printf("Want to enter another city to %s(0/1):",newName);
scanf("%d",&flg);
while((m=getchar())!='\n');
if(flg!=1) break;
continue;
}
printf("Enter weight of new city from %s:",newName);
scanf("%d",&weight);
while((m=getchar())!='\n');
if(weight<=0)
{
printf("%d is a invalid weight\n",weight);
printf("Want to enter another weight to %s(0/1):",newName);
scanf("%d",&flg);
while((m=getchar())!='\n');
if(flg!=1) break;
continue;
}
printf("Save(0/1):");
scanf("%d",&flg);
while((m=getchar())!='\n');
if(flg!=1) break;
removeFromAVL(advTree,(void *)&p,&succ,adjacentVertexComparator);
Pair *advP=(Pair *)malloc(sizeof(Pair));
advP->first=(void *)advCity;
wgt=(int *)malloc(sizeof(int));
*wgt=weight;
advP->second=(void *)wgt;
insertIntoAVL(advTree,0,(void *)advP,&succ,adjacentVertexComparator);
AVLInOrderIterator iter=getAVLInOrderIterator(graph,&succ);
FILE *f=fopen("graph.dat","wb");
int suc;
if(succ)
{
while(hasMoreElementAVLInOrder(&iter))
{
Pair *dfs=(Pair *)getElementFromAVLInOrderIterator(&iter,&succ);
Data *ds=(Data *)dfs->first;
fprintf(f,"%d,",ds->cityCode);
AVL *e=(AVL *)dfs->second;
AVLInOrderIterator it=getAVLInOrderIterator(e,&suc);
if(suc)
{
while(hasMoreElementAVLInOrder(&it))
{
Pair *kfs=(Pair *)getElementFromAVLInOrderIterator(&it,&suc);
Data *gd=(Data *)kfs->first;
int *dd=(int  *)kfs->second;
if(hasMoreElementAVLInOrder(&it)) fprintf(f,"%d,%d,",gd->cityCode,*dd);
else fprintf(f,"%d,%d#",gd->cityCode,*dd);
}
}
}
fclose(f);
}
printf("%s city is successfully deleted from adjacent city to %s\n",advName,name);
printf("Want to update another city to %s(0/1):",name);
scanf("%d",&flg);
while((m=getchar())!='\n');
if(flg!=1) break;
continue;
}
}
int main()
{
int succ;
cityNames=populateAvlTree(stringComparator);
cityCodes=populateAvlTree(IntComparator);
populateGraph();
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
if(ch2==7) addAdjacentVertex();
if(ch2==8) removeAdjacentVertex();
if(ch2==9) editAdjacentVertex();
if(ch2==10) break;
}
}
if(ch1==3) break;
}
return 0;
 }