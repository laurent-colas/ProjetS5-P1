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
const unsigned char div_temp[] = " sur 90 Celsius";
int debug = 0;

void main(void) {
    
    init_all();
    while (debug == 1) {
        send_data(CHAR_CONFIG);
        while(timeout < 10000) {
            timeout = timeout + 1;
        }
        timeout = 0;
    }
    set_default_coffee();
    get_ready_for_coffee();
    ETAT = ACCEUIL;
    
    while(1) {
        switch(ETAT) {
            case ACCEUIL:
                acceuil_usager();
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
    init_ADC();
    initialisation_LCD();
    init_num_pad();
    init_dist_sensor();
    init_periph();
}

void get_ready_for_coffee(void) {
    
    DistanceEau = calc_distance_mm(1);
    if (DistanceEau > SeuilEau) {
        avertissement(1);
        while (DistanceEau > SeuilEau) {
            DistanceEau = calc_distance_mm(1);
        }
    }
    TempEau = get_temp(1);
    if (TempEau < SeuilTempEau) {
        chauffe_eau(1);
        avertissement(2);
        while (TempEau < SeuilTempEau) {
            TempEau = get_temp(1);
            clearRow(1);
            moveCursor(1,0);
            putNumberLCD(TempEau);            
            putStringLCD(div_temp);
        }   
    }
    chauffe_eau(0);
    avertissement(0);
    
    init_interruption_temp();
}

void set_default_coffee(void) {
    utilisateur[increment_utilisateur].qqt_eau = 2;
    utilisateur[increment_utilisateur].qqt_lait = 1;
    utilisateur[increment_utilisateur].qqt_sucre = 1;
    utilisateur[increment_utilisateur].id = ID_USERS[increment_utilisateur];
    increment_utilisateur = increment_utilisateur + 1;
    utilisateur[1].id = ID_USERS[1];
    utilisateur[2].id = ID_USERS[2];
    utilisateur[3].id = ID_USERS[3];
    utilisateur[4].id = ID_USERS[4];
    utilisateur[5].id = ID_USERS[5];
    utilisateur[6].id = ID_USERS[6];
    utilisateur[7].id = ID_USERS[7];
    utilisateur[8].id = ID_USERS[8];
    utilisateur[9].id = ID_USERS[9];
    
}

void __interrupt(high_priority) Serial_interrupt() {
//    p.417
    while(PIR1bits.RC1IF == 0);
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
    clearRow(2);
}


void acceuil_usager(void) {
    message_etat(ACCEUIL);
    char pad_option_acceuil[2] = {'1', '2'};
    
    read_validate_pad(pad_option_acceuil, 2);
    
    if (pad_value == '1'){
        send_data(CHAR_CONFIG);
        while (((sys_state != CHAR_CONFIG) && (timeout <= TIMEOUT))) {
            timeout = timeout + 1;
        }
        timeout = 0;
        ETAT = CONFIGURATION;

    }
    else if (pad_value == '2') {
        ETAT = IDENTIFICATION;
    }
}

void create_new_user(void) {
    
    message_etat(CONFIGURATION);
    send_data(CHAR_CONFIG);
    
    while (((sys_state != CHAR_CONFIG) && (timeout <= TIMEOUT))) {
            timeout = timeout + 1;
    }
    timeout = 0;
    avertissement(4);
    __delay_ms(500);
            
    question_configuration(1);
    char choices_new_user_eau[3] = {'1', '2', '3'};
    read_validate_pad(choices_new_user_eau, 3);
    utilisateur[increment_utilisateur].qqt_eau = digit_to_int(pad_value);
    __delay_ms(500);
    
    question_configuration(2);
    char choices_new_user_lait[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    read_validate_pad(choices_new_user_lait, 9);
    utilisateur[increment_utilisateur].qqt_lait = digit_to_int(pad_value);
    __delay_ms(500);
    question_configuration(3);
    char choices_new_user_sucre[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    read_validate_pad(choices_new_user_sucre, 9);
    utilisateur[increment_utilisateur].qqt_sucre = digit_to_int(pad_value);
    
    while (((sys_state != CHAR_CONFIR1_CONFIG) && (timeout <= TIMEOUT))) {
            timeout = timeout + 1;
    }
    timeout = 0;
    avertissement(9);
    
//    utilisateur[increment_utilisateur].id = ID_USERS[increment_utilisateur];
//            sys_state;
    
//    utilisateur[increment_utilisateur].id = '1';
    
    increment_utilisateur = increment_utilisateur + 1;

}

void identify_user(void) {
    char previous_sys_state;
    int position_user_struct = -1;
    int detection_strikes = 3;
    char choices_identification[2] = {'1', '0'};
    
    while ((position_user_struct == -1 && detection_strikes != 0)) {
        message_etat(IDENTIFICATION);
        read_validate_pad(choices_identification, 2);

        if (pad_value == '1') {
            previous_sys_state = sys_state;
            
            avertissement(10);
            send_data(CHAR_IDENTI);
            avertissement(11);
            while (((sys_state != CHAR_IDENTI) && (timeout <= TIMEOUT))) {
                timeout = timeout + 1;
            }
            timeout = 0;
            
            while (((sys_state == CHAR_IDENTI) && (timeout <= TIMEOUT))) {
                timeout = timeout + 1;
            }
            timeout = 0;
            avertissement(9);
            
            position_user_struct = verify_id(sys_state);
//            position_user_struct = verify_id('1');
        
            if (position_user_struct == -1) {
                avertissement(5);
                detection_strikes = detection_strikes - 1;
                position_user_struct = 0;
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
    for (i = 0; i < MAX_USERS; i++) {
        if (id == utilisateur[i].id) {
            verified_id = i;
        } 
    } 
    return verified_id;
}

void make_coffee(void) {
    avertissement(6);
    show_portions(1);
    send_water(utilisateur[id_user_identifier].qqt_eau);
    avertissement(7);
    show_portions(2);
    send_milk(utilisateur[id_user_identifier].qqt_lait);
    avertissement(8);
    show_portions(3);
    send_sugar(utilisateur[id_user_identifier].qqt_sucre);
    
}

void show_portions(int step) {
    int temp;
    if (step == 1) {
        clearRow(1);
        moveCursor(1,0);
        putStringLCD(portion_eau);

        if (utilisateur[id_user_identifier].qqt_eau == 1) {
            putStringLCD(portion_eau_S);
        }
        if (utilisateur[id_user_identifier].qqt_eau == 2) {
            putStringLCD(portion_eau_M);
        }
        if (utilisateur[id_user_identifier].qqt_eau == 3) {
            putStringLCD(portion_eau_L);
        }
    }
    if (step == 2) {
        clearRow(1);
        moveCursor(1,0);
        temp = utilisateur[id_user_identifier].qqt_lait;
        putNumberLCD(temp);       
        putStringLCD(portion_lait);
    }
    
    if (step == 3) {
        
        clearRow(1);
        moveCursor(1,0);
        temp = utilisateur[id_user_identifier].qqt_sucre;
        putNumberLCD(temp); 
        putStringLCD(portion_sucre);
    } 
}

char check(char input) {
    if(RCSTA1bits.FERR == 1 || RCSTA1bits.OERR == 1){
        RCSTA1bits.CREN = 0;
        return 0x65;
    }
    // reception Attente detecter
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