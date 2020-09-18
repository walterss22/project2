/*
Author: Scott Walters
CSCI-320

This program is a sequential implementation
of the Monte Carlo estimation of pi.
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h> //to use uint_64
#include <time.h> //to use clock
#include <math.h> //to use pow function

int64_t SAMPLES = 1000000;

long double estimate(){
    double x = 0;
    double y = 0;
    uint64_t hits = 0;
    for(uint64_t i = 0; i < SAMPLES; i++){
        x = ((double)rand()/(double)RAND_MAX);
        y = ((double)rand()/(double)RAND_MAX);

        if(sqrt(pow(x,2) + pow(y,2)) <= 1 ){
            hits +=1;
        }
    }
    printf("%llu\n", hits);
    printf("%f\n",((double)hits)/SAMPLES);
    return (((double)hits)/SAMPLES) * 4;
}

int main(int argc, char** argv){
    struct timespec start, end; //structs used for timing purposes, it has two memebers, a tv_sec which is the current second, and the tv_nsec which is the current nanosecond.
    double time_diff;
    srand(time(0));
    //Segmentation fault

    if(argc >= 2){
        SAMPLES = strtoull(argv[1], NULL, 10);
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

