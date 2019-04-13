/*
 * analyse_son.c
 *
 *  Created on: 1 avr. 2019
 *      Author: Laurent Colas
 */
#include "functionHelperProjetS5.h"
#include "DSPF_sp_cfftr2_dit.h"
#include "DSPF_sp_icfftr2_dif.h"    //<--- SI JAMAIS ON EN A BESOIN SINON ON ENLÈVERA CETTE LIGNE!
#include "twiddle_512.h"              //<--- LE "X" DANS LE NOM DOIT ÊTRE REMPLACÉ PAR LE NOMBRE DE TWIDDLES CONTENUS DANS LE FICHIER!
#include <math.h>                   //<--- SI JAMAIS ON EN A BESOIN SINON ON ENLÈVERA CETTE LIGNE!
#include <bitrev_index.h>
#include <stdlib.h>
#include "max.h"
#include "abs.h"
#include "norm.h"

int i = 0;
int j = 0;

float fen_triang[N/2] = {0};
float fen_hamming[N] = {0};
#pragma DATA_SECTION(fen_triang,".EXT_RAM");
#pragma DATA_SECTION(fen_hamming,".EXT_RAM");

#pragma DATA_ALIGN(X_Z,8);
float X_Z[2*N];
#pragma DATA_SECTION(X_Z,".EXT_RAM");

#pragma DATA_ALIGN(index,8);
short index[16];
#pragma DATA_SECTION(index,".EXT_RAM");

float tempx[(3 * N/2) - 2];
float tempy[(3 * N/2) - 2];
#pragma DATA_SECTION(tempx,".EXT_RAM");
#pragma DATA_SECTION(tempy,".EXT_RAM");



float diff_corr[N-1];
#pragma DATA_SECTION(diff_corr, ".EXT_RAM");

float score[3] = {0};
#pragma DATA_SECTION(score, ".EXT_RAM");

extern struct TABLEAU_REF Sig_Ref;

void analyse_son(struct TABLEAU_IDENT x2[1]) {
    float max_abs_temp;
    short max_abs_temp_short;

    fenetre_hamming(fen_hamming, N);
    fenetre_triangle(fen_triang, N/2);

    max_abs_temp_short = maxi_abs_short(x2[0].signal_ref, N);

    for (i = 0; i<N; i++) {
        x2[0].signal_norm[i] = (float)x2[0].signal_ref[i] / (float)max_abs_temp_short;
        x2[0].signal_norm[i] = x2[0].signal_norm[i] * fen_hamming[i];
    }
    max_abs_temp = maxi_abs(x2[0].signal_norm, N);

    FFT(x2[0].signal_norm, x2[0].real_tableau_ref, x2[0].imag_tableau_ref);
    magnitude_complex(x2[0].real_tableau_ref, x2[0].imag_tableau_ref, x2[0].mag_tableau_ref, N/2);

    max_abs_temp = maxi_abs(x2[0].mag_tableau_ref, N/2);
    for (i = 0; i< N/2; i++) {
        x2[0].mag_tableau_ref[i] = x2[0].mag_tableau_ref[i] / max_abs_temp;
        x2[0].mag_tableau_ref[i] = x2[0].mag_tableau_ref[i] * fen_triang[i];
    }
    max_abs_temp = maxi_abs(x2[0].mag_tableau_ref, N/2);
    for (i = 0; i< N/2; i++) {
        x2[0].mag_tableau_ref[i] = x2[0].mag_tableau_ref[i] / max_abs_temp;
    }


    correlation(Sig_Ref.mag_tableau_ref,x2[0].mag_tableau_ref, N/2, x2[0].autoCorr);


    for (i = 0; i<N-1; i++) {
        diff_corr[i] = Sig_Ref.autoCorr[i] - x2[0].autoCorr[i];
        diff_corr[i] = val_absolut(diff_corr[i]);
    }

    x2[0].seuil = pow(5,(mean(diff_corr, N-1)*100));

}

