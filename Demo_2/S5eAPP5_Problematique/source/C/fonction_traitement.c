/*
 * fonction_traitement.c
 *
 *  Created on: 1 avr. 2019
 *      Author: laure
 */



#include "functionHelperProjetS5.h"
#include "DSPF_sp_cfftr2_dit.h"
#include "DSPF_sp_icfftr2_dif.h"    //<--- SI JAMAIS ON EN A BESOIN SINON ON ENLÈVERA CETTE LIGNE!
#include "twiddle_512.h"              //<--- LE "X" DANS LE NOM DOIT ÊTRE REMPLACÉ PAR LE NOMBRE DE TWIDDLES CONTENUS DANS LE FICHIER!
#include <math.h>                   //<--- SI JAMAIS ON EN A BESOIN SINON ON ENLÈVERA CETTE LIGNE!

int i = 0;



void magnitude_complex(float tableau_in_real[], float tableau_in_imag[], float tableau_out_magnitude[],int length) {
    for (i = 0; i < length; i++)
    {
        tableau_out_magnitude[i] = sqrt((tableau_in_real[i])*(tableau_in_real[i]) + (tableau_in_imag[i])*(tableau_in_imag[i]));
    }
}

void phase_complex(float tableau_in_real[], float tableau_in_imag[], float tableau_out_phase[], int length) {
    for (i = 0; i < length; i++)
    {
        tableau_out_phase[i] = (float) atan2((double) tableau_in_imag[i],(double) tableau_in_real[i]);
    }
}

void fenetre_hamming(float w[], int length) {
    for (i = 0; i < length; i++)
    {
        w[i] = (float) (0.54 - 0.46*cos(2 * 3.14* i / length));
    }
}

void fenetre_triangle(float w[], int length) {
//    float temp;
    if (length % 2 == 0) {
        for (i = 1; i <= length / 2; i++)
        {
            w[i-1] = (((2 * i - 1)) / (float)(length));
        }
        for (i = (length / 2) + 1; i <= length; i++)
        {
            w[i-1] = (2 - (((2 * i - 1)) / (float)(length)));
        }
    }
    else {
        for (i = 1; i <= length / 2; i++)
        {
            w[i-1] = ((2 * i) / (length + 1));
        }
        for (i = (length / 2)+1; i <= length; i++)
        {
            w[i-1] = (2 - ((2 * i) / (length + 1)));
        }
    }

}

