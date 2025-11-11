#include<heap.h>
#include<stdio.h>
Heap *createHeap(bool  *success,int (*comparator)(void *,void *))
{
if(success) *success=false;
bool succ;
Heap *heap=(Heap *)malloc(sizeof(Heap));
if(heap==NULL) return NULL;
heap->array=createArray(&succ);
if(succ==false)  return heap;
if(comparator==NULL) 
{
free(heap);
return NULL;
}
heap->comparator=comparator;
heap->size=0;
if(success) *success=true;
return heap;
}
void addToHeap(Heap *heap,void *elem,bool *success)
{
if(success) *success=false;
bool succ;
if(heap==NULL) return;
if(elem==NULL) return;
setElementIntoArray(heap->array,heap->size,elem);  // always do add at end
heap->size++;
void *ciValue,*riValue;
int ri,ci=heap->size-1;
while(ci>0)
{
ri=(ci-1)/2;
ciValue=getElementFromArray(heap->array,ci);
riValue=getElementFromArray(heap->array,ri);
int res=heap->comparator(ciValue,riValue);
if(res<0) 
{
setElementIntoArray(heap->array,ri,ciValue);
setElementIntoArray(heap->array,ci,riValue);
ci=ri;
}
else break;
}
if(success) *success=true;
return;
}
void *removeFromHeap(Heap *heap,bool *success)
{
if(success) *success=false; 
if(heap==NULL) return NULL;
if(heap->size==0) return NULL;
int lci,rci,ri,swi,ub,res;
void *lciValue,*rciValue,*swiValue,*riValue,*ansElem,*elem2;
ansElem=getElementFromArray(heap->array,0);
elem2=getElementFromArray(heap->array,heap->size-1);  // remove from end
setElementIntoArray(heap->array,0,elem2); // swap(arr[lb],arr[ub]) , size--
heap->size--;
ri=0;
ub=heap->size-1;
while(ri<ub)
{
lci=(ri*2)+1;
rci=lci+1;
if(lci>ub) break;
if(rci>ub) swi=lci;
lciValue=getElementFromArray(heap->array,lci);
rciValue=getElementFromArray(heap->array,rci);
res=heap->comparator(lciValue,rciValue);
if(res<0) swi=lci;
else swi=rci;
swiValue=getElementFromArray(heap->array,swi);
riValue=getElementFromArray(heap->array,ri);
res=heap->comparator(swiValue,riValue);
if(res<0) 
{
setElementIntoArray(heap->array,swi,riValue);
setElementIntoArray(heap->array,ri,swiValue);
ri=swi;
}
else break;
}
if(success) *success=true;
return ansElem;
}
void *elementAtTopOfHeap(Heap *heap,bool *success)
{
if(success) *success=false;
if(heap==NULL) return NULL;
if(heap->size==0) return NULL;
return getElementFromArray(heap->array,0);
}
int getSizeOfHeap(Heap *heap)
{
if(heap==NULL) return 0;
return heap->size;
}
void destroyHeap(Heap *heap,bool *success)
{
if(heap==NULL) return;
if(heap->array==NULL) return;
if(success) *success=false;
bool succ;
destroyArray(heap->array,&succ);
if(succ==false) return;
free(heap);
if(success) *success=true;
return;
}
void updateElementInHeap(Heap *heap,int index,void *elem,bool *success)
{
if(success) *success=false;
if(heap==NULL || elem==NULL) return;
if(index<0 || index>=heap->size) return;
setElementIntoArray(heap->array,index,elem);
if(success) *success=true;
return;
}