//Button Based Delay on the MSP430F5529
//Jessica Wozniak
//Created: 10/5/17
//Last updated: 10/7/17

#include <msp430fr6989.h>

#define LED1 BIT0      //Defines LED1 as BIT0
#define LED2 BIT7      //Defines LED2 as BIT7
#define BUTTON BIT1    //Defines BUTTON as BIT1

void main(void) {

    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer

    P1DIR |=LED1;               //sets LED1 as output
    P9DIR |=LED2;               //sets LED2 as output

  //  P2DIR &= ~BUTTON;           //sets BUTTON as input
    P1REN|= BUTTON;              //enable pull-up resistor on
    P1OUT|= BUTTON;              //

    P1IE |= BUTTON;              //enable Button interrupt
    P1IES |= BUTTON;             //set as falling edge/ rising edge
    P1IFG &= ~BUTTON;           //clear interrupt flag

    TA0CCTL0 = CCIE;            // sets timer on compare mode
   // TA0CCR0 = 10000;          // sets initial frequency to 10Hz
    TA0CTL= TASSEL_1+MC_1;      // SMCLK, UP MODE, DIV 8

    PM5CTL0 &= ~LOCKLPM5;



    __bis_SR_register(LPM0_bits + GIE);  //enter LPM4 mode and enable global interrupt
}

//Port 2 ISR
#pragma vector=PORT1_VECTOR
    __interrupt void PORT_1(void)
    {
if (P1IES & BUTTON)
{
            TA1CTL = TASSEL_1 + MC_2;  //SMCLK, CONT MODE
            P9OUT ^= LED2;             //Turns on LED2
            P1IES &= ~BUTTON;          //flip edge
}
else
{

            TA0CCR0 = TA1R;            //set TA1R to capture compare to timer a_0
            P9OUT &= ~LED2;            //turn off LED2
            P1IES |= BUTTON;           //flip edge
            TA1CTL = TACLR;            //Clear timerA_1
}

//clears interrupt flag to exit interrupt
P1IFG &= ~BUTTON;
}
// Timer A0 ISR
#pragma vector= TIMER0_A0_VECTOR
    __interrupt void Timer_A0 (void)
    {
        P1OUT ^= LED1;
    }
