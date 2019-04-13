/* accordeur.c */
/*
  Créateur:    Bruno Gagnon, M. Sc.A
  Date:        2 septembre 2009
  Revisions:   Paul Charette (automne 2016)
  	  	  	  - Changé le nom de certains variables dans c_int11() pour rendre le
  	  	  	  	code plus compréhensible.
  	  	  	  - Ajouté à c_int11() la capacité de sortir les échantillons
  	  	  	    non-filtrés et filtrés sur les canaux droite/gauche de OUT
  	  	  	    pour débugger les filtres indépendemment du calcul de l'erreur
  	  	  	    d'accordage.

  DESCRIPTION : 
     Code principal pour un accordeur de guitare. Permet d'écouter 
     la fréquence fondamentale des cordes de guitare et d'obtenir 
     l'erreur sur l'accordement.

  ENTRÉES : 
	 Il y a deux types d'entrées physiques :
     1) Signal audio branché sur l'entrée LINE IN du DSK. Ce signal
     correspondant à une note de guitare jouée par un musicien. 
     2) Les sélections de l'utilisateur provenant des boutons du DSK.

  SORTIES : 
     1) Erreur sur l'accordement de la note jouée. Cette erreur
        est transmise sur le canal gauche de la sortie HEADPHONE du DSK.
	 2) Signal sinusoïdal correspondant à la fréquence fondamentale
	    de la note sélectionnée. Ce signal est transmis sur le canal droit
		de la sortie HEADPHONE du DSK (Pour écouter il faut appuyer sur
		la DIP SWITCH #3)
*/
#include <stdio.h>
#include <math.h>
#include "main_accordeur.h"
#include "CONSTANTES.h"
#include "dsk6713_aic23.h"
#include "dsk6713_dip.h"
#include "dsk6713_led.h"
#include "C6713Helper_UdeS.h"
#include "functionHelperProjetS5.h"



// VARIABLES GLOBALES
//USELECTIONS Commandes;				// Commandes de l'utilisateur (voir main_accordeur.h)

//const float F0_NOMINAL[NB_CORDES] = // Fréquences fondamentales de chacune des cordes
//     { 82.407,110.000,146.832,195.998,246.942,329.628 };
//float tamponEchFilt[L_TAMPON];			// Tampon d'échantillons
int noEchFilt=0;						// Numéro de l'échantillon courant
//float errAccordement;

// Variable globale pour la génération de signal
const int fe = 8000;
const float PI = 3.14159265358979;
//extern struct complx C_delta[NB_CORDES];
//extern int nb[NB_CORDES];			// Erreur sur l'accordement de l'instrument

#define TAMPON_L  256
#pragma DATA_ALIGN(tampon, TAMPON_L*2); // Requis pour l'adressage circulaire en assembleur
short tampon[TAMPON_L]={0};         // Tampon d'échantillons
short *pTampon=&tampon[TAMPON_L-1]; // Pointeur sur l'échantillon courant

// VARIABLES GLOBALES POUR DSK
Uint32 fs=DSK6713_AIC23_FREQ_8KHZ; 			 // Fréquence d'échantillonnage
#define DSK6713_AIC23_INPUT_LINE 0x0011		 // Définition de l'entrée LINE IN
#define DSK6713_AIC23_INPUT_MIC  0x0015
Uint16 inputsource=DSK6713_AIC23_INPUT_MIC; // Selection de l'entrée LINE IN

#define GAUCHE 0 // Définition du haut-parleur gauche
#define DROIT  1 // Définition du haut-parleur droit
union {Uint32 uint; short channel[2];} AIC23_data; // Pour contenir les deux signaux


struct TABLEAU_INIT Ech[2];
struct TABLEAU_IDENT x2[1];

#pragma DATA_SECTION(Ech, ".EXT_RAM")
#pragma DATA_SECTION(x2, ".EXT_RAM")

short tableau_in_temporaire[2*N];
#pragma DATA_SECTION(tableau_in_temporaire, ".EXT_RAM")

int noDIP = 0;
int interruption_full = 0;

struct TABLEAU_REF  Sig_Ref;
#pragma DATA_SECTION(Sig_Ref, ".EXT_RAM");

