#include <msp430fr2311.h>

#define LED BIT0

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	TB0CTL=TBSSEL_2+MC_1+ID_3;  //SMCLK, UP MODE, DIV 8
	P1DIR|=LED;                 //LED is output
	TB0CCTL0 = CCIE;            //
	TB0CCR0 = 12000;            //

    PM5CTL0 &= ~LOCKLPM5;       //Disables High impedance mode

    __bis_SR_register(LPM3 + GIE);       // Enter LPM0, enable interrupts
         __no_operation();
}

#pragma vector=TIMER0_B0_VECTOR
__interrupt void Timer_B(void)
{
P1OUT^=LED;
}
