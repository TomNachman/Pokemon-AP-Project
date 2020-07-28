//
// Created by tom on 15.12.2019.
//
#include "BattleByCategory.h"

struct battle_s{
    LinkedList list;
    int numberOfCategories;
    char* categories;
    char** myCategories;
    equalFunction equalFunc;
    copyFunction copyFunc;
    freeFunction freeFunc;
    getCategoryFunction getCatFunc;
    getAttackFunction getAttFunc;
    printFunction printFunc;
};

/** Function that have no declaration in the header file */
// This is The free function of the LinkedList,when calling this function it calls the DestroyHeap Function
static status freeHeap(element elem){
    return destroyHeap(elem);
}
// This is the print function of the LinkedList, when calling this function it calls the PrintHeap Function
static status printElem(element elem)
{
    return printHeap(elem);
}

// This is the copy function of the LinkedList, when calling this function it calls the CopyHeap Function
static element heapCopy(element elem)
{
    return copyHeap((MaxHeap)elem);
}

// Function compare between names: used in LinkedList to compare between 2 maxHeap names.
static int compNames(element elem1,element elem2)
{
    char tmp = ((char*)elem2)[0];
    if((tmp >= 'A' && tmp<='Z') || (tmp>='a' && tmp<= 'z')) {
        if (strcmp(getHeapId(elem1), (char *) elem2) == 0) {
            return 0;
        }
        return 1;
    }
    if(strcmp(getHeapId(elem1), getHeapId(elem2)) == 0) {
        return 0;
    }
    return 1;
}


/** Function that have declaration in the header file */
//Create the Battle struct
Battle createBattleByCategory(int capacity,int numberOfCategories,char* categories,equalFunction equalElement,
                              copyFunction copyElement,freeFunction freeElement,getCategoryFunction getCategory,getAttackFunction getAttack,printFunction printElement) {
    if (equalElement == NULL || copyElement == NULL || freeElement == NULL || getCategory == NULL ||
        getAttack == NULL || printElement == NULL) {
        puts("Functions Not Available");
        return NULL;
    }

    Battle newBattle = (Battle) malloc(sizeof(struct battle_s));
    if (newBattle == NULL) {
        puts("No memory available"
             "");
        return NULL;
    }

    // new Linked list for the pokemons heaps
    newBattle->list = createLinkedList(heapCopy, freeHeap, printElem, compNames);
    if (newBattle->list == NULL) {
        destroyBattleByCategory(newBattle);
        puts("list is NULL");
        return NULL;
    }


    char** my_Categories = (char**)malloc(numberOfCategories*(sizeof(char*)));
    if(my_Categories ==  NULL){
        puts("no memory available");
        return NULL;
    }

    MaxHeap* heaps = (MaxHeap*) malloc(sizeof(MaxHeap)*numberOfCategories);
    char *catName;
    char *name;


    if (numberOfCategories == 1) {
        catName = strtok(categories, "\r\n");
        name = (char *) malloc(sizeof(strlen(catName))+1);
        my_Categories[0] = (char*)malloc(sizeof(strlen(catName))+1);
        strcpy(name, catName);
        strcpy(my_Categories[0],catName);
        heaps[0] = createHeap(name, capacity , copyElement, freeElement, printElement, equalElement);
        free(name);
        name=NULL;
    }

    if (numberOfCategories == 2) {
        catName = strtok(categories, ",");
        name = (char *) malloc(sizeof(strlen(catName) )+1);
        my_Categories[0] = (char*)malloc(sizeof(strlen(catName))+1);
        strcpy(name, catName);
        strcpy(my_Categories[0],catName);
        heaps[0] = createHeap(name, capacity , copyElement, freeElement, printElement, equalElement);
        free(name);
        name = NULL;

        catName = strtok(NULL, "\r\n");
        name = (char *) malloc(sizeof(strlen(catName))+1);
        my_Categories[1] = (char*)malloc(sizeof(strlen(catName))+1);
        strcpy(name, catName);
        strcpy(my_Categories[1],catName);
        heaps[1] = createHeap(name, capacity , copyElement, freeElement, printElement, equalElement);
        free(name);
        name=NULL;
    }
    if(numberOfCategories>=3){
        catName = strtok(categories, ",");
        name = (char *) malloc(sizeof(strlen(catName) )+1);
        my_Categories[0] = (char *) malloc(sizeof(strlen(catName))+1);
        strcpy(name, catName);
        strcpy(my_Categories[0], catName);
        heaps[0] = createHeap(name, capacity, copyElement, freeElement, printElement, equalElement);
        free(name);
        name = NULL;


        for (int i = 1; i < numberOfCategories - 1; i++) {

            catName = strtok(NULL, ",");
            name = (char *) malloc(sizeof(strlen(catName))+1);
            my_Categories[i] = (char *) malloc(sizeof(strlen(catName))+1);
            strcpy(name, catName);
            strcpy(my_Categories[i], catName);
            heaps[i] = createHeap(name, capacity, copyElement, freeElement, printElement, equalElement);
            free(name);
            name = NULL;
        }

        catName = strtok(NULL, "\r\n");
        name = (char *) malloc(sizeof(strlen(catName))+1);
        my_Categories[numberOfCategories - 1] = (char *) malloc(sizeof(strlen(catName))+1);
        strcpy(name, catName);
        strcpy(my_Categories[numberOfCategories - 1], catName);
        heaps[numberOfCategories - 1] = createHeap(name, capacity, copyElement, freeElement, printElement,
                                                   equalElement);
        free(name);
        name = NULL;
    }

    for(int i = 0; i<numberOfCategories; i++)
    {
        status addNode = appendNode(newBattle->list, (element)heaps[i]);
        if(addNode==failure)return NULL;
        destroyHeap(heaps[i]);
    }

    newBattle->numberOfCategories = numberOfCategories;
    newBattle->categories = categories;
    newBattle->myCategories = my_Categories;
    newBattle->copyFunc = copyElement;
    newBattle->freeFunc = freeElement;
    newBattle->printFunc = printElement;
    newBattle->equalFunc = equalElement;
    newBattle->getAttFunc = getAttack;
    newBattle->getCatFunc = getCategory;
    free(heaps);

    return newBattle;
}

