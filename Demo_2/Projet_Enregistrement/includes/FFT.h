/*
 * FFT.h
 *
 *  Created on: 30 Mars 2019
 *      Author: Louis
 */

#ifndef SOURCE_C_FFT_H_
#define SOURCE_C_FFT_H_

#include "DSPF_sp_cfftr2_dit.h"
#include "DSPF_sp_icfftr2_dif.h"    //<--- SI JAMAIS ON EN A BESOIN SINON ON ENL�VERA CETTE LIGNE!
#include "twiddle_512.h"              //<--- LE "X" DANS LE NOM DOIT �TRE REMPLAC� PAR LE NOMBRE DE TWIDDLES CONTENUS DANS LE FICHIER!
#include <math.h>                   //<--- SI JAMAIS ON EN A BESOIN SINON ON ENL�VERA CETTE LIGNE!

//  INFO DONN�E PAR LAURENT COLAS ET BERTHI� GOUIN :
/*
 * LE PROTOTYPE ---> void FFT(float tableau_in[N], float tableau_out_real[N/2],float tableau_out_imag[N/2])
 * OBJECTIF -------> Couper la partie de gauche, garder la premi�re moiti�.
 *
 * R�F�RENCES -----> void faireAutocorr_fft(float bloc[], float resultat[]) <---- PROVENANT DE L'APP6
 */

void FFT(float tableau_in[N], float tableau_out_real[N/2],float tableau_out_imag[N/2] )
{
    /***************************************************************************************
    //STEP 1 :  R�CEPTION DES DONN�ES BRUTES R�ELLES :
    ***************************************************************************************/
    //          NB.: LES TAILLES ET TABLEAUX SUIVANTS DOIVENT �TRES D�CLAR�S EN TANT QUE VARIABLES GLOBALES!!!!!
    //               (ON LES VOIENT ICI QUE POUR MONTRER COMMENT TROUVER LEURS VALEURS ET/OU POUR FINS DE TESTS SI N�CESSAIRE)

    int TAILLE_BRUTE = 16000;    //<--- � D�TERMINER SELON LE NOMBRE D'�CHANTILLONS AQUISITIONN�S
    int TAILLE_TableFFT = 4*TAILLE_BRUTE;
    float TableFFT[TAILLE_TableFFT];

    int TAILLE_FFT = 2*TAILLE_BRUTE;
    int TAILLE_INDEX = ;                    //sqrt(2*TAILLE_BRUTE)
    short index[TAILLE_INDEX];

    int n;
    /***************************************************************************************
    //STEP 2 :  R�CEPTION DES DONN�ES BRUTES R�ELLES :
    //          (MISE DES R�ELS DANS LES CASES PAIRES, IMAGINAIRES (Z�ROS) DANS LES IMPAIRES
    //           ET PADDING DE Z�ROS � PARTIR DE LA MOITI� DU TABLEAU JUSQU'� LA FIN)
    ***************************************************************************************/
    //          NB.: LE TABLEAU DOIT �TRE 4 X LA LONGUEUR DU TABLEAU DE DONN�ES BRUTES
    //          EXEMPLE TIR� DE L'APP6 :
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
    //STEP 3 :  CALCUL DE LA FFT AVEC LA FONCTION "RADIX" CHOISIE (INPUT = �CHANTILLONS ORDONN�S, OUTPUT = �CHANTILLONS M�LANG�S)
    ***************************************************************************************/
    //          NB.: LES TWIDDLES "w" SONT G�N�R�S PAR L'UTILITAIRE DE "Texas Instrument" AVEC LA COMMANDE UTILISANT "L'invite de commande"
    //               (\ti\ccsv7\ccs_base\c6700\dsplib\bin\tw_r2fft.exe 512 > twiddle_X.h) ***NE PAS OUBLIER D'ENLEVER LE MOT "const" DANS LE FICHIER G�N�R�***

        DSPF_sp_cfftr2_dit(TableFFT, w, TAILLE_FFT);

    /***************************************************************************************
    //STEP 4 :  G�N�RER LES VALEURS D'INDEX EN UTILISANT LA FONCTION "bitrev_index(short index[], int nx)"
    ***************************************************************************************/
    //          NB-1.: "nx" VAUT LE NOMBRE D'�CHANTILLONS BRUTES R�ELS ... (voir SPRU657c).
    //          NB-2.: "index[]" DOIT �TRE DE TAILLE sqrt(2*nx) ET DONC UNE PUISSANCE DE 2.
    //          NB-3.: JE CROIS QU'IL SERAIS PR�F�RABLE DE CALCULER LES INDEX AU D�BUT DU MAIN ET DE METTRE LE TABLEAU D'INDEX COMME GLOBAL.
    //                 (�VITER DE RE-G�N�RER LES INDEX � CHAQUE APPEL DE LA FONCTION FFT)

        bitrev_index(index, TAILLE_BRUTE);

    /***************************************************************************************
    //STEP 5 :  REMETTRE LES �CHANTILLONS DANS L'ORDRE VIA LA FONCTION "DSPF_sp_bitrev_cplx((double *) TableFFT, index, nx)"
    ***************************************************************************************/

        DSPF_sp_bitrev_cplx((double *) TableFFT, index, TAILLE_BRUTE);

    /***************************************************************************************
    //STEP 6 :  R�CUP�RATION DES VALEURS R�ELLES ET IMAGINAIRES DE LA FFT DANS DES TABLEAUX RESPECTIFS.
    ***************************************************************************************/
    //          NB.: ON NE R�CUP�RE QUE LA 2e MOITI� DES VALEURS OBTENUES AVEC LA FFT.
    //               (DONC ON D�MARRE LA "boucle for" � LA MOITI� ET JUSQU'� LA FIN DU TABLEAU R�-ORDONN� DE LA FFT)
        for(n = TAILLE_FFT; n < TAILLE_TableFFT; n++){
            tableau_out_real[n] = TableFFT[n*2];
            tableau_out_imag[n] = TableFFT[n*2 + 1];
        }


}

#endif /* SOURCE_C_FFT_H_ */


