//Button Based Delay on the MSP430F5529
//Jessica Wozniak
//Created: 10/5/17
//Last updated: 10/7/17

#include <msp430fr5994.h>

#define LED1 BIT0      //Defines LED1 as BIT0
#define LED2 BIT1     //Defines LED2 as BIT1
#define BUTTON BIT6    //Defines BUTTON as BIT6

void main(void) {

    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer

    P1DIR |=LED1;               //sets LED1 as output
    P1DIR |=LED2;               //sets LED2 as output

  //  P2DIR &= ~BUTTON;           //sets BUTTON as input
    P5REN|= BUTTON;              //enable pull-up resistor on
    P5OUT|= BUTTON;              //

    P5IE |= BUTTON;              //enable Button interrupt
    P5IES |= BUTTON;             //set as falling edge/ rising edge
    P5IFG &= ~BUTTON;           //clear interrupt flag

    TA0CCTL0 = CCIE;            // sets timer on compare mode
   // TA0CCR0 = 10000;          // sets initial frequency to 10Hz
    TA0CTL= TASSEL_1+MC_1;      // SMCLK, UP MODE, DIV 8

    PM5CTL0 &= ~LOCKLPM5;

    __bis_SR_register(LPM0_bits + GIE);  //enter LPM4 mode and enable global interrupt
}

//Port 2 ISR
#pragma vector=PORT5_VECTOR
    __interrupt void PORT_5(void)
    {
if (P5IES & BUTTON)
{
            TA1CTL = TASSEL_1 + MC_2;  //SMCLK, CONT MODE
            P1OUT ^= LED2;             //Turns on LED2
            P5IES &= ~BUTTON;          //flip edge
}
else
{

            TA0CCR0 = TA1R;            //set TA1R to capture compare to timer a_0
            P1OUT &= ~LED2;            //turn off LED2
            P5IES |= BUTTON;           //flip edge
            TA1CTL = TACLR;            //Clear timerA_1
}

//clears interrupt flag to exit interrupt
P2IFG &= ~BUTTON;
}
// Timer A0 ISR
#pragma vector= TIMER0_A0_VECTOR
    __interrupt void Timer_A0 (void)
    {
        P1OUT ^= LED1;
    }
