/********************************************************
**  Session 5 - APP5 - Téléphonie par DSP
**  Fichier principal Telephone.c
**  Auteurs :   Louis-Félix Beaudry
**              Jordan Laroche
**              Pierre-Yan Gingtras
**              Julien Lapointe
**
**  Date : 12 mars 2019
********************************************************/

//***************************************************************************
#pragma once
#ifndef _SPI_MODULE_
#define _SPI_MODULE_
//***************************************************************************

//***************************************************************************
//  Include headers

// standard libraries 
#include <stdio.h>   // get standard I/O functions (as printf)
#include <stddef.h>  // get null and size_t definition
#include <stdbool.h> // get boolean, true and false definition

// autres libraries
#include <csl.h>
#include <csl_irq.h>
#include <csl_gpio.h>
#include <csl_mcbsphal.h>

#include <dsk6713.h>
#include <dsk6713_led.h>
#include <dsk6713_dip.h>
#include <C6713Helper_UdeS.h>
#include <csl_mcbsp.h>
#include "DSK6713_AIC23.h"
//***************************************************************************

//***************************************************************************
//	Set EXTERN macro
#ifdef SPI_DRIVER_MODULE_IMPORT
	#define EXTERN  
#else 
	#define EXTERN extern
#endif
//***************************************************************************

//***************************************************************************
//	Function prototype
EXTERN void SPI_init(void);
EXTERN interrupt void c_int4(void);
void MCBSP_ecrire(unsigned int MCBSP_sortie);
unsigned int MCBSP_lire(void);
//***************************************************************************

//***************************************************************************
#undef SPI_DRIVER_MODULE_IMPORT
#undef EXTERN
#endif // end of #ifndef _SPI_MODULE_
//***************************************************************************

// end of SPI_driver.h
