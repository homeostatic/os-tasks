#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <stdbool.h>

// capacity of the pot
const int M = 4;

// number of zerglings
const int Z = 10;

//hunger of each zergling - number of "meals" each needs to finish
const int H = 13;

// Global variable controlling that the cook should keep cooking
static volatile bool keep_cooking;

// acess semaphore for the cooking pot 
sem_t pot_sem; 

// TODO: Model the pot and synchronise the behaviour somehow!
// Hint: Take a look on the global variables of the last exercise sheet's task (but not for the whole synchronisation please)


/**
 * @brief Helper that returns the thread id of the calling thread
 *
 * @return long the thread id as a long
 */
long tid_help() {
    return SYSCALL(SYS_gettid);
}

/**
 * @brief Message that the baby zergling has eaten a portion. Do not change.
 *
 */
void has_eaten(int i) {
    printf("Baby zergling (tid: %li) has eaten its %i-th portion.\n", tid_help(), i + 1);
}

/**
 * @brief Message that a baby zergling tries to get a portion. Do not change.
 *
 */
void try_to_get_portion() {
    printf("Baby zergling (tid: %li) tries to get a portion.\n", tid_help());
}


/**
 * @brief The start routine of a baby zergling
 *
 * @param in
 * @return void*
 */
void* baby_zergling(void* in) {
    // TODO: Synchronisation and pot access 
    for (int eaten = 0; eaten < 13; eaten++) {
        try_to_get_portion();
        has_eaten(eaten);
    }
    return NULL;
}


/**
 * @brief Message that the cook zergling fills the pot. Do not change.
 *
 */
void put_serving_in_the_pot() {
    printf("Cook fills up the pot");
}


/**
 * @brief Start routine for the cook zergling.
 *
 * @param in
 * @return void*
 */
void* cook_zergling(void* in) {
    // TODO: Synchronisation and pot access
    while (keep_cooking) {
        put_serving_in_the_pot();
    }
    printf("Cook finishes cooking and an ultralisk eats the whole remaining pot!\n");
    return NULL;
}

/**
 * @brief Initialises the semaphores
 *
 */
void init_sems() {
    //pot access control
    sem_init(&pot_sem,0,1); //initally free
}

/**
 * destroy semaphores 
 */
void destroy_sems() {
    sem_destroy(&pot_sem);
}

// TODO: Main Function that spawns 10 zergling processes, one cook process and joins all of them in the end. Use keep_cooking for controlling the cook

int main() {

    init_sems();

    //create cook zergling
    pthread_t cook_zergling_t;

    // create Z (10) baby zerglings
    pthread_t baby_zerglings_t[Z];
    for(int z = 0; z < Z; z++){
        int err = pthread_create(&baby_zerglings_t[z],NULL, baby_zergling, NULL);
        if(err){
            perror("baby zergling thread creation failed");
            return -1;
        }
    }


    destroy_sems();
    return 0;
}