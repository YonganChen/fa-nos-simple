/*
 * gpio.h
 *
 *  Created on: 2012-12-17
 *      Author: cya
 */

#ifndef GPIO_H_
#define GPIO_H_

#define GPA0CON   (*((volatile uint32_t *)0xE0200000))  //  Port Group GPA0 Control Register
#define GPA1CON   (*((volatile uint32_t *)0xE0200020))
#define GPJ2CON   (*((volatile uint32_t *)0xE0200280))
#define GPJ2DAT   (*((volatile uint32_t *)0xE0200284))
#define GPF0CON   (*((volatile uint32_t *)0xE0200120))
#define GPF1CON   (*((volatile uint32_t *)0xE0200140))
#define GPF2CON   (*((volatile uint32_t *)0xE0200160))
#define GPF3CON   (*((volatile uint32_t *)0xE0200180))
#define GPF0DAT   (*((volatile uint32_t *)0xE0200124))
#define	GPF1DAT   (*((volatile uint32_t *)0xE0200144))
#define	GPF2DAT   (*((volatile uint32_t *)0xE0200164))
#define	GPF3DAT   (*((volatile uint32_t *)0xE0200184))
#define GPF0DRV   (*((volatile uint32_t *)0xE020012C))
#define GPF1DRV   (*((volatile uint32_t *)0xE020014C))
#define GPF2DRV   (*((volatile uint32_t *)0xE020016C))
#define GPF3DRV   (*((volatile uint32_t *)0xE020018C))
#define GPD1CON   (*((volatile uint32_t *)0xE02000C0))
#define GPD1DAT   (*((volatile uint32_t *)0xE02000C4))
#define GPH2CON   (*((volatile uint32_t *)0xE0200C40))

#define GPH0CON   (*((volatile uint32_t *)0xE0200C00))
#define GPH0DAT   (*((volatile uint32_t *)0xE0200C04))
#define GPH0PUD   (*((volatile uint32_t *)0xE0200C08))
#define GPH0DRV   (*((volatile uint32_t *)0xE0200C0C))


#endif /* GPIO_H_ */
