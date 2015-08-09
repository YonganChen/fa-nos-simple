/*
 * mipi-dsim.c
 *
 *  Created on: 2012-12-29
 *      Author: chen
 */
#include <stdint.h>
#include "mipi_dsim.h"


void mipi_dsim_init()
{
	DSIM_CLKCTRL |= 0x90000000;        // turn on HS CLK, turn on byte CLK,
			                           // Enables the escape clock generating prescaler
	DSIM_CONFIG |= 0x386f;             // 24bpp, 4 Lane, Enable all lanes
	DSIM_ESCMODE |= 0x80;              // CmdLpdt=1
	DSIM_MDRESOL |= (1<<31|720);           // MainStandby=1, 720*768
	DSIM_MVPORCH |= (10<<16|10);
	DSIM_MHPORCH |= (20<<16|20);
	DSIM_MSYNC   |= (5<<22|10);
	DSIM_SDRESOL |= (1<<31);
	DSIM_PLLCTRL |= (1<<24|1<<23|3<<13|80<<3|8);
	DSIM_PHYACCHR |= (1<<14|4);





}
