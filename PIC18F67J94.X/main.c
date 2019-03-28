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
char CHAR_ATTENTE = 'A';
char CHAR_IDENTI = 'I';
char CHAR_CONFIG = 'C';
char CHAR_ACCEUIL = 'E';


int ETAT = 1;

void init_all(void);
void get_ready_for_coffee(void);
void avertissement(int NumAvertissement);
void message_etat(int etat);
void menu1(void);
void __interrupt(high_priority) Serial_interrupt(void); 
void __interrupt(low_priority) Temp_interrupt(void);
//void init_interruption_temp(void);
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
char pad_value;

void main(void) {
    
    init_all();
    get_ready_for_coffee();
    ETAT = ATTENTE;
    
    while(1) {
        switch(ETAT) {
            case ATTENTE:
                message_etat(ATTENTE);
                send_data(CHAR_ATTENTE);
                while (sys_state != CHAR_ATTENTE) {}
                ETAT = ACCEUIL;
                break;
                
            case ACCEUIL:
                message_etat(ACCEUIL);
                pad_value = read_pad();
                while (pad_value != '1' || pad_value !='2') {
                    avertissement(3);
                    pad_value = read_pad();
                }
                if (pad_value == '1'){
                    ETAT = CONFIGURATION;
                }
                else if (pad_value == '2') {
                    ETAT = IDENTIFICATION;
                }
                break;
            
            case IDENTIFICATION:
                
                break;
                
            case CONFIGURATION:
                
                break;
                     
        }
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
            moveCursor(1,0);
            putNumberLCD(TempEau);
            moveCursor(1,4);
            const unsigned char div[13] = " / 90 Celsius";
            putStringLCD(&div[0]);
        }   
    }
    chauffe_eau(0);
    avertissement(0);
    
    init_interruption_temp();
}

void avertissement(int NumAvertissement) {
    if (NumAvertissement == 0) {
        const unsigned char avert0[14] = "Machine Prete!";
        clearDisplay();
        moveCursor(0,0);
        putStringLCD(&avert0[0]);
    }
    if (NumAvertissement == 1) {
        const unsigned char avert1[10] = "Manque eau";
        clearDisplay();
        moveCursor(0,0);
        putStringLCD(&avert1[0]);
    }
    if (NumAvertissement == 2) {
        const unsigned char avert2[13] = "Prep temp eau";
        clearDisplay();
        moveCursor(0,0);
        putStringLCD(&avert2[0]);
    }
    if (NumAvertissement == 3) {
        const unsigned char avert3[17] = "Touche non valide";
        //clearDisplay();
        moveCursor(2,0);
        putStringLCD(&avert3[0]);
    }
}

void message_etat(int etat) {
    if (etat == ATTENTE) {
        const unsigned char etat_attente[14] = "Machine Prete!";
        const unsigned char etat_attente1[21] = "Attente d'utilisateur";
        clearDisplay();
        moveCursor(0,0);
        putStringLCD(&etat_attente[0]);
        moveCursor(1,0);
        putStringLCD(&etat_attente1[0]);
    }
    if (etat == ACCEUIL) {
        const unsigned char etat_acceuil1[23] = "1- Nouvelle utilisateur";
        const unsigned char etat_acceuil2[23] = "2- Utilisateur existant";
        clearDisplay();
        moveCursor(0,0);
        putStringLCD(&etat_acceuil1[0]);
        moveCursor(1,0);
        putStringLCD(&etat_acceuil2[0]);
    }
    if (etat == IDENTIFICATION) {
        const unsigned char etat_identification[13] = "Prep temp eau";
        clearDisplay();
        moveCursor(0,0);
        putStringLCD(&etat_identification[0]);
    }
    if (etat == CONFIGURATION) {
        const unsigned char etat_configuration[13] = "Prep temp eau";
        clearDisplay();
        moveCursor(0,0);
        putStringLCD(&etat_configuration[0]);
    }
}

void __interrupt(high_priority) Serial_interrupt() {
//    p.417
    while(RC1IF == 0);
    out = RCREG1;
    sys_state = check(out);
}

void __interrupt(low_priority) Temp_interrupt() {
    int temperature;
    if (TMR0IF == 1) {
        temperature = get_temp(1);
        gestion_temp_eau(temperature);
        TMR0IF = 0;
    }
}



char check(char input) {
    if(RCSTA1bits.FERR == 1 || RCSTA1bits.OERR == 1){
        RCSTA1bits.CREN = 0;
        return 0x65;
    }
    // reception Attente detecter
    if (input == CHAR_ATTENTE) {
        // A
        return CHAR_ATTENTE;
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