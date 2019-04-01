/*
 * functionHelperProjetS5.h
 *
 *  Created on: 1 avr. 2019
 *      Author: laure
 */

#ifndef INCLUDES_FUNCTIONHELPERPROJETS5_H_
#define INCLUDES_FUNCTIONHELPERPROJETS5_H_


//#pragma once

//#include <iostream.h>
#include <math.h>
#include <stdio.h>




//const float PI = 3.14159265358979;
#define N   160000

struct TABLEAU_INIT {
    float mag_tableau_in[N];
    float phase_tableau_in[N];
    float real_tableau_in[N];
    float imag_tableau_in[N];
    float cmplx_tableau_in[N];
    float signal_in[N];
};

void magnitude_complex(float tableau_in_real[], float tableau_in_imag[], float tableau_out_magnitude[], int length);
void phase_complex(float tableau_in_real[], float tableau_in_imag[], float tableau_out_phase[], int length);
void fenetre_hamming(float w[], int length);
void fenetre_triangle(float w[], int length);
void FFT(float tableau_in[], float tableau_out_real[],float tableau_out_imag[]);
void pre_traitement(struct TABLEAU_INIT Ech_1, struct TABLEAU_INIT Ech_2, struct TABLEAU_INIT Ech_3 );

#endif /* INCLUDES_FUNCTIONHELPERPROJETS5_H_ */
