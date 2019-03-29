/*
 * File:   HC-SR04.c
 * Author: Laurent
 *
 * Created on 26 février 2019, 09:41
 */

#include "HC-SR04.h"
#include "pic18f67j94.h"

void init_dist_sensor(void) {
//    
    TRISDbits.TRISD0 = 0;
    TRISDbits.TRISD1 = 0;
    
    INTCON2bits.RBPU = 0;
    WPUBbits.WPUB1 = 1; // Activate pull-up on B1
    TRISBbits.TRISB1 = 1;
    
    Trigger_Pulse = 0;
    
    init_timer_1();    
}

void init_timer_1(void) {
//    T1CON = 0x02; // RD16 
//    PIR1bits.TMR1IF = 0;
    OSCCON = 0x07; //72;
    TMR1 = 0;
    T1CONbits.TMR1CS = 0;
//    T1CONbits.RD16 = 1;
    
    T1CKPS0 = 0;
    T1CKPS1 = 0;
    
    TMR1L = 0;
    TMR1H = 0;
}

void Trigger_Pulse_10us(int channel){
//    Trigger_Pulse = 1;
    if (channel == 1) {
        PORTDbits.RD0 = 1;
        __delay_us(10);
        //Trigger_Pulse = 0;
        PORTDbits.RD0 = 0;
    }
    else if (channel == 2) {
        PORTDbits.RD1 = 1;
        __delay_us(10);
        //Trigger_Pulse = 0;
        PORTDbits.RD1 = 0;
    }
    
}

int calc_distance_mm(int channel) {
    int a;
    int retour;
    const unsigned char dist[11] = "Distance = ";
    const unsigned char cm[3] = " cm";
    const unsigned char OoR[12] ="Out of Range";
    
    TMR1L = 0;
    TMR1H = 0;
    
    Trigger_Pulse_10us(channel);
    
    while(!PORTBbits.RB1);
    T1CONbits.TMR1ON = 1;
//    TMR1ON = 1;
    while(PORTBbits.RB1);
    T1CONbits.TMR1ON = 0;
//    TMR1ON = 0;
    
    a = (TMR1L | (TMR1H << 8));
    
    Distance_mm_int = (0.0272*a)/2; //TMR1 / 58.82;
            
    a = a/(58.82*2);
    a = a+1;
//    putStringLCD(&dist[0]);
//    putNumberLCD(Distance_mm_int);
    
    if (a>=2 && a <=400) {
        retour = a; 
    }
    else {
        retour = 0;
    }
//    __delay_ms(100);
    
//    while(PORTBbits.RB1 == 1 && !PIR1bits.TMR1IF);
//    Time = TMR1;
//    TMR1ON = 0;
//    Distance = ((float)Time/117.00);
//    Distance_mm_int = (int)(Distance * 10);
//    
//    return Distance_mm_int;
    return retour;
}