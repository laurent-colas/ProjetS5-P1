
/*
  Créateur:    Team P1
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

// libraries
#include <csl.h>
#include <csl_irq.h>
#include <csl_gpio.h>
#include <csl_mcbsphal.h>
#include <csl_mcbsp.h>
#include <main.h>
#include <stdio.h>
#include <math.h>
#include <stddef.h>  // get null and size_t definition
#include <stdbool.h> // get boolean, true and false definition


#include "CONSTANTES.h"
#include "dsk6713_aic23.h"
#include "dsk6713_dip.h"
#include "dsk6713_led.h"
#include "C6713Helper_UdeS.h"
#include "functionHelperProjetS5.h"
#include "SPI_driver.h"

static GPIO_Handle lehandle;
void init_ext_intr();
extern far void vectors();   // Vecteurs d'interruption


// VARIABLES GLOBALES

int noEchFilt=0;						// Numéro de l'échantillon courant
int reception_SPI = 0;
int rec = 0;

// Variable globale pour la génération de signal
const int fe = 8000;
const float PI = 3.14159265358979;

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
struct TABLEAU_ID identite[10];

#pragma DATA_SECTION(Ech, ".EXT_RAM")
#pragma DATA_SECTION(x2, ".EXT_RAM")

short tableau_in_temporaire[2*N];
#pragma DATA_SECTION(tableau_in_temporaire, ".EXT_RAM")

int noDIP = 0;
int interruption_full = 0;

struct TABLEAU_REF  Sig_Ref;
#pragma DATA_SECTION(Sig_Ref, ".EXT_RAM");

int incrementUser = 0;

short short_temp;

int debug = 1;

// Variable pour userID
float betterScore = 0;
float betterScoreTemp = 0;
int nbUser = 0;
int user = 0;
char ID;

void main()
{

	initDSK();	// Initialisations des variables et du hardware
	initUSER(); // Les scor de tous les usagers sont mis à 0. l'élément score est utilisé pour savoir si l'ID existe ou pas (si != 0 == existe)

	while(1) {

	        int DIP0 = DSK6713_DIP_get(0);
	        int DIP1 = DSK6713_DIP_get(1);
	        int DIP2 = DSK6713_DIP_get(2);
	        noDIP = 3;
	        // Si on appuie sur la DIP0, enregistrement simple

	        char Etat;
	        if (debug == 0){
	            Etat = (char) SPI_Read();
	        switch (Etat){

                case CHAR_CONFIG:
                    SPI_Write((unsigned int) CHAR_CONFIG);
/*
                    DSK6713_LED_on(1);
                    comm_intr();
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
                    incrementUser++;
                    identite[incrementUser].id = tabId[incrementUser];
                    //identite[incrementUser].pointeurAutoCorr = pointeurAutoCorrelation;
                   // identite[incrementUser].score = score;
                    */
                    enregistrement(0);
                    interruption_full = 0;


                    enregistrement(1);
                    interruption_full = 0;

                    pre_traitement(Ech);
                    noEchFilt = 0;

                    incrementUser = 0;
                    while(identite[incrementUser].score != 0){
                        incrementUser++;
                    }

                    SPI_Write((unsigned int) CHAR_CONFIR1_CONFIG);

                    identite[incrementUser].id = tabId[incrementUser];
                    identite[incrementUser].score = Sig_Ref.seuil;
                    identite[incrementUser].pointeurAutoCorr = *Sig_Ref.autoCorr;

                    break;
                case CHAR_IDENTI:
                    SPI_Write((unsigned int) CHAR_IDENTI);
                    /* DSK6713_LED_on(2);
                    comm_intr();
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
*/
                    enregistrement(2);
                    interruption_full = 0;

                    incrementUser = 0;
                    while(identite[incrementUser].score != 0){
                        incrementUser++;
                    }

                    user = userID(incrementUser);
                    //Si on passe un seuil alors c'est une réussite, la voix enregistrée est la même que celle qui parle
                    if (x2[0].seuil <= 18*Sig_Ref.seuil) {


                        SPI_Write((unsigned int) identite[incrementUser].id);

                        printf("Reussite");
                    }
                    //Si on ne passe pas un seuil alors c'est un échec, la voix enregistrée n'est pas la même que celle qui parle
                    else {

                        printf("Echec ");

                        SPI_Write((unsigned int) 'f');
                    }
                    break;

                }
        }

	        //Mode permettant de tester l'enregistrement
	        if (debug == 1) {
	            //comm_intr();
	            //debug = 0;
	            SPI_Write((unsigned int) 'L');

                if (reception_SPI) // On a reçu du data par SPI
                    {
                        char dataw;
                       // short data = 0;
                        dataw = (char) SPI_Read();

                        reception_SPI = 0;
                    }
	            //SPI_run();
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


interrupt void c_int04(void)
{
    reception_SPI = 1;
}

interrupt void c_int11() 
{
	short echLineIn;	 // Amplitude de l'échantillon provenant de l'entrée LINE IN
	short echLineInFilt;
	if (debug == 0 && rec == 1){
        // Capture de l'échantillon provenant de l'entrée "IN"
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
	}
	return;
}


void initDSK()
{
    DSK6713_DIP_init(); // Initialisation de la communication du DSP avec les 4 DIP swichs
    DSK6713_LED_init(); // Initialisation des 4 LEDS (éteindre)
	// INITIALISATION DU HARDWARE
    comm_intr(DSK6713_AIC23_FREQ_44KHZ,DSK6713_AIC23_INPUT_MIC);
    //attendre(0.2);
    //CODEC_stop();


	SPI_init();
	init_ext_intr();

	return;			
}

void init_ext_intr()
{
    /* Initialisation de la pin 4*/
    lehandle = GPIO_open(GPIO_DEV0, GPIO_OPEN_RESET);
    GPIO_pinEnable(lehandle, GPIO_PIN4);
    GPIO_pinDirection(lehandle, GPIO_PIN4, GPIO_INPUT);
    GPIO_intPolarity(lehandle, GPIO_GPINT4, GPIO_FALLING);

    /* Initialisation de l'IRQ*/
    IRQ_setVecs(vectors);
    IRQ_globalEnable();
    IRQ_nmiEnable();
    IRQ_map(IRQ_EVT_EXTINT4,4);
    IRQ_reset(IRQ_EVT_EXTINT4);
    IRQ_enable(IRQ_EVT_EXTINT4);
}


int userID(int nbUser){
    incrementUser = 0;
    for(incrementUser = 0; incrementUser < nbUser; incrementUser++){
        analyse_son(x2);
        betterScoreTemp = x2[0].seuil;
            if(betterScoreTemp > betterScore){
                betterScore = betterScoreTemp;
                user = incrementUser;
            }
    }
    return user;
}

void enregistrement(int LED){
    rec = 1;
    noDIP = LED;
    while (noEchFilt!=L_TAMPON){
       attendre(0.1);
    }
    attendre(0.3);

    rec = 0;
    DSK6713_LED_off(LED);
}

void initUSER(){
    for(incrementUser = 0; incrementUser < 10; incrementUser++){
        identite[incrementUser].score = 0;
    }
}
