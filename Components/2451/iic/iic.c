/*
 * iic.c
 *
 *  Created on: 2015-1-8
 *      Author: chya
 */


#include <stdint.h>
#include "iic.h"
#include "../gpio/gpio.h"


/*
 *   ACK enable, TX clock source = PCLK/512, interrupt disable
 */
void iic_init( IIC_TypeDef* IIC, uint32_t tclk_div )
{

	if ( IIC==IIC0 ){
		 GPIOE->CON &= ~(0x0f<<28);
		 GPIOE->CON |= 0x0a<<28;
	}
	if ( IIC==IIC1 ){
		 GPIOE->SEL |= 0x06;
	}

	IIC->CON = (1<<7)|(1<<6)|(1<<5)|((0x0f&tclk_div)<<0 );
    IIC->STAT = 0xd0;
    IIC->CON &= ~( 1<<4 );
}

/*
 *   mode: MASTER/SLAVE,  stop=1:put stop-bit
 */
int iic_transmit( IIC_TypeDef* IIC, uint32_t mode, uint32_t addr, uint32_t *tbytes, uint32_t len )
{
	volatile uint32_t i, j;

    switch ( mode ){
    case IIC_MASTER:
        IIC->DS = addr & ~( 0x01 );
        IIC->STAT |= 0xf0;
        i = 0;
        while ( !( IIC->CON & 1<<4 ) ){   // wait for tramsmit done
        	i++;
        	if ( i>5000 ){
        		IIC->STAT = 0xd0;
        		IIC->CON &= ~( 1<<4 );
        		return -1;              // time out
        	}
        }

        if ( ( IIC->STAT & 1<<0 ) ){
        	IIC->STAT = 0xd0;
        	IIC->CON &= ~( 1<<4 );
        	return -2;      // NO ACK
        }

        for ( j=0; j<len; j++ ){        // transmit data

        	IIC->DS = tbytes[j];
        	IIC->CON &= ~( 1<<4 );
            while ( !( IIC->CON & 1<<4 ) ){   // wait for tramsmit done
            	i++;
            	if ( i>5000 ){
            		IIC->STAT = 0xd0;
            		IIC->CON &= ~( 1<<4 );
            		return -3;              // time out
            	}
            }
            if ( ( IIC->STAT & 1<<0 ) ){
              	IIC->STAT = 0xd0;
              	IIC->CON &= ~( 1<<4 );
              	return -4;      // NO ACK
            }
        }

    	break;
    case IIC_SLAVE:
    	// to do
    	return -5;
    	break;
    default :
    	return -6;
    }

    IIC->STAT = 0xd0;
    IIC->CON &= ~( 1<<4 );
    return 0;
}

/*
 *   mode: MASTER/SLAVE
 */
int iic_receive( IIC_TypeDef* IIC, uint32_t mode, uint32_t addr, uint32_t *rbytes, uint32_t len )
{
	volatile uint32_t i, j;

    switch ( mode ){
    case IIC_MASTER:
        IIC->DS = addr | 0x01;
        IIC->STAT = 0xb0;
        i = 0;
        while ( !( IIC->CON & 1<<4 ) ){   // wait for tramsmit done
        	i++;
        	if ( i>5000 ){
        		IIC->STAT = 0x90;
        		IIC->CON &= ~( 1<<4 );
        		return -1;              // time out
        	}
        }

        if ( ( IIC->STAT & 1<<0 ) ){
        	IIC->STAT = 0x90;
        	IIC->CON &= ~( 1<<4 );
        	return -2;      // NO ACK
        }


        // i = IIC->DS;
        for ( j=0; j<len; j++ ){        // receive data

            if ( j+1 == len ) {
            	IIC->CON &= ~ ( 1<<7 );    // NACK
            }
            else {
            	IIC->CON |=  ( 1<<7 );    // ACK
            }

        	IIC->CON &= ~( 1<<4 );
        	i = 0;
            while ( !( IIC->CON & 1<<4 ) ){   // wait for receive done
            	i++;
            	if ( i>5000 ){
            		IIC->STAT = 0x90;
            		IIC->CON &= ~( 1<<4 );
            		return -3;              // time out
            	}
            }
            rbytes[j] = IIC->DS;
        }

    	break;
    case IIC_SLAVE:
    	// to do
    	return -5;
    	break;
    default :
    	return -6;
    }

    IIC->STAT = 0x90;
    IIC->CON &= ~( 1<<4 );
    return 0;
}



