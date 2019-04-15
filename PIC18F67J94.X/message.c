/*
 * File:   message.c
 * Author: laure
 *
 * Created on 12 avril 2019, 11:26
 */

//#include "LCD_SPI.h"
#include "message.h"
#include "main.h"

void avertissement(int NumAvertissement) {
    switch(NumAvertissement) {
        case 0: 
            clearDisplay();
            moveCursor(0,0);
            putStringLCD(etat_attente);
            break;
        case 1:
            clearDisplay();
            moveCursor(0,0);
            putStringLCD(avert1);
            break;
        case 2:
            clearDisplay();
            moveCursor(0,0);
            putStringLCD(avert2);
            break;
        case 3:
            moveCursor(2,0);
            putStringLCD(avert3);
            break;
        case 4:
            clearDisplay();
            moveCursor(0,0);
            putStringLCD(avert4);
            break;
        case 5:
            clearRow(1);
            moveCursor(1,0);
            putStringLCD(avert5);
            break;
        case 6:
            clearDisplay();
            moveCursor(0,0);
            putStringLCD(avert6);
            break;
        case 7:
            clearRow(0);
            moveCursor(0,0);
            putStringLCD(avert7);
            break;
        case 8:
            clearRow(0);
            moveCursor(0,0);
            putStringLCD(avert8);   
            break;
        case 9:
            moveCursor(1,0);
            putStringLCD(avert9);   
            break;
        case 10:
            clearDisplay();
            moveCursor(0,0);
            putStringLCD(avert10);   
            break;
        case 11:
            moveCursor(1,0);
            putStringLCD(avert11);   
            break;                
    }
}


void message_etat(int etat) {
    if (etat == ATTENTE) {
        
        clearDisplay();
        moveCursor(0,0);
        putStringLCD(etat_attente);
        moveCursor(1,0);
        putStringLCD(etat_attente1);
    }
    if (etat == ACCEUIL) {
        
        clearDisplay();
        moveCursor(0,0);
        putStringLCD(etat_acceuil1);
        moveCursor(1,0);
        putStringLCD(etat_acceuil2);
    }
    if (etat == IDENTIFICATION) {
        clearDisplay();
        moveCursor(0,0);
        putStringLCD(etat_identification);
        moveCursor(1,0);
        putStringLCD(etat_identification2);
    }
    if (etat == CONFIGURATION) {
        clearDisplay();
        moveCursor(0,0);
        putStringLCD(etat_configuration);
    }
}

void question_configuration(int etape) {
    if (etape == 1) {
        clearDisplay();
        moveCursor(0,0);
        putStringLCD(q_eau);
        moveCursor(1,0);
        putStringLCD(q_eau_choix);
    }
    if (etape == 2) {
        clearDisplay();
        moveCursor(0,0);
        putStringLCD(q_lait);
        moveCursor(1,0);
        putStringLCD(q_lait_choix);
    }
    if (etape == 3) {
        clearDisplay();
        moveCursor(0,0);
        putStringLCD(q_sucre);
        moveCursor(1,0);
        putStringLCD(q_sucre_choix);
    }
}