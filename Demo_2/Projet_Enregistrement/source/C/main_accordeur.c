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


#define CPLD_USER_REG 0x90080000
#define MASK_LED0 0x01


const float F0_NOMINAL[NB_CORDES] = // Fréquences fondamentales de chacune des cordes
     { 82.407,110.000,146.832,195.998,246.942,329.628 };

float tamponEchFilt[L_TAMPON];			// Tampon d'échantillons
int noEchFilt=0;						// Numéro de l'échantillon courant
float errAccordement;	

// Variable globale pour la génération de signal
const int fe = 8000;
const float PI = 3.14159265358979;
extern struct complx C_delta[NB_CORDES];
extern int nb[NB_CORDES];			// Erreur sur l'accordement de l'instrument

#define TAMPON_L  256
#pragma DATA_ALIGN(tampon, TAMPON_L*2); // Requis pour l'adressage circulaire en assembleur
short tampon[TAMPON_L]={0};         // Tampon d'échantillons
short *pTampon=&tampon[TAMPON_L-1]; // Pointeur sur l'échantillon courant
short *pTamponPH=&tampon[TAMPON_L-1];


// VARIABLES GLOBALES POUR DSK
Uint32 fs=DSK6713_AIC23_FREQ_8KHZ; 			 // Fréquence d'échantillonnage
#define DSK6713_AIC23_INPUT_LINE 0x0011	 // Définition de l'entrée LINE IN
Uint16 inputsource=DSK6713_AIC23_INPUT_LINE; // Selection de l'entrée LINE IN

#define GAUCHE 0 // Définition du haut-parleur gauche
#define DROIT  1 // Définition du haut-parleur droit
union {Uint32 uint; short channel[2];} AIC23_data; // Pour contenir les deux signaux

void main()
{
//	initGenM2();
//	afficherMenu();		// Affichage du menu principal à l'écran
	initAccordeur();	// Initialisations des variables et du hardware
	struct TABLEAU_INIT Ech[3];
	struct TABLEAU_REF  Sig_Ref;
	struct TABLEAU_IDENT x2;
/*
	int i;
	for (i = 0; i<N; i++) {
	    Ech[0].signal_in[i] = i;
	    Ech[1].signal_in[i] = i;
	    Ech[2].signal_in[i] = i;
	}*/
	//pre_traitement(Ech, &Sig_Ref);
	//analyse_son(&x2, &Sig_Ref);
	//initAIC();

	while(1) {

	    int DIP0 = DSK6713_DIP_get(0);
		// Si on appuie sur la DIP0 (actif etat bas 4103)
		if (DIP0 == 0) {

		    comm_intr();        /* Initialisation de la communication entre DSP et AIC23 codec
		                               et démarage des interruptions pour l'échantillonnage */

		    while (noEchFilt!=L_TAMPON){

		        attendre(0.1);

		    }
		    // Permettre au tampon de se remplir de nouveau
		    noEchFilt = 0;

		    CODEC_stop();

		}
	}
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
	float echOut; 		 // Amplitude de l'échantillon générée pour l'écoute d'une note
	short echLineIn;	 // Amplitude de l'échantillon provenant de l'entrée LINE IN
	short echLineInFilt; // Amplitude de l'échantillon filtré
	short echLineInFiltPH; // Amplitude de l'échantillon filtré
	//short pwm[10] = {0,0,0,0,0,0,0,0,25,25}; // Pulse width modulation
	//int debugFiltres = 1;
	//static int n = 0;

	// Capture de l'échantillon provenant de l'entrée "IN"
	echLineIn = (short) input_sample();


//	// VOTRE **SOLUTION** DE FILTRAGE FIR + IIR REMPLACE LA PROCHAINE LIGNE!!!
//	echLineInFilt = echLineIn;
	//pTamponPH = FIR_ASM(pTamponPH, echLineIn, coefPH, &echLineInFiltPH);
	pTampon = FIR_ASM(pTampon, echLineIn, coefPBd, &echLineInFilt);


//	// Si le tampon d'échantillons filtrés pour l'autocorrélation n'est pas plein,
//	// y ajouter l'échantillon courant filtré
	if (noEchFilt < L_TAMPON) {
//		// Enregistrement de l'échantillon dans le tampon
	tamponEchFilt[noEchFilt++] = (float) echLineInFilt;

	}
//
	AIC23_data.channel[GAUCHE] = echLineIn;
	AIC23_data.channel[DROIT] = echLineInFilt;
//	// Sortir les deux signaux sur "HP/OUT"
	output_sample(AIC23_data.uint);


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


	return;			
}


