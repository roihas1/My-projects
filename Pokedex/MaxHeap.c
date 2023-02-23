//
// Created by roihas on 12/10/21.
//
#include "MaxHeap.h"
#include <string.h>
struct t_MaxHeap{
    char *HeapName;
    int maxSize;
    int num_element;
    element *ElemArr;
    copyFunction copyFunc;
    freeFunction FreeFunc;
    equalFunction equalFunc;
    printFunction printFunc;

};

MaxHeap CreateHeap(int MaxSize,char *name,copyFunction copyf, freeFunction freef,equalFunction equalf,printFunction printfunc){
    MaxHeap heap = (MaxHeap) malloc(sizeof(struct t_MaxHeap));
    if(heap == NULL){
        return NULL;
    }
    if(copyf == NULL || freef == NULL || equalf == NULL || printfunc == NULL||name == NULL) {
        free(heap);
        return NULL;
    }
    heap->HeapName = (char *) malloc(strlen(name)+1);
    if(heap->HeapName == NULL){
        free(heap);
        return NULL;
    }
    strcpy(heap->HeapName,name);
    heap->ElemArr = (element*) malloc(sizeof(element)*MaxSize);
    if(heap->ElemArr == NULL){
        free(heap->HeapName);
        free(heap);
        return NULL;
    }
    heap->copyFunc = copyf;
    heap->FreeFunc =freef;
    heap->printFunc = printfunc;
    heap->equalFunc =equalf;
    heap->maxSize = MaxSize;
    heap->num_element = 0;
    return heap;

}
status destroyHeap(MaxHeap heap){
    if(heap == NULL)
        return failure;
    int i;
    for (i=0;i<heap->num_element;i++){
        if(heap->ElemArr[i]!=NULL) {
            heap->FreeFunc(heap->ElemArr[i]);
        }
    }
    free(heap->HeapName);
    free(heap->ElemArr);
    free(heap);
    return success;

}
void exchange(int toElem,int fromElem,MaxHeap heap){
    element temp;
    temp = heap->ElemArr[toElem];
    heap->ElemArr[toElem] = heap->ElemArr[fromElem];
    heap->ElemArr[fromElem] = temp;

}
//heapify the array.
//if one of the node is greater than the father, so it changes  them and so on
void MaxHeapify(int index,MaxHeap heap){
    int left = -1;
    int right = -1;
    int largest = -1;
    if(index == 0){
        left = 1;
        right = 2;
    }
    else {
        left = 2 * index;
        right = 2 * index + 1;
    }
    if(left < heap->num_element) {
        if (heap->equalFunc(heap->ElemArr[left], heap->ElemArr[index]) == 1)
            largest = left;
        else
            largest = index;
    }
    else
        largest = index;
    if(right<heap->num_element) {
        if ( heap->equalFunc(heap->ElemArr[right], heap->ElemArr[largest]) == 1)
            largest = right;
    }
    if(largest != index){
        exchange(index,largest,heap);
        MaxHeapify(largest,heap);
    }

}
status insertToHeap(MaxHeap heap,element elem){

    if(heap == NULL || elem == NULL)
        return emptyPointer;
    if(heap->num_element == 0){
        heap->ElemArr[0] = elem;
        heap->num_element ++;
        return success;
    }
    if(heap->num_element < heap->maxSize){
        heap->ElemArr[heap->num_element] = elem;
        heap->num_element++;
        int i;
        for(i = heap->num_element/2; i> -1 ;i--)
            MaxHeapify(i,heap);
        return success;
    }
    return failure;
}
MaxHeap copyHeap(MaxHeap heap){
    if(heap == NULL )
        return NULL;
    MaxHeap temp = CreateHeap(heap->maxSize,heap->HeapName,heap->copyFunc,heap->FreeFunc,heap->equalFunc,heap->printFunc);
    if(temp == NULL )
        return NULL;
    int i;
    for (i = 0; i < heap->num_element; ++i) {
        element e = heap->ElemArr[i];
        insertToHeap(temp,e);
    }
    return temp;
}

status printHeap(MaxHeap heap){
    if(heap == NULL)
        return emptyPointer;
    if(heap->num_element==0){
        printf("%s:\n",heap->HeapName);
        printf("No elements.\n\n");
        return success;
}
    printf("%s:\n",heap->HeapName);
    int i;
    MaxHeap temp = copyHeap(heap);
    if(temp == NULL )
        return MemoryNull;
    element max;
    for(i=0;i<heap->num_element;i++){
        printf("%d. ",i+1);
        max = PopMaxHeap(temp);
        heap->printFunc(max);
    }
    destroyHeap(temp);
    return success;
}

element PopMaxHeap(MaxHeap heap){
    if(heap == NULL || heap->num_element == 0)
        return NULL;
    element temp;
    temp =heap->ElemArr[0];
    heap->ElemArr[0] = heap->ElemArr[heap->num_element-1];
    heap->num_element--;
    MaxHeapify( 0,  heap);

    return temp;
}
element TopMaxHeap(MaxHeap heap){
    if(heap == NULL || heap->num_element == 0)
        return NULL;
    return heap->copyFunc(heap->ElemArr[0]);
}
char* getHeapId(MaxHeap heap){
    if(heap == NULL)
        return NULL;
    return heap->HeapName;
}
int getHeapCurrentSize(MaxHeap heap){
    if(heap == NULL)
        return -1;
    return heap->num_element;
}
int equalHeap(MaxHeap heap,MaxHeap heap2){
    if(heap == NULL || heap2 == NULL)
        return emptyPointer;
    if(strcmp(heap->HeapName, heap2->HeapName) == 0)
        return  0;
    return -1;
}

