/*
 * uart.h
 *
 *  Created on: 2014-08-10
 *      Author: cya
 */

#ifndef UART_H_
#define UART_H_

#include <stdint.h>

typedef struct
{
	volatile uint32_t ULCON;    		 // UART line control register
	volatile uint32_t UCON;   		     // UART control register
	volatile uint32_t UFCON;   		     // UART FIFO control register
	volatile uint32_t UMCON;  		     // UART Modem control register
	volatile uint32_t UTRSTAT;    		 // UART Tx/Rx status register
	volatile uint32_t UERSTAT;   		 // UART Rx error status register
	volatile uint32_t UFSTAT;   		 // UART FIFO status register
	volatile uint32_t UMSTAT;   		 // UART modem status register
	volatile uint32_t UTXH;   	         // UART transmit buffer register
	volatile uint32_t URXH;  		     // UART receive buffer register
	volatile uint32_t UBRDIV;            // Baud rate divisior(integer place) register
	volatile uint32_t UDIVSLOT;          // Baud rate divisior(decimal place) register
} UART_TypeDef;

#define UART0_BASE    (0x50000000)
#define UART1_BASE    (0x50004000)
#define UART2_BASE    (0x50008000)
#define UART3_BASE    (0x5000C000)
#define UART0         ((UART_TypeDef *)UART0_BASE)
#define UART1         ((UART_TypeDef *)UART1_BASE)
#define UART2         ((UART_TypeDef *)UART2_BASE)
#define UART3         ((UART_TypeDef *)UART3_BASE)


 void     uart_init(UART_TypeDef *);   // 115200bps,8bits data, none pair, no flow ctrl, 1 stop bit, FIFO disable
 uint32_t uart_getc(UART_TypeDef *);
 void     uart_putc(UART_TypeDef *, uint32_t sbyte);

#endif /* UART_H_ */
