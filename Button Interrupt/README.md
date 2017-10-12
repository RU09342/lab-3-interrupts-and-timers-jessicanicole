# Button Interrupt
* Creator: Jessica Wozniak
* Created: October 4, 2017
* Last updated: October 8, 2017

## Libraries Used
* <msp430.h>

## Compatability:
* MSP430F5529
* MSP430FR2311
* MSP430FR5994
* MSP430FR6989
* MSP430G2553

## Program Description
The Button Interrupt Program was made to learn how to use interrupts vs. polling. LED1 and LED2 were initialized to be outputs, the button was set as an input. The interrupt was enabled and set to the falling edge of the button. Within the button interrupt, an if else statement was made to turn on LED1 if the button was pressed and turn on LED2 when button was realeased. In the if statement the edge of the interrupt was flipped to detect the button being released, and then was flipped again in the else portion. 