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
#include "syscon/syscon.h"
#include "interrupt/interrupt.h"
#include "xprintf/xprintf.h"


void start(void) __attribute__((section(".start")));
void start()
{
	uint32_t temp;
	uint8_t getstr[20];

	GPJ2CON = 0x1111;
	GPJ2DAT = 0x0a;

	uart0_init(115200);
	fimd_init();

	VIC0INTENABLE = 0xffffffff;
	VIC1INTENABLE = 0xffffffff;
	VIC2INTENABLE = 0xffffffff;
	VIC3INTENABLE = 0xffffffff;

	GPH2CON = 0xffffffff;

	VIC0VECTADDR16 = 0x20000000;

	xdev_out(uart0_putc);
	xdev_in(uart0_getc);

	xprintf("FA210 Tester v1\n");

	while(1){

		xputc('>');
		xgets(getstr,15);
		xprintf("enter sleep mode...\n");
		enter_sleep_mode();

	}
}
