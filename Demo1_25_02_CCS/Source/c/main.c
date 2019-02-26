/*
 * main.c
 */
//Définition des états de l'enregistreuse
#define ATTENTE 0
#define SIGNAL_PAS_OK 1
#define SIGNAL_OK 2

unsigned int State;

//Définition des masques et des adresses utiles pour le projet
#define CPLD_USER_REG 0x90080000
#define MASK_LED0 0x01
#define MASK_LED1 0x02
#define MASK_LED2 0x04

#include <stdio.h>
#include <math.h>
#include <iostream>

double correlation(s_ref,x)
{
    int length_s = sizeof(s_ref)/sizeof(s_ref[0]);


}


void main(void)
{
    //Initialisation du DSK
    comm_intr();

    float t[10] = [];
    for (int i = 0; i < 10; i++)
    {

        t[i] = i/10*3.14;

    }
    double s_ref=sin(t);
    State = ATTENTE;

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

            case SIGNAL_OK: // Recueillir l'échantillon de start et l'analyser
                *(unsigned int*) CPLD_USER_REG |= MASK_LED2;
                break;


        }
    }
}
