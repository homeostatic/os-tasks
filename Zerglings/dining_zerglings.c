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

// access semaphore for the cooking pot and singal for when it is empty
sem_t pot_sem;
sem_t pot_empty;
sem_t pot_full; 

// TODO: Model the pot and synchronise the behaviour somehow!
// Hint: Take a look on the global variables of the last exercise sheet's task (but not for the whole synchronisation please)

volatile int pot = 0;

/**
 * @brief Helper that returns the thread id of the calling thread
 *
 * @return long the thread id as a long
 */
long tid_help() {
    return syscall(SYS_gettid);
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
        sem_wait(&pot_sem);
        /////////////critical///////////////
        if(pot == 0){
            printf("pot empty\n");
            // call the cook
            sem_post(&pot_empty);

            // wait for the refill
            sem_wait(&pot_full);
        }
        pot--;
        has_eaten(eaten);
        printf("pot = %d \n",pot);
        ///////////////////////////////////
        sem_post(&pot_sem);
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
    // the cook is blocked until a baby zergling calls sempost on the pot_empty semaphore,
    // this also means the cook has access to the pot within the critical region of the calling baby
    while (keep_cooking) {
        sem_wait(&pot_empty);
        //////////////critical//////////////////
        //for(int m=0; m<M;m++){
        if(keep_cooking){
            put_serving_in_the_pot();
            pot+=4;
        }
        ///////////////////////////////////////
        //sem_post(&pot_empty);
        sem_post(&pot_full);
    }
    printf("Cook finishes cooking and an ultralisk eats the whole remaining pot!\n");
    pot = 0;
    return NULL;
}

/**
 * @brief Initialises the semaphores
 *
 */
void init_sems() {
    //pot access control
    sem_init(&pot_sem,0,1); //initally free
    //signal for the cook to refill
    sem_init(&pot_empty,0,0); //initally locked
    //signal the cook has cooked
    sem_init(&pot_full,0,0);//initally locked
}

/**
 * destroy semaphores 
 */
void destroy_sems() {
    sem_destroy(&pot_sem);
    sem_destroy(&pot_empty);
    sem_destroy(&pot_full);
}

// TODO: Main Function that spawns 10 zergling processes, one cook process and joins all of them in the end. Use keep_cooking for controlling the cook

int main() {

    init_sems();
    keep_cooking = true;
    //create cook zergling
    pthread_t cook_zergling_t;
    int err = pthread_create(&cook_zergling_t,NULL,cook_zergling,NULL);
    if(err){
        perror("cook zergling thread creation failed");
        return -1;
    }

    // create Z (10) baby zerglings
    pthread_t baby_zerglings_t[Z];
    for(int z = 0; z < Z; z++){
        err = pthread_create(&baby_zerglings_t[z],NULL, baby_zergling, NULL);
        if(err){
            perror("baby zergling thread creation failed");
            return -1;
        }
    }

    //wait for zerglings to dine
    for(int z=0; z<Z; z++){
        if(pthread_join(baby_zerglings_t[z],NULL)){
            perror("joining baby zergling threads failed");
            return -1;
        }
    }
    //signal cook to stop cooking
    keep_cooking = false;
    sem_post(&pot_empty);
    if(pthread_join(cook_zergling_t,NULL)){
        perror("joining cook zergling thread failed");
        return -1;
    }


    destroy_sems();
    return 0;
}