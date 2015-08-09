/*
 * gpio.h
 *
 *  Created on: 2012-12-17
 *      Author: cya
 */

#ifndef GPIO_H_
#define GPIO_H_

#include <stdint.h>

typedef struct
{
	volatile uint32_t CON;
	volatile uint32_t DAT;
	volatile uint32_t UDP;
	volatile uint32_t SEL;
} GPIO_TypeDef;

#define  GPIO_OUTPUT  (0x01)
#define  GPIO_INPUT   (0x00)
#define  GPIO_PULLUP  (0x02)

#define GPIOB_BASE   (0x56000010)  //  Port Group GPB Control Register base address
#define GPIOE_BASE   (0x56000040)
#define GPIOG_BASE   (0x56000060)
#define GPIOH_BASE   (0x56000070)
#define GPIOL_BASE   (0x560000f0)
#define GPIOJ_BASE   (0x560000d0)

#define GPIOB   ((GPIO_TypeDef *) GPIOB_BASE)
#define GPIOE   ((GPIO_TypeDef *) GPIOE_BASE)
#define GPIOG   ((GPIO_TypeDef *) GPIOG_BASE)
#define GPIOH   ((GPIO_TypeDef *) GPIOH_BASE)
#define GPIOL   ((GPIO_TypeDef *) GPIOL_BASE)
#define GPIOJ   ((GPIO_TypeDef *) GPIOJ_BASE)


#endif /* GPIO_H_ */
