#include <dirent.h>
#include <errno.h>
#include <fnmatch.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <regex.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>



int simple_ls(char path[], int max_depth) {
    // TODO: The main logic of the programme should endup roughly here
    // Return 0 if everything worked out as expected
    // Return -1 if anything causes headaches or explodes

    //If no path is explicitly passed, defaults to the currently opened path
    if (path == "."){
        path = malloc(100*sizeof(char));
        path = getcwd(path, 100);
        if (path == NULL){
            perror("could not get current working directory");
            return -1;
            }
    }

    //open directory stream
    struct dirent *pDirent;
    DIR *pDir;
    pDir = opendir (path);
        if (pDir == NULL) {
            printf ("Cannot open directory '%s'\n", path);
            return -1;
        }

    //printf("in scope path = %s\n", path);

    // Process each entry.

    while ((pDirent = readdir(pDir)) != NULL) {

        //entries .. and . in directories shall be skipped while exploring a directory.
        if (!(pDirent->d_name[0] == '.')){

            printf ("%s/%s\n",path, pDirent->d_name);
            // d_type = 4 is a directory
            if (pDirent->d_type == 4){

                char* subpath = malloc(100*sizeof(char));
                sprintf(subpath, "%s/%s", path, pDirent->d_name);
                
                // if max depth unspecified or set to -1 then go to full depth
                // if max depth == 0 no more recursion
                // otherwise max_depth gives number of recursions (still) permitted
                if (max_depth != 0){
                    simple_ls(subpath, (max_depth-1));
                }
                free(subpath);
            }
        }
    }


    //one file listed on each line
    closedir(pDir);
    //free(path);
    return 0;
    }


int main(int argc, char* argv[]) {
    char* path = NULL;
    //path = malloc(100*sizeof(char)); //assume maximum path length of 100
    int max_depth = 0;
    
    //first parameter always corresponds to the path. no path means current directory
        // "." -empty path
    if(argc < 2){
        path = "."; 
    } else {
        path = argv[1];
    }

    //second argument corresponds to the maximal depth for descending in the file tree. No number passed means full descent.
    if (argc < 3){
        //no arg 2 = full depth
        max_depth = -1;
    } else {
        max_depth = atoi(argv[2]);
    }

    if (argc > 3){
        printf("Usage: %s <path> <depth>\n",argv[0]);
        exit(-1);
    }

    simple_ls(path, max_depth);
    // debug
    // printf("Path = %s, depth = %d\n", path, max_depth);
    return 0;

}
