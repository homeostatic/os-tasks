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
  int res = 0;
  int* resp = &res;
  
  for (int i = tip->lowerbound; i < (tip->upperbound)-1; i++){
    *resp += tip->arr[i];
  }

  tip->res += res;
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
    
    long* iap = &input_arr;

    //Initialize thread_input struct
    struct Thread_input* t_input = (struct Thread_input*)malloc(sizeof(struct Thread_input));
    t_input->lower_bound = 0;
    t_input->upper_bound = 0;
    t_input->res = 0;
    t_input->arr = iap;

    // Create threads and start their routines
    pthread_t threads[thread_num];
    for (int i = 0; i < local_tnum; i++){
        // Determine bounds of array
        t_input->lower_bound = i*interval;
        t_input->upper_bound = (i+1)*interval;     

        //Try to create thread   
        int ec = pthread_create(&threads[i], NULL, thread_routine, t_input)

        // Check if creating threads failed (pthread_create returns null if successfull, errorcode if not)
        if (ec){
            perror("Creating thread %d failed! Error: %d \n", i, ec);
            return -1;
        }
    }

    // Wait for all threads to finish
    for (int i = 0; i < local_tnum; i++){
        // Check if the join failed
        if (pthread_join(threads[i], NULL)){
            perror("Joining of thread %d failed!\n", i);
            return -1;
        }
    }
}


int main(){
    int test_arr[15];
    int** tap = &test_arr;

    for(int i = 0; i<15; i++){
        *tap[i] = i*12 - 5; 
    }

    printf("Input the number of threads you want to use: \n")
    int t_num = scanf();

    long result = threaded_sum(t_num, testarr, 15)
    if (!result){
    printf("The sum of the given array was: %ld \n", result);
    return 0;
    } else {
        printf("Threaded sum failed, see prior error message. Returning -1.\n")
    }

}