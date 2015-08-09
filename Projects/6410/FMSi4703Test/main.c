/*
 * Main.c
 *
 *  Created on: 2012-12-12
 *      Author: cya
 */

#include <stdint.h>
#include "../../Components/uart//uart.h"
#include "../../Components/xprintf/xprintf.h"
#include "../../Components/delay/delay.h"
#include "../../Components/Si470x/Si470x_io2w.h"
#include "../../Components/Si470x/Si470x_cmd.h"

#define DEBUG_COM  UART0

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

	uint8_t data_out[10]={0xff, 0xff, 0xff,0,0,0,0};
	uint8_t data_in[10]={0xff, 0xff, 0xff,0,0,0,0};

	uart_init(DEBUG_COM);
	xdev_in(get_char);
	xdev_out(put_char);

	xprintf("\nHello, 6410!\n");
//	delay(DELAY_1S_VAL);
//	xprintf("init si470x...");
//	if (si470x_init()){
//		xprintf("ok\n");
//	}
//	else {
//		xprintf("failed\n");
//	}


//	delay(DELAY_1S_VAL);
//    xprintf("powerdown si470x...");
//	if (si470x_powerdown()){
//			xprintf("ok\n");
//		}
//		else{
//			xprintf("failed\n");
//		}

//	delay(DELAY_1S_VAL);
//	xprintf("powerup si470x...");
//	if (si470x_powerup()){
//		xprintf("ok\n");
//	}
//	else{
//		xprintf("failed\n");
//	}




	while(1){

    }
	//test_FMRX();
  //  test_FMRXrds();            // Tunes to an RDS station and populates
	                           // variables with RDS information.

}






