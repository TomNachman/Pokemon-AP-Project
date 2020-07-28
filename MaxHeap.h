//
// Created by tom on 15.12.2019.
//

#ifndef POKEMON_MAXHEAP_H
#define POKEMON_MAXHEAP_H
#include "Defs.h"
typedef struct MaxHeap_t *MaxHeap;

MaxHeap createHeap(char*,int ,copyFunction, freeFunction , printFunction , equalFunction );
status destroyHeap(MaxHeap);
status insertToHeap(MaxHeap , element elem);
status printHeap(MaxHeap);
element PopMaxHeap(MaxHeap);
element TopMaxHeap(MaxHeap);
status Heapify(MaxHeap, int);
char* getHeapId(MaxHeap);
int getHeapCurrentSize(MaxHeap);

MaxHeap copyHeap(MaxHeap heap);

#endif //POKEMON_MAXHEAP_H
