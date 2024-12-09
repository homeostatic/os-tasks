#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

int is_numeric(const char * str) {
    // TODO: Implement
    // ACTUALLY: No thanks
    return 1;
}

struct dirent* open_read_dir(char* path) {
    errno = 0;
    DIR* d = opendir(path);
    if (!d) {
        printf("%d", errno);
        exit(0);
    }
    errno = 0;
    struct dirent* res = calloc(5000,sizeof(struct dirent)); //I hope there's less than 5000 entries in there
    struct dirent* contents = readdir(d);
    int eof = contents == NULL;
    int i = 0;
    while (!eof)
    {   
        res[i] = *contents;
        contents = readdir(d);
        eof = contents == NULL;
        i++;
    }
    if (errno) {
        printf("Error reading Processes");
        exit(1);
    } 
    return res;
}
int main() {
    struct dirent* procs = open_read_dir("/proc");
    while (*procs->d_name) { 
        char* d_name = procs->d_name;
        if  (isdigit(*d_name)) {
            char path[255] = "/proc/";
            strcat(path, d_name);
            strcat(path, "/stat");
            FILE* f = fopen(path, "r");
            char cmd[255] = "/proc/";
            strcat(cmd, d_name);
            strcat(cmd, "/cmdline");
            FILE* c = fopen(cmd, "r");
            if (!f || !c) {
                exit(1);
            }
            char name[255];
            char state[255];
            char threads[255];
            char cmdline[1024]; //this one does need more space
            //Unfortunately, the number of threads is the 20th element in the stat file
            fscanf(f, "%*s (%s %s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %s", name, state, threads);
            name[strlen(name)-1] = '\0'; //remove the ')' at the end

            fscanf(c, "%[^\n] ", cmdline);
            printf("PID: %s, Name: %s, State: %s, Threads: %s, CmdLine: %s\n", d_name, name, state, threads, cmdline);
            fclose(f);
            fclose(c);
        }
        procs++;
    }
    return 0;
}