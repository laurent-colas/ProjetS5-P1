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
	int i = 0;
	for (; i < 2 * length - 1; i++)
	{
		temp[i] = x[i];
	}
	absolute(temp, 2 * length - 1);
	double AbsMax = max(temp, 2 * length - 1);
	i = 0;
	for (; i < l; i++)
	{
		x[i] = x[i] / AbsMax;
	}
}
#endif  /*SOURCE_HEADER_NORM_H_ */
