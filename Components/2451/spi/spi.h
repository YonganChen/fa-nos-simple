/*
 * spi.h
 *
 *  Created on: 2014Äê8ÔÂ10ÈÕ
 *      Author: ChYA
 */

#ifndef SPI_H_
#define SPI_H_


#include <stdint.h>

typedef struct
{
	volatile uint32_t CHCFG;    		 // HS_SPI  configuration register
	volatile uint32_t CLKCFG;   		 // Clock configuration register
	volatile uint32_t MODECFG;   		 // HS_SPI FIFO control register
	volatile uint32_t SlAVESEL;  		 // Slave selection signal
	volatile uint32_t INTEN;    		 // HS_SPI Interrupt Enable register
	volatile uint32_t STATUS;   		 // HS_SPI status register
	volatile uint32_t TXDATA;   		 // HS_SPI TX DATA register
	volatile uint32_t RXDATA;   		 // HS_SPI RX DATA register
	volatile uint32_t PACKETCOUNT;   	 // Count how many data master gets
	volatile uint32_t PENDCLR;  		 // Pending clear register
	volatile uint32_t SWAPCFG;           // SWAP configuration register
	volatile uint32_t FBCLKSEL;          // Feedback clock selecting register
} SPI_TypeDef;

#define SPI0_BASE   (0x52000000)
#define SPI1_BASE   (0x59000000)    //  HS_SPI_CH1 Control Register base address
#define SPI0        ((SPI_TypeDef *) SPI0_BASE)
#define SPI1        ((SPI_TypeDef *) SPI1_BASE)

#define SPI_READ_READY    !((SPI->STATUS & 0x7f<<13)==0)|((SPI->STATUS & 0x01<<21)==0)
#define SPI_SHIFT_READY   !((SPI->STATUS & 0x01<<21)==0)
#define SPI_RXFIFO_BYTES  (((SPI->STATUS)>>13) & 0x7f)

void spi_init(SPI_TypeDef* SPI, uint32_t mode, uint32_t cpol, uint32_t cpha, uint32_t clk_prescaler );
void spi_write(SPI_TypeDef* SPI, uint32_t* wbytes, uint32_t len );
void spi_read(SPI_TypeDef* SPI, uint32_t* rbytes, uint32_t len );


#endif /* SPI_H_ */
