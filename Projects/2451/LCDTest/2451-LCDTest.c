/*
 * Main.c
 *
 *  Created on: 2012-12-12
 *      Author: cya
 */

#include <stdint.h>
#include "../../Components/uart//uart.h"
#include "../../Components/gpio/gpio.h"
#include "../../Components/xprintf/xprintf.h"
#include "../../Components/display/lcd.h"
#include "../../Components/display/bmp.h"

#define DEBUG_COM  UART0


#define DELAY_1S_VAL      (0xfffff)
#define DELAY_1MS_VAL     (0x418)
#define DELAY_1US_VAL     (0x01)
#define DELAY_500US_VAL   (0x23c)
#define DELAY_250US_VAL   (0x11f)

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




void start(void) __attribute__((section(".start")));
void start()
{

	uint32_t i=0,j=0,k=0;

	uart_init(DEBUG_COM);
	xdev_in(get_char);
	xdev_out(put_char);
	xprintf("\nHello 2451\n");

	Lcd_Init(LCD_S70D);
	Lcd_Draw_Outline ( 0x00, 0x00, 0xff );
	Lcd_Printf(5, 5, RGB( 0x00,0xFF,0x00),RGB(0x00,0x00,0x00),0,"LCD-S70D Test");
	//Lcd_Draw_Bmp ( gImage_800480 );

	while(1)
	{
		;
	}
}






