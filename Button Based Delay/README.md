# Button Based Delay
* Creator: Jessica Wozniak
* Created: October 4, 2017
* Last updated: October 9, 2017

##Libraries Used
* <msp430.h>

## Compatability:
* MSP430F5529
* MSP430FR2311
* MSP430FR5994
* MSP430FR6989
* MSP430G2553

## Program Description
The Button Based Delay program was made so that a user could hold down a button and the delay of the blink would be set to the amount of time the button was held down. The initial delay was set 10Hz on start up or reset. This progeam required two interrupts, one on Port2 and one on Timer0_A0. The button interrupt became active when the button was pressed. WIthin the button interrupt, a different timer, Timer0_A1, was started. The edge of the interrupt was then flipped, causing the timer to stop counting when the button was realeased. The value in TA1R was stored in  TA0CCR0. Then within the Timer0_A0 interrupt, the LED1 was set to toggle. The toggle then took on the delay of the new value stored in TA0CCR0. 

## Extra Work
### Reset Button
Instead of using the reset button that is wired into the development board, a reset using the other button was implemented. This was done by adding another interrupt on PORT1. If BUTTON2 is pressed, the value in  TA0CCR0 will be reset so the LED will blink at 10Hz.
