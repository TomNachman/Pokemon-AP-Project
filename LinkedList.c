//
// Created by tom on 15.12.2019.
//
#include "LinkedList.h"

struct Node_t {
    element elem;
    Node next;
};
struct LinkedList_t {
    Node head;
    Node tail;
    copyFunction copyF;
    freeFunction  freeF;
    printFunction  printF;
    equalFunction equalF;
    int numOfElements;
};

// This Function create a linked list given all the necessary parameters. return the new linked list.
LinkedList createLinkedList(copyFunction copyf, freeFunction freef, printFunction printf, equalFunction equalf)
{
    //check if all the functions available
    if(copyf==NULL || freef==NULL || printf==NULL || equalf ==NULL){
        puts("Functions not legal");
        return NULL;
    }

    //malloc to the list
    LinkedList list = (LinkedList)malloc(sizeof(struct LinkedList_t));
    if (list==NULL){
        free(list);
        list=NULL;
        return NULL;
    }

    //init list
    list->head = NULL;
    list->tail = NULL;

    list->copyF = copyf;
    list->freeF = freef;
    list->equalF = equalf;
    list->printF = printf;
    list->numOfElements = 0;

    return list;
}

// This Function destroy a given linked list. return Status.
status destroyList(LinkedList list)
{
    if (list==NULL)return success;
    while(list->numOfElements>0){
        Node next = list->head->next;
        deleteNode(list, list->head->elem);
        free(list->head);
        list->head = next;
        list->numOfElements--;
    }
    free(list);
    return success;
    /**
    //check if list exist
    if(list==NULL){
        puts("list not legal");
        return failure;
    }

    Node tmp = list->head;
    Node next;

    while(tmp!=NULL){
        next = tmp->next;
        deleteNode(list, tmp->elem);
        tmp = next;
    }

    list->head = NULL;
    list->tail = NULL;
    free(list);
    return success;*/
}

// This Function add element to a given linked list. return Status.
status appendNode(LinkedList list, element elem) {
    if (list == NULL || elem == NULL) {
        puts("List or Element not legal");
        return failure;
    }

    Node tmp = (Node) malloc(sizeof(struct Node_t));
    if (tmp == NULL) {
        puts("No Memory Available");
        return failure;
    }

    tmp->elem = list->copyF(elem);

    if (tmp->elem == NULL) {
        puts("No Memory Available");
        free(tmp);
        return failure;
    }
    tmp->next=NULL;

    // first insertion
    if (list->head == NULL) {
        list->head = tmp;
        list->tail = tmp;
        list->numOfElements++;
        return success;
    }

    // not first insertion
    list->tail->next = tmp;
    list->tail = tmp;
    list->numOfElements++;
    return success;

}

// This Function delete element to a given linked list. return Status.
status deleteNode(LinkedList list, element elem)
{
    if (list == NULL || elem == NULL) {
        puts("List or Element not legal");
        return failure;
    }
    status freed = list->freeF(elem);
    if (freed == success){
        elem = NULL;
        return success;
    }
    return failure;
}

// This Function display a given linked list. return Status.
status displayList(LinkedList list)
{
    if (list != NULL && list->head != NULL) {
        Node tmp = list->head;
        while(tmp!=NULL){
            list->printF(tmp->elem);
            tmp = tmp->next;
        }
        return success;
    }
    return failure;
}

// This Function search a given element in a given linked list. return this element if found.
element searchByKeyInList(LinkedList list, element elem)
{
    if (list == NULL || elem == NULL) {
        puts("List/Element/function not legal");
        return NULL;
    }
    Node tmp = list->head;
    while(tmp!=NULL){
        if(list->equalF(tmp->elem, elem)==0){
            return (element)tmp->elem;
        }
        tmp = tmp->next;
    }
    return NULL;
}

