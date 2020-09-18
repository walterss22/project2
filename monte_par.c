/*
Author: Scott Walters
CSCI-320

This program is a parallel implementation
of the Monte Carlo estimation of pi.
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h> //to use uint_64
#include <time.h> //to use clock
#include <math.h> //to use pow function

int64_t SAMPLES = 1000000;
int DIGITS;
int THREADS = 10;

long double estimate(){
    int samps [SAMPLES][2];
    int hits = 0;
    for(uint64_t i = 0; i < SAMPLES; i++){
        for(uint64_t x = 0; x < 2; x++){
            samps [i][x] = (rand()/(pow(10, DIGITS))); //Cannot set upper bound
        }
        if(sqrt(pow(samps[i][0],2) + pow(samps[i][1],2)) <= 1 ){
            hits +=1;
        }
    }
    printf("%d\n", hits);
    return (((double)hits)/SAMPLES) * 4;
}

int main(int argc, char** argv){
    struct timespec start, end; //structs used for timing purposes, it has two memebers, a tv_sec which is the current second, and the tv_nsec which is the current nanosecond.
    double time_diff;
    srand(time(0));
    DIGITS = floor(log10(RAND_MAX));
    //Segmentation fault

    if(argc >= 2){
        SAMPLES = strtoull(argv[1], NULL, 10);
        if(argc > 2){
            THREADS = strtoull(argv[2], NULL, 10);
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &start); //Start the clock!
    long double estimation = estimate();
    clock_gettime(CLOCK_MONOTONIC, &end);   //Stops the clock!
    time_diff = (end.tv_sec - start.tv_sec); //Difference in seconds
    time_diff += (end.tv_nsec - start.tv_nsec) / 1e9; //Difference in nanoseconds

    //print results
    printf("The time taken is %f \n", time_diff);
    printf("%lld terms used.\n", SAMPLES);
    printf("Pi is %.20Lf\n", estimation);
    return 0;
}   
