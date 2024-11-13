#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Parameters {
    // the greeting to print. 1 for "Hello", 2 for "Hi", 3 for "Greetings". (or replace by any other greetings as you like)
    int greeting;
    // the name to greet.
    char *name;
    // a flag for a season-specific greeting. 0 for no season-specific greeting, 1 for easter, 2 for halloween, 3 for christmas. (or replace by any other seasonal greetings as you like)
    int season;
};

// Parse the parameters and put them into the params struct.
// Returns 0 on success, -1 on failure.
int parseParameters(int argc, char *argv[], struct Parameters *params) {
    params->greeting = atoi(argv[1]);

    // malloc uneeded as arg's exist within the main function.

    //char *name = malloc(sizeof(char)*(strlen(argv[2])+1));
    //if(!name){
    //    perror("malloc failed");
    //    return -1;
    //}
    //name = argv[2];

    params->name = argv[2];
    if (argc == 5){
        if(argv[3][0] != '-' || argv[3][1] != 's'){
            printf("unknown option: %s", argv[3]);
            return -1;
            }
        else{params->season = atoi(argv[4]);
            }
    }   
    else{
        params->season = 0;
        return 0;
    }

    return 0;
}

// Print a formatted greeting message.
void printMessage(struct Parameters *params) {
    if(params->greeting == 1){
        printf("Hello ");
    } else if (params->greeting == 2) {
        printf("Hi ");
    } else {
        printf("unknown greeting");
        return;
    }
    printf("%s", params->name);
    if (params->season == 0) {
        printf("\n");
        return;
    }
    if (params->season == 1) {
        printf(", happy easter!\n");
        return;
    } else if(params->season == 2){
        printf(", happy halloween!\n");
        return;
    } else{
        printf("unknown season %d", params->season);
        return;
    }

}

int main(int argc, char *argv[]) {
    if (argc < 3 || argc==4 || argc > 5){
        printf("Usage: %s <greeting> <name> (-s <season>)\n",argv[0]);
        return -1;
    }

    struct Parameters *params = malloc(sizeof(struct Parameters));
    int error = parseParameters(argc,argv, params);
    if(error){
        return error;
    } 
    printMessage(params);
    return 0;
}