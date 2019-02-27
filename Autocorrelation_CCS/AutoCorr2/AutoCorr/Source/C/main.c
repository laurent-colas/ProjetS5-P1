/*
 * main.c
 */

#include <stdio.h>
#include <math.h>
#include <string.h>


int AutoCorrelation(int *tabSing, int lon);

int main(void) {

    int sing[4] = {1,-1,1,-1};
    int l = sizeof(sing) / sizeof(sing[0]);


    int g=AutoCorrelation(sing, l);

    return 0;
}
