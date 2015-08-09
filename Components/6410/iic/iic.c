/*
 * iic.c
 *
 *  Created on: 2014-10-28
 *      Author: chya
 */


#include <stdint.h>
#include "iic.h"
#include "../gpio/gpio.h"
#include "../delay/delay.h"

#define SET_GPIOIIC0_SDA_IN     S3C6410_GPIO_REG->GPBCON &= ~(0xf000000)
#define SET_GPIOIIC0_SDA_OUT    S3C6410_GPIO_REG->GPBCON |= (0x1000000)
#define SET_GPIOIIC0_SDA_LOW    S3C6410_GPIO_REG->GPBDAT &= ~(1<<6)
#define SET_GPIOIIC0_SDA_HIGH   S3C6410_GPIO_REG->GPBDAT |= (1<<6)
#define GET_GPIOIIC0_SDA_VAL    !((S3C6410_GPIO_REG->GPBDAT & (1<<6))== 0 )
#define SET_GPIOIIC0_SCL_LOW    S3C6410_GPIO_REG->GPBDAT &= ~(1<<5)
#define SET_GPIOIIC0_SCL_HIGH   S3C6410_GPIO_REG->GPBDAT |= (1<<5)

static uint32_t gpioiic_delay_count = 100;


/* congfig gpio */
void iic_init( volatile S3C6410_IIC_REG_TypeDef* iic, uint32_t speed)
{
	// set gpio to iic function
   if (iic == S3C6410_IIC0){
	   S3C6410_GPIO_REG->GPBCON &= ~(0xff00000);
	   S3C6410_GPIO_REG->GPBCON |= (0x2200000);
   }
   if (iic == S3C6410_IIC1){
	   S3C6410_GPIO_REG->GPBCON &= ~(0xff00);
	   S3C6410_GPIO_REG->GPBCON |= (0x6600);
   }

   iic->IICCON = (1<<7)|(1<<6)|(speed & 0xf);  // ack enable
}

/*
 * ok, return 1, fail-0
 */
uint32_t iic_master_read( volatile S3C6410_IIC_REG_TypeDef* iic, uint32_t slave_add, uint32_t* read_buf, uint32_t read_num )
{
	uint32_t i;

  	iic->IICDS = slave_add | 0x00;
   	iic->IICSTAT = 0xF0;
   	while((iic->IICSTAT & 1<<5) == 1);   // waite for shift out
   	iic->IICCON &= ~0x20;
   	iic->IICSTAT = 0x90;
//   	i=200;
//    while( (iic->IICSTAT & 1<<0) == 1 ){
//    	i--;
//    	if (i==0){
//    		return 0;
//    	}
//    }
//    iic->IICSTAT = 0x90;


//   i = iic->IICDS;
//   iic->IICCON &= ~0x20;
//   for (i=0;i<read_num;i++){
//	   while((iic->IICCON & 1<<4) == 0);
//	   iic->IICCON &= ~0x20;
//	   read_buf[10] = iic->IICDS;
//   }
//   iic->IICSTAT = 0x90;   // stop
   return 1;
}

/*
 * ok, return 1, fail-0
 */
//uint32_t iic_master_write( S3C6410_IIC_REG_TypeDef iic, uint32_t slave_add, uint32_t* write_buf )
//{
//   iic->IICSTAT =
//}


void gpioiic0_init(uint32_t speed)
{
	S3C6410_GPIO_REG->GPBCON &= ~(0xff00000);
	S3C6410_GPIO_REG->GPBCON |= (0x1100000);
	S3C6410_GPIO_REG->GPBDAT |= 0x60;

	gpioiic_delay_count = speed;
}


/*
 * ok, return 1, fail-0
 */
uint32_t gpioiic0_master_read( uint32_t slave_addr, uint32_t* read_buf, uint32_t read_num )
{
	uint32_t i,j,k, temp;

		// start bit
		SET_GPIOIIC0_SCL_HIGH;
		SET_GPIOIIC0_SDA_HIGH;
		delay(DELAY_1US_VAL*gpioiic_delay_count);
		SET_GPIOIIC0_SDA_OUT;
		SET_GPIOIIC0_SDA_LOW;
		delay(DELAY_1US_VAL*gpioiic_delay_count);

		// send slave address
	    temp = slave_addr | 0x01;
	    for (i=0; i<8; i++){
	    	SET_GPIOIIC0_SCL_LOW;
	    	delay(DELAY_1US_VAL*gpioiic_delay_count);

	        if ((temp & (0x80>>i)) == 0){
	        	SET_GPIOIIC0_SDA_LOW;
	        }
	        else {
	        	SET_GPIOIIC0_SDA_HIGH;
	        }

	        delay(DELAY_1US_VAL*gpioiic_delay_count);
	        SET_GPIOIIC0_SCL_HIGH;
	        delay(DELAY_1US_VAL*gpioiic_delay_count);
	        delay(DELAY_1US_VAL*gpioiic_delay_count);
	    }

	    // get ack
	    SET_GPIOIIC0_SCL_LOW;
	    SET_GPIOIIC0_SDA_HIGH;
	    SET_GPIOIIC0_SDA_IN;
	    delay(DELAY_1US_VAL*gpioiic_delay_count);
	    SET_GPIOIIC0_SCL_HIGH;
	    i = 100;
	    while ( GET_GPIOIIC0_SDA_VAL ){
	       i--;
	       if (i==0){
	    	   SET_GPIOIIC0_SCL_HIGH;
	    	   SET_GPIOIIC0_SDA_OUT;
	    	   return 0; }   //  slave did not ack
	    }
	    delay(DELAY_1US_VAL*gpioiic_delay_count);
	    SET_GPIOIIC0_SCL_LOW;
	    delay(DELAY_1US_VAL*gpioiic_delay_count);
	    SET_GPIOIIC0_SDA_HIGH;

	    for (i=0; i<read_num; i++){
	    	temp=0;
	    	SET_GPIOIIC0_SDA_IN;
	        for (j=0; j<8; j++){

	        	SET_GPIOIIC0_SCL_LOW;
	        	delay(DELAY_1US_VAL*gpioiic_delay_count);
	        	SET_GPIOIIC0_SCL_HIGH;

	            if (GET_GPIOIIC0_SDA_VAL){
	        		    temp |= (0x80>>j);
	        	}
	            else {
	        		   ;
	            }
	        }
	        // put ack
	        SET_GPIOIIC0_SCL_LOW;
	        SET_GPIOIIC0_SDA_HIGH;
	        SET_GPIOIIC0_SDA_OUT;
	        delay(DELAY_1US_VAL*gpioiic_delay_count);
	        SET_GPIOIIC0_SCL_HIGH;
	        delay(DELAY_1US_VAL*gpioiic_delay_count);
	        SET_GPIOIIC0_SDA_LOW;
	       delay(DELAY_1US_VAL*gpioiic_delay_count);
	       SET_GPIOIIC0_SCL_LOW;
	       delay(DELAY_1US_VAL*gpioiic_delay_count);
	       SET_GPIOIIC0_SDA_HIGH;

	       read_buf[i] = temp;
	    }

	    SET_GPIOIIC0_SCL_HIGH;

    return 1;    // done
}

