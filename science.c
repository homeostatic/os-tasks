#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <string.h>

// You are supposed to use semaphores - but how many do you need? 1, 2 or more?
sem_t sem1, sem2;

// Two global variabls that will store our scientist's "papers"
char text1[50] = "";
char text2[50] = "";

/**
 * @brief Start routine that corresponds to the behaviour of scientist 1.
 * @return void* 
 */
void *scientist_one() {
    printf("Scientist 1 sits down.\n");
    char paper[] = "Very interesting paper about NLP.";
    
    strcpy(text1, paper);
    sem_post(&sem1);
    // TODO Copying and Synchronisation
    sem_wait(&sem2);
    char paper2[50];
    strcpy(paper2, text2);
    printf("Scientist 1: I think your paper \"%s\" is very intriguing!\n", text2);
    printf("Scientist 1 stands up and goes away.\n");
    return NULL;
}

/**
 * @brief Start routine that corresponds to the behaviour of scientist 2.
 * @return void* 
 */
void *scientist_two(){
    printf("Scientist 2 sits down.\n");
    char paper[] = "Very interesting paper about DRL.";
    strcpy(text2, paper);
    sem_post(&sem2);
    // TODO Copying and Synchronisation
    sem_wait(&sem1);
    char paper1[50];
    strcpy(paper1, text1);
    printf("Scientist 2: I think your paper \"%s\" is very enlightening!\n", text1);
    printf("Scientist 2 stands up and goes away.\n");
    return NULL;
}


int main() {
    printf("Science Meeting is beginning.\n");

    sem_init(&sem1, 0, 0);
    sem_init(&sem2, 0, 0);

    pthread_t sc1, sc2;
    pthread_create(&sc1, NULL, &scientist_one, NULL);
    pthread_create(&sc2, NULL, &scientist_two, NULL);

    pthread_join(sc1, NULL);
    pthread_join(sc2, NULL);
    // TODO: Handle semaphores and threads!
    // Important aspect: Which starting value should our semaphores have?
    
    printf("Science Meeting is over - Parent thread is terminating.\n");
    return 0;
}