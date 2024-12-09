#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

// README! Handlers do not allow to pass arguments so we have to use a global variable - volatile for async signals
volatile int KEEP_GOING = 1;

/* \brief We could write different handlers per signal but one handler for both also works.
 If SIGINT is caught, our programme shall stop the loop, thus terminate gracefully
 If SIGTERM is caught our programme shall simply terminate completely.
 SIGINT is the signal sent by CTRL + C shortcut in the shell or with kill -2 <pid> to a process in background
 SIGTERM can be send using kill -- kill 15 <pid>
 \param signal - the signal id of our signal that should be handled
 */
void handler(int signal){
  // Implement me!
}

/*
Setups signal handling for SIGINT, SIGTERM.
SIGINT should stop the while loop in our print_file_names.
SIGTERM should terminate our programme harshly. (This is usually not done for SIGERM but we want this behaviour)
System calls should be automatically restarted!
*/
void signal_handling() {
  // Implement me!
}

// Prints the names of all files in a directory. DO NOT CHANGE this function or its signature!
int print_file_names(char *path) {
    
    // Initialises signal handling
    signal_handling();
    
    // Open the directory stream of the current directory
    DIR* dir = opendir(path);

    // Implicit not NULL check - since NULL always evalutes to 0 in if conditions (garantueed by C99)
    if (!dir){
        perror("print_file_names - Could not open dir");
        return 1;
    }
    
    errno = 0;
    struct dirent *e = readdir(dir);
    
    // Read the next entry from the DIR stream until there is none left.
    while(e && KEEP_GOING){
        printf("%s\n", e->d_name);
        errno = 0;
        e = readdir(dir);

        // We add a sleep so that you can see your signal behaviour more easily :)
        sleep(1);  
    }
    
    // Readdir changes errno if an error occurs
    if(!e && errno != 0){
        perror("print_file_names - Error while reading dir entry");
        return 1;
    }
    
    int ret = closedir(dir);
    if(ret == 1){
        perror("print_file_names - Error on closedir");
        return 1;
    }
    return 0;
}


int main(int argc, char *argv[]) {
    if (argc < 2){
        printf("Please pass a path! \n");
        return 1;
    }
    char *path = argv[1];
    return print_file_names(path);
}