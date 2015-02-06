#include <stdio.h>
#include <time.h>
#include "analyzecache.h"

int main(int argc, char *argv[])
{
    clock_t start, end;
    double secondsUsed;
    char memory [6000000];
    int i;
     
    for(i = 0; i < 6000000; i++) {
        memory[i] = 'a';
    }
    int temp = 0;
    int step = 1;
    int j; 
    for(step = 1; step < 10000; step = step * 2){ 
        start = clock();
        for(i = 0; i < 600; i++){
            temp = temp + memory[i * step];
        }
        end = clock();
        printf("\n%d \n", step);
        printf("%d \n", temp);
        secondsUsed = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("%f seconds \n", secondsUsed);
    }
    for(j = 0; j < 400; j = j + 10){ 
        start = clock();
        for(i = 0; i < j; i++){
            temp = temp + memory[i * step];
        }
        end = clock();
        printf("\n%d lines\n", j);
        printf("%d \n", temp);
        secondsUsed = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("%f seconds \n", secondsUsed);
    }
    return 0;
}
