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
    uint32_t ULCON;        // 0x000
    uint32_t UCON;        // 0x004
    uint32_t UFCON;        // 0x008
    uint32_t UMCON;        // 0x00c

    uint32_t UTRSTAT;        // 0x010
    uint32_t UERSTAT;        // 0x014
    uint32_t UFSTAT;        // 0x018
    uint32_t UMSTAT;        // 0x01c

    uint32_t UTXH;        // 0x020
    uint32_t URXH;        // 0x024
    uint32_t UBRDIV;        // 0x028
    uint32_t UDIVSLOT;    // 0x02c

    uint32_t UINTP;        // 0x030
    uint32_t UINTSP;        // 0x034
    uint32_t UINTM;        // 0x038
    uint32_t PAD0;        // 0x03c
} UART_TypeDef;

typedef struct
{
    uint32_t ULCON0;        // 0x000
    uint32_t UCON0;        // 0x004
    uint32_t UFCON0;        // 0x008
    uint32_t UMCON0;        // 0x00c

    uint32_t UTRSTAT0;    // 0x010
    uint32_t UERSTAT0;    // 0x014
    uint32_t UFSTAT0;        // 0x018
    uint32_t UMSTAT0;        // 0x01c

    uint32_t UTXH0;        // 0x020
    uint32_t URXH0;        // 0x024
    uint32_t UBRDIV0;        // 0x028
    uint32_t UDIVSLOT0;    // 0x02c

    uint32_t UINTP0;        // 0x030
    uint32_t UINTSP0;        // 0x034
    uint32_t UINTM0;        // 0x038
    uint32_t PAD0;        // 0x03c

    uint32_t PAD1[240];    // 0x040~0x3ff

    uint32_t ULCON1;        // 0x400
    uint32_t UCON1;        // 0x404
    uint32_t UFCON1;        // 0x408
    uint32_t UMCON1;        // 0x40c

    uint32_t UTRSTAT1;    // 0x410
    uint32_t UERSTAT1;    // 0x414
    uint32_t UFSTAT1;        // 0x418
    uint32_t UMSTAT1;        // 0x41c

    uint32_t UTXH1;        // 0x420
    uint32_t URXH1;        // 0x424
    uint32_t UBRDIV1;        // 0x428
    uint32_t UDIVSLOT1;    // 0x42c

    uint32_t UINTP1;        // 0x430
    uint32_t UINTSP1;        // 0x434
    uint32_t UINTM1;        // 0x438
    uint32_t PAD2;        // 0x43c

    uint32_t PAD3[240];    // 0x440~0x7ff

    uint32_t ULCON2;        // 0x800
    uint32_t UCON2;        // 0x804
    uint32_t UFCON2;        // 0x808
    uint32_t UMCON2;        // 0x80c

    uint32_t UTRSTAT2;    // 0x810
    uint32_t UERSTAT2;    // 0x814
    uint32_t UFSTAT2;        // 0x818
    uint32_t UMSTAT2;        // 0x81c

    uint32_t UTXH2;        // 0x820
    uint32_t URXH2;        // 0x824
    uint32_t UBRDIV2;        // 0x828
    uint32_t UDIVSLOT2;    // 0x82c

    uint32_t UINTP2;        // 0x830
    uint32_t UINTSP2;        // 0x834
    uint32_t UINTM2;        // 0x838
    uint32_t PAD4;        // 0x83c

    uint32_t PAD5[240];    // 0x840~0xbff

    uint32_t ULCON3;        // 0xc00
    uint32_t UCON3;        // 0xc04
    uint32_t UFCON3;        // 0xc08
    uint32_t UMCON3;        // 0xc0c

    uint32_t UTRSTAT3;    // 0xc10
    uint32_t UERSTAT3;    // 0xc14
    uint32_t UFSTAT3;        // 0xc18
    uint32_t UMSTAT3;        // 0xc1c

    uint32_t UTXH3;        // 0xc20
    uint32_t URXH3;        // 0xc24
    uint32_t UBRDIV3;        // 0xc28
    uint32_t UDIVSLOT3;    // 0xc2c

    uint32_t UINTP3;        // 0xc30
    uint32_t UINTSP3;        // 0xc34
    uint32_t UINTM3;        // 0xc38
    uint32_t PAD6;        // 0xc3c
} S3C6410_UART_REG_TypeDef;

#define UART0_BASE    (0x7F005000)
#define UART1_BASE    (0x7F005400)
#define UART2_BASE    (0x7F005800)
#define UART3_BASE    (0x7F005C00)
#define UART0         ((volatile UART_TypeDef *)UART0_BASE)
#define UART1         ((volatile UART_TypeDef *)UART1_BASE)
#define UART2         ((volatile UART_TypeDef *)UART2_BASE)
#define UART3         ((volatile UART_TypeDef *)UART3_BASE)

#define S3C6410_UART_REG  ((volatile S3C6410_UART_REG_TypeDef *) 0x7F005000)

 void     uart_init( volatile UART_TypeDef *);   // 115200bps,8bits data, none pair, no flow ctrl, 1 stop bit, FIFO disable
 uint32_t uart_getc( volatile UART_TypeDef *);
 void     uart_putc( volatile UART_TypeDef *, uint32_t sbyte);

#endif /* UART_H_ */
