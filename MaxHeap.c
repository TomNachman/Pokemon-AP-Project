//
// Created by tom on 15.12.2019.
//
#include "MaxHeap.h"
#define LCHILD(x) (int)(2 * x )+ 1
#define RCHILD(x) (int)(2 * x )+ 2
#define PARENT(x) (int)(x-1)/2


// create the struct of the MaxHeap
struct MaxHeap_t {
    char* name;
    element *elements;
    int numOfElements;
    int size;
    copyFunction copyF;
    freeFunction  freeF;
    printFunction  printF;
    equalFunction equalF;
};

// This Function increase the elem to is place.
void increaseKey(MaxHeap heap, element elem){
    if(heap==NULL || elem == NULL){
        puts("increaseKey inValid");
        return;
    }
    int i = heap->numOfElements-1;
    while(i>0 && heap->equalF(heap->elements[PARENT(i)],heap->elements[i])<0){
        element tmp = heap->elements[PARENT(i)];
        heap->elements[PARENT(i)]= heap->elements[i];
        heap->elements[i]=tmp;
        i= PARENT(i);
    }
}

// This Function create new MaxHeap. return the new MaxHeap
MaxHeap createHeap(char* name , int capacity ,copyFunction copyF, freeFunction freeF , printFunction printF , equalFunction equalF)
{
    if( name ==NULL ||copyF == NULL || freeF == NULL || printF ==NULL || equalF == NULL){
        puts("(createHeap)Pointer not available\n");
        return NULL;
    }

    MaxHeap newHeap = (MaxHeap)malloc(sizeof(struct MaxHeap_t));
    if(newHeap==NULL){
        puts("No Memory Available\n");
        return NULL;
    }
    newHeap->elements = (element *) malloc(sizeof(element)*capacity);
    if (newHeap->elements == NULL ){
        puts("No Memory Available\n");
        return NULL;
    }
    char * catname = (char *) malloc(sizeof(strlen(name))+1);
    if (catname == NULL ){
        puts("No Memory Available\n");
        return NULL;
    }

    strcpy(catname,name);
    newHeap->name = catname;
    newHeap->size = capacity;
    newHeap->copyF = copyF;
    newHeap->freeF = freeF;
    newHeap->printF = printF;
    newHeap->equalF = equalF;
    newHeap->numOfElements=0;

    return newHeap;
}

// This Function do heapify to a given MaxHeap and index i. return status.
status Heapify(MaxHeap maxHeap, int i)
{
    if(maxHeap==NULL || i>maxHeap->size){
        puts("Heapify failed\n");
        return failure;
    }
    int largest;
    int left = LCHILD(i);
    int right = RCHILD(i);
    if(left<=maxHeap->numOfElements-1 && maxHeap->equalF(maxHeap->elements[left], maxHeap->elements[i])==1){ largest = left;}
    else {largest = i;}
    if(right<=maxHeap->numOfElements-1 && maxHeap->equalF(maxHeap->elements[right], maxHeap->elements[largest])==1)
    {largest = right; }
    if (largest!=i){
        //swap(maxHeap->elements[i], maxHeap->elements[largest]);
        element tmp = maxHeap->elements[i];
        maxHeap->elements[i] = maxHeap->elements[largest];
        maxHeap->elements[largest] = tmp;
        Heapify(maxHeap, largest);
    }
    return success;
}

// This Function destroy a given MaxHeap. return status.
status destroyHeap(MaxHeap maxHeap)
{
    if(maxHeap==NULL){
        puts("Heap not legal");
        return failure;
    }

    for(int i = 0; i<maxHeap->numOfElements; i++)
    {
        maxHeap->freeF(maxHeap->elements[i]);
        //free(maxHeap->elements[i]);
    }
    free(maxHeap->name);
    free(maxHeap->elements);
    free(maxHeap);
    maxHeap=NULL;
    return success;
}

