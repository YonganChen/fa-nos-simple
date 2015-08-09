/*
 * Main.c
 *
 *  Created on: 2012-12-12
 *      Author: cya
 */

#include <stdint.h>
#include "uart/uart.h"
#include "gpio/gpio.h"
#include "clock/clock.h"
#include "fimd/fimd.h"
#include "mipi/mipi_dsim.h"
#include "xprintf/xprintf.h"
#include "../ICs/LTC2309/LTC2309.h"


void start(void) __attribute__((section(".start")));
void start()
{
	uint32_t temp;
	uint8_t getstr[20];

	GPJ2CON = 0x1111;
	GPJ2DAT = 0x0a;

	uart2_init(38400);
	uart0_init(115200);
	fimd_init();

	xdev_out(uart0_putc);
	xdev_in(uart0_getc);

	xprintf("FA210 Tester v1\n");

    if (LTC2309_init())
    	xprintf("LTC2309_init failed\n");
    else
    	{
    	xprintf("LTC2309_init ok\n");

    	if (LTC2309_set_channel(LTC2309_AD4))
    		xprintf("LTC2309_set_channel(LTC2309_AD4) failed\n");
    	else
    	{
    		xprintf("LTC2309_set_channel(LTC2309_AD4) ok\n");
    	}
    	}


	while(1){

   		xprintf("LTC2309_read() %d\n", LTC2309_read());
   		xprintf("Send 'AT' to XBee\n");

        uart2_putc('A');
        uart2_putc('T');
        uart2_putc('\r');
        uart2_putc('\n');

        uart0_putc(uart2_getc());
        uart0_putc(uart2_getc());
        uart0_putc(uart2_getc());
        uart0_putc(uart2_getc());

		uart0_getc();


	}
}
