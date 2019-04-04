/*
 * functionHelperProjetS5.h
 *
 *  Created on: 1 avr. 2019
 *      Author: laure
 */

#ifndef INCLUDES_FUNCTIONHELPERPROJETS5_H_
#define INCLUDES_FUNCTIONHELPERPROJETS5_H_

#include <math.h>
#include <stdio.h>


//const float PI = 3.14159265358979;
#define N   4096//256 //16384
//#define Fs  8000;
//const float dt = 0.000125;



struct TABLEAU_INIT {
    float mag_tableau_in[N/2];
//    float phase_tableau_in[N];
    float real_tableau_in[N];
    float imag_tableau_in[N];
//    float cmplx_tableau_in[N];
    short signal_in[N];
    float signal_norm[N];
    float autoCorr[N];
};

struct TABLEAU_REF {
    float mag_tableau_ref[N];
//    float phase_tableau_ref[N];
    float real_tableau_ref[N];
    float imag_tableau_ref[N];
//    float cmplx_tableau_ref[N];
    short signal_ref[N];
    float autoCorr[N];
    float seuil;
};

struct TABLEAU_IDENT {
    float mag_tableau_ref[N];
    float signal_norm[N];
//    float phase_tableau_ref[N];
    float real_tableau_ref[N];
    float imag_tableau_ref[N];
    short signal_ref[N];
    float autoCorr[N];
    float seuil;
};


double AutoCorrelation(double * tab1, int longueur, double * tab2);

void magnitude_complex(float tableau_in_real[], float tableau_in_imag[], float tableau_out_magnitude[], int l);
void phase_complex(float tableau_in_real[], float tableau_in_imag[], float tableau_out_phase[], int l);
void fenetre_hamming(float w[], int l);
void fenetre_triangle(float w[], int l);
void FFT(float tableau_in[], float tableau_out_real[],float tableau_out_imag[]);
void IFFT(float tableau_in_real[],float tableau_in_imag[],float tableau_out[]);
void pre_traitement(struct TABLEAU_INIT Ech[2]);
void analyse_son(struct TABLEAU_IDENT x2[1]);
float maxi(float tab[],int l);
float mean(float tab[], int l);
float val_absolut(float val);
float maxi_abs(float tab[],int l);
short maxi_abs_short(short tab[],int l);
short mean_short(short tab[], int l);
void correlation(float x[], float y[],int l,float out[]);
void correlationLouis(float signal1[], float signal2[],int l,float out[]);


#endif /* INCLUDES_FUNCTIONHELPERPROJETS5_H_ */
