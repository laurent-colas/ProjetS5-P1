/*
 * File:   main.c
 * Author: laure
 *
 * Created on 21 février 2019, 13:07
 */


#include <xc.h>
#include <stdbool.h> /* For true/false definition */
#include <stdint.h>
#include <stdio.h>
#include "LCD_SPI.h"
//#include <i2c.h>
#include "config_bits.h"

//#include <usart.h>
void init_all(void);
void init_num_pad(void);
char read_pad(void);


//#define _XTAL_FREQ 20000000
int number = 3;
int i;
char pressed_pad;
const unsigned char str[17] = "Nico est francais";

void main(void) {
    
    init_all();
    putStringLCD(&str[0]);
    while(1) {
        pressed_pad = read_pad();
        if (pressed_pad != 'z') {
            putchLCD(pressed_pad);
            _delay(500);
        }
        pressed_pad = 'z';
//        for (int k = 0; k<3; k++) {
//            moveCursor(k, 0);
//            for (i=0;i<4;i++) {
//                putchLCD('a');
//                putNumberLCD(number);
//            }
//        
//        }
//        for (int j = 0;j<100000;j++){}
//        clearDisplay();
        
//    
//        _delay(500); 
//        putNumberLCD(number);
//
//        _delay(500); 
    
    }

}

void init_all(void) {
    initialisation_LCD();
    init_num_pad();
}

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




