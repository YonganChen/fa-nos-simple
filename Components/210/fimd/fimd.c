/*
 * fimd.c
 *
 *  Created on: 2012-12-20
 *      Author: cya
 */

#include <stdint.h>
#include "fimd.h"
#include "lcd.h"
#include "../clock/clock.h"
#include "../gpio/gpio.h"
#include "bmp.h"

#define WIN0_PAGEWIDTH_W   (HOZ_VAL)
#define WIN0_OFFSIZE_W     (0)
#define WIN0_BUFF_LEN_W    ((WIN0_PAGEWIDTH_W+WIN0_OFFSIZE_W)*(LINE_VAL+1))
#define RTQoS_FIFO_LEVEL   255

 __attribute__((aligned(8))) static uint32_t win0_frame_buffer0[WIN0_BUFF_LEN_W];


void fimd_init()
{
	uint32_t clkval_f, i,temp;
	uint32_t *buff;

#ifdef VOUT_RGB                             // for RGB

	GPF0CON = 0x22222222;                   // set gpio to RGB Output
	GPF1CON = 0x22222222;
	GPF2CON = 0x22222222;
	GPF3CON = 0x22222222;

    clkval_f = get_hclk_dsys()/VCLK-1;
    VIDCON0 |= (clkval_f << 6);    // RGB interface, VCLK = HCLK/(CLKVAL+1)
    VIDCON1 = VIDCON1_VAL;
	VIDCON2 = VIDCON2_VAL;
	VIDCON3 = VIDCON3_VAL;
	VIDTCON0 = ((TVB-1)<<16) | ((TVFP-1)<<8) | (TVPW-1);
	VIDTCON1 = ((THB-1)<<16) | ((THFP-1)<<8) | (THPW-1);
	VIDTCON2 = ((LINE_VAL-1)<<11 | (HOZ_VAL-1));
	VIDTCON3 = VIDTCON3_VAL;
    VIDCON0 |= 0x40000013;

	DISPLAY_PATH_SEL = 0x02;               // RGB=FIMD I80=FIMD ITU=FIMD
#endif /* VOUT_RGB */

#ifdef VOUT_I80                           // for I80
	/*
	 * put i80 register init code here
	 */
#endif /* VOUT_I80 */

#ifdef VOUT_YUV                            // for YUV
	/*
	 * put YUV register init code here
	 */
#endif /* VOUT_YUV */

	CLK_GATE_IP1 |= 0x01;                // Gating all clocks for FIMD

	// setting frame buffers

    for (i=0;i<WIN0_BUFF_LEN_W;i++)          // init frame buff,RGB ARRY
    {

    	temp = ((uint32_t)(bmp[24+i*2+1]&0xf8))<<16;
    	temp |= ((uint32_t)(bmp[24+i*2+1]&0x07))<<13;
    	temp |= ((uint32_t)(bmp[24+i*2]&0xe0))<<5;
    	temp |= ((uint32_t)(bmp[24+i*2]&0x1f))<<3;


    	win0_frame_buffer0[i] = temp;

    }

	VIDW00ADD0B0 = (uint32_t)win0_frame_buffer0;
	VIDW00ADD2 = ((WIN0_OFFSIZE_W*4)<<13) | (WIN0_PAGEWIDTH_W*4);
	VIDW00ADD0B1 = VIDW00ADD0B0+((WIN0_PAGEWIDTH_W+WIN0_OFFSIZE_W)*(LINE_VAL+1))*4;


	// setting windows
	WINCON0 = 0x2d;                       // DMA, 24bpp R:8-G:8-B:8
	                                      // Enables the video output and video control signal.
	VIDOSD0A = 0x00;
	VIDOSD0B = (HOZ_VAL<<11) | (LINE_VAL);
	VIDOSD0C = HOZ_VAL*LINE_VAL;

	WIN0MAP = 0x0000ff00;         // bit 24: MAPCOLEN_F
	WPALCON_L = 0x201;

	SHODOWCON = 0x01;                   // Enables Channel 0
	W0RTQOSCON = RTQoS_FIFO_LEVEL<<4 | 0x02 ;

}




