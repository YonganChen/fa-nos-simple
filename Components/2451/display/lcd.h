
#ifndef LCD_H_
#define LCD_H_

void Lcd_Init(int lcd_type);
void Lcd_Draw_Bmp(const unsigned char image_bmp[]);
void Lcd_Draw_Pixel(int row, int col, int color);
void Lcd_Clear_Screen(int color);
void Lcd_Draw_Hline(int row, int col1, int col2, int color);
void Lcd_Draw_Vline(int col, int row1, int row2, int color);
void Lcd_Draw_Cross(int row, int col, int halflen, int color);
void Lcd_Draw_Circle(void);
void Lcd_Draw_Outline ( int xblue, int xgreen, int xred );
void Lcd_Draw_Char(unsigned char c);
void Lcd_PutASCII(unsigned int x,unsigned int y,unsigned char ch,unsigned int c,unsigned int bk_c,unsigned int st);
void Lcd_PutHZ(unsigned int x,unsigned int y,unsigned short int QW,unsigned int c,unsigned int bk_c,unsigned int st);
void Lcd_Printf(unsigned int x,unsigned int y,unsigned int c,unsigned int bk_c,unsigned int st,char *fmt,...);

#define RGB(r,g,b)   (unsigned int)( (r << 16) + (g << 8) + b )

#define	LCD_BAD         0
#define	LCD_N43         1
#define	LCD_A70         2
#define LCD_S70			3
#define LCD_W50			4
#define LCD_L80			5
#define LCD_W35			8
#define LCD_H43			14
#define LCD_W101		15
#define LCD_A121		16
#define LCD_U80			17
#define LCD_XD700		18
#define LCD_P43			19
#define LCD_P35			20
#define LCD_TD35        21
#define LCD_PA43        22
#define LCD_PB43        23
#define LCD_S702        24
#define LCD_HD101       25
#define LCD_S70D        26


#endif /* LCD_H_ */
