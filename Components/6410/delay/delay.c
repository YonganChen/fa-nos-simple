/*
 * delay.c
 *
 *  Created on: 2014-10-31
 *      Author: chya
 */


#include <stdint.h>
#include "delay.h"

/*
 *  delay some time
 */
void delay(volatile uint32_t count)
{
	for(;count>0;count--){
	}
}
