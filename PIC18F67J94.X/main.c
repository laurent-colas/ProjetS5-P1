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
#include "config_bits.h"
#include "LCD_SPI.h"
#include "HC-SR04.h"
#include "num_pad.h"
#include "UART_MAX.h"

void init_all(void);
void menu1(void);
void __interrupt() Serial_interrupt(void); 
char check(char input);


int number = 3;
int i;
char pressed_pad;
const unsigned char str[17] = "Nico est francais";
const unsigned char str_read_dist[20] = "1-Pour prelever dist";
float Total_distance[10];
int Distance_mm_int;
const unsigned char total_dist[10];
int first_run = 1;


char out;
char sys_state;

void main(void) {
    
    init_all();
//    putStringLCD(&str[0]);
    while(1) {
        
        pressed_pad = read_pad();
        
        if (first_run == 1) {
            menu1();
            first_run = 0;
        }
        
        
        if (pressed_pad == 'B') {
            clearDisplay();
            putStringLCD(&str_read_dist[0]);
            while(pressed_pad != 'C') {
                pressed_pad = read_pad();
                if (pressed_pad == '1') {
                    calc_distance_mm(); 
                    pressed_pad = 'z';
                }
   
            }
        }
        if (pressed_pad == 'A') {
            clearDisplay();
            while(pressed_pad != 'C') {
                pressed_pad = read_pad();
                if (pressed_pad != 'z') {
                    putchLCD(pressed_pad);
                    __delay_ms(100);
                }
                
            }
            
        }
        if (pressed_pad == 'C') {
//            clearDisplay();
//            menu1();
            first_run = 1;
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
    init_UART();
    initialisation_LCD();
    init_num_pad();
    init_dist_sensor();
}

void menu1(void) {
    const unsigned char menu1[20] = "A- Verif touches";
    const unsigned char menu2[] = "B- Verif capteur dist";
    const unsigned char menu3[] = "C- Retourner au menu";
    
    clearDisplay();
    
    moveCursor(0,0);
    putStringLCD(&menu1[0]);
    moveCursor(1,0);
    putStringLCD(&menu2[0]);
    moveCursor(2,0);
    putStringLCD(&menu3[0]);
    
}


void __interrupt() Serial_interrupt() {
    while(RC1IF == 0);
    out = RCREG1;
    sys_state = check(out);
}

char check(char input) {
    if(RCSTAbits.FERR == 1 || RCSTAbits.OERR == 1){
        RCSTA1bits.CREN = 0;
        return 0x65;
    }
    if (input == 0x64) {
        // d
        return 0x64;
    }
    if (input == 0x63) {
        // C
        return 0x63;
    }
    if (input == 0x66) {
        // F
        return 0x66;
    }
    else{
         // U
        return input;
    }
}