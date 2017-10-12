//Timer A Blink on the MSP430F5529
//Jessica Wozniak
//Created: 10/1/17
//Last updated: 10/5/17

#include <msp430.h>

#define LED1 BIT0                                 //Defines LED1 as BIT0

void main(void)
{
     WDTCTL = WDTPW | WDTHOLD;                    // stop watchdog timer

        TA0CTL=TASSEL_1+MC_1+TACLR;               //ACLK, UP MODE, Clear
        P1DIR|=LED1;                              //sets LED1 as output
        TA0CCTL0 = CCIE;                          //CCR0 interrupt enabled
        TA0CCR0 = 12000;                          //Sets initial value of TA0CCR0 to 12000, setting an initial delay for toggle

        __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0, enable interrupts
}

// Timer A0 ISR
#pragma vector=TIMER0_A0_VECTOR
    __interrupt void Timer_A (void)
    {
        P1OUT ^= LED1;                            //Toggles LED1
    }
