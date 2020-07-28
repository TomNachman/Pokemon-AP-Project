//
// Created by tom on 15.12.2019.
//

#ifndef POKEMON_LINKEDLIST_H
#define POKEMON_LINKEDLIST_H
#include "Defs.h"


typedef struct Node_t *Node;
typedef struct LinkedList_t *LinkedList;

LinkedList createLinkedList(copyFunction, freeFunction , printFunction , equalFunction );
status destroyList(LinkedList list);
status appendNode(LinkedList list, element elem);
status deleteNode(LinkedList list, element elem);
status displayList(LinkedList list);
element searchByKeyInList(LinkedList list, element elem);

#endif //POKEMON_LINKEDLIST_H
