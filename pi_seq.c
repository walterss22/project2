/*
Author: Scott Walters
CSCI-320

This program sequentially estimates pi.
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>

double find_pi(){
    //C doesn't actually have Pi as a constant, but...
    //Most modern CPUs actually have an instruction to just load Pi into a register!
    //Some inline assembly here. This should work for all versions of GCC...
    //*** Author: Kefu Lu
    double Pi;
    asm("fldpi \n\t"
        "fstpl %0"
        : "=m"(Pi));
    return Pi; 
}