void pre_traitement(struct TABLEAU_INIT Ech[2]){


    float max_temp, mean_temp;
    short max_temp_short;

    fenetre_hamming(fen_hamming, N);
    fenetre_triangle(fen_triang, N/2);

    max_temp_short = maxi_abs_short(Ech[0].signal_in, N);
    for (j = 0; j<N; j++) {
        Ech[0].signal_norm[j] = (float)Ech[0].signal_in[j] / (float)max_temp_short;
        Ech[0].signal_norm[j] = Ech[0].signal_norm[j] * fen_hamming[j];
    }

    max_temp_short = maxi_abs_short(Ech[1].signal_in, N);
    for (j = 0; j<N; j++) {
        Ech[1].signal_norm[j] = (float)Ech[1].signal_in[j] / (float)max_temp_short;
        Ech[1].signal_norm[j] = Ech[1].signal_norm[j] * fen_hamming[j];
    }
//        mean_temp = mean(Ech[i].signal_norm, N);
//        for (j = 0; j<N; j++) {
////            Ech[i].signal_norm[j] = Ech[i].signal_norm[j] - mean_temp;
//            Ech[i].signal_norm[j] = Ech[i].signal_norm[j] * fen_hamming[j];
//        }


    FFT(Ech[0].signal_norm, Ech[0].real_tableau_in, Ech[0].imag_tableau_in);
    magnitude_complex(Ech[0].real_tableau_in, Ech[0].imag_tableau_in, Ech[0].mag_tableau_in, N/2);

    max_temp_short = max_temp_short;

    FFT(Ech[1].signal_norm, Ech[1].real_tableau_in, Ech[1].imag_tableau_in);
    magnitude_complex(Ech[1].real_tableau_in, Ech[1].imag_tableau_in, Ech[1].mag_tableau_in, N/2);

//    for (i = 0; i<2; i++) {
//        FFT(Ech[i].signal_norm, Ech[i].real_tableau_in, Ech[i].imag_tableau_in);
//        magnitude_complex(Ech[i].real_tableau_in, Ech[i].imag_tableau_in, Ech[i].mag_tableau_in, N);
////        phase_complex(Ech[i].real_tableau_in, Ech[i].imag_tableau_in, Ech[i].phase_tableau_in, N);
//    }

    for (i = 0; i<N; i++) {
        Sig_Ref.real_tableau_ref[i] = (Ech[0].real_tableau_in[i] + Ech[1].real_tableau_in[i]) / 2;
        Sig_Ref.imag_tableau_ref[i] = (Ech[0].imag_tableau_in[i] + Ech[1].imag_tableau_in[i]) /2;
    }

    magnitude_complex(Sig_Ref.real_tableau_ref, Sig_Ref.imag_tableau_ref, Sig_Ref.mag_tableau_ref, N/2);


        max_temp = maxi_abs(Ech[0].mag_tableau_in, N/2);
        for (j = 0; j<N/2; j++) {
            Ech[0].mag_tableau_in[j] = Ech[0].mag_tableau_in[j]/max_temp;
            Ech[0].mag_tableau_in[j] = fen_triang[j] * Ech[0].mag_tableau_in[j];
        }
        max_temp = maxi_abs(Ech[0].mag_tableau_in, N/2);
        for (j = 0; j<N/2; j++) {
            Ech[0].mag_tableau_in[j] = Ech[0].mag_tableau_in[j]/ max_temp;
        }

        max_temp = maxi_abs(Ech[1].mag_tableau_in, N/2);
        for (j =0; j<N/2; j++) {
            Ech[1].mag_tableau_in[j] = Ech[1].mag_tableau_in[j]/max_temp;
            Ech[1].mag_tableau_in[j] = fen_triang[j] * Ech[1].mag_tableau_in[j];
        }
        max_temp = maxi_abs(Ech[1].mag_tableau_in, N/2);
        for (j = 0; j<N/2; j++) {
            Ech[1].mag_tableau_in[j] = Ech[1].mag_tableau_in[j]/ max_temp;
        }

    max_temp = maxi_abs(Sig_Ref.mag_tableau_ref, N/2);
    for (j = 0; j<N/2; j++) {
        Sig_Ref.mag_tableau_ref[j] = Sig_Ref.mag_tableau_ref[j] / max_temp;
        Sig_Ref.mag_tableau_ref[j] = fen_triang[j] * Sig_Ref.mag_tableau_ref[j];
    }

    max_temp = maxi_abs(Sig_Ref.mag_tableau_ref, N/2);
    for (j = 0; j<N/2; j++) {
       Sig_Ref.mag_tableau_ref[j] = Sig_Ref.mag_tableau_ref[j]/ max_temp;
    }

    correlation(Sig_Ref.mag_tableau_ref,  Sig_Ref.mag_tableau_ref, N/2, Sig_Ref.autoCorr);
    // optimiser pour autocorelation


    correlation(Sig_Ref.mag_tableau_ref, Ech[0].mag_tableau_in, N/2, Ech[0].autoCorr);
    for (j = 0; j<N-1; j++) {
        diff_corr[j] = Sig_Ref.autoCorr[j] - Ech[0].autoCorr[j];
        if (diff_corr[j] < 0) {
            diff_corr[j] = diff_corr[j] * -1;
        }
    }
    mean_temp = mean(diff_corr, N-1);
    score[0] = pow(5, mean_temp*100);

    correlation(Sig_Ref.mag_tableau_ref, Ech[1].mag_tableau_in, N/2, Ech[1].autoCorr);
    for (j = 0; j<N-1; j++) {
        diff_corr[j] = Sig_Ref.autoCorr[j] - Ech[1].autoCorr[j];
        if (diff_corr[j] < 0) {
            diff_corr[j] = diff_corr[j] * -1;
        }
    }
    mean_temp = mean(diff_corr, N-1);
    score[1] = pow(5, mean_temp*100);

//    for (i = 0; i<2; i++) {
//
//    }
    Sig_Ref.seuil = (score[0] + score[1])/2;
}

