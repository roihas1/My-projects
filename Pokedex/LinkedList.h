#ifndef HW3_LINKEDLIST_H
#define HW3_LINKEDLIST_H
#include "Defs.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct t_linkedlist *LinkedList;
typedef element (*searchIfExist)(element ,element);
typedef struct t_Node Node;


LinkedList createLinkedList(copyFunction copyf, freeFunction freef,equalFunction equalf,printFunction printf);
status destroyList(LinkedList list);// destroy every Node and element in it
status appendNode(LinkedList list , element elem);// add Node to the end of the list
status deleteNode(LinkedList list, element elem); // delete a specific Node that have the element
status displayList(LinkedList list);//print the List
element searchByKeyInList(LinkedList list, element elem);
// getters functions
Node* getHeadOfList(LinkedList list);
element getValue(Node* temp);
Node* getNextNode(Node* ptr);





#endif //HW3_LINKEDLIST_H