// This Function insert a given element to a given MaxHeap. return status.
status insertToHeap(MaxHeap maxHeap, element elem)
{
    if(maxHeap==NULL || elem == NULL){
        puts("increaseKey inValid");
        return failure;
    }
    if(maxHeap->numOfElements==maxHeap->size) {
        return failure;
    }
    element newElem = maxHeap->copyF(elem);
    if(newElem == NULL)
        return failure;
    maxHeap->numOfElements++;
    maxHeap->elements[maxHeap->numOfElements-1] = newElem;
    increaseKey(maxHeap,elem);
    return success;
}

// This Function print a given MaxHeap (by order). return status.
status printHeap(MaxHeap maxHeap){

    if(maxHeap==NULL){
        puts("No Heap available\n");
        return failure;
    }
    printf("%s:\n",maxHeap->name);
    if(maxHeap->numOfElements==0){
        printf("No elements.\n\n");
        return success;
    }

    MaxHeap newMaxHeap = copyHeap(maxHeap);
    if(newMaxHeap==NULL){
        puts("copy didn't work");
        return failure;
    }

    int tmp = newMaxHeap->numOfElements;
    for(int i = 0; i<tmp; i++){
        printf("%d.", i+1);
        element elemtodelete;
        elemtodelete = PopMaxHeap(newMaxHeap);
        maxHeap->printF(elemtodelete);
        maxHeap->freeF(elemtodelete);
    }
    destroyHeap(newMaxHeap);
    return success;
}

// This Function return the biggest element in a given MaxHeap (and doesn't delete this element).
element TopMaxHeap(MaxHeap maxHeap)
{
    if(maxHeap==NULL){
        puts("(TopMaxHeap)Pointer not available\n");
        return NULL;
    }

    if(maxHeap->numOfElements==0){
        return NULL;
    }
    return maxHeap->elements[0];
}

// This Function return the biggest element in a given MaxHeap (and delete this element).
element PopMaxHeap(MaxHeap maxHeap)
{
    if(maxHeap==NULL){
        puts("Pointer not available\n");
        return NULL;
    }

    element elemToReturn = maxHeap->copyF(TopMaxHeap(maxHeap));
    maxHeap->freeF(TopMaxHeap(maxHeap));
    maxHeap->elements[0] = NULL;
    if(maxHeap->elements[maxHeap->numOfElements-1]!=NULL) {
        maxHeap->elements[0] = maxHeap->copyF(maxHeap->elements[maxHeap->numOfElements - 1]);
        maxHeap->freeF(maxHeap->elements[maxHeap->numOfElements - 1]);
        maxHeap->elements[maxHeap->numOfElements - 1] = NULL;
    }
    maxHeap->numOfElements--;
    Heapify(maxHeap, 0);

    return elemToReturn;
}

// This Function get a MaxHeap and return the MaxHeap name.
char* getHeapId(MaxHeap maxHeap)
{
    if(maxHeap==NULL){
        puts("Pointer not available\n");
        return NULL;
    }
    return maxHeap->name;
}

// This Function get a MaxHeap and return the number of elements.
int getHeapCurrentSize(MaxHeap maxHeap)
{
    if(maxHeap==NULL){
        puts("Pointer not available\n");
        return 0;
    }

    return maxHeap->numOfElements;
}

// This Function get MaxHeap and return a copy MaxHeap.
MaxHeap copyHeap(MaxHeap heap)
{
    if(heap == NULL)
    {
        puts("heap not legal");
        return NULL;
    }


    MaxHeap newheap;
    newheap = createHeap(getHeapId(heap),heap->size,heap->copyF,heap->freeF,heap->printF,heap->equalF);

    if(newheap == NULL){
        return NULL;
    }

    newheap->numOfElements = heap->numOfElements;

    for(int i=0; i<heap->numOfElements;i++){
        if(heap->elements[i]==NULL) printf("(func copyheap) elem num %d is NULL \n",i);
        newheap->elements[i] = heap->copyF(heap->elements[i]);
    }

    return (element)newheap;
}