// pour obtenir le maximum
float maxi(float tab[],int l)
{

    float temp;
    float max = 0;
    for(i = 0; i < l; i++) {
        temp = tab[i];
        if (temp > max) {
            max = temp;
        }
    }
    return max;
}

float maxi_abs(float tab[],int l)
{

    float temp;
    float max = 0;
    for(i = 0; i < l; i++) {
        temp = tab[i];
        if (temp < 0) {
            temp = - temp;
        }
        if (temp > max) {
            max = temp;
        }
    }
    return max;
}

short maxi_abs_short(short tab[],int l)
{

    short temp;
    short max = 0;
    for(i = 0; i < l; i++) {
        temp = tab[i];
        if (temp < 0) {
            temp = - temp;
        }
        if (temp > max) {
            max = temp;
        }
    }
    return max;
}

float mean(float tab[], int l) {

    float sum;
    for (i = 0; i<l; i++) {
        sum += tab[i];
    }
    return sum/l;
}

short mean_short(short tab[], int l) {

    short sum;
    for (i = 0; i<l; i++) {
        sum += tab[i];
    }
    return sum/(short)l;
}

float val_absolut(float val) {

    if (val < 0) {
        val = val * -1;
    }
    return val;
}

void magnitude_complex(float tableau_in_real[], float tableau_in_imag[], float tableau_out_magnitude[],int l) {
    int i = 0;

    for (i = 0; i < l; i++)
    {
        tableau_out_magnitude[i] = sqrt((tableau_in_real[i])*(tableau_in_real[i]) + (tableau_in_imag[i])*(tableau_in_imag[i]));
    }
}

void phase_complex(float tableau_in_real[], float tableau_in_imag[], float tableau_out_phase[], int l) {
    int i = 0;

    for (i = 0; i < l; i++)
    {
        tableau_out_phase[i] = (float) atan2((double) tableau_in_imag[i],(double) tableau_in_real[i]);
    }
}

void fenetre_hamming(float w[], int l) {
    int i = 0;

    for (i = 0; i < l; i++)
    {
        w[i] = (0.54 - 0.46*cos(2 * 3.14* i / l));
    }
}

