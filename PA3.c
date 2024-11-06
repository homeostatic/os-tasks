#include <stdio.h>
#include <stdlib.h>

//PA_3 in OS24/25 - excerise about malloc and creating an array of a dynamic size


int main( int argc, char *argv[]){
    //argc is the number of args passed
    //argv is a list of strings containing args
    if (argc != 2){
        printf("used it wrong");
        return 1;
    }
    //convert first arg to int
    int n = atoi(argv[1]);

    //create and array of size n
    int* arr = malloc(n*sizeof(int));
    if (arr == NULL){
        perror("malloc failed");
        return 1;
    }
    // fill created array with ints 0-n 
    for (int i=0; i<n; i++){
        //*(arr+i) = i;
        arr[i] = i;
    } 

    //read and print array

    for (int i=0; i<n;i++){
        printf("array[%d] = %d\n", i, arr[i]);
    }

    //free allocated memory
    free(arr);

    return 0;

}