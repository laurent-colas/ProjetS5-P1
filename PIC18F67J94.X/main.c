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


//#include <usart.h>
void init_all(void);

int number = 3;
int i;
char pressed_pad;
const unsigned char str[17] = "Nico est francais";
float Total_distance[10];
int Distance_mm_int;
const unsigned char total_dist[10];


void main(void) {
    
    init_all();
//    putStringLCD(&str[0]);
    while(1) {
        
        pressed_pad = read_pad();
        if (pressed_pad == '1') {
            calc_distance_mm();
        }
        if (pressed_pad != 'z') {
            putchLCD(pressed_pad);
            _delay(50);
        }
        if (pressed_pad == 'C') {
            clearDisplay();
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
    init_dist_sensor();
}
