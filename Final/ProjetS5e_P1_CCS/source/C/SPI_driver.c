/********************************************************
**  Session 5 - APP6 - Téléphonie par DSP
**  Fichier SPI_driver.c
**  Auteurs : < vos noms >
**  Date : < derniere modification >
********************************************************/


/***************************************************************************
	Include headers :
***************************************************************************/

//#include "SPI_Config.h"


/***************************************************************************
	Include Module Header :
***************************************************************************/

#define SPI_DRIVER_MODULE_IMPORT
#include "SPI_driver.h"
#include "SPI_Config.h"
#include "dsk6713_aic23.h"
#include "dsk6713_dip.h"
#include "dsk6713.h"
#include <stdbool.h>

#include <csl.h>
#include <csl_gpio.h>
#include <csl_timer.h>
#include <csl_irq.h>
#include <csl_mcbsp.h>

// VARIABLES GLOBALES POUR DSK
Uint32 fsss=DSK6713_AIC23_FREQ_8KHZ;           // Fréquence d'échantillonnage
#define DSK6713_AIC23_INPUT_LINE 0x0011      // Définition de l'entrée LINE IN
#define DSK6713_AIC23_INPUT_MIC  0x0015
Uint16 inputsourcesss=DSK6713_AIC23_INPUT_MIC; // Selection de l'entrée LINE IN

/****************************************************************************
	Extern content declaration :
****************************************************************************/

extern far void vectors();   // Vecteurs d'interruption

extern MCBSP_Handle DSK6713_AIC23_CONTROLHANDLE;

/****************************************************************************
	Private macros and constants :
****************************************************************************/

// These defines are only valid is this .c

//#define something somethingelse

/****************************************************************************
	Private Types :
****************************************************************************/

// These type declaration are only valid in this .c

/****************************************************************************
	Private global variables :
****************************************************************************/
extern int output;
extern unsigned int input;
extern int reception_micro;
extern int reception_SPI;
extern GPIO_Handle lehandle;

/****************************************************************************
	Private functions :
****************************************************************************/

// these function can only be called by this .c
// Use static keyword

/****************************************************************************
	Public functions :
****************************************************************************/


// Function description here ...
void SPI_Write(unsigned int data)


{
    comm_intr(fsss,inputsourcesss);
    while(!MCBSP_xrdy(DSK6713_AIC23_CONTROLHANDLE));
    MCBSP_write(DSK6713_AIC23_CONTROLHANDLE, data | SPI_WRITE_DATA);
    DSK6713_waitusec(1000);
    while(!MCBSP_rrdy(DSK6713_AIC23_CONTROLHANDLE));
    DSK6713_waitusec(1000);
    MCBSP_read(DSK6713_AIC23_CONTROLHANDLE);
    CODEC_stop();
}

unsigned int SPI_Read(void)
{
    comm_intr(fsss,inputsourcesss);
    unsigned int temp;
    while(!MCBSP_xrdy(DSK6713_AIC23_CONTROLHANDLE));
    MCBSP_write(DSK6713_AIC23_CONTROLHANDLE, 0x00);
    while(!MCBSP_rrdy(DSK6713_AIC23_CONTROLHANDLE));
    DSK6713_waitusec(1000);
    temp = 0xFF & MCBSP_read(DSK6713_AIC23_CONTROLHANDLE);
    return temp;
    CODEC_stop();
}

void SPI_init(void)
{
    int CPLD_MISC_value;
    MCBSP_config(DSK6713_AIC23_CONTROLHANDLE, &MCBSP0_SPI_Cfg);
    MCBSP_start(DSK6713_AIC23_CONTROLHANDLE, MCBSP_XMIT_START | MCBSP_RCV_START | MCBSP_SRGR_START | MCBSP_SRGR_FRAMESYNC, 256);

    // On assure l'écriture SPI vers le breadboard
    CPLD_MISC_value =  DSK6713_rget(DSK6713_MISC);
    CPLD_MISC_value ^= 0x01; // Le MCBSP0SEL est le bit 0;
    DSK6713_rset(DSK6713_MISC, CPLD_MISC_value);

    // On fait la configuration vers MAX3111 en write
    while(!MCBSP_xrdy(DSK6713_AIC23_CONTROLHANDLE));
    MCBSP_write(DSK6713_AIC23_CONTROLHANDLE, SPI_WRITE_CONFIG);
	return;
}



void SPI_run(void)
{
    if (reception_SPI) // On a reçu du data par SPI
    {
        char dataw;
       // short data = 0;
        dataw = (char) SPI_Read();

        reception_SPI = 0;
    }
    int test = 1 ;
    if (test == 1 )
    {

        // On a du data à envoyer par SPI
        char data = 'l';
        SPI_Write((unsigned short) data);


    }

}


/****************************************************************************
	ISR :
****************************************************************************/
/* interrupt void c_int04(void)
{
    reception_SPI = 1;
}
*/
// end of SPI_driver.c
