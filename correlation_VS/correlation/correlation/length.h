/*
 * length.h
 *
 *  Created on: Feb 26, 2019
 *      Author: berth
 */

 #ifndef SOURCE_HEADER_LENGTH_H_
#define SOURCE_HEADER_LENGTH_H_ 

int length(double x[]) {

	int length = sizeof(x) / sizeof(x[1]);

	return length;
}
 #endif /*SOURCE_HEADER_LENGTH_H_ */
