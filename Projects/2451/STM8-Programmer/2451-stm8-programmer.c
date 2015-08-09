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

#define SWIM_PIN    (12)
#define SWIM_PORT   GPIOG
#define RESET_PIN   (10)
#define RESET_PORT  GPIOG

#define SWIM_LOW       SWIM_PORT->DAT &= ~(0x01<<SWIM_PIN)
#define SWIM_HIGH      SWIM_PORT->DAT |= 0x01<<SWIM_PIN
#define SWIM_VALUE     !!(SWIM_PORT->DAT & (uint32_t)0x01<<SWIM_PIN)
#define RESET_LOW      RESET_PORT->DAT &= ~(0x01<<RESET_PIN)
#define RESET_HIGH     RESET_PORT->DAT |= 0x01<<RESET_PIN


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

static void inline set_swim_in()
{
	SWIM_PORT->CON &= ~(0x03<<(SWIM_PIN*2));
	SWIM_PORT->CON |= GPIO_INPUT<<(SWIM_PIN*2);
}

static void inline set_swim_out()
{
	SWIM_PORT->CON &= ~(0x03<<(SWIM_PIN*2));
	SWIM_PORT->CON |= GPIO_OUTPUT<<(SWIM_PIN*2);
}

static void swim_init()
{

    SWIM_PORT->UDP &= ~(0x03<<(SWIM_PIN*2));
    SWIM_PORT->UDP |= GPIO_PULLUP<<(SWIM_PIN*2);
    set_swim_out();
    SWIM_HIGH;

	RESET_PORT->CON &= ~(0x03<<(RESET_PIN*2));
    RESET_PORT->CON |= GPIO_OUTPUT<<(RESET_PIN*2);
    RESET_HIGH;

}

static int swim_active()
{
	volatile uint32_t  i, j;

    while(1){
	    RESET_LOW;
	    delay(DELAY_1MS_VAL);
	    set_swim_out();
	    SWIM_LOW;
	    delay(DELAY_1MS_VAL);

	    // 4 Plus 1KHz
	    for (i=0; i<4; i++){
	    	SWIM_HIGH;
	    	delay(DELAY_500US_VAL);
	    	SWIM_LOW;
	    	delay(DELAY_500US_VAL);
	    }
	    //  4 plus 2khz
	    for (i=0; i<4; i++){
		    SWIM_HIGH;
		    delay(DELAY_250US_VAL);
	        SWIM_LOW;
	        delay(DELAY_250US_VAL);
	    }
	    SWIM_HIGH;
	    set_swim_in();

	    i = 0;
        while ( SWIM_VALUE ){
        	i++;
        	if (i>200){
        		xprintf( "wait sync err\n" );
        		return -1;
        	}
        }

        j = 0;
        while( !SWIM_VALUE ){
        	j++;
        	if( j>200 ){
        		xprintf( "get sync err\n" );
        		return -2;
        	}
        }
        xprintf( "get sync ok, i=%d, j=%d \n", i, j );

	    delay(DELAY_250US_VAL);
	    delay(DELAY_1MS_VAL);
	    RESET_HIGH;
	    delay(DELAY_1MS_VAL*30);

	 }
	   return 0;
}


void start(void) __attribute__((section(".start")));
void start()
{

	uint32_t i=0,j=0,k=0;

	uart_init(DEBUG_COM);
	xdev_in(get_char);
	xdev_out(put_char);
	xprintf("\nFriendlyARM LCD Board Firmware Progrmmer\n");

	Lcd_Init(LCD_W35);
	Lcd_Clear_Screen(RGB(0x00,0x00,0x00));
	Lcd_Printf(5, 5, RGB( 0x00,0xFF,0x00),RGB(0x00,0x00,0x00),0,"STM8 Progrmmer");

	swim_init();

	while(1)
	{
		swim_active();
		;
	}
}






