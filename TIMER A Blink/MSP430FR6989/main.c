#include <msp430fr6989.h>

#define LED BIT0

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    TB0CTL=TASSEL_2+MC_1+ID_3;
    P1DIR|=LED;
    TA0CCTL0 = CCIE;
    TA0CCR0 = 12000;

    PM5CTL0 &= ~LOCKLPM5;

    __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0, enable interrupts
         __no_operation();
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A(void)
{
P1OUT^=LED;
}
