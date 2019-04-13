/* 
 * File:   main.h
 * Author: laure
 *
 * Created on 28 mars 2019, 15:09
 */

#ifndef MAIN_H
#define	MAIN_H

#ifdef	__cplusplus
extern "C" {
#endif
    

    
    
#define SeuilEau        5
#define SeuilTempEau    60
#define ATTENTE         1   
#define ACCEUIL         2
#define IDENTIFICATION  3
#define CONFIGURATION   4
#define PREP_CAFE       5    
    
#define MAX_USERS       10
#define TIMEOUT         3
    
#include "LCD_SPI.h"
#include "HC-SR04.h"
#include "num_pad.h"
#include "UART_MAX.h"
#include "temperature.h"
#include "config_user.h"
#include "message.h"
#include "fonction_periph.h"

char CHAR_ATTENTE = 'A';
char CHAR_IDENTI = 'I';
char CHAR_CONFIG = 'C';
char CHAR_CONFIR1_CONFIG = 'G';
char CHAR_ACCEUIL = 'E';


int ETAT = 1;
int TempEau, TempLait;
int DistanceEau, DistanceLait;


void init_all(void);
void get_ready_for_coffee(void);
void set_default_coffee(void);

void __interrupt(high_priority) Serial_interrupt(void); 
void __interrupt(low_priority) Temp_interrupt(void);


void create_new_user(void);
void read_validate_pad(char choices[], int length);

void identify_user(void);
int verify_id(char id);
void make_coffee(void);
int digit_to_int(char d);

//void init_interruption_temp(void);
char check(char input);

struct Utilisateur {
    char id;
    int qqt_eau;
    int qqt_lait;
    int qqt_sucre;
};
#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

