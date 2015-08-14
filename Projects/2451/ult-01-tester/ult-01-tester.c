/*
 *  Created on: 2015/08/14
 *      Author: cya
 */

#include <stdint.h>
#include "2451/uart//uart.h"
#include "2451/gpio/gpio.h"
#include "2451/spi/spi.h"
#include "xprintf/xprintf.h"

#define DEBUG_COM  UART1

#define SPI_INT_PIN    (9)
#define SPI_INT_PORT   GPIOG
#define SPI_NSS_PIN    (14)
#define SPI_NSS_PORT   GPIOL

#define READ_REQUEST_TIMEOUT    (1000)    // us
#define SPI_PS2_READ            (0x01)
#define SPI_PARALLEL_READ       (0x03)

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

/*
 * return 0, ok, >0, err, should try again
 */
uint32_t read_ps2_request(uint32_t cmd)
{
	uint32_t i;
	// send cmd
	SPI_NSS_PORT->DAT &= ~(0x01<<SPI_NSS_PIN);
	spi_write(SPI1, &cmd, 1);
	SPI_NSS_PORT->DAT |= 0x01<<SPI_NSS_PIN;

	i=0;
	// waiting for response
    while((SPI_INT_PORT->DAT & (uint32_t)0x01<<SPI_INT_PIN)==0){
          delay(DELAY_1US_VAL);
          i++;
          if (i>=READ_REQUEST_TIMEOUT){
        	  return i;   // return to main. if INT pin is still low, main should recall this function
          }
    }

    return 0;
}



/*
 * program start from here
 * read 8bytes: 0[bit0:has mouse data, bit1:has keyboard data]
 *              1[mouse byte 0: Y_overflow|X_overflow|Y_sign_bit|X_sign_bit|Always_1|Middle_Btn|Right_Btn|Left_Btn]
 *              2[mouse byte 1: X movement]
 *              3[mouse byte 2: Y movement]
 *              4[mouse byte 3: Z movement(scrolling wheel)]
 *              5,6,7[keyboard data: Make Code or Break Code]
 */

void start(void) __attribute__((section(".start")));
void start()
{
	uint32_t u32_arr[11]={0};
	uint32_t u32_arr2[11]={0};
	uint32_t i=0,j=0,k=0;

	uart_init(DEBUG_COM);
	spi_init(SPI1, 0, 1, 0, 40);
	xdev_in(get_char);
	xdev_out(put_char);

	/* init GPIO */
	SPI_NSS_PORT->CON &= ~(0x03<<(SPI_NSS_PIN*2));
	SPI_NSS_PORT->CON |= GPIO_OUTPUT<<(SPI_NSS_PIN*2);

	xprintf("\nHello, 2451!\n");

	while(1)
	{
		 while((SPI_INT_PORT->DAT & (uint32_t)0x01<<SPI_INT_PIN)!=0);

		 if (read_ps2_request(SPI_PS2_READ)==0){

			SPI_NSS_PORT->DAT &= ~(0x01<<SPI_NSS_PIN);

			spi_read(SPI1, u32_arr2, 8);

			SPI_NSS_PORT->DAT |= 0x01<<SPI_NSS_PIN;

			xprintf("\nget:");
				for (i=0;i<8;i++){
				xprintf("%02x ", u32_arr2[i]);
			}
		 }

	}
}






