/*
 * analyse_son.c
 *
 *  Created on: 1 avr. 2019
 *      Author: Laurent Colas
 */
#include "functionHelperProjetS5.h"

float fen_triang[8000];

void analyse_son(float tableau_son_in[]) {

}

void pre_traitement(struct TABLEAU_INIT Ech_1, struct TABLEAU_INIT Ech_2, struct TABLEAU_INIT Ech_3 ){
//        float tableau_son_in1[], float tableau_son_in2[], float tableau_son_in3[]) {
    int i = 0;
//    float tableau_son_organiser[3] = {tableau_son_in1, tableau_son_in2, tableau_son_in3};
    fenetre_triangle(fen_triang, 8000);

    FFT(Ech_1.signal_in[], Ech_1.real_tableau_in[], Ech_1.imag_tableau_in[]);
    FFT(Ech_2.signal_in[], Ech_2.real_tableau_in[], Ech_2.imag_tableau_in[]);
    FFT(Ech_3.signal_in[], Ech_3.real_tableau_in[], Ech_3.imag_tableau_in[]);

    magnitude_complex(Ech_1.real_tableau_in[], Ech_1.imag_tableau_in[], Ech_1.mag_tableau_in[], N);


}
