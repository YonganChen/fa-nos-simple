/*
 * wait.c
 *
 *  Created on: 2014-11-4
 *      Author: chya
 */


#include "si470x_wait.h"
#include "../delay/delay.h"

//-----------------------------------------------------------------------------
// delay routine for long delays
//
// Inputs:
//      Delay in milliseconds
//-----------------------------------------------------------------------------
void wait_ms(uint16_t ms)
{
    int i;

    for ( i = 0; i < ms; i++ ) {
        wait_us(1000);
    }
}

//-----------------------------------------------------------------------------
// Delay routine based on hardware timer
//
// Inputs:
//      Delay in microseconds
//-----------------------------------------------------------------------------
void wait_us(uint16_t us)
{
    delay(DELAY_1US_VAL*us*10);
}

//-----------------------------------------------------------------------------
// delay routine for small delays.  Assume each for loop takes
// at least 64nS, and divide parameter by just doing a shift.
// This routine primarily exists for documentation purposes.
// On this 8051, all waits will be much longer than they need to be.
//
// Inputs:
//		Delay in nanoseconds
//-----------------------------------------------------------------------------
void wait_ns(uint16_t ns)
{
    uint8_t i;

    for ( i = 1; i <= ns / 32; i++ )
    ;
}

void _nop_(void)
{
	volatile uint8_t i;
	i++;
}
