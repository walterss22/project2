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
#include <pthread.h> //to thread

int64_t SAMPLES = 1000000;
int DIGITS;
int THREADS = 10;
double* results;

long double estimate(){
    srand(time(NULL));
    int samps [SAMPLES][2]; //could not save as matrix and use ifs in loops to save mem
    //maybe get rid of segmentation err
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
    double est = 0;
    DIGITS = floor(log10(RAND_MAX));
    //Segmentation fault

    if(argc >= 2){
        SAMPLES = strtoull(argv[1], NULL, 10);
        if(argc > 2){
            THREADS = strtoull(argv[2], NULL, 10);
        }
    }
    SAMPLES /= THREADS;
    //get time taken
    clock_gettime(CLOCK_MONOTONIC, &start); //Start the clock!

    pthread_t * handlers = malloc(sizeof(pthread_t) * THREADS);//allocate mem for threads
    results = malloc(sizeof(double) * THREADS);

    //create threads
    for(int i = 0; i < THREADS; i++){
        pthread_create(&handlers[i], NULL, estimate, NULL);
    }

    //join threads
    for(int i = 0; i < THREADS; i ++){
        pthread_join(handlers[i], NULL);
    }
    
    //free mem
    free(handlers);

    //gather results
    for(int i = 0; i < THREADS; i++){
        est += results[i];
    }

    clock_gettime(CLOCK_MONOTONIC, &end);   //Stops the clock!
    time_diff = (end.tv_sec - start.tv_sec); //Difference in seconds
    time_diff += (end.tv_nsec - start.tv_nsec) / 1e9; //Difference in nanoseconds

    //print results
    printf("The time taken is %f \n", time_diff);
    printf("%lld terms used.\n", SAMPLES);
    printf("Pi is %.20f\n", est);
    return 0;
}   
