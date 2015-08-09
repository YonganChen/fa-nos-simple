/*
 *  uart.c
 *
 *  Created on: 2012-12-17
 *      Author: cya
 */

#include <stdint.h>
#include "uart.h"
#include "../gpio/gpio.h"

/*
 * 115200bps, 8bits data, none pair, no flow ctrl, 1 stop bit, FIFO disable
 */
void uart_init(UART_TypeDef * UART)
{
	UART->ULCON = 0x0003;
	UART->UCON = 0x0245;
    UART->UBRDIV  = 0x0023;
    UART->UDIVSLOT = 0x0888;

    // set relative gpio as uart function

    if (UART == UART0){
       GPIOH->CON &= 0xfffffff0;
       GPIOH->CON |= 0x0000000a;
       GPIOH->UDP &= 0xfffffff0;
       GPIOH->UDP |= 0x0000000a;
    }
    if (UART == UART1){
       GPIOH->CON &= 0xffffff0f;
       GPIOH->CON |= 0x000000a0;
       GPIOH->UDP &= 0xffffff0f;
       GPIOH->UDP |= 0x000000a0;
    }
    if (UART == UART2){
       GPIOH->CON &= 0xfffff0ff;
       GPIOH->CON |= 0x00000a00;
       GPIOH->UDP &= 0xfffff0ff;
       GPIOH->UDP |= 0x00000a00;
    }
    if (UART == UART3){
       GPIOH->CON &= 0xffff0fff;
       GPIOH->CON |= 0x0000a000;
       GPIOH->UDP &= 0xffff0fff;
       GPIOH->UDP |= 0x0000a000;
    }

}


uint32_t uart_getc(UART_TypeDef * UART)
{
	while( !(UART->UTRSTAT & 0x01) );
	return UART->URXH;
}

void uart_putc(UART_TypeDef * UART, uint32_t sbyte)
{
	while( !(UART->UTRSTAT & 0x02) );
	UART->UTXH = sbyte;
}


