#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "try_pointers.h"

// Intended for the live exercise:  not everything here is correct and will be shown in class in detail.
// These examples will show you how to play around with pointers. (comment them in individually)
// authored by Niklas Rentz

// int main() {
//     int x = 4;
//     int *y;
//     int z;
//     y = &x;
//     z = *y;

//     // What is the content of the variables y and z?
//     printf("y=%i\n", y);
//     printf("z=%i\n", z);

//     return 0;
//}







// int main() {
//     int x = 41;

//     // What is wrong here? How do we manage to change the value of x?
//     changeMe(x);

//     printf("x=%i\n", x);

//     return 0;
// }

// void changeMe(int x) {
//     ++x;
// }







// int main() {
//     // Accessing arrays (or pointers)
//     int array[4] = {1, 2, 3, 4};

//     printf("index 3: %i\n", array[3]);
//     printf("index 3: %i\n", *(array + 3));

//     printf("index 4: %i\n", array[4]);


//     // int *array2 = {1, 2, 3, 4};
//     // array++;

//     return 0;
// }


// int main(int argc, char *argv[]) {
//     // print all arguments to the console.
//     for (int i = 0; i < argc; ++i) {
//         printf("Argument #%i: %s\n", i, argv[i]);
//     }

//     return 0;
// }