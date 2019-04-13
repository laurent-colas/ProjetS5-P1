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
#include <stdlib.h>
#include "config_bits.h"

#include "main.h"


int number = 3;
int i;
char pressed_pad;

float Total_distance[10];
int Distance_mm_int;
const unsigned char total_dist[10];
int first_run = 1;


char out;
char sys_state;
char pad_value;


struct Utilisateur utilisateur[MAX_USERS];
int increment_utilisateur = 0;
int id_user_identifier = 0;
int timeout = 0;
const unsigned char div_temp[15] = " sur 90 Celsius";

void main(void) {
    
    init_all();
    set_default_coffee();
    get_ready_for_coffee();
    ETAT = ATTENTE;
    
    while(1) {
        switch(ETAT) {
            case ATTENTE:
                message_etat(ATTENTE);
//                send_data(CHAR_ATTENTE);
                while (((sys_state != CHAR_ATTENTE) && (timeout <= TIMEOUT))) {
                    timeout = timeout + 1;
                }
                timeout = 0;
                ETAT = ACCEUIL;
                break;
                
            case ACCEUIL:
                message_etat(ACCEUIL);
                pad_value = read_pad();
                while ((pad_value != '1' && pad_value !='2')) {
                    avertissement(3);
                    pad_value = read_pad();
                }
                if (pad_value == '1'){
                    send_data(CHAR_CONFIG);
                    while (((sys_state != CHAR_ATTENTE) && (timeout <= TIMEOUT))) {
                        timeout = timeout + 1;
                    }
                    timeout = 0;
                    ETAT = CONFIGURATION;
                    
                }
                else if (pad_value == '2') {
                    ETAT = IDENTIFICATION;
                }
                break;
            
            case IDENTIFICATION:
                identify_user();
                ETAT = PREP_CAFE;
                break;
                
            case CONFIGURATION:
                create_new_user();
                ETAT = ACCEUIL;
                break;
            
            case PREP_CAFE:
                make_coffee();
                ETAT = ACCEUIL;
                break;
        }
    }
}

void init_all(void) {
    init_UART();
//    init_ADC();
    initialisation_LCD();
    init_num_pad();
    init_dist_sensor();
    init_periph();
}

void get_ready_for_coffee(void) {
    
//    DistanceEau = calc_distance_mm(1);
    DistanceEau = 6;
    if (DistanceEau < SeuilEau) {
        avertissement(1);
        while (DistanceEau < SeuilEau) {
            DistanceEau = calc_distance_mm(1);
        }
    }
//    TempEau = get_temp(1);
    TempEau = 70;
    if (TempEau < SeuilTempEau) {
        chauffe_eau(1);
        avertissement(2);
        while (TempEau< SeuilTempEau) {
            TempEau = get_temp(1);
            clearRow(1);
            moveCursor(1,0);
            putNumberLCD(TempEau);
            moveCursor(1,4);
            
            putStringLCD(&div_temp[0]);
        }   
    }
    chauffe_eau(0);
    avertissement(0);
    
//    init_interruption_temp();
}

void set_default_coffee(void) {
    utilisateur[increment_utilisateur].qqt_eau = 2;
    utilisateur[increment_utilisateur].qqt_lait = 0;
    utilisateur[increment_utilisateur].qqt_sucre = 0;
    utilisateur[increment_utilisateur].id = '0';
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



void read_validate_pad(char choices[], int length) {
    int i;
    int validation = 0;
    while (validation != 1) {
        pad_value = read_pad();
        for (i = 0; i<length; i++) {
            if (pad_value == choices[i]) {
                validation = 1;
            }
        }
        if (validation == 0) {
            avertissement(3);
        }
    }
}


void create_new_user(void) {
    
    question_configuration(1);
    char choices_new_user_eau[3] = {'1', '2', '3'};
    read_validate_pad(choices_new_user_eau, 3);
    utilisateur[increment_utilisateur].qqt_eau = digit_to_int(pad_value);
    
    question_configuration(2);
    char choices_new_user_lait[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    read_validate_pad(choices_new_user_lait, 9);
    utilisateur[increment_utilisateur].qqt_lait = digit_to_int(pad_value);
    
    question_configuration(3);
    char choices_new_user_sucre[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    read_validate_pad(choices_new_user_sucre, 9);
    utilisateur[increment_utilisateur].qqt_sucre = digit_to_int(pad_value);
    
//    utilisateur[increment_utilisateur].id = sys_state;
    utilisateur[increment_utilisateur].id = '1';
    
    increment_utilisateur = increment_utilisateur + 1;
    
    

}

void identify_user(void) {
    char previous_sys_state;
    int position_user_struct = -1;
    int detection_strikes = 3;
    char choices_identification[2] = {'1', '0'};
    
    while (position_user_struct == -1 || detection_strikes != 0) {
        message_etat(IDENTIFICATION);
        read_validate_pad(choices_identification, 2);

        if (pad_value == '1') {
            previous_sys_state = sys_state;
            send_data(CHAR_IDENTI);
        
            avertissement(4);
            while (sys_state != previous_sys_state || timeout != TIMEOUT) {
                timeout = timeout + 1;
            }
//            position_user_struct = verify_id(sys_state);
            position_user_struct = verify_id('1');
        
            if (position_user_struct == -1) {
                avertissement(5);
                detection_strikes = detection_strikes - 1;
            }
        }
        else {
            position_user_struct = 0;
        }

    }
    id_user_identifier = position_user_struct;

    
    
}

int verify_id(char id) {
    int i;
    int verified_id = -1;
    for (i = 0; i<MAX_USERS; i++) {
        if (id == utilisateur[i].id) {
            verified_id = i;
        } 
    } 
    return verified_id;
}

void make_coffee(void) {
    avertissement(6);
    send_water(utilisateur[id_user_identifier].qqt_eau);
    avertissement(7);
    send_milk(utilisateur[id_user_identifier].qqt_lait);
    avertissement(8);
    send_sugar(utilisateur[id_user_identifier].qqt_sucre);
}

int digit_to_int(char d) {
    int entier;

    switch(d){
        case '0':
            entier = 0;
            break;
        case '1':
            entier = 1;
            break;
        case '2':
            entier = 2;
            break;
        case '3':
            entier = 3;
            break;
        case '4':
            entier = 4;
            break;
        case '5':
            entier = 5;
            break;
        case '6':
            entier = 6;
            break;
        case '7':
            entier = 7;
            break;
        case '8':
            entier = 8;
            break;
        case '9':
            entier = 9;
            break;
        case 'A':
            entier = 10;
            break;
        case 'B':
            entier = 11;
            break;
        case 'C':
            entier = 12;
            break;
        case 'D':
            entier = 13;
            break;
        case 'E':
            entier = 14;
            break;
        case 'F':
            entier = 15;
            break;
    }
            
    return entier;
}



char check(char input) {
    if(RCSTA1bits.FERR == 1 || RCSTA1bits.OERR == 1){
        RCSTA1bits.CREN = 0;
        return 0x65;
    }
    // reception Attente detecter
    if (input == CHAR_ATTENTE) {
        return CHAR_ATTENTE;
    }
    if (input == CHAR_IDENTI) {
        return CHAR_IDENTI;
    }
    if (input == CHAR_CONFIG) {
        return CHAR_CONFIG;
    }
    if (input == CHAR_CONFIR1_CONFIG) {
        return CHAR_CONFIR1_CONFIG;
    }
    else{
        return input;
    }
}