#ifndef LINKED_LIST
#define LINKED_LIST

// The data that is stored within a node of the doubly-linked list
struct Data {
    int id;
    int length;
};

// Struct for the nodes of the doubly-linked list
struct Node {
    struct Data data;
    struct Node* next;
    struct Node* prev;
};

// Define the structure of the doubly-linked list
struct DoublyLinkedList {
    struct Node* first;
    struct Node* last;
    //int length;
};

// Function to create a new node
// Return a pointer to the node
// Exit if allocation fails.
struct Node* createNode(struct Data data);

// Function to initialize a doubly-linked list with NULL
void initializeDoublyList(struct DoublyLinkedList* list);

// Function to print the doubly-linked list in forward direction
void printListForward(const struct DoublyLinkedList* list);

// Function to print the doubly-linked list in reverse direction
void printListReverse(const struct DoublyLinkedList* list);

// Function to free the memory allocated for the doubly-linked list
void freeDoublyList(struct DoublyLinkedList* list);

// Function to insert a node at the end of the doubly-linked list
// A list cannot be full so this operation theoretically cannot fail.
void append(struct DoublyLinkedList* list, struct Data data);

// Function to insert a node at the head of the doubly-linked list
void appendLeft(struct DoublyLinkedList* list, struct Data data);

// Pops the current head of the linked list
// Stores the popped data in the variable pointed to by popped
// Return 0 if the popping worked, 1 if you tried to pop from an empty list (do not exit)
int pop(struct DoublyLinkedList* list, struct Data* popped);

#endif