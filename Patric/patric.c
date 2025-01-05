#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <pthread.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <semaphore.h>
#include <limits.h>
#include "triangle.h"

/*
To compile patric, you need to compile triagle.c and your patric source file first, then link them:

gcc -o triangle.o triangle.c -c
gcc -o patric.o patric.c -c -pthread -Wall -Werror
gcc -o patric triangle.o patric.o -pthread -Wall -Werror

This can also be done in a single command:

gcc -o patric triangle.c patric.c -pthread -Wall -Werror

*/




// The shared state in our concurrent scenario
struct state {
  int boundary, interior;

  int active, finished;
} state;

sem_t thread_counter, mutex, update;


/**
 * @brief Callback function for the countPoints() function of triangle.h.
 * This function should increment the number of found points by the given amount and signal the
 * output thread to update the progress report on stdout.
 * @param boundary Found points on the boundary of the triangle
 * @param interior Found points in the interior of the triangle
 */
static void calc_finished_cb(int boundary, int interior){

  sem_wait(&mutex);
  state.boundary += boundary;
  state.interior += interior;
  sem_post(&mutex);

  //signal printer thread
  sem_post(&update);

};

/**
*\brief Start routine of our worker threads of this problem.
* Remember the threads are meant to run detached.
* This has the advantage that no join is necessary but 
* you need to bookkeep yourself if a thread has finished its workload.
* @param param the param of our worker threads - a pointer to the triangle struct to be counted
*/
static void *worker(void *tri){
  sem_wait(&mutex);
  state.active += 1;
  sem_post(&mutex);

  countPoints(tri, calc_finished_cb);

  sem_wait(&mutex);
  state.active -= 1;
  state.finished += 1;
  sem_post(&mutex);

  free(tri);

  sem_post(&thread_counter);

  return NULL;
};

/**
*\brief Start routine of the thread that is meant to present the results.
**/
static void * printer(){
  //printf("printer started\n");
  
  while(true){
    //logic to only print when an worker thread finishes
    //printf("\r");
    sem_wait(&update);

    struct state* snap = malloc(sizeof(struct state));

    sem_wait(&mutex);
    //grab global variables
    snap->boundary = state.boundary;
    snap->interior = state.interior;
    snap->active   = state.active;
    snap->finished = state.finished;
    sem_post(&mutex);
    // something with "\r"? to make it update?
    printf("Found %d boundary and %d interior points, %d active threads, %d finished threads\n",snap->boundary,snap->interior,snap->active,snap->finished);
    free(snap);
  }
  return NULL; //thread will be killed when main() exits
};



int main(int argc, char * argv[]) {
  if(argc != 2){
    printf("wrong number of args. Usage: %s <maximum number of worker threads>\n", argv[0]);
    perror("wrong args");
    exit(EXIT_FAILURE);
    }
  int max_threads = atoi(argv[1]);
  if (max_threads < 1){
    perror("invalid number of threads");
    exit(EXIT_FAILURE);
  }
  pthread_t thread, output;  //we only need one local "worker" thread variable because the threads are detached
  
  sem_init(&thread_counter, 0, max_threads); // semaphore for keeping threads under specified limit
  sem_init(&update, 0, 0); // semaphore for signaling the printer thread to output starts locked
  sem_init(&mutex, 0, 1); // ensure mutual exclusivity of access to global state struct, initially free
  struct state state = {0,0,0,0};

  bool run = true;

  //start and detach output/printer thread:
  pthread_create(&output,NULL,printer, NULL);
  pthread_detach(output);
  

  //printf("enter triangle:\n");
  while(run){
    struct triangle* tri = malloc(sizeof(struct triangle)); // this needs to be per thread, malloc and inside loop?
    if (!tri){
      perror("malloc failed");
      exit(EXIT_FAILURE);
    }

    if (scanf("(%d,%d),(%d,%d),(%d,%d)",
          &tri->point[0].x, &tri->point[0].y,
          &tri->point[1].x, &tri->point[1].y,
          &tri->point[2].x, &tri->point[2].y ) == 6)
      {
      while (getchar() != '\n'); //clear buffer
      //printf("triangle parsed!\n"); 
      //check threadcount is not exceeded
      sem_wait(&thread_counter);
      //create & detach worker
      pthread_create(&thread,NULL,worker,tri);
      pthread_detach(thread);

      } else {
            if(feof(stdin)){
              printf("EOF detected\n");
              run = false;
            } else {
            printf("invalid input! format: (<x_1>,<y_1>),(<x_2>,<y_2>),(<x_3>,<y_3>)\n");
            while (getchar() != '\n'); //clear buffer
            }
      }
  }
  
  sem_destroy(&thread_counter);
  sem_destroy(&mutex);
  sem_destroy(&update);
  return EXIT_SUCCESS;
}
