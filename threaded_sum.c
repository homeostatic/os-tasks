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
    long* arr;
} Thread_input;

/* 
\brief The start routine for all our threads
@param tip (thread_input) void pointer as sole argument
@return The start routine has to return a void pointer - just return NULL in this task :)
*/
void* thread_routine(void* tip){
  // cast arguments to an array we can use  
  Thread_input* args = (Thread_input*) tip;  

  
  // work through the array and sum up the assigned range
  for (int i = args->lower_bound; i < (args->upper_bound)-1; i++){
    args->res += args->arr[i];
  }
  
  return NULL;
}

/*
\brief Sums an array in a threaded fashion using a passed number of threads.
@param thread_num the number of threads
@param input_arr The array that has to be summed
@return the sum
*/
long threaded_sum(int thread_num, long input_arr[], size_t array_len){
    int local_tnum = thread_num;
    int* ltmp = &local_tnum;

    // Check if number of threads and array length are > 0
    if (array_len == 0){
        perror("Array has size 0, sum cannot be computed. Aborting! \n");
        return -1;
    }

    if (thread_num == 0){
        perror("Number of threads is 0, sum cannot be computed. Aborting! \n");
        return -1;
    }

    // Adjust thread_num if greater than array_len 
    if (thread_num > array_len){
        *ltmp = array_len;
    }

    // Compute interval for upper and lower bounds for the subarrays
    int interval = array_len/local_tnum;
    
    //long* iap = &input_arr;

    
    //Initialize thread_input struct
    //-> we need an array of these -> moved withing the thread creation loop

    //struct Thread_input* t_input = (struct Thread_input*)malloc(sizeof(struct Thread_input));
    //t_input->lower_bound = 0;
    //t_input->upper_bound = 0;
    //t_input->res = 0;
    //t_input->arr = iap;

    // Create threads and start their routines
    // an array of threads
    pthread_t threads[thread_num];

    //an array of input structs 
    struct Thread_input* t_input[thread_num];

    
    for (int i = 0; i < local_tnum; i++){
        t_input[i] = (struct Thread_input*)malloc(sizeof(struct Thread_input));
        // Determine bounds of array
        t_input[i]->lower_bound = i*interval;
        if (i==local_tnum-1){ 
            t_input[i]->upper_bound = array_len+1;
        }else{
        t_input[i]->upper_bound = (i+1)*interval+1;
        }
        // init result value
        t_input[i]->res = 0;
        // pointer to array of values to sum up
        t_input[i]->arr = input_arr;     

        //Try to create thread   
        int ec = pthread_create(&threads[i], NULL, thread_routine, t_input[i]);

        // Check if creating threads failed (pthread_create returns null if successfull, errorcode if not)
        if (ec){
            char buffer[50];
            sprintf(buffer,"Creating thread %d failed! Error: %d \n", i, ec);
            perror(buffer);
            return -1;
        }
        }
    // return value
    long sum_from_threads;
    
    // Wait for all threads to finish
    for (int i = 0; i < local_tnum; i++){
        // Check if the join failed

        if (pthread_join(threads[i], NULL)){
            char buffer[50];
            sprintf(buffer, "Joining of thread %d failed!\n", i);
            perror(buffer);
            return -1;
        }
        // sum up results
            // this might not be needed, i didn't think of using a single shared result pointer in the input
        sum_from_threads += t_input[i]->res;
        
    }
   
    return sum_from_threads;
}


int main(){
    long test_arr[16];
    //int** tap = &test_arr;

    for(int i = 0; i<16; i++){
        test_arr[i] = (long) 1; 
    }
    int t_num;    
    printf("Input the number of threads you want to use: \n");
    scanf("%d", &t_num);

    long result = threaded_sum(t_num, test_arr, 16);
    printf("The sum of the given array was: %ld \n", result);
    return 0;


}