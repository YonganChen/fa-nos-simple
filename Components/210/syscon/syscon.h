/*
 * syscon.h
 *
 *  Created on: 2013-10-29
 *      Author: chya
 */

#ifndef SYSCON_H_
#define SYSCON_H_


/* Power Management Register (PMU) */

#define SLEEP_CFG        (*((volatile uint32_t *)0xE010C040))     //
#define	PWR_CFG			 (*((volatile uint32_t *)0xE010C000))     //
#define PMU_OTHERS       (*((volatile uint32_t *)0xE010E000))     //


void  enter_sleep_mode();


#endif /* SYSCON_H_ */
