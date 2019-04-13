/*
 * max.h
 *
 *  Created on: Feb 26, 2019
 *      Author: berth
 */

#ifndef SOURCE_HEADER_MAX_H_
#define SOURCE_HEADER_MAX_H_

double max(double x[], int l) {
	
double tempMax = 0;
int i ;
	for (i= 0; i < l; i++)
	{
		if (x[i] > tempMax)
		{
			tempMax = x[i];
		}
	}
	return tempMax;
}
#endif  /*SOURCE_HEADER_LENGTH_H_ */
