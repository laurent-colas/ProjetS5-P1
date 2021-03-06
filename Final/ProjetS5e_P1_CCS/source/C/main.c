
/*
  Cr�ateur:    Team P1
  DESCRIPTION : 
     Code principal pour d�tection de voix

  ENTR�ES : 
	 Il y a deux types d'entr�es  :
     1) Signal audio branch� sur l'entr�e MIC du DSK.
     2) Les caract�res envoy�s par le PIC.

  SORTIES : 
     1) Caract�res & id utilisateurs envoy�s au PIC

Note : Pour faire fonctionner le micro utiliser C6713Helper_UdeS de l'APP5

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

int noEchFilt=0;						// Num�ro de l'�chantillon courant
int reception_SPI = 0;
int rec = 1;

// Variable globale pour la g�n�ration de signal
const int fe = 8000;
const float PI = 3.14159265358979;

#define TAMPON_L  256
#pragma DATA_ALIGN(tampon, TAMPON_L*2); // Requis pour l'adressage circulaire en assembleur
short tampon[TAMPON_L]={0};         // Tampon d'�chantillons
short *pTampon=&tampon[TAMPON_L-1]; // Pointeur sur l'�chantillon courant

// VARIABLES GLOBALES POUR DSK
Uint32 fs=DSK6713_AIC23_FREQ_8KHZ; 			 // Fr�quence d'�chantillonnage
#define DSK6713_AIC23_INPUT_LINE 0x0011		 // D�finition de l'entr�e LINE IN
#define DSK6713_AIC23_INPUT_MIC  0x0015
Uint16 inputsource=DSK6713_AIC23_INPUT_MIC; // Selection de l'entr�e LINE IN

#define GAUCHE 0 // D�finition du haut-parleur gauche
#define DROIT  1 // D�finition du haut-parleur droit
union {Uint32 uint; short channel[2];} AIC23_data; // Pour contenir les deux signaux


struct TABLEAU_INIT Ech[2];
struct TABLEAU_IDENT x2[1];
struct TABLEAU_ID identite[10];
#pragma DATA_SECTION(identite, ".EXT_RAM")

#pragma DATA_SECTION(Ech, ".EXT_RAM")
#pragma DATA_SECTION(x2, ".EXT_RAM")

short tableau_in_temporaire[2*N];
#pragma DATA_SECTION(tableau_in_temporaire, ".EXT_RAM")

int noDIP = 0;
int noDIP1 = 1;
int interruption_full = 0;

struct TABLEAU_REF  Sig_Ref;
#pragma DATA_SECTION(Sig_Ref, ".EXT_RAM");

int incrementUser = 0;

short short_temp;

int debug = 0;
int kk =0;

// Variable pour userID
float betterScore = 0;
float betterScoreTemp = 0;
int nbUser = 0;
int user = 0;
char ID;

void main()
{

	initDSK();	// Initialisations des variables et du hardware
	initUSER(); // Les scor de tous les usagers sont mis � 0. l'�l�ment score est utilis� pour savoir si l'ID existe ou pas (si != 0 == existe)
	rec = 1;
	char Etat;
	Etat = 'C';
	while(1) {

	        int DIP0 = DSK6713_DIP_get(0);
	        int DIP1 = DSK6713_DIP_get(1);
	        int DIP2 = DSK6713_DIP_get(2);
	        noDIP = 3;

	        if (debug == 0){
	            //Etat = (char) SPI_Read();

	        switch (Etat){

                case CHAR_CONFIG:
                    SPI_Write((unsigned int) CHAR_CONFIG);
                    DSK6713_LED_on(0);
                    comm_intr(fs,inputsource);
                    noDIP = 0;

                    while (noEchFilt!=L_TAMPON){
                        attendre(0.1);
                    }

                    attendre(0.2);
                    noEchFilt = 0;

                    CODEC_stop();
                    interruption_full = 0;
                    DSK6713_LED_off(0);
                    incrementUser = 0;

                    SPI_Write((unsigned int) CHAR_CONFIR1_CONFIG);
                    Etat = 'R';
                    break;

                case CHAR_CONFIG2:
                    SPI_Write((unsigned int) CHAR_CONFIG2);
                    DSK6713_LED_on(1);
                       comm_intr(fs,inputsource);
                       noDIP = 1;
                       while (noEchFilt!=L_TAMPON){
                           attendre(0.1);
                       }
                       attendre(0.3);
                       CODEC_stop();

                       DSK6713_LED_off(1);
                       interruption_full = 0;

                       SPI_Write((unsigned int) CHAR_CONFIR1_CONFIG);

                       pre_traitement(Ech);
                       noEchFilt = 0;

                    incrementUser = 0;

                    while(identite[incrementUser].score != 0){
                        incrementUser++;
                    }

                    SPI_Write((unsigned int) CHAR_CONFIR1_CONFIG);

                    identite[incrementUser].id = tabId[incrementUser];
                    kk = 0;
                    for(kk ; kk < N-1 ; kk++){
                        identite[incrementUser].pointeurAutoCorr[kk] = Sig_Ref.autoCorr[kk];
                    }
                    identite[incrementUser].score = Sig_Ref.seuil;
                    Etat = 'I';
                    break;

                case CHAR_IDENTI:
                    DSK6713_LED_on(2);
                    comm_intr(fs,inputsource);
                    noDIP = 2;

                    while (noEchFilt!=L_TAMPON){
                        attendre(0.1);
                    }

                    attendre(0.2);
                    noEchFilt = 0;

                    CODEC_stop();
                    interruption_full = 0;
                    DSK6713_LED_off(0);

                    incrementUser = 0;
                    while(identite[incrementUser].score != 0){
                        incrementUser++;
                    }

                    user = userID(incrementUser);
                    //Si on passe un seuil alors c'est une r�ussite, la voix enregistr�e est la m�me que celle qui parle
                    if (x2[0].seuil <= 18*identite[user].score) {

                        SPI_Write((unsigned int) identite[incrementUser].id);

                        printf("Reussite");
                        Etat = 'C';
                    }
                    //Si on ne passe pas un seuil alors c'est un �chec, la voix enregistr�e n'est pas la m�me que celle qui parle
                    else {

                        printf("Echec ");
                        Etat = 'C';

                        SPI_Write((unsigned int) 'f');
                    }
                    break;

                }
        }

	        //Mode permettant de tester l'enregistrement
	        if (debug == 1) {

	            SPI_Write((unsigned int) 'g');
	            attendre(0.5);

                if (reception_SPI) // On a re�u du data par SPI
                    {
                    char dataw;
                    unsigned int temep;
                    temep = SPI_Read();
                    dataw = 0xFF & (char) temep;

                    reception_SPI = 0;
                    }

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
	short echLineIn;	 // Amplitude de l'�chantillon provenant de l'entr�e LINE IN
	short echLineInFilt;
	echLineInFilt = 0;
	if (debug == 0 && rec == 1){
        // Capture de l'�chantillon provenant de l'entr�e "IN"
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
    DSK6713_LED_init(); // Initialisation des 4 LEDS (�teindre)
	// INITIALISATION DU HARDWARE
    comm_intr(fs,inputsource);
    //attendre(0.2);
    CODEC_stop();

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


void initUSER(){
    for(incrementUser = 0; incrementUser < 10; incrementUser++){
        identite[incrementUser].score = 0;
    }
}
