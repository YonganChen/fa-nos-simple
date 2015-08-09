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
void uart_init( volatile UART_TypeDef * uart)
{

	if (uart==UART0){
		S3C6410_GPIO_REG->GPACON &= ~0xff;
		S3C6410_GPIO_REG->GPACON |= 0x22;
     }
	if (uart==UART1){
		S3C6410_GPIO_REG->GPACON &= ~0xff0000;
		S3C6410_GPIO_REG->GPACON |= 0x220000;
	}
	if (uart==UART2){
		S3C6410_GPIO_REG->GPBCON &= ~0xff;
		S3C6410_GPIO_REG->GPBCON |= 0x22;
	}
	if (uart==UART3){
		S3C6410_GPIO_REG->GPBCON &= ~0xff00;
		S3C6410_GPIO_REG->GPBCON |= 0x2200;
	}

	uart->ULCON = 0x3;  					//
	uart->UCON  = 0x5;  					//
	uart->UFCON = 0x01; 					//
	uart->UMCON = 0;						//

	// DIV_VAL = (PCLK / (bps x 16 ) ) - 1 = (66500000/(115200x16))-1 = 35.08
	// DIV_VAL = 35.08 = UBRDIVn + (num of 1’s in UDIVSLOTn)/16
	uart->UBRDIV   = 35;
	uart->UDIVSLOT = 0x1;

}


uint32_t uart_getc( volatile UART_TypeDef * UART)
{
	while( !(UART->UTRSTAT & 0x01) );
	return UART->URXH;
}

void uart_putc( volatile UART_TypeDef * UART, uint32_t sbyte)
{
	while( !(UART->UTRSTAT & 0x02) );
	UART->UTXH = sbyte;
}

