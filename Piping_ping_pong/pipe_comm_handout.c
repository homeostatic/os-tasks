#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Our pipe file descriptors
static int pipefd_ptc[2], pipefd_ctp[2];

/**
 * @brief Create twp pipes and call perror and exit, if the creation fails.
 */
void create_pipes() {
  //TODO: Create two pipes
}
/**
 * @brief The child process sends the parent Pong
 */
void tell_parent() {
  /* TODO: Pipe handling missing*/
  printf("Child sent a message to parent!\n");

}

/**
 * @brief Child reads a message out of the paper that was sent by the parent
 */
void wait_parent() {
  /* TODO: Pipe handling missing*/
  printf("Child received %s from the parent!\n", buf);
}
/**
 * @brief Parent sends the child a message through the pipe
 * 
 */
void tell_child() {
  /* TODO: Pipe handling missing*/
  printf("Parent sent a message to child!\n");
}

/**
 * @brief Read the message out of the pipe that was sent by the child
 * 
 */
void wait_child() {
  /* TODO: Pipe handling missing*/
  printf("Parent received %s from the child!\n", buf);
}

int main(int argc, char* argv[]) {
  create_pipes();
  pid_t pid;
  pid = fork();
  if(pid < 0) {
    perror("fork failed");
    exit(EXIT_FAILURE);
  }

  // Set a timer, the process will end after 10 seconds - sends an SIGALRM after the passage of this time.
  // The default disposition for SIGALRM is TERM(ination) ==> alarm kills our parent process
  // The OS will reap our zombie child (yeah admittdedly no clean solution)
  alarm(10);
  if (pid == 0) {
    // Parent process
    // TODO: You might need pipe handling here
    while (1) {
      sleep(rand() % 2 + 1);
      tell_child();
      wait_child();
    }
  }
  else {
    // Child process
    // TODO: You might need pipe handling here
    while (1) {
      sleep(rand() % 2 + 1);
      wait_parent();
      tell_parent();
    }
  }
  return 0;
}