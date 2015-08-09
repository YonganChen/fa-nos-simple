/*
 * iic.h
 *
 *  Created on: 2015-1-8
 *      Author: chya
 */

#ifndef IIC_H_
#define IIC_H_

#include <stdint.h>

typedef struct
{
	volatile uint32_t CON;    		 // IIC control
	volatile uint32_t STAT;    		 // IIC control/status
	volatile uint32_t ADD;    		 // IIC address
	volatile uint32_t DS;    		 // IIC address
	volatile uint32_t LC;    		 // IIC address
} IIC_TypeDef;

#define IIC0_BASE   (0x54000000)
#define IIC1_BASE   (0x54000100)
#define IIC0        ((IIC_TypeDef *) IIC0_BASE)
#define IIC1        ((IIC_TypeDef *) IIC1_BASE)

#define IIC_MASTER    0x01
#define IIC_SLAVE     0x02

void iic_init( IIC_TypeDef* IIC, uint32_t tclk_div );
int iic_transmit( IIC_TypeDef* IIC, uint32_t mode, uint32_t addr, uint32_t *tbytes, uint32_t len );
int iic_receive( IIC_TypeDef* IIC, uint32_t mode, uint32_t addr, uint32_t *rbytes, uint32_t len );


#endif /* IIC_H_ */
