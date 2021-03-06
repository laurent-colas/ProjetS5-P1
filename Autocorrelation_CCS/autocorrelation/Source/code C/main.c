/*
 * main.c
 */
//D�finition des �tats de l'enregistreuse
#define ATTENTE 0
#define SIGNAL_PAS_OK 1
#define SIGNAL_OK 2

unsigned int State;

//D�finition des masques et des adresses utiles pour le projet
#define CPLD_USER_REG 0x90080000
#define MASK_LED0 0x01
#define MASK_LED1 0x02
#define MASK_LED2 0x04


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include <iostream>
#define length 10
#include "max.h"
#include "abs.h"
#include "norm.h"
#include "correlation.h"


void main(void)
{

    *(unsigned int*) CPLD_USER_REG &= MASK_LED0;
    *(unsigned int*) CPLD_USER_REG &= MASK_LED1;
    *(unsigned int*) CPLD_USER_REG &= MASK_LED2;
    //Initialisation du DSK
    //comm_intr();
/*
    double t[10];
    int i;
    double s_ref[10];
    for (i=0; i < 10; i++)
    {

        s_ref[i] = sin(i*3.14/10);

    }
    int a;
    a = length(s_ref);
    printf("%d",a);
*/
    State = ATTENTE;

    double t[length];
    int i;
    double s_ref[length];
    for (i = 0; i < length; i++)
    {
        s_ref[i] = sin(i*3.14 / 10);
    }
    double out[2 * length - 1] = {0};
    correlation(s_ref, s_ref, length,out);
    printf("Le resultat de la correlation est \n");
    printf("[ %f", out[0]);

    i = 1;
    for (; i < 2 * length - 1; i++)
    {
        printf(", %f",out[i]);
    }
    printf("]");
/*
    while(1)
    {


        switch (State)
        {
            case ATTENTE: // En attente de l'utilisateur
                *(unsigned int*) CPLD_USER_REG |= MASK_LED0;
                break;

            case SIGNAL_PAS_OK: // initialisation des interruptions
                *(unsigned int*) CPLD_USER_REG |= MASK_LED1;
                break;

            case SIGNAL_OK: // Recueillir l'�chantillon de start et l'analyser
                *(unsigned int*) CPLD_USER_REG |= MASK_LED2;
                break;


        }
    }*/
}
