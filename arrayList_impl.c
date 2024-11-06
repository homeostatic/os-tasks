#include <stdio.h>
#include <stdlib.h>

//implimentation of a dynamically sized array (that resizes when a certain capacity is reached)


struct Arraylist* create_list(int init_cap){
    //assign memory for array
    struct Arraylist *list = malloc(sizeof(struct Arraylist));
    if (!list){
        printf("Allocation failed");
        exit(1);
    }

    //assign parameters of array
    list->capacity = init_cap;
    list->size = 0;

    //content is a struct with ID and length
    list->content = malloc(init_cap * sizeof(struct Data));
    if (!list->content){
        printf("Allocation failed");
        exit(1);
    }

    //initiallise data
    for (int i = 0; i < init_cap; i++){
        list->content[i] = (struct Data){0,0}; 
    }

}

//function to check and resize an arrayList as needed 
int ensure_capacity(struct ArrayList* list, int cap_test) {
    if (cap_test > list->capacity){
        //reallocacte memory
        list = 
        if(!list){
            perror(memory resize failed);
            exit(1);
        }
    }
    

}

;