uint32_t gpioiic0_master_write( uint32_t slave_addr, uint32_t* write_buf, uint32_t write_num )
{
	uint32_t i,j,k, temp;

		// start bit
		SET_GPIOIIC0_SCL_HIGH;
		SET_GPIOIIC0_SDA_HIGH;
		delay(DELAY_1US_VAL*gpioiic_delay_count);
		SET_GPIOIIC0_SDA_OUT;
		SET_GPIOIIC0_SDA_LOW;
		delay(DELAY_1US_VAL*gpioiic_delay_count);

		// send slave address
	    temp = slave_addr & ~0x01;
	    for (i=0; i<8; i++){
	    	SET_GPIOIIC0_SCL_LOW;
	    	delay(DELAY_1US_VAL*gpioiic_delay_count);

	        if ((temp & (0x80>>i)) == 0){
	        	SET_GPIOIIC0_SDA_LOW;
	        }
	        else {
	        	SET_GPIOIIC0_SDA_HIGH;
	        }

	        delay(DELAY_1US_VAL*gpioiic_delay_count);
	        SET_GPIOIIC0_SCL_HIGH;
	        delay(DELAY_1US_VAL*gpioiic_delay_count);
	        delay(DELAY_1US_VAL*gpioiic_delay_count);
	    }

	    // get ack
	    SET_GPIOIIC0_SCL_LOW;
	    SET_GPIOIIC0_SDA_HIGH;
	    SET_GPIOIIC0_SDA_IN;
	    delay(DELAY_1US_VAL*gpioiic_delay_count);
	    SET_GPIOIIC0_SCL_HIGH;
	    i = 100;
	    while ( GET_GPIOIIC0_SDA_VAL ){
	       i--;
	       if (i==0){
	    	   SET_GPIOIIC0_SCL_HIGH;
	    	   SET_GPIOIIC0_SDA_OUT;
	    	   return 0; }   //  slave did not ack
	    }
	    delay(DELAY_1US_VAL*gpioiic_delay_count);
	    SET_GPIOIIC0_SCL_LOW;
	    delay(DELAY_1US_VAL*gpioiic_delay_count);
	    SET_GPIOIIC0_SDA_HIGH;

	    for (i=0; i<write_num; i++){
	    	temp=write_buf[i];
	    	SET_GPIOIIC0_SDA_OUT;
	        for (j=0; j<8; j++){
	        	SET_GPIOIIC0_SCL_LOW;
	            delay(DELAY_1US_VAL*gpioiic_delay_count);

	            if ((temp & (0x80>>j)) == 0){
	        		    SET_GPIOIIC0_SDA_LOW;
	        	}
	            else {
	        		    SET_GPIOIIC0_SDA_HIGH;
	            }
	        	delay(DELAY_1US_VAL*gpioiic_delay_count);
                SET_GPIOIIC0_SCL_HIGH;
	        	delay(DELAY_1US_VAL*gpioiic_delay_count);
	        	delay(DELAY_1US_VAL*gpioiic_delay_count);
	        }
	        // get ack
	        SET_GPIOIIC0_SCL_LOW;
	        SET_GPIOIIC0_SDA_HIGH;
	        SET_GPIOIIC0_SDA_IN;
	        delay(DELAY_1US_VAL*gpioiic_delay_count);
	        SET_GPIOIIC0_SCL_HIGH;
	        k = 100;
	        while ( GET_GPIOIIC0_SDA_VAL ){
	        	 k--;
	        	 if (k==0){
	        	   SET_GPIOIIC0_SCL_HIGH;
	        	   SET_GPIOIIC0_SDA_OUT;
	        	   return 0;
	        	 }   //  slave did not ack
	        }
	       delay(DELAY_1US_VAL*gpioiic_delay_count);
	       SET_GPIOIIC0_SCL_LOW;
	       delay(DELAY_1US_VAL*gpioiic_delay_count);
	       SET_GPIOIIC0_SDA_HIGH;
	    }

	    SET_GPIOIIC0_SCL_HIGH;


	    return 1;    // done
}



















