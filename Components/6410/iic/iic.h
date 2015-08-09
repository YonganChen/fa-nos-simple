/*
 * iic.h
 *
 *  Created on: 2014-10-28
 *      Author: chya
 */

#ifndef IIC_H_
#define IIC_H_

#include <stdint.h>

typedef struct
{
	uint32_t    IICCON;
	uint32_t    IICSTAT;
	uint32_t    IICADD;
	uint32_t    IICDS;
	uint32_t    IICLC;

} S3C6410_IIC_REG_TypeDef;

#define S3C6410_IIC0  ((volatile S3C6410_IIC_REG_TypeDef *) 0x7F004000)
#define S3C6410_IIC1  ((volatile S3C6410_IIC_REG_TypeDef *) 0x7F00F000)

void     iic_init( volatile S3C6410_IIC_REG_TypeDef* iic, uint32_t speed);
uint32_t iic_master_read( volatile S3C6410_IIC_REG_TypeDef* iic, uint32_t slave_addr, uint32_t* read_buf, uint32_t read_num );

void     gpioiic0_init(uint32_t speed);
uint32_t gpioiic0_master_read( uint32_t slave_addr, uint32_t* read_buf, uint32_t read_num );
uint32_t gpioiic0_master_write( uint32_t slave_addr, uint32_t* write_buf, uint32_t write_num );

#endif /* IIC_H_ */
