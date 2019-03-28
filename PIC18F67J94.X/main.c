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
#include "temperature.h"

#define SeuilEau        5
#define SeuilTempEau    60
#define ATTENTE         1   
#define ACCEUIL         2
#define IDENTIFICATION  3
#define CONFIGURATION   4

int ETAT = 1;

void init_all(void);
void get_ready_for_coffee(void);
void avertissement(int NumAvertissement);
void menu1(void);
void __interrupt() Serial_interrupt(void); 
char check(char input);

int TempEau, TempLait;
int DistanceEau, DistanceLait;


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
    get_ready_for_coffee();
    
    while(1) {
        switch(ETAT) {
            case ATTENTE:
                
                break;
            
            case ACCEUIL:
                
                break;
            
            case IDENTIFICATION:
                
                break;
                
            case CONFIGURATION:
                
                break;
                     
        }

}

void init_all(void) {
    init_UART();
    initialisation_LCD();
    init_num_pad();
    init_dist_sensor();
}

void get_ready_for_coffee(void) {
    
    DistanceEau = calc_distance_mm(1);
    if (DistanceEau < SeuilEau) {
        avertissement(1);
        while (DistanceEau < SeuilEau) {
            DistanceEau = calc_distance_mm(1);
        }
    }
    TempEau = get_temp(1);
    if (TempEau< SeuilTempEau) {
        chauffe_eau(1);
        avertissement(2);
        while (TempEau< SeuilTempEau) {
            TempEau = get_temp(1);
            clearRow(1);
            moveCursor(1,0)
            putNumberLCD(TempEau);
            moveCursor(1,4);
            const unsigned char div[13] = " / 90 Celsius";
            putStringLCD(&div[0]);
        }   
    }
    avertissement(0);
    ETAT = ATTENTE;
}

void avertissement(int NumAvertissement) {
    if (NumAvertissement == 0) {
        const unsigned char avert1[14] = "Machine Prete!";
        clearDisplay();
        moveCursor(0,0);
        putStringLCD(&avert1[0]);
    }
    if (NumAvertissement == 1) {
        const unsigned char avert1[10] = "Manque eau";
        clearDisplay();
        moveCursor(0,0);
        putStringLCD(&avert1[0]);
    }
    if (NumAvertissement == 2) {
        const unsigned char avert1[13] = "Prep temp eau";
        clearDisplay();
        moveCursor(0,0);
        putStringLCD(&avert1[0]);
        
    }
    
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
//    p.417
    while(RC1IF == 0);
    out = RCREG1;
    sys_state = check(out);
}

char check(char input) {
    if(RCSTA1bits.FERR == 1 || RCSTA1bits.OERR == 1){
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