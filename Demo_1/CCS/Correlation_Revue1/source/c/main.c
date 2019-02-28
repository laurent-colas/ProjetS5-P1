/*
 * main.c
 */
//Définition des états de l'enregistreuse
#define ATTENTE 0
#define SIGNAL_PAS_OK 1
#define SIGNAL_OK 2
#define length 60

unsigned int State;

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


void main(void)
{
//On éteint toutes les LEDs du DSK
    *(unsigned int*) CPLD_USER_REG &= MASK_LED0;
    *(unsigned int*) CPLD_USER_REG &= MASK_LED1;
    *(unsigned int*) CPLD_USER_REG &= MASK_LED2;

    State = ATTENTE;

    while(1)
    {

        switch (State)
        {
            case ATTENTE: // En attente de l'utilisateur
                *(unsigned int*) CPLD_USER_REG |= MASK_LED0; //LED0 allumé
                State =  test1(t, s_ref, b_ref);
                *(unsigned int*) CPLD_USER_REG &= MASK_LED0; //LED0 éteinte
                break;

            case SIGNAL_PAS_OK: // Signal détecté mais pas le bon
                *(unsigned int*) CPLD_USER_REG |= MASK_LED1; //LED1 allumé
                for (i=0;i<10000;i++);
                *(unsigned int*) CPLD_USER_REG &= MASK_LED1; //LED1 éteinte
                State = ATTENTE;
                break;

            case SIGNAL_OK: // Bon signal détecté
                *(unsigned int*) CPLD_USER_REG |= MASK_LED2; //LED2 allumé
                for (i=0;i<10000;i++);
                *(unsigned int*) CPLD_USER_REG &= MASK_LED2; //LED2 éteinte
                State = ATTENTE;
                break;


        }
    }
}
