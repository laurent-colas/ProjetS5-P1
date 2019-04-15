/*
 * File:   fonction_periph.c
 * Author: laure
 *
 * Created on 21 février 2019, 16:36
 */

#include <stdio.h> 
#include <time.h> 

#include "HC-SR04.h"
#include "fonction_periph.h"


void send_water(int cup_size) {
    Relai_eau = 0;
    my_delay(2000*cup_size);
    Relai_eau = 1;
}

void send_milk(int num_cup) {
    DEL_LD = 1;
    my_delay(2*num_cup);
    DEL_LD = 0;
}

void send_sugar(int num_cup) {
    DEL_SD = 1;
    my_delay(2*num_cup);
    DEL_SD = 0;
}


void init_periph(void) {
    TRISCbits.TRISC4 = 0;
    TRISCbits.TRISC7 = 0;
    TRISCbits.TRISC6 = 0;
    TRISCbits.TRISC5 = 0;
    TRISCbits.TRISC2 = 0;
    TRISCbits.TRISC1 = 0;
    TRISCbits.TRISC0 = 0;
    
    TRISAbits.TRISA1 = 0;
    TRISFbits.TRISF6 = 0;
    
    Relai_eau = 1;
    DEL_SD = 0;
    DEL_LD = 0;
    DEL_ED = 0;
    DEL_NC_S = 0;
    DEL_NC_L = 0;
    DEL_NC_E = 0;
    DEL_TA_L = 0;
    DEL_TA_E = 0;
    
}


  
void my_delay(int number_of_seconds) 
{ 
    int i;
    for (i = 0; i<number_of_seconds*1000; i++) {
        __delay_ms(1);
    }
} 

int digit_to_int(char d) {
    int entier;

    switch(d){
        case '0':
            entier = 0;
            break;
        case '1':
            entier = 1;
            break;
        case '2':
            entier = 2;
            break;
        case '3':
            entier = 3;
            break;
        case '4':
            entier = 4;
            break;
        case '5':
            entier = 5;
            break;
        case '6':
            entier = 6;
            break;
        case '7':
            entier = 7;
            break;
        case '8':
            entier = 8;
            break;
        case '9':
            entier = 9;
            break;
        case 'A':
            entier = 10;
            break;
        case 'B':
            entier = 11;
            break;
        case 'C':
            entier = 12;
            break;
        case 'D':
            entier = 13;
            break;
        case 'E':
            entier = 14;
            break;
        case 'F':
            entier = 15;
            break;
    }
            
    return entier;
}