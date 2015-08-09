/*
 * spi.c
 *
 *  Created on: 2014Äê8ÔÂ10ÈÕ
 *      Author: ChYA
 */


#include <stdint.h>
#include "../gpio/gpio.h"
#include "spi.h"

/*
 * spi_init
 * TX and RX ON, FIFO enable, DMA disable, interrupt disable, clock source:PCLK, Transfer size:byte
 * manual Chip select toggle
 * mode: 0=Master, 1=Slave
 */
void spi_init(SPI_TypeDef* SPI, uint32_t mode, uint32_t cpol, uint32_t cpha, uint32_t clk_prescaler )
{
	/* set relative pin to spi function */
	if(SPI == SPI0){
		GPIOE->CON &= ~(0x3f<<22);
		GPIOE->CON |= (0x2a<<22);
		}
	if(SPI == SPI1){
		GPIOL->CON &= ~(0x3f<<20);
		GPIOL->CON |= (0x2a<<20);
	}

	SPI->CLKCFG = 1<<8|clk_prescaler;
	SPI->CHCFG = 1<<6|mode<<4|cpol<<3|cpha<<2|1<<1|1;

}

void spi_write(SPI_TypeDef* SPI, uint32_t* wbytes, uint32_t len )
{
	uint8_t i,k;

	SPI->SlAVESEL &= ~(0x1);
	for(i=0;i<len;i++){
		SPI->TXDATA = wbytes[i];
	}
	while(!SPI_READ_READY);
	for(i=0;i<len;i++){
		k=SPI->RXDATA ;
		}
	SPI->SlAVESEL |= (0x1);
}

void spi_read(SPI_TypeDef* SPI, uint32_t* rbytes, uint32_t len )
{
	uint32_t i;

//	SPI->CHCFG &= ~(0x01);  // TX off

	SPI->SlAVESEL &= ~(0x1);
	for(i=0;i<len;i++){
		SPI->TXDATA = 0;
		}
	while(!SPI_READ_READY);
	for(i=0;i<len;i++){
		rbytes[i] = SPI->RXDATA ;
	}
	SPI->SlAVESEL |= (0x1);

//	SPI->CHCFG |= (0x01);  // TX on
}
