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

	const int size = (3 * length) - 2;
	double tempx[size];
	double tempy[size];

	int i = 0;
	for (i; i < l-1; i++)
	{
		tempx[i] = 0;
	}

	i = 0;
	for (i; i < l; i++)
	{
		tempx[l-1+i] = x[i];
	}

	i = 0;
	for (i; i < l-1; i++)
	{
		tempx[i+2*l-1] = 0;
	}

	i = 0;
	int j = 0;
	for (i; i < 2*l - 1; i++)
	{
		j = 0;
		for (j; j < i ; j++)
		{

		}
		
	}


}
#endif  /*SOURCE_HEADER_CORRELATION_H_*/
