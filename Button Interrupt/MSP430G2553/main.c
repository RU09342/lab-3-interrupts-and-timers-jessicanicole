#include <msp430.h>

#define LED1 BIT0
#define BUTTON BIT3

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;// Stop watchdog timer

    P1DIR |=LED1; //set Port 1.0 output ---LED
    P1DIR &= ~BUTTON; //set Port 1.1 input --- pushbutton
    P1REN|=BUTTON;//enable pull-up resistor on
    P1OUT|=BUTTON;

    P1IE |=BUTTON;//enable the interrupt on Port 1.1
    P1IES |=BUTTON;//set as falling edge
    P1IFG &=~BUTTON;//clear interrupt flag
    //enter LPM4 mode and enable global interrupt

    _BIS_SR(LPM4_bits + GIE);
}

//Port 1 ISR
#pragma vector=PORT1_VECTOR
    __interrupt void PORT_1(void)
    {
        P1OUT ^= LED1;
        P1IFG &= ~(BUTTON);
    }
