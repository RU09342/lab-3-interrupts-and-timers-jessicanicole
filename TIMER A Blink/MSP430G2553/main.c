#include <msp430g2553.h>

#define LED1 BIT0

void main(void)
{
     WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

        TA0CTL=TASSEL_2+MC_1+ID_3;
        P1DIR|=LED1;
        TA0CCTL0 = CCIE;
        TA0CCR0 = 12000;

        __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0, enable interrupts
             __no_operation();
}

// Timer A0 interrupt service routine
#pragma vector= TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{

P1OUT ^= LED1;
}
