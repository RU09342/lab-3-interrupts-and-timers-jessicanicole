#include <msp430FR5994.h>

#define LED1 BIT0
#define BUTTON BIT6

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;// Stop watchdog timer

    P1DIR |=LED1; //set Port 1.0 output ---LED
    P5DIR &= ~BUTTON; //set Port 5.6 input --- pushbutton
    P5REN|=BUTTON;//enable pull-up resistor on
    P5OUT|=BUTTON;

    P5IE |=BUTTON;//enable the interrupt on Port 5.6
    P5IES |=BUTTON;//set as falling edge
    P5IFG &=~BUTTON;//clear interrupt flag
    //enter LPM4 mode and enable global interrupt

    PM5CTL0 &= ~LOCKLPM5;

    _BIS_SR(LPM4_bits + GIE);
}

//Port 1 ISR
#pragma vector=PORT5_VECTOR
    __interrupt void PORT_5(void)
    {
        P1OUT ^= LED1;
        P5IFG &= ~(BUTTON);
    }
