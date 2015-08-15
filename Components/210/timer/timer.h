/*
 * timer.h
 *
 *  Created on: 2015-08-15
 *      Author: yognanch
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <stdint.h>

#define TCFG0  (*((volatile uint32_t *)0xE2500000))
#define TCFG1  (*((volatile uint32_t *)0xE2500004))
#define TCNTB4 (*((volatile uint32_t *)0xE250003C))
#define TCNTO4 (*((volatile uint32_t *)0xE2500040))
#define TCON   (*((volatile uint32_t *)0xE2500008)) 


void  start_timimg(void); // using timer4 for timing
void stop_timimg( float *value );  // stop and return timing result in us


#endif /* TIMER_H_ */
