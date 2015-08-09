/*
 * gpio_iic.h
 *
 *  Created on: 2013-4-27
 *      Author: chen
 */

#ifndef GPIO_IIC_H_
#define GPIO_IIC_H_

/*
 * SCL: GPD1_1,  SDA: GPD1_0
 */
#include <stdint.h>
#include "gpio.h"

#define IIC_DELAY_TIME  (10)

#define IIC_GPIO_CON   GPD1CON
#define IIC_GPIO_DAT   GPD1DAT

#define SDA_PIN   0x00
#define SCL_PIN   0x01

#define SET_SCL_OUTPUT()  IIC_GPIO_CON = (IIC_GPIO_CON & 0xffffff0f)|0x00000010
#define SET_SDA_INPUT()   IIC_GPIO_CON = (IIC_GPIO_CON & 0xfffffff0)
#define SET_SDA_OUTPUT()  IIC_GPIO_CON = (IIC_GPIO_CON & 0xfffffff0)|0x00000001
#define SET_SDA()         IIC_GPIO_DAT |= 1<<SDA_PIN
#define CLR_SDA()         IIC_GPIO_DAT &= ~(1<<SDA_PIN)
#define SET_SCL()         IIC_GPIO_DAT |= 1<<SCL_PIN
#define CLR_SCL()         IIC_GPIO_DAT &= ~(1<<SCL_PIN)
#define GET_SDA()         (IIC_GPIO_DAT&0x01)


void gpio_iic_init(void);
void gpio_iic_start (void);
void gpio_iic_stop (void);
char gpio_iic_Gack (void);  // 1-failed, 0-ok
void gpio_iic_Pack (void);
void gpio_iic_Pnack (void);
void gpio_iic_write ( unsigned char wbyte );
void gpio_iic_read ( unsigned char *rbyte );

#endif /* GPIO_IIC_H_ */
