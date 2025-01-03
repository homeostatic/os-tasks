#include <stdio.h>    // IO such as println and puts
#include <stdlib.h>   // malloc, free and more
#include <pthread.h>  // POSIX threads and useful functions for them

/* 
The input for our threads as a struct since thread_create expects exactly one input
 Having a typedef makes it a bit more comfortable to use*/
typedef struct Thread_input{
    // We have to divide the array somehow between all threads
    int lower_bound, upper_bound;
    // Store the result of the computation in res
    long res;
    // The reference to the array
    long *arr;
} Thread_input;

/* 
\brief The start routine for all our threads
@param thread_input void pointer as  sole argument
@return The start routine has to return a void pointer - just return NULL in this task :)
*/
void *thread_routine(void *thread_input){
  // Implement me!
}

/*
\brief Sums an array in a threaded fashion using a passed number of threads.
@param thread_num the number of threads
@param input_arr The array that has to be summed
@return the sum
*/
long threaded_sum(int thread_num, long input_arr[], size_t array_len){
    // Implement me!
}


int main(){
    // Implement me!
}