//This Function Destroy the given battle and returns status
status destroyBattleByCategory(Battle b)
{
    if(b==NULL)
    {
        return failure;
    }
    destroyList(b->list);
    for(int i=0;i<b->numberOfCategories;i++){
        free(b->myCategories[i]);
    }
    free(b->myCategories);
    free(b);
    return success;
}

//This Function insert an object in to the given battle struct and returns status
status insertObject(Battle b, element elem)
{
    if(b==NULL || elem==NULL)
    {
        puts("No Pointers available");
        return failure;
    }
    element tmp;

    tmp = searchByKeyInList(b->list,(element)b->getCatFunc(elem));
    if(tmp==NULL)
    {
        return failure;
    }
    return insertToHeap((MaxHeap)tmp,elem);
}

//This function prints all the battle elements
void displayObjectsByCategories(Battle b)
{
    if(b==NULL || b->list == NULL){
        puts("No Pointer Legal");
        return;
    }
    displayList(b->list);
}

//This Function removes the max element from a given category in the struct
element removeMaxByCategory(Battle b,char* category)
{
    if(b==NULL || category ==NULL){
        puts("No Pointer available");
        return NULL;
    }

    element tmpHeap = searchByKeyInList(b->list, (element)category);
    if (tmpHeap==NULL)
        return NULL;
    if (getNumberOfObjectsInCategory(b, category)==0)
    {
        printf("There is no Pokemon to remove.\n");
        return NULL;
    }
    element tmpElement = PopMaxHeap((MaxHeap)tmpHeap);
    if(tmpElement==NULL){ return NULL;}
    return tmpElement;
}

//This Function returns the number of category in the struct
int getNumberOfObjectsInCategory(Battle b,char* category)
{
    if(b==NULL || category ==NULL){
        puts("No Pointer available");
        return 0;
    }

    MaxHeap tmpHeap = (MaxHeap)searchByKeyInList(b->list, (element)category);
    if (tmpHeap==NULL)
        return 0;
    return getHeapCurrentSize(tmpHeap);

}

//This Function simulates a battle between given element and strongest elemnt in the battle struct, and returns the winner
element fight(Battle b,element elem)
{
    MaxHeap tmp = NULL;
    element tmpElement= NULL;
    element maxElement = NULL;


    int check;
    int maxAtt1=0,maxAtt2=0;
    int att1, att2;
    int * attP1;
    int * attP2;
    attP1 = &att1;
    attP2 = &att2;

    int maxDiff ; // can return negative!!!!!!!!!!!!!
    char* chosenName;

    if(b->numberOfCategories==0) {return NULL;}

    for(int i=0; i<b->numberOfCategories; i++){
        tmp = (MaxHeap)searchByKeyInList(b->list , (element)b->myCategories[i]);
        if(tmp == NULL) printf("Function Fight: MaxHeap not found\n");

        tmpElement = TopMaxHeap(tmp);
        if(tmpElement!=NULL) {

            check = b->getAttFunc(tmpElement, elem, attP1, attP2);

            if (i == 0) {
                maxElement = b->copyFunc(tmpElement);
                maxDiff = check;
                chosenName = getHeapId(maxElement);
                maxAtt1 = att1;
                maxAtt2 = att2;
            } else {
                if (check > maxDiff) {
                    maxElement = b->copyFunc(tmpElement);
                    maxDiff = check;
                    chosenName = getHeapId(maxElement);
                }
            }
            if ((att1 - att2) > (maxAtt1 - maxAtt2)) {
                maxAtt1 = att1;
                maxAtt2 = att2;
            }
        }
    }
    printf("you choose to fight with:\n");
    b->printFunc(elem);
    if(maxElement==NULL)
    {
        printf("There are no Pokemons to fight against you.\n");
        return NULL;
    }
    printf("The final battle between:\n");
    b->printFunc(elem);
    printf("In this battle the attack is :%d\n\n", maxAtt2);
    printf("against ");
    b->printFunc(maxElement);
    printf("In this battle the attack is :%d\n\n", maxAtt1);


    if(maxDiff>0)
    {
        printf("THE WINNER IS:\n");
        b->printFunc(maxElement);
        b->freeFunc(maxElement);
        return (element)chosenName;
    }

    if(maxDiff==0)
    {
        printf("ITS A DRAW.\n");
        b->freeFunc(maxElement);
        return (element)chosenName;
    }

    else
    {
        printf("THE WINNER IS:\n");

        b->printFunc(elem);
        b->freeFunc(maxElement);
        return elem;
    }
}
