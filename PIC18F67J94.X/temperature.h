/* 
 * File:   temperature.h
 * Author: laure
 *
 * Created on 15 mars 2019, 11:20
 */

#ifndef TEMPERATURE_H
#define	TEMPERATURE_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#define RT0 10000   // ?
#define B 3977      // K
#define VCC 5    //Supply voltage
#define R 10000  //R=10K?
    
void init_ADC(void);
int get_temp(int channel);
void Delay(void);
void chauffe_eau(int etat);

#ifdef	__cplusplus
}
#endif

#endif	/* TEMPERATURE_H */

