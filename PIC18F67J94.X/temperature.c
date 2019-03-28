/*
 * File:   temperature.c
 * Author: laure
 *
 * Created on 15 mars 2019, 11:19
 */


#include <xc.h>
#include <math.h>
#include "temperature.h"
#include "pic18f67j94.h"

float RT, VR, ln, TX, T0, VRT;

void init_ADC(void) {
    
    // p.452
    TRISDbits.TRISD5 = 0; // Relai eau en output
    // Conversion Analogique a digital pin setup
    ANCON1bits.ANSEL0 = 1; // RA0
    
    ADCON1Hbits.MODE12 = 0; //10-bit A/D operation
    ADCON1Hbits.FORM = 0x00; //Absolute decimal result, unsigned, right-justified
    ADCON1Hbits.ADON = 1; //A/D Converter module is operating
    
    ADCON1Lbits.SSRC = 0b0101;  //TMR1
    ADCON1Lbits.ASAM = 0; //Sampling begins when SAMP bit is manually set
    ADCON1Lbits.SAMP = 1; //A/D Sample-and-Hold amplifiers are sampling
    
    ADCON2Lbits.SMPI = 0x05; //Interrupt/address increment at the completion of conversion for each 5th sample
    
    ADCON3Hbits.ADRC = 0;  //Clock derived from system clock
    // p.438
    
//    ADCON1bits.PCFG = 0b1101; // 0b1110; //0b1101; // Configure analog pins
//    ADCON0bits.CHS0 = 1; // Selects channel 1 (AN1)
//    
//    ADCON2bits.ADFM = 0; //1; 0 = left justify
//    ADCON2bits.ACQT = 0x6; // 0b110; // A/D Acquisition Time Select bits
//    ADCON2bits.ADCS = 0x2; //0b010; // FOSC/32 A/D Conversion Clock Select bits
//    
//    ADCON0bits.ADON = 1; // A/D converter module is enabled

    T0 = 25 + 273.15;   
}

int get_temp(int channel) {
    int TempValue;
    if (channel == 1) {
        ADCON1Lbits.SAMP = 1;
        Delay();
        ADCON1Lbits.SAMP = 0;
        while (!ADCON1Lbits.DONE){}; // conversion done?

        VRT = ADCBUF0; // yes then get ADC value
        VRT = (5.00 / 1023.00) * VRT;
        VR = VCC - VRT;
        RT = VRT / (VR / R);
        ln = log(RT / RT0);
        TX = (1 / ((ln / B) + (1 / T0))); //Temperature from thermistor
        TX = TX - 273.15;                 //Conversion to Celsius

        TempValue = (int)TX;
    }
    
    return TempValue;
    
}

void Delay(void) {
    int i;
    for (i=0; i<10000; i++) ;
}


void chauffe_eau(int etat) {
    if (etat == 1) {
        PORTDbits.RD5 = 1;
    }
    else {
        PORTDbits.RD5 = 0;
    }
}