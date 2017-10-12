# TIMER A Blink
* Creator: Jessica Wozniak
* Created: October 4, 2017
* Last updated: October 8, 2017

##Libraries Used
* <msp430.h>

## Compatability:
* MSP430F5529
* MSP430FR2311
* MSP430FR5994
* MSP430FR6989
* MSP430G2553

## Program Description
The Timer A Blink program was made to use an interrupt on Timer A to blink an LED at an initilized delay rate of the value in TA0CCR0. The timer was initilized as using ACLK (32 kHz) and in UP MODE. In UP MODE the timer counts to the value in TA0CCR0,goes back to 0, and counts up again. In this program the timer counts up to 12000, so everys 12000 ticks, the LED will toggle.
