/*
Author: Scott Walters
CSCI-320

This program sequentially estimates pi.
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h> //to use uint_64
#include <time.h> //to use clock
#include <math.h> //to use pow function

#define DEFAULT 1000000

double find_pi(long terms ){
    //C doesn't actually have Pi as a constant, but...
    //Most modern CPUs actually have an instruction to just load Pi into a register!
    //Some inline assembly here. This should work for all versions of GCC...
    long double Pi = 4; //initialize Pi
    long double mult = 0; //initialize multiplier
    for (int i = 0; i < terms; i++){
        mult += pow(-1, i) * (1.0 / ((2 * i) + 1)); //use estimation algo
    }
    // printf("multiplier is %Lf\n", mult); //used for checking multiplier
    Pi *= mult; //finish estimation
    return Pi;  //return Pi
}

int main(int argc, char** argv){
    struct timespec start, end; //structs used for timing purposes, it has two memebers, a tv_sec which is the current second, and the tv_nsec which is the current nanosecond.
    double time_diff;
    long terms;

    //gather command line arg
    if(argc >=2){
        terms = strtoull(argv[1], NULL, 10);
    } else {
        terms = DEFAULT;
    }
    
    //get time taken
    clock_gettime(CLOCK_MONOTONIC, &start); //Start the clock!
    double pi = find_pi(terms);
    clock_gettime(CLOCK_MONOTONIC, &end);   //Stops the clock!

    time_diff = (end.tv_sec - start.tv_sec); //Difference in seconds
    time_diff += (end.tv_nsec - start.tv_nsec) / 1e9; //Difference in nanoseconds

    //print results
    printf("The time taken is %f \n", time_diff);
    printf("%ld terms used.\n", terms);
    printf("Pi is %.20lf\n", pi);
}

