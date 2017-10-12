//Button Interrupt on the MSP430G2553
//Jessica Wozniak
//Created: 10/1/17
//Last updated: 10/5/17

#include <msp430.h>

#define LED1 BIT0                   //defines LED1 as BIT0
#define BUTTON BIT1                 //defines BUTTON as BIT1

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;       // Stop watchdog timer

    P1DIR |=LED1;                   //set Port 1.0 output ---LED

    P1DIR &= ~BUTTON;               //set Port 1.1 input --- pushbutton
    P1REN|=BUTTON;                  //enable pull-up resistor on
    P1OUT|=BUTTON;                  //Writes a "1" to the portpin, telling the resistor to pullup

    P1IE |=BUTTON;                  //enable the interrupt on Port 1.1
    P1IES |=BUTTON;                 //set as falling edge
    P1IFG &=~BUTTON;                //clear interrupt flag


    PM5CTL0 &= ~LOCKLPM5;           //disables high impedance mode

    _BIS_SR(LPM4_bits + GIE);        //enter LPM4 mode and enable global interrupt
}

//Port 1 ISR
#pragma vector=PORT1_VECTOR
    __interrupt void PORT_1(void)
    {
        P1OUT ^= LED1;              //Toggles LED1
        P1IFG &= ~(BUTTON);         //clears interrupt flag
    }
