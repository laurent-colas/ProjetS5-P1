/* 
 * File:   UART_MAX.h
 * Author: laure
 *
 * Created on 14 mars 2019, 10:56
 */

#ifndef UART_MAX_H
#define	UART_MAX_H

#include <xc.h>
#include <usart.h>

#include "pic18f67j94.h"

void SetupClock(void);
void init_UART(void);
void send_data(char input);

#ifdef	__cplusplus
}
#endif

#endif	/* UART_MAX_H */

