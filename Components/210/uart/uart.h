/*
 * uart.h
 *
 *  Created on: 2012-12-17
 *      Author: cya
 */

#ifndef UART_H_
#define UART_H_

#include <stdint.h>

#define ULCON0    (*((volatile uint32_t *)0xE2900000))   // UART0 Line Control Register
#define UCON0     (*((volatile uint32_t *)0xE2900004))   // UART0 Control Register
#define UTRSTAT0  (*((volatile uint32_t *)0xE2900010))   // b1:TX ety, b0:RX rdy
#define UTXH0     (*((volatile uint32_t *)0xE2900020))   // UART0 Transmit Buffer Register
#define URXH0     (*((volatile uint32_t *)0xE2900024))   // UART0 Recive Buffer Register
#define UBRDIV0   (*((volatile uint32_t *)0xE2900028))   // UART0 Channel Baud Rate Division Register
#define UDIVSLOT0 (*((volatile uint32_t *)0xE290002C))   // UART0 Channel Dividing Slot Register
#define UINTM0    (*((volatile uint32_t *)0xE2900038))   // UART0 Interrupt Mask Register

#define ULCON2    (*((volatile uint32_t *)0xE2900800))   // UART2 Line Control Register
#define UCON2     (*((volatile uint32_t *)0xE2900804))   // UART2 Control Register
#define UTRSTAT2  (*((volatile uint32_t *)0xE2900810))   // b1:TX ety, b0:RX rdy
#define UTXH2     (*((volatile uint32_t *)0xE2900820))   // UART2 Transmit Buffer Register
#define URXH2     (*((volatile uint32_t *)0xE2900824))   // UART2 Recive Buffer Register
#define UBRDIV2   (*((volatile uint32_t *)0xE2900828))   // UART2 Channel Baud Rate Division Register
#define UDIVSLOT2 (*((volatile uint32_t *)0xE290082C))   // UART2 Channel Dividing Slot Register
#define UINTM2    (*((volatile uint32_t *)0xE2900838))   // UART2 Interrupt Mask Register


 void     uart0_init(uint32_t baudrate);   // 8bits data, none pair, no flow ctrl, 1 stop bit, FIFO disable
 uint32_t uart0_getc();
 void     uart0_putc(uint32_t sbyte);

 void     uart2_init(uint32_t baudrate);   // 8bits data, none pair, no flow ctrl, 1 stop bit, FIFO disable
 uint32_t uart2_getc();
 void     uart2_putc(uint32_t sbyte);
#endif /* UART_H_ */
