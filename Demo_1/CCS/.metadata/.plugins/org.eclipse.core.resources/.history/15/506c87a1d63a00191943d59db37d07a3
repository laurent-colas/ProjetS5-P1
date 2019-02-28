/*
 * norm.h
 *
 *  Created on: Feb 26, 2019
 *      Author: berth
 */

#ifndef SOURCE_HEADER_NORM_H_
#define SOURCE_HEADER_NORM_H_
#include "max.h"
#include "abs.h"

void norm(double x[], int l) {
	double temp[2*length-1];
	int i;
	for (i = 0; i < 2 * length - 1; i++)
	{
		temp[i] = x[i];
	}
	absolute(temp, 2 * length - 1);				// redressement
	double AbsMax = max(temp, 2 * length - 1);	// valeur max
	
// boucle principale qui normalise le signal
	for (i = 0; i < l; i++)
	{
		x[i] = x[i] / AbsMax;
	}
}
#endif  /*SOURCE_HEADER_NORM_H_ */
