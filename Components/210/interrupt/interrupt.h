/*
 * interrupt.h
 *
 *  Created on: 2013-10-29
 *      Author: chya
 */

#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#define VIC0INTENABLE   (*((volatile uint32_t *)0xF2000010))     //
#define VIC1INTENABLE   (*((volatile uint32_t *)0xF2100010))     //
#define VIC2INTENABLE   (*((volatile uint32_t *)0xF2200010))     //
#define VIC3INTENABLE   (*((volatile uint32_t *)0xF2300010))     //
#define VIC0VECTADDR16  (*((volatile uint32_t *)0xF2000140))     //
#endif /* INTERRUPT_H_ */
