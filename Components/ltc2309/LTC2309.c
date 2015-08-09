/*
 * LTC2309.c
 *
 *  Created on: 2013-4-28
 *      Author: chen
 */

#include <stdint.h>
#include "../../Components/gpio/gpio_iic.h"
#include "LTC2309.h"


uint8_t  LTC2309_init()                          // 1-failed, 0-ok
{
	gpio_iic_init ();
	return LTC2309_set_channel(LTC2309_AD0);

}

uint8_t LTC2309_set_channel(uint8_t channel)     // 1-failed, 0-ok
{
	gpio_iic_start ();
	gpio_iic_write (LTC2309_ADDR_W);
	if ( gpio_iic_Gack () )
		return 1;
	else
		{
		gpio_iic_write (channel);
		if ( gpio_iic_Gack () )
	    return 1;
		else
		   {
			gpio_iic_stop();
			return 0;
		   }
		}
}

uint32_t LTC2309_read()   //  > 0xffff failed
{
	uint32_t rdata;
	uint8_t  temp;

	rdata=0;
	temp=0;
	gpio_iic_start ();
	gpio_iic_write (LTC2309_ADDR_R);
	if ( gpio_iic_Gack () == 0)
	{
		gpio_iic_read(&temp);
	    gpio_iic_Pack ();
	    rdata = temp;
	    gpio_iic_read(&temp);
	    gpio_iic_Pnack ();
	    gpio_iic_stop();
	    rdata <<= 8;
	    rdata += temp;
	    rdata >>= 4;
	}
	else
	{
		rdata = 0xf0000;
	}

    return rdata;
}
