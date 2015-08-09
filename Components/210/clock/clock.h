/*
 * clock.h
 *
 *  Created on: 2012-12-18
 *      Author: cya
 */

#ifndef CLOCK_H_
#define CLOCK_H_

#include <stdint.h>

//  PIN XOM0 must be low

#define XXTI  (24000000)            //  external crystal, Hz

#define CLK_SRC0        (*((volatile uint32_t *)0xE0100200))     // Clock Source Control Registers
#define CLK_SRC4        (*((volatile uint32_t *)0xE0100210))     // Clock Source Control Registers, b19~16:UART0_SEL
#define CLK_DIV0        (*((volatile uint32_t *)0xE0100300))     // Clock Divider Control Register
#define CLK_DIV4        (*((volatile uint32_t *)0xE0100310))     // Clock Divider Control Register, b19~16:UART0_RATIO
#define CLK_GATE_IP1    (*((volatile uint32_t *)0xE0100464))
#define CLK_GATE_IP3    (*((volatile uint32_t *)0xE010046C))     // Clock Gating Control Register
#define MPLL_CON        (*((volatile uint32_t *)0xE0100108))     // MPLL Control Registers
#define APLL_CON0       (*((volatile uint32_t *)0xE0100100))     // APLL Control Registers


uint32_t get_hclk_dsys(void);
uint32_t get_sclk_mpll(void);
uint32_t get_sclk_apll(void);

#endif /* CLOCK_H_ */
