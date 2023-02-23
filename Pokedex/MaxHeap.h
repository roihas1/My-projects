

#ifndef HW3_MAXHEAP_H
#define HW3_MAXHEAP_H
#include "Defs.h"
#include <stdlib.h>
#include <stdio.h>
typedef struct t_MaxHeap *MaxHeap;

MaxHeap CreateHeap(int MaxSize,char *name,copyFunction copyf, freeFunction freef,equalFunction equalf,printFunction printfunc);
status destroyHeap(MaxHeap heap);
status insertToHeap(MaxHeap heap,element elem);
status printHeap(MaxHeap heap);
element PopMaxHeap(MaxHeap heap);
element TopMaxHeap(MaxHeap heap);
char* getHeapId(MaxHeap heap);
int getHeapCurrentSize(MaxHeap heap);
MaxHeap copyHeap(MaxHeap heap);
int equalHeap(MaxHeap heap,MaxHeap heap2);


#endif //HW3_MAXHEAP_H
