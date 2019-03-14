/*
 * File:   UART_MAX.c
 * Author: laure
 *
 * Created on 14 mars 2019, 14:57
 */


#include <xc.h>
#include "UART_MAX.h"


void SetupClock(){
    /*
    NOSC<2:0>: New Oscillator Selection bits
    000 = Fast RC Oscillator (FRC)
    001 = Fast RC Oscillator (FRC), divided by N, with PLL module
    010 = Primary Oscillator (MS, HS, EC)
    011 = Primary Oscillator (MS, HS, EC) with PLL module
    100 = Secondary Oscillator (SOSC)
    101 = Low-Power RC Oscillator (LPRC)
    110 = Fast RC Oscillator (FRC) divided by 16 (500 kHz)
    111 = Fast RC Oscillator (FRC) divided by N
     */
    OSCCONbits.NOSC0 = 1;
    OSCCONbits.NOSC1 = 1;
    OSCCONbits.NOSC2 = 1;
}

void init_UART() {
    SetupClock(); 
    
    SPBRGH = 12; // Baude rate value
    OSCCON2bits.IOLOCK = 0; //Register values can only be changed if IOLOCK = 0

    //RX pin set as input
    RPINR0_1bits.U1RXR = 0x6; //RP27 RD7
    //TX pin set as output
    RPOR26_27bits.RPO26R = 0x1; //RP26 RD6
    
    // Internal Clock to 8MHz
    // RCSTAbits.SPEN = 1;

//    SPBRG = 64; //107;//64;
    
//     BAUDCONx: BAUD RATE CONTROL REGISTER
    /*
     * 1 = Receive data (RXx) is inverted (active-low)
     * 0 = Receive data (RXx) is not inverted (active-high)
     * 1 = Idle state for transmit (TXx) is a low level
     * 0 = Idle state for transmit (TXx) is a high leve
     */
    BAUDCONbits.TXCKP = 1;
    BAUDCONbits.RXDTP = 1;
    
    // TXSTAx: EUSARTx TRANSMIT STATUS AND CONTROL REGISTER
    TXSTAbits.TX9 = 0; //9-Bit Transmit Enable bit 
    TXSTAbits.TXEN = 1; //Transmit Enable bit
    TXSTAbits.SYNC = 0; //EUSARTx Mode Select bit
    TXSTAbits.SENDB = 0; //Send Break Character bit
    TXSTAbits.BRGH = 1; //High Baud Rate Select bit 
    TXSTAbits.TX9D = 0; //9th bit of Transmit Data
    
    RCSTAbits.SPEN = 1; //Serial Port Enable bit
    RCSTAbits.RX9 = 0; //9-Bit Receive Enable bit
    RCSTAbits.CREN = 1; //Continuous Receive Enable bit 
//    RCSTAbits.ADDEN = 0; //Address Detect Enable bit
//    RCSTAbits.RX9D = 0;
//    RCSTA = 0x90;
    // p 170
    RCONbits.IPEN = 1; //Interrupt Priority Enable Register bit
    
    INTCONbits.GIE = 1; //Global Interrupt Enable bit
    INTCONbits.PEIE = 1; //Peripheral Interrupt Enable bit
    PIE1bits.RC1IE = 1; //EUSART1 Receive Interrupt Enable bit
    PIE1bits.TXIE = 0; //EUSART1 Transmit Interrupt Enable bit 
    
}

void send_data(char input) {
    while(TXIF==0);
    TXREG1 = input; //out;
}
