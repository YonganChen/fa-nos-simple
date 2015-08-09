#include <stdint.h>
#include <stdarg.h>
#include "../xprintf/xprintf.h"
#include "../s3c2416.h"
#include "font_8x16.h"
#include "bmp.h"

extern unsigned char __CHS[];
extern unsigned char __VGA[];

// FB addr
int gFB_Addr = 0x33C00000;
int gRow,gCol;
int gLeftTopX, gLeftTopY, gRightBotX, gRightBotY;
unsigned char *gImage_bmp;


// init LCD
void Lcd_Init(int lcd_type)
{	
	int hspw,hbpd,hfpd,vspw,vbpd,vfpd,vsync,hsync,vclk,ivclk;

	// init value
	rVIDCON0 = 0;
	rVIDCON1 = 0;
	rWINCON0 = 0;

	// set gpio to lcd func
	rGPCCON = 0xAAAAAAAA;
	rGPDCON = 0xAAAAAAAA; 

	// turn on lcd power
	rGPBCON &= ~(0x3<<2);
	rGPBCON |= (1<<2);
	rGPBDAT |= (1<<1);

	// turn lcd backlight
	rGPGCON &= ~(0x3<<14);
	rGPGCON |= (1<<14);
	rGPGDAT |= (1<<7);

	gLeftTopX = 0;
	gLeftTopY = 0;

	xprintf("lcd_type = %x\n",lcd_type);
	switch(lcd_type)  
	{
	case 26:
	{
		// S70D
		gImage_bmp = gImage_800480;

		gRow=480;
		gCol=800;
		gRightBotX  = gCol-1;
		gRightBotY  = gRow-1;

		hspw = 20;
		hbpd = 87;
		hfpd = 100;                 // hfpd dose not make sense
		vspw = 10;
		vbpd = 20;
		vfpd = 1;                 // vfpd dose not make sense

		vsync = 1;
		hsync = 0;
		vclk = 1;
		ivclk = 0;

		break;
	}
	case 8:    // W35
	{
		gImage_bmp = gImage_320240;

		gRow=240;
		gCol=320;
		gRightBotX  = gCol-1;
		gRightBotY  = gRow-1;

		hspw = 1;
		hbpd = 68;
		hfpd = 100;
		vspw = 1;
		vbpd = 10;
		vfpd = 1;

		vsync = 1;
		hsync = 1;
		vclk = 15;      // 0x00~0x3f(63)

		break;
	}
	case 19:   // P43
	{
		gImage_bmp = gImage_480272;

		gRow=272;
		gCol=480;
		gRightBotX  = gCol-1;
		gRightBotY  = gRow-1;

		hspw = (10);
		hbpd = (43);        // hbpd+hfpd must be 43
		hfpd = (0);
		vspw = (10);
		vbpd = (4);
		vfpd = (2);

		vsync = 1;
		hsync = 1;
		vclk = 9;
		ivclk = 1;

		break;
	}
	case 14:   // H43
	{
		gImage_bmp = gImage_480272;

		gRow=272;
		gCol=480;
		gRightBotX  = gCol-1;
		gRightBotY  = gRow-1;

		hspw = (0);
		hbpd = (40 - 1);
		hfpd = (5 - 1);
		vspw = (0);
		vbpd = (8 - 1);
		vfpd = (8 - 1);

		vsync = 1;
		hsync = 1;
		vclk = 9;


		break;
	}
	case 1:   // N43
	{
		gImage_bmp = gImage_480272;

		gRow=272;
		gCol=480;
		gRightBotX  = gCol-1;
		gRightBotY  = gRow-1;

		hspw = 0x6;
		hbpd = 0x2d;
		hfpd = 0x4;
		vspw = 0x2;
		vbpd = 0x3;
		vfpd = 0x2;

		vsync = 0;
		hsync = 0;
		vclk = 9;

		break;
	}
	case 3:  // S70
	{
		gImage_bmp = gImage_800480;

		gRow=480;
		gCol=800;
		gRightBotX  = gCol-1;
		gRightBotY  = gRow-1;

		hspw = 19;
		hbpd = 45;
		hfpd = 1;                 // hfpd dose not make sense
		vspw = 10;
		vbpd = 11;
		vfpd = 1;                 // vfpd dose not make sense

		vsync = 1;
		hsync = 0;
		vclk = 1;
		ivclk = 0;

		break;
	}
	case 2:    // A70
	{
		gImage_bmp = gImage_800480;

		gRow=480;
		gCol=800;
		gRightBotX  = gCol-1;
		gRightBotY  = gRow-1;

		hspw = 0x30;
		hbpd = 0x28;
		hfpd = 0x28;
		vspw = 0x18;
		vbpd = 0x1d;
		vfpd = 0x11;

		vsync = 1;
		hsync = 1;
		vclk = 9;

		break;
	}
	case 4:   // W50
	{
		gImage_bmp = gImage_800480;

		gRow=480;
		gCol=800;
		gRightBotX  = gCol-1;
		gRightBotY  = gRow-1;

		hspw = 48;
		hbpd = 40;
		hfpd = 40;
		vspw = 12;
		vbpd = 20;
		vfpd = 20;

		vsync = 1;
		hsync = 1;
		vclk = 9;

		break;
	}
	}

	// config timming
	// config VIDCONx，config interface-type clock polarity and enable lcd controller, etc
	rVIDCON0 |= (0<<22)|(0<<13)|(vclk<<6)|(1<<5)|(1<<4)|(0<<2)|(3<<0);
	rVIDCON1 |= vsync<<5 | hsync<<6 | ivclk<<7;
	rVIDTCON0 = vbpd<<16 | vfpd<<8 | vspw<<0;
	rVIDTCON1 = hbpd<<16 | hfpd<<8 | hspw<<0;
	// config length, width
	rVIDTCON2 = (gRightBotY << 11) | (gRightBotX << 0);

	// config windows1
	// bit[0]:enable
	// bit[2~5]:24bpp
	rWINCON0 |= 1<<0;
	rWINCON0 &= ~(0xf << 2);
	rWINCON0 |= (0xB<<2);

	// config windows1 up down left right
	rVIDOSD0A = (gLeftTopX<<11) | (gLeftTopY << 0);
	rVIDOSD0B = (gRightBotX<<11) | (gRightBotY << 0);
	// rVIDOSD0C = (gRightBotY + 1) * (gRightBotX + 1);

	// config fb addr
	rVIDW00ADD0B0 = gFB_Addr;
	rVIDW00ADD1B0 = (((gRightBotX + 1)*4 + 0) * (gRightBotY + 1)) & (0xffffff);
}


