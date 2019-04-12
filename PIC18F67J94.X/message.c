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
    if (NumAvertissement == 4) {
        const unsigned char avert4[21] = "Traitement de la voix";
        clearDisplay();
        moveCursor(0,0);
        putStringLCD(&avert4[0]);
    }
    if (NumAvertissement == 5) {
        const unsigned char avert5[19] = "Voix non identifier";
//        clearDisplay();
        moveCursor(1,0);
        putStringLCD(&avert5[0]);
    }
    if (NumAvertissement == 6) {
        const unsigned char avert6[13] = "Versement eau";
        clearDisplay();
        moveCursor(0,0);
        putStringLCD(&avert6[0]);
    }
    if (NumAvertissement == 7) {
        const unsigned char avert7[14] = "Versement lait";
//        clearDisplay();
        moveCursor(1,0);
        putStringLCD(&avert7[0]);
    }
    if (NumAvertissement == 8) {
        const unsigned char avert8[15] = "Versement sucre";
//        clearDisplay();
        moveCursor(2,0);
        putStringLCD(&avert8[0]);
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
        const unsigned char etat_identification[20] = "1 -> identifier vous";
        const unsigned char etat_identification2[18] = "0 -> usager defaut";
        clearDisplay();
        moveCursor(0,0);
        putStringLCD(&etat_identification[0]);
        moveCursor(1,0);
        putStringLCD(&etat_identification2[0]);
    }
    if (etat == CONFIGURATION) {
        const unsigned char etat_configuration[13] = "Prep temp eau";
        clearDisplay();
        moveCursor(0,0);
        putStringLCD(&etat_configuration[0]);
    }
}

void question_configuration(int etape) {
    if (etape == 1) {
        const unsigned char q_eau[19] = "Grosseur de tasse ?";
        const unsigned char q_eau_choix[19] = "S = 1, M = 2, L = 3";
        clearDisplay();
        moveCursor(0,0);
        putStringLCD(&q_eau[0]);
        moveCursor(1,0);
        putStringLCD(&q_eau_choix[0]);
    }
    if (etape == 2) {
        const unsigned char q_lait[16] = "Qqt pot de lait?";
        const unsigned char q_lait_choix[10] = "0 a 9 pot";
        clearDisplay();
        moveCursor(0,0);
        putStringLCD(&q_lait[0]);
        moveCursor(1,0);
        putStringLCD(&q_lait_choix[0]);
    }
    if (etape == 3) {
        const unsigned char q_sucre[17] = "Qqt sac de sucre?";
        const unsigned char q_sucre_choix[9] = "0 a 9 sac";
        clearDisplay();
        moveCursor(0,0);
        putStringLCD(&q_sucre[0]);
        moveCursor(1,0);
        putStringLCD(&q_sucre_choix[0]);
    }
}