/*
 * correlation.h
 *
 *  Created on: Feb 26, 2019
 *      Author: berth
 */

#ifndef SOURCE_HEADER_CORRELATION_H_
#define SOURCE_HEADER_CORRELATION_H_

#include "max.h"
#include "abs.h"
#include "norm.h"

#define length 8192

double AutoCorrelation(double * tab1, int longueur, double * tab2);

void correlation(double x[], double y[],int l,double out[]) {

    int i = 0;

    //Déclaration de tableaux temporaires pour les calculs des coefficients
	double tempx[(3 * length) - 2];
	double tempy[(3 * length) - 2];

	//Déclaration du tableau pour le résultat assembleur
	double res_asm_corr [2*length -1];

	//Déclaration des coefficients d'autocorrelation
    double rxx0 = 0;
    double ryy0 = 0;

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
#endif  /*SOURCE_HEADER_CORRELATION_H_*/
