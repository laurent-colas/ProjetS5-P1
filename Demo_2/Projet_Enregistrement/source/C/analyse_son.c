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
#include "correlation.h"

float fen_triang[8192];
float fen_hamming[N];

void analyse_son(struct TABLEAU_IDENT *x2, struct TABLEAU_REF *Sig_Ref) {
    float max_abs_temp, mean_temp;
    int i;

    max_abs_temp = maxi_abs(x2->signal_ref, N);
    for (i = 0; i<N; i++) {
        x2->signal_ref[i] = x2->signal_ref[i] / max_abs_temp;
    }

    mean_temp = mean(x2->signal_ref, N);
    for (i = 0; i<N; i++) {
        x2->signal_ref[i] = x2->signal_ref[i] - mean_temp;
    }

    fenetre_hamming(fen_hamming, N);
    for (i = 0; i<N; i++) {
        x2->signal_ref[i] = x2->signal_ref[i] * fen_hamming[i];
    }

    FFT(x2->signal_ref, x2->real_tableau_ref, x2->imag_tableau_ref);
    magnitude_complex(x2->real_tableau_ref, x2->imag_tableau_ref, x2->mag_tableau_ref, N);
    phase_complex(x2->real_tableau_ref, x2->imag_tableau_ref, x2->phase_tableau_ref, N);

    max_abs_temp = maxi_abs(x2->mag_tableau_ref, N/2);
    fenetre_triangle(fen_triang, N/2);
    for (i = 0; i< N/2; i++) {
        x2->mag_tableau_ref[i] = x2->mag_tableau_ref[i] / max_abs_temp;
        x2->mag_tableau_ref[i] = x2->mag_tableau_ref[i] * fen_triang[i];
    }

    max_abs_temp = maxi_abs(x2->mag_tableau_ref, N/2);
    for (i = 0; i< N/2; i++) {
        x2->mag_tableau_ref[i] = x2->mag_tableau_ref[i] / max_abs_temp;
    }
    correlation((double*)Sig_Ref->mag_tableau_ref, (double*)x2->mag_tableau_ref, N/2, x2->autoCorr);
    float diff_corr[N/2];

    for (i = 0; i<N/2; i++) {
        diff_corr[i] = Sig_Ref->autoCorr[i] - x2->autoCorr[i];
        diff_corr[i] = val_absolut(diff_corr[i]);
    }

    x2->seuil = pow(5,(mean(diff_corr, N/2)*100));

}

