/*
 * clock.c
 *
 *  Created on: 2012-12-21
 *      Author: cya
 */


#include <stdint.h>
#include "clock.h"


uint32_t get_sclk_mpll()
{
	uint32_t mdiv, pdiv, sdiv;

	mdiv = (MPLL_CON & 0x3ff0000) >> 16;
	pdiv = (MPLL_CON & 0x3f00) >> 8;
	sdiv = MPLL_CON & 0x03;


	if (CLK_SRC0 & 0x10)
		return mdiv*(XXTI/(pdiv<<sdiv));
	else
		return XXTI;
}


uint32_t get_sclk_apll()
{
	uint32_t mdiv, pdiv, sdiv;

	mdiv = (APLL_CON0 & 0x3ff0000) >> 16;
	pdiv = (APLL_CON0 & 0x3f00) >> 8;
	sdiv = APLL_CON0 & 0x03;

	if (CLK_SRC0 & 0x01)
			return mdiv*(XXTI/(pdiv<<(sdiv-1)));
		else
			return XXTI;
}


uint32_t get_hclk_dsys()
{
	uint32_t a2m_ratio, hclk_dsys_ratio;

	a2m_ratio = (CLK_DIV0 & 0x70) >> 4;
	hclk_dsys_ratio = (CLK_DIV0 & 0xf0000) >> 16;

	if (CLK_SRC0 & 0x100000)
		return get_sclk_apll()/(a2m_ratio+1)/(hclk_dsys_ratio+1);
	else
		return get_sclk_mpll()/(hclk_dsys_ratio+1);


}