void FFT(float tableau_in[N], float tableau_out_real[N/2],float tableau_out_imag[N/2] )
{
    /***************************************************************************************
    //STEP 1 :  RÉCEPTION DES DONNÉES BRUTES RÉELLES :
    ***************************************************************************************/
    //          NB.: LES TAILLES ET TABLEAUX SUIVANTS DOIVENT ÊTRES DÉCLARÉS EN TANT QUE VARIABLES GLOBALES!!!!!
    //               (ON LES VOIENT ICI QUE POUR MONTRER COMMENT TROUVER LEURS VALEURS ET/OU POUR FINS DE TESTS SI NÉCESSAIRE)

    int TAILLE_BRUTE = 16000;    //<--- À DÉTERMINER SELON LE NOMBRE D'ÉCHANTILLONS AQUISITIONNÉS
    int TAILLE_TableFFT = 4*N;
    float TableFFT[640000];

    int TAILLE_FFT = 2*N;
    int TAILLE_INDEX = 180;                    //sqrt(2*TAILLE_BRUTE)
    short index[180];

    int n;
    /***************************************************************************************
    //STEP 2 :  RÉCEPTION DES DONNÉES BRUTES RÉELLES :
    //          (MISE DES RÉELS DANS LES CASES PAIRES, IMAGINAIRES (ZÉROS) DANS LES IMPAIRES
    //           ET PADDING DE ZÉROS À PARTIR DE LA MOITIÉ DU TABLEAU JUSQU'À LA FIN)
    ***************************************************************************************/
    //          NB.: LE TABLEAU DOIT ÊTRE 4 X LA LONGUEUR DU TABLEAU DE DONNÉES BRUTES
    //          EXEMPLE TIRÉ DE L'APP6 :
    //                                      TAILLE_BRUTE = 256;
    //                                      TAILLE_TableFFT = 4 * 256 = 1024;
    //                                      TAILLE_FFT = 2 * 256 = 512;
    //                                      TAILLE_TWIDDLES = 2 * 256 = 512



    for(n = 0; n < TAILLE_BRUTE; n++){
        TableFFT[n*2] = tableau_in[n];
        TableFFT[n*2 + 1] = 0;
        TableFFT[n*2 + TAILLE_FFT] = 0;
        TableFFT[n*2 + 1 + TAILLE_FFT] = 0;
    }
    /***************************************************************************************
    //STEP 3 :  CALCUL DE LA FFT AVEC LA FONCTION "RADIX" CHOISIE (INPUT = ÉCHANTILLONS ORDONNÉS, OUTPUT = ÉCHANTILLONS MÉLANGÉS)
    ***************************************************************************************/
    //          NB.: LES TWIDDLES "w" SONT GÉNÉRÉS PAR L'UTILITAIRE DE "Texas Instrument" AVEC LA COMMANDE UTILISANT "L'invite de commande"
    //               (\ti\ccsv7\ccs_base\c6700\dsplib\bin\tw_r2fft.exe 512 > twiddle_X.h) ***NE PAS OUBLIER D'ENLEVER LE MOT "const" DANS LE FICHIER GÉNÉRÉ***

        DSPF_sp_cfftr2_dit(TableFFT, w, TAILLE_FFT);

    /***************************************************************************************
    //STEP 4 :  GÉNÉRER LES VALEURS D'INDEX EN UTILISANT LA FONCTION "bitrev_index(short index[], int nx)"
    ***************************************************************************************/
    //          NB-1.: "nx" VAUT LE NOMBRE D'ÉCHANTILLONS BRUTES RÉELS ... (voir SPRU657c).
    //          NB-2.: "index[]" DOIT ÊTRE DE TAILLE sqrt(2*nx) ET DONC UNE PUISSANCE DE 2.
    //          NB-3.: JE CROIS QU'IL SERAIS PRÉFÉRABLE DE CALCULER LES INDEX AU DÉBUT DU MAIN ET DE METTRE LE TABLEAU D'INDEX COMME GLOBAL.
    //                 (ÉVITER DE RE-GÉNÉRER LES INDEX À CHAQUE APPEL DE LA FONCTION FFT)

        bitrev_index(index, TAILLE_BRUTE);

    /***************************************************************************************
    //STEP 5 :  REMETTRE LES ÉCHANTILLONS DANS L'ORDRE VIA LA FONCTION "DSPF_sp_bitrev_cplx((double *) TableFFT, index, nx)"
    ***************************************************************************************/

        DSPF_sp_bitrev_cplx((double *) TableFFT, index, TAILLE_BRUTE);

    /***************************************************************************************
    //STEP 6 :  RÉCUPÉRATION DES VALEURS RÉELLES ET IMAGINAIRES DE LA FFT DANS DES TABLEAUX RESPECTIFS.
    ***************************************************************************************/
    //          NB.: ON NE RÉCUPÈRE QUE LA 2e MOITIÉ DES VALEURS OBTENUES AVEC LA FFT.
    //               (DONC ON DÉMARRE LA "boucle for" À LA MOITIÉ ET JUSQU'À LA FIN DU TABLEAU RÉ-ORDONNÉ DE LA FFT)
        for(n = TAILLE_FFT; n < TAILLE_TableFFT; n++){
            tableau_out_real[n] = TableFFT[n*2];
            tableau_out_imag[n] = TableFFT[n*2 + 1];
        }


}