void fenetre_triangle(float w[], int l) {
    int i = 0;
//    int temp = l%2;
//    float temp;
    if (l % 2 == 0) {
        for (i = 1; i <= l / 2; i++)
        {
            w[i-1] = (((2 * i - 1)) / (float)(l));
        }
        for (i = (l / 2) + 1; i <= l; i++)
        {
            w[i-1] = (2 - (((2 * i - 1)) / (float)(l)));
        }
    }
    else {
        for (i = 1; i <= l / 2; i++)
        {
            w[i-1] = ((2 * i) / (l + 1));
        }
        for (i = (l / 2)+1; i <= l; i++)
        {
            w[i-1] = (2 - ((2 * i) / (l + 1)));
        }
    }

}



void FFT(float tableau_in[], float tableau_out_real[],float tableau_out_imag[])
{
    // Remplissez les cases paires du tableau de floats avec les valeurs de l'entrée et les cases impaires avec des 0.
    for (i = 0; i < N;i++)
    {
        X_Z[2*i] = tableau_in[i];
        X_Z[2*i+1] = 0.;
    }

    // Calculer la FFT
    DSPF_sp_cfftr2_dit(X_Z, w, N);

    // Inverse-bit
    bitrev_index(index, N);

    DSPF_sp_bitrev_cplx((double *)X_Z, index, N);

    for (i = 0; i < N;i++)
    {
        tableau_out_real[i] = X_Z[2*i];
        tableau_out_imag[i] = X_Z[2*i+1];
    }
    return;
}





void IFFT(float tableau_in_real[],float tableau_in_imag[],float tableau_out[])
{
//    int i;
//    #pragma DATA_ALIGN(X_Z,8);
//    float X_Z[2*N];
//    #pragma DATA_ALIGN(index,8);
//    short index[128];


    // Remplissez les cases paires du tableau de floats avec les valeurs de l'entrée et les cases impaires avec des 0.
    for (i = 0; i < N;i++)
    {
        X_Z[2*i] = tableau_in_real[i];
        X_Z[2*i+1] = tableau_in_real[i];
    }
    // Inverse-bit
    bitrev_index(index, N);

    DSPF_sp_bitrev_cplx((double *)X_Z, index, 2*N);

    // Calculer la IFFT
    DSPF_sp_cfftr2_dit(X_Z, w, 2*N);

    for (i = 0; i < N;i++)
    {
        tableau_out[i] = X_Z[2*i];
    }
}



void correlation(float x[], float y[],int l,float out[]) {

//    int i = 0;
//    Déclaration du tableau pour le résultat assembleur
//    double res_asm_corr [2*length -1];

    //Déclaration des coefficients d'autocorrelation
    float rxx0 = 0;
    float ryy0 = 0;

    //Calculs des coefficient d'autocorrélation des coefficients d'autocorrelation
    for (i = 0; i < l; i++) {
        rxx0 = rxx0 + x[i]*x[i];
        ryy0 = ryy0 + y[i]*y[i];
    }

//Ajout de "0" avant et après pour pouvoir faire les opérations dans x
    for (i; i < l-1; i++)
    {
        tempx[i] = 0;
    }

    int offset = i;
    for (i; i < offset+l; i++)
    {
        tempx[i] = x[i- offset];
    }

    offset = i;
    for (i; i < offset + l-1; i++)
    {
        tempx[i] = 0;
    }

//Boucle principale de l'algo
    i = 0;
    int j = 0;
    for (i; i < 2*l - 1; i++)
    {
        j = 0;
        for (j; j < i ; j++)
        {
            tempy[j] = 0;
        }

        int offset = j;
        for (j; j < offset + l; j++)
        {
            tempy[j] = y[j- offset];
        }

        offset = j;
        for (j; j < l+1-i+offset; j++)
        {
            tempy[j] = 0;
        }

        int k = 0;
        out[i] = 0;

        /*res_asm_corr [i] = AutoCorrelation(tempx, 3*length - 2, tempy); //Appel de la fonction assembleur
        printf("[ %f", res_asm_corr [i]);
         */

        for (k;k < 2*l -1; k++)
        {
            out[i] = out[i] + tempx[k] * tempy[k]; //Calcul du coefficient de correlation
        }
        out[i] = out[i] / sqrt(rxx0 * ryy0); //Normalisation de la corrélation


    }

}


