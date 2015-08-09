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

#define DEBUG_COM  UART1

#define SPI_PORT       SPI0
#define SPI_INT_PIN    (6)
#define SPI_INT_PORT   GPIOG
#define SPI_NSS_PIN    (13)
#define SPI_NSS_PORT   GPIOL

/* cmd */
#define SPI_ADS_READX   (0x94)
#define SPI_ADS_READY   (0xd4)


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
 * program start from here
 */

void start(void) __attribute__((section(".start")));
void start()
{
	uint32_t u32_temp[10] = {0};
	uint32_t xpos, ypos;
	uint32_t i=0,j=0,k=0;
	uint32_t ads_cmd[3] = {SPI_ADS_READX, SPI_ADS_READY, 0x00};

	uart_init(DEBUG_COM);
	spi_init(SPI_PORT, 0, 0, 0, 200);
	xdev_in(get_char);
	xdev_out(put_char);

	/* init GPIO */
	SPI_NSS_PORT->CON &= ~(0x03<<(SPI_NSS_PIN*2));
	SPI_NSS_PORT->CON |= GPIO_OUTPUT<<(SPI_NSS_PIN*2);
	SPI_NSS_PORT->DAT |= (0x01<<SPI_NSS_PIN);


	xprintf("\nHello, 2451!\n");



	while(1)
	{

		 while((SPI_INT_PORT->DAT & (uint32_t)0x01<<SPI_INT_PIN)!=0);
		 SPI_NSS_PORT->DAT &= ~(0x01<<SPI_NSS_PIN);
		 spi_write(SPI_PORT, ads_cmd, 1);
		 delay(DELAY_1US_VAL*50);
	     spi_read(SPI_PORT, u32_temp, 2);
         SPI_NSS_PORT->DAT |= 0x01<<SPI_NSS_PIN;

         xprintf("\n x: %02x %02x", u32_temp[0],  u32_temp[1]);
         u32_temp[0] = u32_temp[0]<<5 | u32_temp[1]>>3;
         xprintf(" %d", u32_temp[0]);

    	 SPI_NSS_PORT->DAT &= ~(0x01<<SPI_NSS_PIN);
    	 spi_write(SPI_PORT, ads_cmd+1, 1);
    	 delay(DELAY_1US_VAL*50);
    	 spi_read(SPI_PORT, u32_temp, 2);
         SPI_NSS_PORT->DAT |= 0x01<<SPI_NSS_PIN;

         xprintf(" y: %02x %02x", u32_temp[0],  u32_temp[1]);
         u32_temp[0] = u32_temp[0]<<5 | u32_temp[1]>>3;
         xprintf(" %d", u32_temp[0]);

         delay(DELAY_1MS_VAL*100);
	}

}






