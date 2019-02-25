/*
 * File:   main.c
 * Author: laure
 *
 * Created on 21 février 2019, 13:07
 */


#include <xc.h>
#include <stdbool.h> /* For true/false definition */
#include <stdint.h>
#include "LCD_SPI.h"
//#include <i2c.h>
#include "config_bits.h"

void clearDisplay();
//#include <usart.h>

//#define _XTAL_FREQ 20000000

//const unsigned char* input = 'b';

void main(void) {
    
    
    while(1) {
        clearDisplay();
    
        _delay(500); 
//        putStringLCD(input);

        _delay(500); 
    
    }

}
