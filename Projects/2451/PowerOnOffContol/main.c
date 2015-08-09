/*
 * Main.c
 *
 *  Created on: 2012-12-12
 *      Author: cya
 */

#include <stdint.h>
#include "../../Components/uart//uart.h"
#include "../../Components/gpio/gpio.h"
#include "../../Components/spi/spi.h"
#include "../../Components/xprintf/xprintf.h"

#define DEBUG_COM  UART0

#define GPIO_PWR      GPIOJ
#define GPIO_PWR_PIN  (0)

#define DELAY_1S_VAL    (0xfffff)
#define DELAY_1MS_VAL   (0x418)
#define DELAY_1US_VAL   (0x01)

/*
 *  delay some time
 */
void delay(volatile uint32_t count)
{
	for(;count>0;count--){
	}
}

/*
 * send char to debug uart, called by xprintf
 */
void put_char(uint32_t ch)
{
	uart_putc(DEBUG_COM, ch);
}

/*
 * get char from debug uart, called by xgets
 */
uint32_t get_char()
{
	return uart_getc(DEBUG_COM);
}

 void set_pin_low()
{
   /* init GPIO GPIOE10 */
	 GPIO_PWR->CON &= ~(0x03<<(GPIO_PWR_PIN*2));
	 GPIO_PWR->CON |= GPIO_OUTPUT<<(GPIO_PWR_PIN*2);

	 GPIO_PWR->DAT &= ~(0x01<<GPIO_PWR_PIN);

}

 void set_pin_high()
{
   /* init GPIO GPIOE10 */
	 GPIO_PWR->CON &= ~(0x03<<(GPIO_PWR_PIN*2));
	 GPIO_PWR->CON |= GPIO_OUTPUT<<(GPIO_PWR_PIN*2);

	 GPIO_PWR->DAT |= 0x01<<GPIO_PWR_PIN;

}


void start(void) __attribute__((section(".start")));
void start()
{
	uart_init(DEBUG_COM);
	xdev_in(get_char);
	xdev_out(put_char);

	xprintf("\nHello, 2451!\n");
	while(1){
		xprintf("\nHello, 2451!\n");
		set_pin_low();
		delay(DELAY_1S_VAL*4);
		set_pin_high();
		xprintf("\nHello, 2451!\n");
		delay(DELAY_1S_VAL*19);

	}
}






