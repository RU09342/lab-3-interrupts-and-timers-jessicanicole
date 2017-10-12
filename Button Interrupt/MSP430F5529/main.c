//Button Interrupt on the MSP430F5529
//Jessica Wozniak
//Created: 10/1/17
//Last updated: 10/11/17

//Based on code from NICK K. Thanks man.

#include <msp430f5529.h>

#define LED1 BIT0                   //defines LED1 as BIT0
#define LED2 BIT7                   //defines LED2 as BIT7
#define BUTTON BIT1                 //defines BUTTON1 as BIT1

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;       // Stop watchdog timer

    P1DIR |=LED1;                   //sets LED1 as output
    P4DIR |= LED2;                  //Sets LED2 as output

    P2DIR &= ~BUTTON;               //sets BUTTON1 as input
    P2REN|=BUTTON;                  //enable pull-up resistor
    P2OUT|=BUTTON;                  //Writes a "1" to the portpin, telling the resistor to pullup

    P2IE |= BUTTON;                  //enable the interrupt on Port 2.1- BUTTON1
    P2IES |=BUTTON;                 //set as falling edge
    P2IFG &=~BUTTON;                //clear interrupt flag

    //enter LPM0 mode and enable global interrupt
    _BIS_SR(LPM0_bits + GIE);
}

//Port 2 ISR
#pragma vector=PORT2_VECTOR
    __interrupt void PORT_2(void)
    {
        if (!(BUTTON & P2IN))
        {
        P1OUT ^= LED1;              //Toggles LED1
        P2IES &= ~BUTTON;           //set as rising edge
        }
        else
        {
        P4OUT ^= LED2;              //toggles LED2
        P2IES |= BUTTON;            //sets as falling edge
        }
        P2IFG &= ~BUTTON;           //clears interrupt flag and exits interrupt
     }
