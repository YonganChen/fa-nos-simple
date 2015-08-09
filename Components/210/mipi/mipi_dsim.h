/*
 * mipi-dsim.h
 *
 *  Created on: 2012-12-29
 *      Author: chen
 */

#ifndef MIPI_DSIM_H_
#define MIPI_DSIM_H_

#include <stdint.h>

#define DSIM_STATUS   (*((volatile uint32_t *)0xFA500000))
#define DSIM_SWRST    (*((volatile uint32_t *)0xFA500004))
#define DSIM_CLKCTRL  (*((volatile uint32_t *)0xFA500008))
#define DSIM_CONFIG   (*((volatile uint32_t *)0xFA500010))
#define DSIM_ESCMODE  (*((volatile uint32_t *)0xFA500014))
#define DSIM_MDRESOL  (*((volatile uint32_t *)0xFA500018))
#define DSIM_MVPORCH  (*((volatile uint32_t *)0xFA50001C))
#define DSIM_MHPORCH  (*((volatile uint32_t *)0xFA500020))
#define DSIM_MSYNC    (*((volatile uint32_t *)0xFA500024))
#define DSIM_SDRESOL  (*((volatile uint32_t *)0xFA500028))
#define DSIM_INTSRC   (*((volatile uint32_t *)0xFA50002C))
#define DSIM_INTMSK   (*((volatile uint32_t *)0xFA500030))
#define DSIM_PKTHDR   (*((volatile uint32_t *)0xFA500034))
#define DSIM_PAYLOAD  (*((volatile uint32_t *)0xFA500038))
#define DSIM_RXFIFO   (*((volatile uint32_t *)0xFA50003C))
#define DSIM_PLLCTRL  (*((volatile uint32_t *)0xFA50004C))
#define DSIM_PHYACCHR (*((volatile uint32_t *)0xFA500054))


void mipi_dsim_init(void);

#endif /* MIPI_DSIM_H_ */
