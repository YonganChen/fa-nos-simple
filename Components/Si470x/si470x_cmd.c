/*
 * si470x_cmd.c
 *
 *  Created on: 2014-11-8
 *      Author: chya
 */


#include <stdint.h>
#include "si470x_io2w.h"
#include "si470x_cmd.h"

static uint8_t si470x_cmd[13] = {0};


void si470x_reset()
{
	SET_SDIO_IN;
	SET_SDIO_OUT;
	SDIO_LOW;

	SET_SCLK_IN;
	SET_SCLK_OUT;
	SCLK_HIGH;

	SET_RSTB_IN;
	SET_RSTB_OUT;
	RSTB_LOW;

	wait_ms(1000);
	RSTB_HIGH;
	wait_ms(100);
	SDIO_HIGH;

}

uint8_t si470x_init()
{
	si470x_reset();

	si470x_cmd[7] = 0x10;
	si470x_cmd[10] = 0x81;

	if (io2w_write(12, si470x_cmd)==0){
		return 0;
	}
	else{
		return 1;
	}

}

/*
 * ok,1 failed,0
 */
uint8_t si470x_powerup(void)
{

	si470x_cmd[1] |= 0x01;
	si470x_cmd[1] &= ~(1<<6);

	if (io2w_write(2, si470x_cmd)==0){
		return 0;
	}
	else{
		return 1;
	}

}

uint8_t si470x_set(void)
{

	si470x_cmd[1] |= 0x01;
	si470x_cmd[1] &= ~(1<<6);

	if (io2w_write(2, si470x_cmd)==0){
		return 0;
	}
	else{
		return 1;
	}

}


uint8_t si470x_powerdown(void)
{
	si470x_cmd[1] |= 0x01;
	si470x_cmd[1] |= (1<<6);
	if (io2w_write(2, si470x_cmd)==0){
		return 0;
	}
	else{
		return 1;
	}

}

uint8_t si470x_seekup()
{

}

uint8_t si470x_seekdown()
{

}

uint8_t si470x_tuneup()
{

}

uint8_t si470x_tunedown()
{

}

uint8_t si470x_volumeup()
{

}

uint8_t si470x_volumedown()
{

}

uint8_t si470x_setfreq()
{

}

uint8_t si470x_getfreq()
{

}

uint8_t si470x_mute()
{
	si470x_powerdown();
    return 1;
}





