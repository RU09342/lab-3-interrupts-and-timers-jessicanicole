//Button Based Delay on the MSP430F5529
//Jessica Wozniak
//Created: 10/5/17
//Last updated: 10/10/17

// Thanks to Tomas

#include <msp430f5529.h>

#define LED1 BIT0      //Defines LED1 as BIT0
#define LED2 BIT7      //Defines LED2 as BIT7
#define BUTTON BIT1    //Defines BUTTON as BIT1
#define BUTTON2 BIT1   //Defines BUTTON2 as BIT1

void main(void) {

    WDTCTL = WDTPW | WDTHOLD;   //Stop watchdog timer

    P1DIR |=LED1;               //sets LED1 as output
    P4DIR |=LED2;               //sets LED2 as output

    P2DIR &= ~BUTTON;           //sets BUTTON as input
    P2REN|= BUTTON;             //enable pull-up resistor on
    P2OUT|= BUTTON;             //

    P1DIR &= ~BUTTON2;          //sets BUTTON as input
    P1REN|= BUTTON2;            //enable pull-up resistor on
    P1OUT|= BUTTON2;            //

    P2IE |= BUTTON;             //enable Button interrupt
    P2IES |= BUTTON;            //set as falling edge/ rising edge
    P2IFG &= ~BUTTON;           //clear interrupt flag

    P1IE |= BUTTON2;            //enable Button interrupt
    P1IES |= BUTTON2;           //set as falling edge/ rising edge
    P1IFG &= ~BUTTON2;          //clear interrupt flag

    TA0CCTL0 = CCIE;            // sets timer on compare mode
    TA0CCR0= 1600;              // sets initial frequency to 10Hz
    TA0CTL= TASSEL_1+MC_1;      // SMCLK, UP MODE, DIV 8


    __bis_SR_register(LPM0_bits + GIE);  //enter LPM4 mode and enable global interrupt
}

//Port 2 ISR
#pragma vector=PORT2_VECTOR
    __interrupt void PORT_2(void)
    {
if (P2IES & BUTTON)
{
            TA1CTL = TASSEL_1 + MC_2;  //SMCLK, CONT MODE
            P4OUT ^= LED2;             //Turns on LED2
            P2IES &= ~BUTTON;          //flip edge
}
else
{
            TA0CCR0 = TA1R;            //set TA1R to capture compare to timer a_0
            P4OUT &= ~LED2;            //turn off LED2
            P2IES |= BUTTON;           //flip edge
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
#pragma vector = PORT1_VECTOR
    __interrupt void Port_1 (void)
    {
        if (P1IES & BUTTON2)    //if BUTTON2 is pressed
        {
            TA0CCR0 = 1600;     //Reset delay to 10kHz
        }
        P1IFG &= ~BUTTON2;
    }
