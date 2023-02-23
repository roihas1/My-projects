#include "LinkedList.h"

struct t_Node{
    element value;
    struct t_Node *nextNode;
};

struct t_linkedlist{
    Node *head;
    int size;
    copyFunction copyFunc;
    freeFunction FreeFunc;
    equalFunction equalFunc;
    printFunction printFunc;
};
Node *createNode(LinkedList  list,element elem){
    if(list == NULL || elem == NULL)
        return NULL;
    Node *new = (Node*) malloc(sizeof(struct t_Node));
    if(new == NULL )
        return NULL;
    new->value = elem;
    new->nextNode = NULL;
    return new;
}

LinkedList createLinkedList(copyFunction copyf, freeFunction freef,equalFunction equalf,printFunction printf){
    LinkedList list = (LinkedList)malloc(sizeof(struct t_linkedlist));
    if(list == NULL) {
        return NULL;
    }
    if(copyf == NULL|| freef == NULL || equalf == NULL|| printf == NULL)
        return NULL;
    list->equalFunc = equalf;
    list->copyFunc = copyf;
    list->FreeFunc = freef;
    list->printFunc = printf;
    list->size = 0;
    list->head = NULL;

    return list;

}
status destroyNode(LinkedList list,Node *ptr){
    if(list == NULL || ptr == NULL)
        return emptyPointer;
    if(list->FreeFunc(ptr->value) == emptyPointer)
        return emptyPointer;
    free(ptr);
    return success;
}
// deleting all the list and return success if destroy evreything
status destroyList(LinkedList list){
    if(list == NULL)
        return emptyPointer;
    if(list->head->nextNode == NULL){
        destroyNode(list,list->head);
        free(list);
        return success;
    }
    Node *pointer =  list->head;
    Node *next = pointer->nextNode;
    // destroy every node except the head
    while(pointer->nextNode != NULL) {
        next = next->nextNode;
       if( destroyNode(list,pointer->nextNode) == emptyPointer)
           return emptyPointer;
        pointer->nextNode = next;
    }
    destroyNode(list,list->head);
    free(list);
    return success;

}
// append new node with an element to the end of the list
status appendNode(LinkedList list , element elem){
    if(list == NULL || elem == NULL)
        return emptyPointer;
    if(list->head == NULL){
        list->head = createNode(list,elem);
        if(list->head == NULL){
            return MemoryNull;
        }
        list->size++;
        return success;
    }
    Node *ptr = list->head;
    while(ptr->nextNode!=NULL){// get to the of the list
        ptr = ptr->nextNode;
    }
    ptr->nextNode = createNode(list,elem);
    if(ptr->nextNode == NULL){
        return MemoryNull;
    }
    list->size++;
    return success;
}

status deleteNode(LinkedList list, element elem){
    if(list == NULL || elem == NULL)
        return emptyPointer;
    Node *ptr = list->head;
    if(list->equalFunc(ptr->value,elem) == 0){
        list->head = list->copyFunc(ptr->nextNode);
        list->FreeFunc(ptr);
        return success;
    }
    Node *pNext = list->head->nextNode;
    while(ptr != NULL){
            if(list->equalFunc(pNext->value,elem) == 0){
                ptr->nextNode = pNext->nextNode;
                list->FreeFunc(pNext);
                list->size--;
                return success;
            }
            else{
                pNext = pNext->nextNode;
                ptr = ptr->nextNode;
            }

    }
    return failure;
}

status displayList(LinkedList list){
    if(list == NULL)
        return emptyPointer;
    Node *ptr = list->head;
    while(ptr != NULL){
        list->printFunc(ptr->value);
        ptr = ptr->nextNode;
    }
    return success;

}

element searchByKeyInList(LinkedList list, element elem){
    if(list == NULL || elem == NULL)
        return NULL;
    Node *ptr = list->head;
    while(ptr!= NULL){
        int to_return;
        to_return = list->equalFunc(ptr->value, elem);
        if(to_return == -1)
            ptr = ptr->nextNode;
        else
            return ptr->value;
    }
    return NULL;
}

Node *getHeadOfList(LinkedList list){
    if(list == NULL)
        return NULL;
    return list->head;
}
element getValue(Node* temp){
    if(temp == NULL)
        return NULL;
    return temp->value;
}
Node* getNextNode(Node* ptr){
    if(ptr == NULL)
        return NULL;
    return ptr->nextNode;
}
