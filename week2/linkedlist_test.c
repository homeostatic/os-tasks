#include <LinkedList.h>
#include <stdio.h>
#include <stdlib.h>

// Function to create a new node
// Return a pointer to the node
// Exit if allocation fails.
struct Node* createNode(struct Data data){
    struct Node* cData = malloc( sizeof(data));
    if (!cData){
        perror("malloc failed");
        exit(1);
    }
    //struct Node* p =  &cData;
    cData->data = data;
    return cData;
    }


void initializeDoublyList(struct DoublyLinkedList* list){
    
    // struct DoublyLinkedList newlist;
    // newlist.first = NULL;
    // newlist.last = NULL;
    // list = &newlist;

    list->first = NULL;
    list->last = NULL;
        
    //list->length = 0; 
    }

void freeDoublyList(struct DoublyLinkedList* list){
    // for all nodes in list run free()

    struct Node* node = list->first; //begin with list.first
    while (node){
        struct Node* next = node->next; //read node.next
        free(node); //free node
        node = next; // set node to next
        }
        //list->length = 0; 
    }

void printListForward(const struct DoublyLinkedList* list){
    struct Node* node = list->first;
    while (node){
        struct Data data = node->data;
        int id = data.id;
        int length = data.length;
        printf("ID: %d, Length: %d \n", id, length);
        node = node->next;
        }
    }

void printListReverse(const struct DoublyLinkedList* list){
    struct Node* node = list->last;
    while (node){
        //struct Data data = node->data;
        //int id = data.id;
        //int length = data.length;
        printf("ID: %d, Length: %d \n", node->data.id, node->data.length);
        node = node->prev;
        }
    
    }


// Function to insert a node at the end of the doubly-linked list
// A list cannot be full so this operation theoretically cannot fail.
void append(struct DoublyLinkedList* list, struct Data data){
    struct Node* newnode = createNode(data);
    if (!(list->last)){
        //list is empty == first = last = newnode
        list->first = newnode;
        list->last = newnode;
        }else{
        //list not empty 
        list->last->next = newnode; //link forward
        newnode->prev = list->last; // link backward
        list->last = newnode;       //end of list update
        }
    }


// Function to insert a node at the head of the doubly-linked list
void appendLeft(struct DoublyLinkedList* list, struct Data data){
    struct Node* newnode = createNode(data);
    if (!(list->last)){
        //list is empty == first = last = newnode
        list->first = newnode;
        list->last = newnode;
        }else{
        //list not empty 
        list->first->prev = newnode; //link forward
        newnode->next = list->first; // link backward
        list->first = newnode;       //end of list update
        }
    }

// Pops the current head of the linked list
// Stores the popped data in the variable pointed to by popped
// Return 0 if the popping worked, 1 if 
// you tried to pop from an empty list (do not exit)
int pop(struct DoublyLinkedList* list, struct Data* popped){

    // list with 1 element??

    // free(oldhead)

    if(!(list->first)){
        //list is empty
        return 1;
        }

    if(list->first == list->last){
        // list is 1 element long
        *popped = list->first->data;
        free(list->first);
        list->first = NULL;
        list->last = NULL;

        return 0;
        }
    *popped = list->first->data;
    // make a temporary copy of first->next pointer
    struct Node* newhead = list->first;
    free(list->first);
    list->first = newhead;

    return 0;
    }

struct Data createData(int n){
    struct Data* data = malloc(sizeof(struct Data));
    if(!data){
        perror("malloc failed during data creation");
        exit(1);
        }
    data->id = n;
    data->length = n*10;
    return *data;
    }


int main(){
    // test pad for the LinkedList.h header written for assignment 1.5 of OS WS24/25 

    //create and init a dll
    struct DoublyLinkedList* mylist; 
    initializeDoublyList(mylist);

    //append and print various things
    append(mylist, createData(5));
    printListForward(mylist);
    printf("\n");
    appendLeft(mylist, createData(10));
    printListForward(mylist);
    printf("\n");
    append(mylist, createData(1));
    printListForward(mylist);
    printf("\n");
    printListReverse(mylist);
    printf("\n");
    appendLeft(mylist, createData(7));
    printListForward(mylist);
    printf("\n");

    //create struct for storing popped data
    struct Data pdata;

    int p = pop(mylist, &pdata);

    //gdb 

    return 0;

};