// draw a point
void Lcd_Draw_Pixel(int row, int col, int color)
{
	unsigned long * pixel = (unsigned long  *)gFB_Addr;
	*(pixel + row * gCol + col) = color;
}

// clean display
void Lcd_Clear_Screen(int color)
{
	int i, j;

	for (i = 0; i < gRow; i++)
		for (j = 0; j < gCol; j++)
			Lcd_Draw_Pixel(i, j, color);

}

// draw a horizontal line
void Lcd_Draw_Hline(int row, int col1, int col2, int color)
{
	int j;

	for (j = col1; j <= col2; j++)
		Lcd_Draw_Pixel(row, j, color);

}

// draw a vertical line
void Lcd_Draw_Vine(int col, int row1, int row2, int color)
{
	int i;
	for (i = row1; i <= row2; i++)
		Lcd_Draw_Pixel(i, col, color);

}

// Cross symbols
void Lcd_Draw_Cross(int row, int col, int halflen, int color)
{
	Lcd_Draw_Hline(row, col-halflen, col+halflen, color);
	Lcd_Draw_Vine(col, row-halflen, row+halflen, color);
}

// Draw characters
void Lcd_Draw_Char(unsigned char c)
{
	// static is needed
	static int x = 0;	// column
	static int y = 0;	// line

	int i,j;
	unsigned char line_dots;

	// Get the font
	unsigned char *char_dots = (unsigned char *) (fontdata_8x16 + c * 16);


	// carriage returns ?
	if (c == '\n')
	{
		y += 16;
		if (y > gRow)
			y = 0;
		return ;
	}
	else if (c == '\r')
	{
		x = 0;
		return;
	}

	for (i = 0; i < 16; i++)
	{
		line_dots = char_dots[i];
		for (j = 0; j < 8; j++)
		{
			// if 1, draw point
			if (line_dots & (0x80 >> j))
			{
				Lcd_Draw_Pixel(y+i, x+j, 0xff);
			}
		}
	}

	// move to the next 8 * 16
	x += 8;
	if (x > gCol)
	{
		x = 0;
		y += 16;
		if (y > gRow)
			y = 0;
	}
}

