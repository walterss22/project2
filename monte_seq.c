/*
Author: Scott Walters
CSCI-320

This program is a sequential implementation
of the Monte Carlo estimation of pi.
*/

/*
1. Randomly sample many points
2. count the number of points in circle
3. divide by 2, gets ratio of area
4. multiply by 4
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h> //to use uint_64
#include <time.h> //to use clock
#include <math.h> //to use pow function

int64_t SAMPLES = 1000000;


long double estimate(){
    

}

int main(int argc, char** argv){
    struct timespec start, end; //structs used for timing purposes, it has two memebers, a tv_sec which is the current second, and the tv_nsec which is the current nanosecond.
    double time_diff;

    if(argc == 2){
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
