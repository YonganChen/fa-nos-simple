/*
 * Main.c
 *
 *  Created on: 2012-12-12
 *      Author: cya
 */

#include <stdint.h>
#include "../../Components/uart//uart.h"
#include "../../Components/gpio/gpio.h"
#include "../../Components/iic/iic.h"
#include "../../Components/xprintf/xprintf.h"
#include "../../Components/s3c2416.h"

#define DEBUG_COM  UART0

#define DELAY_1S_VAL    (0xfffff)
#define DELAY_1MS_VAL   (0x418)
#define DELAY_1US_VAL   (0x01)

#define CMD_DO_NOTHING             0x00
#define CMD_POWER_OFF              0x11
#define CMD_POWER_ON               0x12
#define CMD_RE_POWER_ON            0x13
#define CMD_RESET                  0x14
#define CMD_RE_POWER_ON_USBMODE    0x15
#define CMD_RE_RESET_USBMODE       0x16
#define CMD_PRESS_HOST_POWERKEY    0x17
#define CMD_RELEASE_HOST_POWERKEY  0x18

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
	uint32_t tbytes[10] = { CMD_DO_NOTHING, CMD_POWER_OFF, CMD_RE_POWER_ON  };
	uint32_t rbytes[10] = { 0x00, 0x00, 0x00 };
	int i;
	uint32_t err;
	uint8_t j;

	uart_init( DEBUG_COM );
	xdev_in( get_char );
	xdev_out( put_char );

	xprintf( "\nHello, 2451!\n" );

	iic_init( IIC0, 0x01 );
    j = 0;
    err = 0;

    while ( 1 ) {
    	rbytes[0] = 0;
    	delay ( DELAY_1S_VAL*5 );
    	i = iic_transmit( IIC0, IIC_MASTER, 0x68, tbytes, 1 );
    	xprintf ( "iic_transmit, i: %d \n", i );
    	i = iic_receive( IIC0, IIC_MASTER, 0x68, rbytes, 1 );
    	xprintf ( "iic_receive, i: %d, data: %d \n", i, rbytes[0] );
    }
}

//while( 1 ){
//	  tbytes[0] = j++;
//	  i = iic_transmit( IIC0, IIC_MASTER, 0x68, tbytes, 1 );
//      if ( i == 0 ){
//    	   i = iic_receive( IIC0, IIC_MASTER, 0x68, rbytes, 1 );
//    	   if ( i == 0 ) {
//    		   if ( rbytes[0] != tbytes[0] ) {
//    			   err++;
//    		   }
//    		   xprintf( "Tx: %d, Rx: %d, err = %d\n", tbytes[0], rbytes[0], err );
//    	   }
//    	   else {
//    		   xprintf( "Receive Err, i = %d \n", i );
//    		   err++;
//    	   }
//       }
//       else {
//    	   xprintf( "Transmit Err, i = %d \n", i );
//    	   err++;
//       }
//
//       delay( DELAY_1MS_VAL );
//	}






