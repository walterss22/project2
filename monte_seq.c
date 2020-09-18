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

