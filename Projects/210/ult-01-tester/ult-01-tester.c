/*
 * Main.c
 *
 *  Created on: 2012-12-12
 *      Author: cya
 */

#include <stdint.h>
#include <math.h>
#include "210/uart/uart.h"
#include "210/gpio/gpio.h"
#include "210/timer/timer.h"
#include "xprintf/xprintf.h"

#define DELAY_1S_VAL    (0xfffff)
#define DELAY_1MS_VAL   (0x418)
#define DELAY_1US_VAL   (0x01)

// GPH0_3(EINT3), GPH0_1(EINT1) ,GPH0_2(EINT2), use GPH0_3(EINT3) as SIGNAL
#define SIGNAL_GPIO_CON   GPH0CON
#define SIGNAL_GPIO_DAT   GPH0DAT
#define SIGNAL_PIN        (3)
#define SET_SIGNAL_OUT    SIGNAL_GPIO_CON &= ~(0x0f<<SIGNAL_PIN*4); \
                          SIGNAL_GPIO_CON |= 1<<SIGNAL_PIN*4
#define SET_SIGNAL_IN     SIGNAL_GPIO_CON &= ~(0x0f<<SIGNAL_PIN*4)
#define SIGNAL_1          SIGNAL_GPIO_DAT |= 1<<SIGNAL_PIN
#define SIGNAL_0          SIGNAL_GPIO_DAT &= ~(1<<SIGNAL_PIN)
#define SIGNAL            !!(SIGNAL_GPIO_DAT & (1<<SIGNAL_PIN))


/*
 *  delay some time
 */
void delay(volatile uint32_t count)
{
    for(;count>0;count--){
    }
}



//-------------------------------------------------------------------------
 void start(void) __attribute__((section(".start")));
 void start() 
 {
	float temp = 0.0f;
	float temp_cm = 0.0f;
	uint32_t temp_float = 0;
	uint32_t temp_int;
	uint32_t count_f = 0;
	uint32_t count_s = 0;

	uint8_t getstr[20];

	uart0_init(115200);

	xdev_out(uart0_putc);
	xdev_in(uart0_getc);

	xprintf("FA210 Tester v1\n");

	while(1){

        xprintf("hit enter to start finder..."); 
        xgets(getstr, 1);

        SET_SIGNAL_OUT;
        SIGNAL_0;
        timer_delayus_init(50);
        timer_delayus_waiting();
		SIGNAL_1;
        timer_delayus_waiting();
		SIGNAL_0;
		timer_delayus_waiting();

		SET_SIGNAL_IN;
//        start_timimg();

       // xprintf("waiting for hight\n");
 
        temp_int = 0;
        while ( !SIGNAL && temp_int < 0xfffff) {
        	temp_int++;
        }
        if ( temp_int >= 0xfffff ){
        	count_f++;
        	xprintf("waiting for hight timeout\n");
            continue;
        }

 /*     
        stop_timimg( &temp );
        temp_int = temp;
		temp_float = fmod(temp, 1)*10000.0f;
        xprintf("time: %d.%dus\n", temp_int, temp_float);
*/
        start_timimg();
     //   xprintf("waiting for Low\n");
        temp_int = 0;
        while ( SIGNAL && temp_int < 0xfffff ) {
        	temp_int++;
        }
        if ( temp_int >= 0xfffff ){
        	stop_timimg( &temp );
        	count_f++;
        	xprintf("waiting for Low timeout\n");
            continue;
        }

        stop_timimg( &temp );

		temp_int = temp;
        count_s++;
		xprintf("time: %dus  %d   %d   %d\n", temp_int, count_f+count_s, count_s, count_f);
		temp_cm = ((temp/2.0f)*343.0f)/10000.0f;
		temp_int = temp_cm;
		temp_float = fmod(temp_cm, 1)*10.0f;
		xprintf("rang: %d.%dcm \n", temp_int, temp_float);


		delay(DELAY_1S_VAL*2);

	 }
 }
