/* 
 * File:   HC-SR04.h
 * Author: laure
 *
 * Created on 26 février 2019, 10:29
 */

#ifndef HC_SR04_H
#define	HC_SR04_H

#include <xc.h>
#include "LCD_SPI.h"

void Trigger_Pulse_10us(int channel);
void init_dist_sensor(void);
void init_timer_1(void);
int calc_distance_mm(int channel);

#define Trigger_Pulse LATDbits.LATD0	/* Define Trig pin of HC-SR04  IOD0*/
#define _XTAL_FREQ 8000000	/* Define freq */

float Distance;
int Distance_mm_int;
int Time;
float Total_distance[10];



#ifdef	__cplusplus
}
#endif

#endif	/* HC_SR04_H */

