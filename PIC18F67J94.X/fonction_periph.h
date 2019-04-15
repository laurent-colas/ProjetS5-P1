/* 
 * File:   fonction_periph.h
 * Author: laure
 *
 * Created on 12 avril 2019, 12:26
 */

#ifndef FONCTION_PERIPH_H
#define	FONCTION_PERIPH_H

#ifdef	__cplusplus
extern "C" {
#endif

#define Relai_eau LATCbits.LATC4
#define DEL_SD LATCbits.LATC7
#define DEL_LD LATCbits.LATC6
#define DEL_ED LATCbits.LATC5
#define DEL_NC_S LATAbits.LATA1
#define DEL_NC_L LATFbits.LATF6
#define DEL_NC_E LATCbits.LATC2
#define DEL_TA_L LATCbits.LATC1
#define DEL_TA_E LATCbits.LATC0


    
void send_water(int cup_size);
void send_milk(int num_cup);
void send_sugar(int num_cup);
void init_periph(void);
void my_delay(int number_of_seconds); 
int digit_to_int(char d);

#ifdef	__cplusplus
}
#endif

#endif	/* FONCTION_PERIPH_H */