void pre_traitement(struct TABLEAU_INIT *Ech, struct TABLEAU_REF  *Sig_Ref){

    int i = 0;
    int j = 0;
    float max_temp, mean_temp;
    float xREF[N];

    fenetre_hamming(&fen_hamming[0], N);

    for (i = 0; i<3; i++) {
        max_temp = maxi_abs(Ech[i].signal_in, N);
        for (j = 0; j<N; j++) {
            Ech[i].signal_in[j] = Ech[i].signal_in[j] / max_temp;
        }
        mean_temp = mean(Ech[i].signal_in, N);
        for (j = 0; j<N; j++) {
            Ech[i].signal_in[j] = Ech[i].signal_in[j] - mean_temp;
            Ech[i].signal_in[j] = Ech[i].signal_in[j] * fen_hamming[j];
        }
    }

    fenetre_triangle(fen_triang, N/2);
    for (i = 0; i<3; i++) {
        FFT(Ech[i].signal_in, Ech[i].real_tableau_in, Ech[i].imag_tableau_in);
        magnitude_complex(Ech[i].real_tableau_in, Ech[i].imag_tableau_in, Ech[i].mag_tableau_in, N);
        phase_complex(Ech[i].real_tableau_in, Ech[i].imag_tableau_in, Ech[i].phase_tableau_in, N);
    }

    for (i = 0; i<N; i++) {
        Sig_Ref->real_tableau_ref[i] = (Ech[0].real_tableau_in[i] + Ech[1].real_tableau_in[i] + Ech[2].real_tableau_in[2]) / 3;
        Sig_Ref->imag_tableau_ref[i] = (Ech[0].imag_tableau_in[i] + Ech[1].imag_tableau_in[i] + Ech[2].imag_tableau_in[i]) /3;
    }

    magnitude_complex(Sig_Ref->real_tableau_ref, Sig_Ref->imag_tableau_ref, Sig_Ref->mag_tableau_ref, N);
    phase_complex(Sig_Ref->real_tableau_ref, Sig_Ref->imag_tableau_ref, Sig_Ref->phase_tableau_ref, N);

    IFFT(Sig_Ref->real_tableau_ref, Sig_Ref->imag_tableau_ref, xREF);
//    IFFT(float tableau_in_real[],float tableau_in_imag[],float tableau_out[]);
    max_temp = maxi(xREF, N);

    for (i= 0; i<N; i++) {
        xREF[i] = xREF[i] / max_temp;
    }

    mean_temp = mean(xREF, N);
    for (i= 0; i<N; i++) {
        xREF[i] = xREF[i] - mean_temp;
    }

//    int Nb = N/2;
//    float T = N*dt;
//    float df = 1/T;


    for(i=0; i<3; i++) {
        max_temp = maxi(Ech[i].mag_tableau_in, N/2);
        for (j = 0; j<N/2; j++) {
            Ech[i].mag_tableau_in[j] = Ech[i].mag_tableau_in[j]/max_temp;
            Ech[i].mag_tableau_in[j] = fen_triang[j] * Ech[i].mag_tableau_in[j];
        }
        max_temp = maxi(Ech[i].mag_tableau_in, N/2);
        for (j = 0; j<N/2; j++) {
            Ech[i].mag_tableau_in[j] = Ech[i].mag_tableau_in[j]/ max_temp;
        }
    }

    max_temp = maxi(Sig_Ref->mag_tableau_ref, N/2);
    for (j = 0; j<N/2; j++) {
        Sig_Ref->mag_tableau_ref[j] = Sig_Ref->mag_tableau_ref[j]/ max_temp;
        Sig_Ref->mag_tableau_ref[j] = fen_triang[j] * Sig_Ref->mag_tableau_ref[j];
    }

    max_temp = maxi(Sig_Ref->mag_tableau_ref, N/2);
    for (j = 0; j<N/2; j++) {
       Sig_Ref->mag_tableau_ref[j] = Sig_Ref->mag_tableau_ref[j]/ max_temp;
    }


    correlation((double*) Sig_Ref->mag_tableau_ref, (double*) Sig_Ref->mag_tableau_ref, N/2, Sig_Ref->autoCorr);

    float score[3];
    float diff_corr[N/2];

    for (i = 0; i<3; i++) {
        correlation((double*)Sig_Ref->mag_tableau_ref, (double*) Ech[i].mag_tableau_in, N/2, Ech[i].autoCorr);
        for (j = 0; j<N/2; j++) {
            diff_corr[j] = Sig_Ref->autoCorr[j] - Ech[i].autoCorr[j];
        }
        mean_temp = mean(diff_corr, N/2);
        score[i] = pow(5, mean_temp*100);
    }
    Sig_Ref->seuil = (score[0] + score[1] + score[2])/3;
}

// pour obtenir le maximum
float maxi(float tab[],int l)
{
    int i;
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
    int i;
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

float mean(float tab[], int l) {
    int i;
    float sum;
    for (i = 0; i<l; i++) {
        sum += tab[i];
    }
    return sum/l;
}

float val_absolut(float val) {
    int i;
    if (val < 0) {
        val = - val;
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

void fenetre_hamming(float w[N], int l) {
    int i = 0;

    for (i = 0; i < l; i++)
    {
        w[i] = (0.54 - 0.46*cos(2 * 3.14* i / l));
    }
}

void fenetre_triangle(float w[], int l) {
    int i = 0;
    int temp = l%2;
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
    int i;
    #pragma DATA_ALIGN(X_Z,8);
    float X_Z[2*N];
    #pragma DATA_ALIGN(index,8);
    short index[128];


    // Remplissez les cases paires du tableau de floats avec les valeurs de l'entrée et les cases impaires avec des 0.
    for (i = 0; i < N;i++)
    {
        X_Z[2*i] = tableau_in[i];
        X_Z[2*i+1] = 0.;
    }

    // Calculer la FFT
    DSPF_sp_cfftr2_dit(X_Z, w, 2*N);

    // Inverse-bit
    bitrev_index(index, N);

    DSPF_sp_bitrev_cplx((double *)X_Z, index, 2*N);

    for (i = 0; i < N;i++)
    {
        tableau_out_real[i] = X_Z[2*i];
        tableau_out_imag[i] = X_Z[2*i+1];
    }
}

void IFFT(float tableau_in_real[],float tableau_in_imag[],float tableau_out[])
{
    int i;
    #pragma DATA_ALIGN(X_Z,8);
    float X_Z[2*N];
    #pragma DATA_ALIGN(index,8);
    short index[128];


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
