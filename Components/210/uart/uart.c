/*
 *  uart.c
 *
 *  Created on: 2012-12-17
 *      Author: cya
 */

#include <stdint.h>
#include "uart.h"
#include "../gpio/gpio.h"
#include "../clock/clock.h"


static const uint32_t udivslot_val[16] = {
		0x0000, 0x0080, 0x0808, 0x0888, 0x2222, 0x4924, 0x4A52, 0x54AA,
		0x5555, 0xD555, 0xD5D5, 0xDDD5, 0xDDDD, 0xDFDD, 0xDFDF, 0xFFDF
};

/*
 * 8bits data, none pair, no flow ctrl, 1 stop bit, FIFO disable
 */
void uart0_init(uint32_t baudrate)
{

	uint32_t div_val;
	                          // set the baudrate
    div_val = (XXTI*10/baudrate/16)-10;
	UBRDIV0 = div_val/10;
	UDIVSLOT0 = udivslot_val[(div_val%10)*16];

	UINTM0 = 0xff;            // disable interrupt
	ULCON0 = 0x0003;          // 8bit data
	UCON0  = 0x070a;          // bit 10 Clock Selection : *PCLK(0), SCLK_UART(1)
	CLK_SRC4 &= ~0xf0000;     // Clock source XXTI
	CLK_DIV4 &= ~0xf0000;     // UART0_RATIO = 0
	CLK_GATE_IP3 |= 0x20000;  // Gating all clocks for UART0
	GPA0CON = 0x22;           // set GPA pin to uart rx, or tx

}

uint32_t uart0_getc()
{
	while( !(UTRSTAT0 & 0x01) );
	return URXH0;
}

void uart0_putc(uint32_t sbyte)
{
	while( !(UTRSTAT0 & 0x02) );
	UTXH0 = sbyte;
}

/*
 * 8bits data, none pair, no flow ctrl, 1 stop bit, FIFO disable
 */
void uart2_init(uint32_t baudrate)
{

	uint32_t div_val;
	                          // set the baudrate
    div_val = (XXTI*10/baudrate/16)-10;
	UBRDIV2 = div_val/10;
	UDIVSLOT2 = udivslot_val[(div_val%10)*16];

	UINTM2 = 0xff;            // disable interrupt
	ULCON2 = 0x0003;          // 8bit data
	UCON2  = 0x070a;          // bit 10 Clock Selection : *PCLK(0), SCLK_UART(1)
	CLK_SRC4 &= ~0xf000000;     // Clock source XXTI
	CLK_DIV4 &= ~0xf000000;     // UART2_RATIO = 0
	CLK_GATE_IP3 |= 0x2000000;  // Gating all clocks for UART2
	GPA1CON = 0x22;           // set GPA pin to uart rx, or tx

}

uint32_t uart2_getc()
{
	while( !(UTRSTAT2 & 0x01) );
	return URXH2;
}

void uart2_putc(uint32_t sbyte)
{
	while( !(UTRSTAT2 & 0x02) );
	UTXH2 = sbyte;
}


