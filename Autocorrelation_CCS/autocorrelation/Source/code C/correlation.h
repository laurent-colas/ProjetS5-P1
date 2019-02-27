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

void correlation(double x[], double y[],int l,double out[]) {

	//const int size = (3 * length) - 2;
	double tempx[(3 * length) - 2];
	double tempy[(3 * length) - 2];

// Ajout de "0" avant et après pour pouvoir faire les oppérations
	int i = 0;
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
		for (k;k < 2*l -1; k++)
		{
			out[i] = out[i] + tempx[k] * tempy[k];
		}
		
	}
	norm(out, 2 * l - 1);		// normalisation
}
#endif  /*SOURCE_HEADER_CORRELATION_H_*/
