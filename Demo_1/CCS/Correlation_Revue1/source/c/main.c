/*
 * main.c
 */
#define length 10
#define ATTENTE 0
#define SIGNAL_PAS_OK 1
#define SIGNAL_OK 2

//Définition des masques et des adresses utiles pour le projet
#define CPLD_USER_REG 0x90080000
#define MASK_LED0 0x01
#define MASK_LED1 0x02
#define MASK_LED2 0x04

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "max.h"
#include "abs.h"
#include "norm.h"
#include "correlation.h"
#include "test.h"

double t[length];
int i;
double s_ref[length];
double b_ref[length];

int main(void) {

    *(unsigned int*) CPLD_USER_REG &= MASK_LED0;
    *(unsigned int*) CPLD_USER_REG &= MASK_LED1;
    *(unsigned int*) CPLD_USER_REG &= MASK_LED2;

    test1(t, s_ref, b_ref);

    test2(t, s_ref, b_ref);

//    test3(t, s_ref, b_ref);

	
	return 0;
}
