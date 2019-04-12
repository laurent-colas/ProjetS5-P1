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
    Relai_eau = 1;
    my_delay(2000*cup_size);
    Relai_eau = 0;
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
    
    Relai_eau = 0;
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
