//
// Created by roihas on 12/10/21.
//
#include "BattleByCategory.h"
#include "LinkedList.h"
#include "MaxHeap.h"
#include <string.h>
struct battle_s{
    int capacity;
    int numOfCategories;
    char **categories;
    LinkedList heapList;
    copyFunction copyFunc;
    freeFunction FreeFunc;
    equalFunction equalFunc;
    printFunction printFunc;
    getCategoryFunction getCategoryFunc;
    getAttackFunction getAttackFunc;

};
Battle createBattleByCategory(int capacity,int numberOfCategories,char* categories,equalFunction equalElement,copyFunction copyElement,freeFunction freeElement,getCategoryFunction getCategory,getAttackFunction getAttack,printFunction printElement){
    Battle battle = (Battle) malloc(sizeof(struct battle_s));
    if(battle == NULL){
        return NULL;
    }
    if(capacity < 1 || numberOfCategories < 1 || categories == NULL || equalElement == NULL || copyElement == NULL || freeElement == NULL ||getCategory == NULL || getAttack == NULL || printElement == NULL){
        free(battle);
        return NULL;
    }

    battle->capacity = capacity;
    battle->numOfCategories = numberOfCategories;
    battle->heapList =createLinkedList((copyFunction) copyHeap, (freeFunction) destroyHeap, (equalFunction) equalHeap,
                                       (printFunction) printHeap);
    if(battle->heapList == NULL){
        free(battle->categories);
        free(battle);
        return NULL;
    }

    int i;
    char *temp;
//insert to every Node-> value a heap for storing the pokemons
    temp = strtok(categories,",\n\r");
    for ( i = 0; i < numberOfCategories; ++i) {
        MaxHeap heap = CreateHeap(capacity, temp,copyElement,freeElement,equalElement,printElement);
        if (heap == NULL){
            free(battle->heapList);
            free(battle);
            return NULL;
        }
        appendNode(battle->heapList,heap);
        temp = strtok(NULL,",\n\r");

    }

    battle->equalFunc = equalElement;
    battle->FreeFunc = freeElement;
    battle->copyFunc = copyElement;
    battle->printFunc = printElement;
    battle->getAttackFunc = getAttack;
    battle->getCategoryFunc = getCategory;
    return battle;
}
// deleting all the structure that battle has.
status destroyBattleByCategory(Battle b){
    if (b == NULL)
        return emptyPointer;
    if (destroyList(b->heapList) == emptyPointer)
        return failure;
    free(b);
    return success;

}
//insert new pokemon to his category heap.
status insertObject(Battle b, element elem){
    if (b == NULL || elem == NULL)
        return emptyPointer;
   Node *temp = getHeadOfList(b->heapList);
   while( temp != NULL){
       if(strcmp(getHeapId(getValue(temp)),b->getCategoryFunc(elem)) == 0 ){
           if(getHeapCurrentSize(getValue(temp)) < b->capacity) {
               if (insertToHeap(getValue(temp), elem) != success)
                   return failure;
               else
                   return success;
           }
           else
               return failure;
       }
       else
           temp = getNextNode(temp);

   }
   return failure;
}
// printing all pokemons in the battle camp
void displayObjectsByCategories(Battle b){
    if(b == NULL)
        return;
    Node *temp = getHeadOfList(b->heapList);
    while(temp != NULL){
        printHeap(getValue(temp));
        temp = getNextNode(temp);
    }
}
// get to the heap with the name, and deleting the strongest pokemon from it.
element removeMaxByCategory(Battle b, char* category){
    if(b == NULL || category == NULL)
        return NULL;
    Node * temp = getHeadOfList(b->heapList);
    element e;
    while(temp != NULL){
        if(strcmp(getHeapId(getValue(temp)),category) == 0 && getHeapCurrentSize(getValue(temp)) != 0){
            e = PopMaxHeap(getValue(temp));

            return e;
        }
        else
            temp = getNextNode(temp);
    }
    return NULL;
}
// get to the right Node where the heap name is what we get in category, and return the number of pokemon in the MaxHeap
int getNumberOfObjectsInCategory(Battle b,char* category){
    if(b == NULL || category == NULL)
        return -1;
    Node* temp = getHeadOfList(b->heapList);
    while(temp != NULL){
        if(strcmp(getHeapId(getValue(temp)),category) == 0){
            return getHeapCurrentSize(getValue(temp));
        }
        else
            temp = getNextNode(temp);
    }
    return -1;
}
/*  getting a pokemon, searching  the strongest pokemon from the battle camp to fight against him*/
element fight(Battle b,element elem) {
    if (b == NULL || elem == NULL || b->numOfCategories == 0)
        return NULL;
    Node* temp = getHeadOfList(b->heapList);
    element *arr_elem = (element*) malloc(sizeof(element)*b->numOfCategories);
    int i =0;
    // storing the strongest pokemon from each category
    while(temp != NULL){
        element e =TopMaxHeap(getValue(temp));
        arr_elem[i]= e;
        temp = getNextNode(temp);
        i++;
    }
    int max ;
    int temp2;
    int attack_first ;
    int attack_second ;
    int max_arr[b->numOfCategories];
    int index_of_max=0;
    int attack_first_max=0 ;
    int attack_second_max=0;
    temp2 = b->getAttackFunc(elem, arr_elem[0], &attack_first, &attack_second);//check the first max element
    max_arr[0] = temp2;
    max = max_arr[0];
    index_of_max = 0;
    attack_first_max = attack_first;
    attack_second_max = attack_second;
    // decide if this is the strongest pokemon  to fight with, if so , storing it in max elem
    for (i=1;i<b->numOfCategories;i++){
        if(arr_elem[i] == NULL)
            continue;
        temp2 = b->getAttackFunc(elem, arr_elem[i], &attack_first, &attack_second);
        max_arr[i] = temp2;
        if( max_arr[i] < max ){
            max = max_arr[i];
            index_of_max = i;
            attack_first_max = attack_first;
            attack_second_max = attack_second;
        }
    }
//  deciding who win in the fight according to the highest attack rate
    element max_element;
    max_element = arr_elem[index_of_max];
    for(i=0 ; i<b->numOfCategories;i++){
        if( i != index_of_max)
            free(arr_elem[i]);
    }
    free(arr_elem);
    printf("The final battle between:\n");
    b->printFunc(elem);
    printf("In this battle his attack is :%d\n\n",attack_first_max);
    printf("against ");
    b->printFunc(max_element);
    printf("In this battle his attack is :%d\n\n",attack_second_max);

    if(attack_first_max > attack_second_max){
        printf("THE WINNER IS:\n");
        b->printFunc(elem);
        free(max_element);
        return elem;
    }
    else if(attack_first_max < attack_second_max){
        printf("THE WINNER IS:\n");
        b->printFunc(max_element);
        return max_element;
    }
    else if(attack_first_max == attack_second_max){
        printf("IT IS A DRAW.\n");
//        b->FreeFunc(max_element);
        free(max_element);
        return elem;
    }

    return NULL;
}


