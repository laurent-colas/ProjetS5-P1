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

	absolute(x,l);
	double AbsMax = max(x,l);
	for (int i = 0; i < l; i++)
	{
		x[i] = x[i] / AbsMax;
	}
}
#endif  /*SOURCE_HEADER_NORM_H_ */
