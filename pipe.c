#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>


void piping(int argc, char* argv[]);

int main(int argc, char* argv[]) {
    if (argc < 3) {
      printf("Usage: pipe <cmd0> <cmd1> ...");
      exit(1);
    }
    piping(argc, argv);
    return 0;
}


/**
 * @brief Things(tm) went terrible wrong, print an error using a passed message 
 * and exit the programme.
 * 
 * @param msg the message (as a string) that is used as a prefix in our perror call
 */
static void die(char *msg) {
  perror(msg);
  exit(EXIT_FAILURE);
}


/**
 * @brief Function replicating the behaviour of the pipe command |
 * You can either implement the original pipe that only works for two commands
 * or implement a "multi" pipe that works for n commands
 * Your programme has only to work for commands without arguments.
 * 
 * @param argc 
 * @param argv 
 */
void piping(int argc,  char * argv[]){
  int pipe_ptr[2];
  pipe(pipe_ptr);
    pid_t pid = fork();
    if (pid == -1) {
        die("Fork failed");
    }
    if (pid == 0) {
      close(pipe_ptr[0]);
      dup2(pipe_ptr[1], STDOUT_FILENO);
      execlp(argv[1], argv[1], (char* ) NULL);
      die("exec failed");
    } else {
      close(pipe_ptr[1]);
      waitpid(pid, NULL, 0);
      dup2(pipe_ptr[0], STDIN_FILENO);
      execlp(argv[2], argv[2], (char *) NULL);
      die("exec failed");
    }
}
