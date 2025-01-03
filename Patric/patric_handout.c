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

// The shared state in our concurrent scenario
struct state {
  int boundary, interior;

  int active, finished;
} state;


/**
 * @brief Callback function for the countPoints() function of triangle.h.
 * This function should increment the number of found points by the given amount and signal the
 * output thread to update the progress report on stdout.
 * @param boundary Found points on the boundary of the triangle
 * @param interior Found points in the interior of the triangle
 */
static void calc_finished_cb(int boundary, int interior);

/**
*\brief Start routine of our worker threads of this problem.
* Remember the threads are meant to run detached.
* This has the advantage that no join is necessary but 
* you need to bookkeep yourself if a thread has finished its workload.
* @param param the param of our worker threads
*/
static void *worker(void *param);

/**
*\brief Start routine of the thread that is meant to present the results.
*@param param the param of our thread
**/
static void * printer(void * param);



int main(int argc, char * argv[]) {
  if(argc != 2){
    printf("wrong number of args. Usage: %s <maximum number of worker threads>\n", argv[0]);
    return 0;
    }
  int max_threads = atoi(argv[1]);
  struct triangle tri;
  bool run = true;
  //printf("enter triangle:\n");
  while(run){
  if (scanf("(%d,%d),(%d,%d),(%d,%d)",
          &tri.point[0].x,&tri.point[0].y,
          &tri.point[1].x,&tri.point[1].y,
          &tri.point[2].x,&tri.point[2].y) == 6)
    {
      while (getchar() != '\n'); //clear buffer
      printf("triangle parsed!\n"); 
      //start work

    } else {
            if(feof(stdin)){
              printf("EOF detected\n");
              run = false;
            } else {
            printf("invalid input! format: (<x>,<y>),(<x>,<y>),(<x>,<y>)\n");
            while (getchar() != '\n'); //clear buffer
            }
  }
  }
  return 1;
}
