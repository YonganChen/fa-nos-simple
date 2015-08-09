/*
 * gpio_iic.c
 *
 *  Created on: 2013-4-27
 *      Author: chen
 */

#include "gpio_iic.h"
#include "gpio.h"
#include <stdint.h>


void static delay ( uint32_t i )
{
      for( ; i >0 ; i--);
}


void gpio_iic_init()
{
	SET_SCL_OUTPUT();
	SET_SCL();
	SET_SDA_OUTPUT();
	SET_SDA();
}

// generate start bit
void gpio_iic_start ()
{
	SET_SDA_OUTPUT();

	SET_SDA();
    delay(IIC_DELAY_TIME);
    SET_SCL();
	delay(IIC_DELAY_TIME);    // start bit
	CLR_SDA();
	delay(IIC_DELAY_TIME);
	CLR_SCL();
	delay(IIC_DELAY_TIME);
}


// generate stop bit
void gpio_iic_stop ()
{
	SET_SDA_OUTPUT();

	CLR_SDA(); delay(IIC_DELAY_TIME);
    SET_SCL(); delay(IIC_DELAY_TIME);	   // stop bit
    SET_SDA(); delay(IIC_DELAY_TIME);
}


// get ACK bit
char gpio_iic_Gack ()
{
	SET_SDA_OUTPUT();

    SET_SDA(); delay(IIC_DELAY_TIME);
	SET_SCL(); delay(IIC_DELAY_TIME);

	SET_SDA_INPUT();

	if (GET_SDA() == 1) return 1;	    // fail
	CLR_SCL(); delay(IIC_DELAY_TIME);
	return 0;                   // ack
}

// generate ACK bit
void gpio_iic_Pack ()
{
	 SET_SDA_OUTPUT();

     CLR_SDA(); delay(IIC_DELAY_TIME);
     SET_SCL(); delay(IIC_DELAY_TIME);
     CLR_SCL(); delay(IIC_DELAY_TIME);
}

void gpio_iic_Pnack ()
{
	SET_SDA_OUTPUT();

     SET_SDA(); delay(IIC_DELAY_TIME);
     SET_SCL(); delay(IIC_DELAY_TIME);
     CLR_SCL(); delay(IIC_DELAY_TIME);
}

// write 8 bits to the bus
void gpio_iic_write ( unsigned char wbyte )
{
  	unsigned char i;

  	SET_SDA_OUTPUT();

	for(i = 0; i<8; i++)
	{
	  if ((wbyte & 0x80)==0x80) SET_SDA();
	  else CLR_SDA();
	  wbyte <<= 1;
	  SET_SCL(); delay(IIC_DELAY_TIME);
	  CLR_SCL(); delay(IIC_DELAY_TIME);
	}
}

// read 8 bits from the bus
void gpio_iic_read ( unsigned char *rbyte )
{
	unsigned char i;

	SET_SDA_OUTPUT();
	SET_SDA();

	SET_SDA_INPUT();
	for(i = 0; i<8; i++)		   // data
	{
	  SET_SCL(); delay(IIC_DELAY_TIME);
	  (*rbyte) <<= 1;
	  if (GET_SDA()) (*rbyte)++;
	  CLR_SCL(); delay(IIC_DELAY_TIME);
	}
}