void main()
{
//	initGenM2();
//	afficherMenu();		// Affichage du menu principal à l'écran
	initAccordeur();	// Initialisations des variables et du hardware
//	int j;
	int debug = 0;
	short short_temp;
//	int i = 0;
//
//	for (i = 0; i<N; i++) {
//	    Ech[0].signal_in[i] = i;
//	    Ech[1].signal_in[i] = i+i;
////	    Ech[2].signal_in[i] = i;
//	}
//	pre_traitement(Ech);
//	analyse_son(x2);

	while(1) {

	        int DIP0 = DSK6713_DIP_get(0);
	        int DIP1 = DSK6713_DIP_get(1);
	        int DIP2 = DSK6713_DIP_get(2);
	        noDIP = 3;
	        // Si on appuie sur la DIP0 (actif etat bas 4103)
	        if (DIP0 == 0) {
	            DSK6713_LED_on(0);
	            comm_intr();
//	            comm_intr();
	            noDIP = 0;

	            while (noEchFilt!=L_TAMPON){
	                attendre(0.1);
	            }
	            attendre(0.2);
	            noEchFilt = 0;

	            CODEC_stop();
//	            for (j=0; j<N; j++) {
//	                Ech[0].signal_in[j] = tableau_in_temporaire[2*j];
//	            }
	            interruption_full = 0;
	            DSK6713_LED_off(0);

	        }
	        if (DIP1 == 0) {
	            DSK6713_LED_on(1);
	            comm_intr();
//                comm_intr();
                noDIP = 1;
                while (noEchFilt!=L_TAMPON){
                    attendre(0.1);
                }
                attendre(0.3);
                CODEC_stop();

                DSK6713_LED_off(1);
                interruption_full = 0;
                pre_traitement(Ech);
                noEchFilt = 0;
	        }
	        if  (DIP2 == 0) {
	            DSK6713_LED_on(2);
	            comm_intr();
//	            comm_intr();
	            noDIP = 2;
	            short_temp = (short) input_sample();
                while (noEchFilt!=L_TAMPON){
                    attendre(0.1);
                }

                attendre(0.2);
                CODEC_stop();

                interruption_full = 0;
                DSK6713_LED_off(2);

                analyse_son(x2);
                noEchFilt = 0;

                if (x2[0].seuil <= 18*Sig_Ref.seuil) {
                    DSK6713_LED_on(0);
                    DSK6713_LED_on(1);
                    DSK6713_LED_on(2);
                    DSK6713_LED_on(3);
                    attendre(2);
                    DSK6713_LED_off(0);
                    DSK6713_LED_off(1);
                    DSK6713_LED_off(2);
                    DSK6713_LED_off(3);

                    printf("Reussite");
                }
                else {
                    DSK6713_LED_on(0);
                    attendre(0.2);
                    DSK6713_LED_on(1);
                    attendre(0.2);
                    DSK6713_LED_on(2);
                    attendre(0.2);
                    DSK6713_LED_on(3);
                    attendre(2);
                    DSK6713_LED_off(0);
                    attendre(0.2);
                    DSK6713_LED_off(1);
                    attendre(0.2);
                    DSK6713_LED_off(2);
                    attendre(0.2);
                    DSK6713_LED_off(3);
                    printf("Echec ");
                }

	        }
	        if (debug == 1) {
	            comm_intr();
	            debug = 0;
	        }


	    }


//	while(1) {
//
//		// Si le tampon d'échantillons filtrés pour l'autocorrélation est plein
//		if (noEchFilt == L_TAMPON) {
//			// Calcul de l'erreur d'accordage
////			errAccordement = findErrAccordage(tamponEchFilt, F0_NOMINAL[Commandes.noCorde-1]);
//
//			// Attendre quelques instants pour permettre au tampon de bien se remplir
//			attendre(0.1); // NOTE : Nécessaire pour le bon fonctionnement des interruptions
//
//			// Permettre au tampon de se remplir de nouveau
//			noEchFilt = 0;
//		}
//	}
}

// Attente en sec. (approximatif)
void attendre(float seconds)
{
	int cnt=0;
	int fin = (int)NB_CYCLES_PAR_SEC*seconds;
	while (cnt++<fin) {}
}

/********************************************************************************************
  Créateur:    Bruno Gagnon, M. Sc.A
  Date:        2 septembre 2009
  Revisions:   
    DESCRIPTION : 
	 Code executé à toutes les interruptions
********************************************************************************************/
interrupt void c_int11() 
{
//	float echOut; 		 // Amplitude de l'échantillon générée pour l'écoute d'une note
	short echLineIn;	 // Amplitude de l'échantillon provenant de l'entrée LINE IN
	short echLineInFilt;

	// Capture de l'échantillon provenant de l'entrée "IN"
//	temp_in = input_sample();
	echLineIn = (short) input_sample();

	pTampon = FIR_ASM(pTampon, echLineIn, coefPBd, &echLineInFilt);

	if (noEchFilt < L_TAMPON && noDIP == 0  && interruption_full % 2 == 0) {
//	    tableau_in_temporaire[noEchFilt++] = echLineIn;
	    Ech[0].signal_in[noEchFilt++] = echLineInFilt; //noEchFilt;
    }
	if (noEchFilt < L_TAMPON && noDIP == 1 && interruption_full % 2 == 0) {
//	    tableau_in_temporaire[noEchFilt++] = echLineIn;
        Ech[1].signal_in[noEchFilt++] = echLineInFilt; //noEchFilt; //echLineIn;
    }
	if (noEchFilt < L_TAMPON && noDIP == 2 && interruption_full % 2 == 0) {
//	    tableau_in_temporaire[noEchFilt++] = echLineIn;
        x2[0].signal_ref[noEchFilt++] = echLineInFilt;
    }

	AIC23_data.channel[GAUCHE] = echLineIn;
    AIC23_data.channel[DROIT] = echLineInFilt;
//  // Sortir les deux signaux sur "HP/OUT"
    output_sample(AIC23_data.uint);
//    output_sample(temp_in);

    interruption_full  = interruption_full + 1;

	return;
}

/********************************************************************************************
  Créateur:    Bruno Gagnon, M. Sc.A
  Date:        2 septembre 2009
  Revisions:   
    DESCRIPTION : 
	 Code pour faire toutes les initialisations matériels
********************************************************************************************/
void initAccordeur() 
{
	// INITIALISATION DES VARIABLES
//	Commandes.noCorde = 1;		// La corde #1 est par défault la première corde à accorder
//	Commandes.isPlay = 0;		// Initialement, n'écoute pas la note
	

	// INITIALISATION DU HARDWARE
	DSK6713_DIP_init();	// Initialisation de la communication du DSP avec les 4 DIP swichs 
	DSK6713_LED_init();	// Initialisation des 4 LEDS (éteindre)

//	comm_intr();		/* Initialisation de la communication entre DSP et AIC23 codec
//						   et démarage des interruptions pour l'échantillonnage */

	return;			
}
