#include <stdio.h>

int fib(int n){

    if (n <= 1){
        return 1;
    }
    else{
        return fib(n-1)+fib(n-2);
    }
}

int main(){

    int x = 15;
    int res = fib(x);
    printf("fib(%d) = %d \n", x, res); 
}