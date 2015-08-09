/*
 * syscon.c
 *
 *  Created on: 2013-10-29
 *      Author: chya
 */

#include <stdint.h>
#include "syscon.h"


void  enter_sleep_mode()
{
	SLEEP_CFG    = 0x03;          //  EN XUSBXTI X-tal Oscillator pad and XXTI X-tal oscillator pad in SLEEP mode
    PWR_CFG     |= (1<<9|1<<8);   //  Enter SLEEP mode
    PMU_OTHERS  |= (1<<0);        //  SYSCON_INT_DISABLE
    asm("wfi");
    asm("wfi");

}