void Lcd_Draw_Bmp(const unsigned char image_bmp[])
{
	int i, j, offset;
	unsigned char *p = (unsigned char *)image_bmp;
	int blue, green, red;
	int color;

	Lcd_Clear_Screen(0x0);

	for (i = 0; i < gRow; i++)
		for (j = 0; j < gCol; j++)
		{

			blue  = *p++;
			green = *p++;
			red   = *p++;

			color = red << 16 | green << 8 | blue << 0;
			Lcd_Draw_Pixel(i, j, color);
		}

}

void Lcd_Draw_Outline ( int xblue, int xgreen, int xred )
{
	int j, i, color, blue, green, red;

	Lcd_Clear_Screen(0x0);

	for (i = 0; i < gRow; i++)
		for (j = 0; j < gCol; j++)
		{

			// draw display area outline
			if (i==0 || i== gRow-1 || j==0 || j==gCol-1){

				blue = xblue;
				green = xgreen;
				red = xred;
			}
			else {
				blue = 0x00;
			    green = 0x00;
				red = 0x00;
			}

			color = red << 16 | green << 8 | blue << 0;
			Lcd_Draw_Pixel(i, j, color);
		}
}
/*
display ASCII
*/
void Lcd_PutASCII(unsigned int x,unsigned int y,unsigned char ch,unsigned int c,unsigned int bk_c,unsigned int st)
{
	unsigned short int i,j;
	unsigned char *pZK,mask,buf;



	pZK = &__VGA[ch*16];
	for( i = 0 ; i < 16 ; i++ )
	{
		mask = 0x80;
		buf = pZK[i];
		for( j = 0 ; j < 8 ; j++ )
		{
			if( buf & mask )
			{
				Lcd_Draw_Pixel(x+i,y+j,c);
			}else
			{
				if( !st )
				{
					Lcd_Draw_Pixel(x+i,y+j,bk_c);
				}
			}

			mask = mask >> 1;
		}
	}
}


/*
dispaly hanzi
*/
void Lcd_PutHZ(unsigned int x,unsigned int y,unsigned short int QW,unsigned int c,unsigned int bk_c,unsigned int st)
{
	unsigned short int i,j;
	unsigned char *pZK,mask,buf;

	pZK = &__CHS[ (  ( (QW >> 8) - 1 )*94 + (QW & 0x00FF)- 1 )*32 ];
	for( i = 0 ; i < 16 ; i++ )
	{
		//left
		mask = 0x80;
		buf = pZK[i*2];
		for( j = 0 ; j < 8 ; j++ )
		{
			if( buf & mask )
			{
				Lcd_Draw_Pixel(x+i,y+j,c);
			}else
			{
				if( !st )
				{
					Lcd_Draw_Pixel(x+i,y+j,bk_c);
				}
			}
			mask = mask >> 1;
		}

		//right
		mask = 0x80;
		buf = pZK[i*2 + 1];
		for( j = 0 ; j < 8 ; j++ )
		{
			if( buf & mask )
			{
				Lcd_Draw_Pixel(x+i ,y+j+8, c);
			}else
			{
				if( !st )
				{
					Lcd_Draw_Pixel(x+i ,y+j+8,bk_c);
				}
			}
			mask = mask >> 1;
		}
	}
}


void Lcd_Printf(unsigned int x,unsigned int y,unsigned int c,unsigned int bk_c,unsigned int st,char *fmt,...)
{
	char __LCD_Printf_Buf[256];
	va_list ap;
	unsigned char *pStr = (unsigned char *)__LCD_Printf_Buf;
	unsigned int i = 0;

	xsprintf(__LCD_Printf_Buf, fmt);

	while(*pStr != 0 )
	{
		switch(*pStr)
		{
		case '\n' :
		{

			break;
		}

		default:
		{
			if( *pStr > 0xA0 & *(pStr+1) > 0xA0 )  //Hanzi
			{
				Lcd_PutHZ( x , y , (*pStr - 0xA0)*0x0100 + *(pStr+1) - 0xA0 , c , bk_c , st);

				pStr++;
				i++;

				y += 16;
			}else               //English
			{
				Lcd_PutASCII( x , y , *pStr , c , bk_c , st );

				y += 8;

			}

			break;
		}
		}

		pStr++;
		i++;

		if( i > 256 ) break;
	}

}


