#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int trimString(char* original, int n, char** resultPtr);

int main() {

    char testInput[] = "Lorem Ipsum";
    int trimLength = 4;

    char* result;
    if(trimString(testInput, trimLength, &result)) {
        printf("%s\n", result);
        free(result);
    }
    return 0;
}

// create new string without last n characters
int trimString(char* original, int n, char** resultPtr) {
    int len = strlen(original);
    if (len <n){
        *resultPtr = NULL;
        return 0;
    }
    char * result = malloc(sizeof(char)*(len-n+1));
    *resultPtr = result;
    if (!resultPtr){
        perror("malloc failed");
        exit(1);
    }
    for(int c; c<(len-n);c++){
        result[c] = original[c]; 
    }
    result[len-n] = '\0';
    return 1;
}