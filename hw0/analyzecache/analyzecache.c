#include <stdio.h>
#include <sys/time.h>
#include "analyzecache.h"

int main(int argc, char *argv[])
{
    struct timeval start, end;
    double secondsUsed;
    char memory [8000000];
    int i;

    for(i = 0; i < 8000000; i++) {
        memory[i] = 'a' + i;
    }
    int temp = 0;
    int step = 1;
    int j;
    for(step = 2; step < 500; step = step * 2){ 
        gettimeofday(&start,0);
        int k = 0;
        for(i = 0; i < 16000; i++){
            temp = temp + memory[i * step];
        }
        gettimeofday(&end,0);
        printf("\n%d \n", step);
        printf("%d \n", temp);
        printf("%d clock ticks\n", end);
        secondsUsed = ((end.tv_sec-start.tv_sec)*1000000 + (end.tv_usec-start.tv_usec));
        printf("%f seconds \n", secondsUsed);
    }
    step = 64;
    for(j = 0; j < 10000; j = j + 100){
        gettimeofday(&start,0);
        int o;
        for(o = 0; o < 10; o++){
        for(i = 0; i < j; i++){
            temp = temp + memory[i * step];
        }}
        gettimeofday(&end,0);
//        printf("\n%d lines\n", j);
//        printf("%d \n", temp);
//        secondsUsed = ((end.tv_sec-start.tv_sec)*1000000 + (end.tv_usec-start.tv_usec));
        //printf("%f seconds \n", secondsUsed);
    }
    return 0;
}
