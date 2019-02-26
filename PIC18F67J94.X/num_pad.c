/*
 * File:   num_pad.c
 * Author: laure
 *
 * Created on 26 février 2019, 10:31
 */


#include <xc.h>
#include "num_pad.h"

void init_num_pad(void) {   
    TRISE = 0xF0;
    PORTEbits.RE0 = 1;
    PORTEbits.RE1 = 1;
    PORTEbits.RE2 = 1;
    PORTEbits.RE3 = 1;   
}

char read_pad(void) {
    char num_pad_val;
    int pressed = 0;
    
    LATEbits.LATE3 = 0;
    if (!PORTEbits.RE7) {
        __delay_ms(100);
        if (!PORTEbits.RE7) {
            num_pad_val = 'C';
            pressed = 1;
        }
    }
    if (!PORTEbits.RE6) {
        __delay_ms(100);
        if (!PORTEbits.RE6) {
            num_pad_val = 'D';
            pressed = 1;
        }
    }
    if (!PORTEbits.RE5) {
        __delay_ms(100);
        if (!PORTEbits.RE5) {
            num_pad_val = 'E';
            pressed = 1;
        }
    }
    if (!PORTEbits.RE4) {
        __delay_ms(100);
        if (!PORTEbits.RE4) {
            num_pad_val = 'F';
            pressed = 1; 
        }
    }
    LATEbits.LATE3 = 1;
    
    LATEbits.LATE2 = 0;
    if (!PORTEbits.RE7) {
        __delay_ms(100); 
        if (!PORTEbits.RE7) {
            num_pad_val = 'B';
            pressed = 1;
        }
    }
    if (!PORTEbits.RE6) {
        __delay_ms(100);
        if (!PORTEbits.RE6) {
            num_pad_val = '9';
            pressed = 1; 
        }
    }
    if (!PORTEbits.RE5) {
        __delay_ms(100);
        if (!PORTEbits.RE5) {
            num_pad_val = '6';
            pressed = 1;
        }
    }
    if (!PORTEbits.RE4) {
        __delay_ms(100);
        if (!PORTEbits.RE4) {
            num_pad_val = '3';
            pressed = 1;
        }
    }
    LATEbits.LATE2 = 1;
    
    LATEbits.LATE1 = 0;
    if (!PORTEbits.RE7) {
        __delay_ms(100);
        if (!PORTEbits.RE7) {
            num_pad_val = '0';
            pressed = 1; 
        }
    }
    if (!PORTEbits.RE6) {
        __delay_ms(100);
        if (!PORTEbits.RE6) {
            num_pad_val = '8';
            pressed = 1; 
        }
    }
    if (!PORTEbits.RE5) {
        __delay_ms(100);
        if (!PORTEbits.RE5) {
            num_pad_val = '5';
            pressed = 1;
        }   
    }
    if (!PORTEbits.RE4) {
        __delay_ms(100);
        if (!PORTEbits.RE4) {
            num_pad_val = '2';
            pressed = 1;            
        }
    }
    LATEbits.LATE1 = 1;
    
    LATEbits.LATE0 = 0;
    if (!PORTEbits.RE7) {
        __delay_ms(100);
        if (!PORTEbits.RE7) {
            num_pad_val = 'A';
            pressed = 1;
        } 
    }
    if (!PORTEbits.RE6) {
        __delay_ms(100);
        if (!PORTEbits.RE6) {
            num_pad_val = '7';
            pressed = 1;
        }
    }
    if (!PORTEbits.RE5) {
        __delay_ms(100);
        if (!PORTEbits.RE5) {
            num_pad_val = '4';
            pressed = 1;
        }
    }
    if (!PORTEbits.RE4) {
        __delay_ms(100);
        if (!PORTEbits.RE4) {
            num_pad_val = '1';
            pressed = 1;
        }
    }
    LATEbits.LATE0 = 1;
    
    if (!pressed) {
        num_pad_val = 'z';
    }
    return num_pad_val;
}
