#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <libgen.h>
#include <string.h>
#include <ctype.h> // to use the isspace() function

// internal wc shall use this function to read a file into
// the string to which char **read_string points to
// Use POSIX read, open, and close
// Do not use fopen, fread, and fclose from stdin!
int read_file(char* path, char** read_string) {
    
    // Try to open the file from a given path
    int fileDesc = open(path, O_RDONLY);
    if (fileDesc == -1){
        return(-2); // This is ususally -1, I changed it for debugging purposes
    }
    
    // Determine file size
    struct stat fileStats;
    fstat(fileDesc, &fileStats);
    size_t fileSize = fileStats.st_size;

    // Allocate buffer
    char* rBuff = NULL;
    rBuff = (char *) malloc(fileSize);

    // Read the file and pass to read_string
    // Returns size of file in bytes if successful,
    // 0 if only EOF is read, -1 if failed
    if (rBuff != NULL){
        int read_bytes = read(fileDesc, rBuff, fileSize);
        close(fileDesc);
        if (read_bytes == 0){
            free(rBuff);
            return 0;
        }
        *read_string = rBuff;
        free(rBuff);
        return read_bytes;
    }else{
        close(fileDesc);
        free(rBuff);
        return -3; // Same as open file debug above
    }
}

struct Res{int lines, words, bytes;};



// This programme is meant to do the main workload
// and store the result in the result struct
int internal_wc(char* path, struct Res* result) {

    // Initialize result string with a pointer
    char* resStr;
    char** resStrP = &resStr;

    // Use read_file on path and abort on error 
    int rfcheck = read_file(path, resStrP);
    
    // Just to check some errors that were occuring earlier
    if (rfcheck < 0){
        printf("File couldn't be read because: ");
        if (rfcheck == -2){
            printf("Opening file failed!\n");
        } else if (rfcheck == -3){
            printf("Reading file failed!\n");
        } else{
            printf("what %d\n", rfcheck);
        }
        return -1;
    }

    int isWord = 0; // Are we currently reading a word?
    int* iWP = &isWord;
    // int i = 0; // Index variable (I know i could do this with a for-loop, but it didnt work for some reason)
    int words = 0; // Amount of words in file
    int* wordsP = &words;
    int lines = 0; // Amount of lines in file
    int* linesP = &lines;

    //printf("%s, %ld\n",*resStrP, strlen(resStr));
    
    // Count the number of words and newlines
    for (int i = 0; i < strlen(resStr); i++){       
        char curChar = *resStrP[i];
        if (isspace(curChar) != 0){ // If the current character is a whitespace...
            if (curChar == '\n'){ // ...add +1 to lines if '\n'..
                *linesP++; 
            }            
            if (isWord == 1){ //...and if we're currently reading a word..
                wordsP++; //...add +1 to words
            }
            *iWP = 0; //...now we're not reading a word anymore!
        } else {
            *iWP = 1; // If we weren't reading a word, dont change anything
        }
    }

    // Pass the result of the above loop to the Res struct
    result->lines = lines;
    result->words = words;
    result->bytes = rfcheck;
    return 0;
}

//This function is meant to print Lines Words Bytes Filename
void prettify_wc(struct Res* result, char* path){
    printf("%d %d %d %s \n", result->lines, result->words, result->bytes, basename(path));
}

// The path shall be passed as a command line arg
// If the programme receives no arg it should terminate with -1
// It might be a good idea to output a string
int main(int argc, char *argv[]) {
    
    // Check for correct usage  
    if (argc != 2){
        printf("The program simplewc expects a path to a file as argument!\n");
        return -1;
    }   
    
    // Initialize result struct
    struct Res* statsP = (struct Res*)malloc(sizeof(struct Res));
    statsP->lines = 0;
    statsP->words = 0;
    statsP->bytes = 0;

    // Count the words of the file in the given path
    // Pass the results to the Res struct
    int wc = internal_wc(argv[1], statsP);
    if (wc < 0){
        perror ("Wordcount failed!");
        return -1;
    }

    // Print out values of the Res struct using prettifiy
    prettify_wc(statsP, argv[1]);
    return 0;
}
