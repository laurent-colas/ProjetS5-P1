/* 
 * File:   message.h
 * Author: laure
 *
 * Created on 12 avril 2019, 11:30
 */

#ifndef MESSAGE_H
#define	MESSAGE_H

#ifdef	__cplusplus
extern "C" {
#endif




const unsigned char etat_attente[] = "Machine Prete";
const unsigned char etat_attente1[] = "Attente utilisateur";
const unsigned char etat_acceuil1[] = "1- Nouvelle utilisateur";
const unsigned char etat_acceuil2[] = "2- Utilisateur existant"; 
const unsigned char etat_identification[] = "1 -> identifier vous";
const unsigned char etat_identification2[] = "0 -> usager defaut";
const unsigned char etat_configuration[] = "Prep temp eau";
        
const unsigned char q_eau[] = "Grosseur de tasse ?";
const unsigned char q_eau_choix[] = "S = 1, M = 2, L = 3";
const unsigned char q_lait[] = "Qqt pot de lait?";
const unsigned char q_lait_choix[] = "0 a 9 pot";
const unsigned char q_sucre[] = "Qqt sac de sucre?";
const unsigned char q_sucre_choix[] = "0 a 9 sac";
        
//const unsigned char avert0[13] = "Machine Prete";
const unsigned char avert1[] = "Manque eau";
const unsigned char avert2[] = "Prep temp eau";
const unsigned char avert3[] = "Touche non valide";
const unsigned char avert4[] = "Traitement de la voix";
const unsigned char avert5[] = "Voix non identifier";
const unsigned char avert6[] = "Versement eau";
const unsigned char avert7[] = "Versement lait";
const unsigned char avert8[] = "Versement sucre";

void avertissement(int NumAvertissement);
void message_etat(int etat);
void question_configuration(int etape);

#ifdef	__cplusplus
}
#endif

#endif	/* MESSAGE_H */

