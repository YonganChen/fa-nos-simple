/*
 * iic.h
 *
 *  Created on: 2013-4-26
 *      Author: chen
 */

#ifndef IIC_H_
#define IIC_H_

#include <stdint.h>

#define I2CCON0    (*((volatile uint32_t *)0xE1800000))
#define I2CSTAT0   (*((volatile uint32_t *)0xE1800004))
#define I2CDS0     (*((volatile uint32_t *)0xE180000C))

void iic0_init(void);

#endif /* IIC_H_ */
