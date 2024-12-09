#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<string.h>
#include<unistd.h>
  
// Handler for SIGINT, caused by 
// Ctrl-C at keyboard 
void handle_sigint(int sig) { 
    printf("*** Caught signal %d\n", sig);
    //remeber to exit here, otherwise the programm would keep running
    exit(0);
}

/* Exit handler function called by sigaction */
void exitHandler(int sig, siginfo_t *siginfo, void *ignore) {
  printf("*** Got signal %d from %d\n", siginfo->si_signo, siginfo->si_pid);
  //remeber to exit here, otherwise the programm would keep running
//   exit(0);
}

// first option
// int main() {
//     signal(SIGINT, handle_sigint); 
//     while (1) {
//         puts("Oh no a loop :/");
//         sleep(1);
//     } 
//     return 0; 
// } 

// second option
int main() {
    struct sigaction act;
    act.sa_flags = SA_SIGINFO;
    act.sa_sigaction = exitHandler;
    sigaction(SIGINT, &act, NULL);
    while (1) {
        puts("Oh no a loop :/");
        sleep(1);
    }
    return 0;
}