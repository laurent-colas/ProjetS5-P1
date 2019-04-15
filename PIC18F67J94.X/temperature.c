/*
 * File:   temperature.c
 * Author: laure
 *
 * Created on 15 mars 2019, 11:19
 */


#include <xc.h>
#include <math.h>
#include "temperature.h"
//#include "pic18f67j94.h"

float RT1, RT, VR, ln, TX, T0, VRT, X, X1;

void init_ADC(void) {
    
    // p.452
    TRISDbits.TRISD5 = 0; // Relai eau en output
    Relai_chauffe = 1;
    
    // Conversion Analogique a digital pin setup
    ADCON1Hbits.ADON = 0; // A/D converter module is enabled
    ADCON1Hbits.MODE12 = 0; //10 bits AD operation
    ADCON1Hbits.FORM = 0b00; //Absolute decimal result, unsigned, right justified
    
    ANCON1bits.ANSEL0 = 1; // Pin RA0 set as analog
    ANCON1bits.ANSEL1 = 1; // Pin RA1 set as analog

    TRISAbits.TRISA0 = 1; //set channel 0 (RA0) as an input
    TRISAbits.TRISA1 = 1; //set channel 1 (RA1) as an input

    ADCON1Lbits.SAMP = 0; //A/D Sample-and-Hold amplifiers are sampling

    ADCON1Lbits.SSRC = 0b000;  //conversion automatique????????????????????
    ADCON1Lbits.ASAM = 0; //Sampling begins when SAMP bit is manually set

    ADCSS0L  = 0;
    ADCON3Hbits.ADRC = 0;  //Clock derived from system clock
    ADCON3L = 0x2F;
    ADCON2Hbits.BUFREGEN = 1;
    ADCON2L = 0;
    ADCON5H = 0x00;
    ADCON5L = 0x00;

    ADCHS0Lbits.CH0SA = 0; //Connect AN0 as S/H+ input
    // p.438
    ADCON1Hbits.ADON = 1; // A/D converter module is enabled
    
    T0 = 25 + 273.15;   
}

int get_temp(int channel) {
    int TempValue;
    if (channel == 1) {
        
        ADCON1Lbits.SAMP = 1;
        Delay();
        ADCON1Lbits.SAMP = 0;
        while (!ADCON1Lbits.DONE){}; // conversion done?

        VRT = ADCBUF0; // yes then get ADC values
        RT1 = RT0*((1023.0/VRT)-1.0);
        
        X=RT1/RT0;
        X=((log10(X))/log10(2.71828));
        
        X=(1/3950.0)*X;
        X=(X+(1/T0));
        X=1/(X);
        X=X -273.15;

        TempValue = (int)X;
    }
    
    return TempValue;
    
}

void Delay(void) {
    int i;
    for (i=0; i<10000; i++) ;
}

void chauffe_eau(int etat) {
    if (etat == 1) {
        Relai_chauffe = 0;
    }
    else {
        Relai_chauffe = 1;
    }
}

void gestion_temp_eau(int temperature) {
    if (temperature < SeuilTempEau) {
        chauffe_eau(1);
    }
    else {
        chauffe_eau(0);
    }
}
void init_interruption_temp(void) {
     //Interrupt timer 0
    RCONbits.IPEN = 1;
    INTCONbits.TMR0IE = 1; //Enables the TMR0 interrupt
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1; //general interrupt
    
    INTCON2bits.TMR0IP = 0; //timer 0 overflow  = low priority
    
    //T0CON = 0x98;
    //T0CON = 0x97; //Environ 8 seconde 1:256 prescaler value  
    T0CON = 0x96; //Environ 5 secondes 1:128 prescaler value
    //T0CON = 0x94; //Environ 1 seconde 1:32 prescaler value
    
}