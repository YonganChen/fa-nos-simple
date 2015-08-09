/*
 * Main.c
 *
 *  Created on: 2012-12-12
 *      Author: cya
 */

#include <stdint.h>
#include "../../Components/uart/uart.h"
#include "../../Components/gpio/gpio.h"
#include "../../Components/xprintf/xprintf.h"

#define DELAY_1S_VAL    (0xfffff)
#define DELAY_1MS_VAL   (0x418)
#define DELAY_1US_VAL   (0x01)

/*
 *  delay some time
 */
void delay(volatile uint32_t count)
{
    for(;count>0;count--){
    }
}

static unsigned char  digitronCharMap[] = {
      // 0     1    2    3    4    5    6    7    8    9    A    b    C    d    E    F    -  .
        0xEB,0x41,0xB3,0xBA,0x78,0xDA,0xDB,0xA8,0xFB,0xF8,0xF9,0x5B,0x13,0x3B,0xD3,0xD1,0x10,0x04
};

// data_pin: GPH0_3, sclk_pin: GPH0_1, rclk_pin: GPH0_2

//-----------------------------------------------------------------------
 void init_gpio()
 {
 	GPH0CON = 0x00001111;                   // set GPH0_0~GPH0_3 to output
	GPH0DAT = 0x00;                         // default high
 }

//------------------------------------------------------------------------
 void set_data( uint32_t data )
 {
 	if ( data==0 ) {
 		GPH0DAT &= ~(0x08); 
 	}
 	else {
 		GPH0DAT |= 0x08;
 	}
 }


//------------------------------------------------------------------------
  void set_sclk( uint32_t sclk )
 {
 	if ( sclk==0 ) {
 		GPH0DAT &= ~(0x02); 
 	}
 	else {
 		GPH0DAT |= 0x02;
 	}
 }

//-------------------------------------------------------------------------
  void set_rclk( uint32_t rclk )
 {
 	if ( rclk==0 ) {
 		GPH0DAT &= ~(0x04); 
 	}
 	else {
 		GPH0DAT |= 0x04;
 	}
 }

//--------------------------------------------------------------------------
void LEDOutput(unsigned char c)           
{   
    unsigned char i;
    for (i=8; i>=1; i--)
    {
        if (c&0x80) {
            set_data(1);
        } else { 
            set_data(0);
        }
        c<<=1;
        set_sclk(0);
        delay(DELAY_1US_VAL);
        set_sclk(1);
        delay(DELAY_1US_VAL);
    }
}

//-------------------------------------------------------------------------
void digitronDispChar(uint32_t pos, uint32_t number)                    
{          
    LEDOutput(1 << (pos+3));     
    LEDOutput(digitronCharMap[number]);      

    set_rclk(0);
    delay(DELAY_1US_VAL);
    set_rclk(1);
    delay(DELAY_1US_VAL);
}


//-------------------------------------------------------------------------
 void start(void) __attribute__((section(".start")));
 void start() 
 {
	uint32_t temp;
	uint8_t getstr[20];

	uart0_init(115200);

	xdev_out(uart0_putc);
	xdev_in(uart0_getc);

	xprintf("FA210 Tester v1\n");

	init_gpio();

	while(1){

		digitronDispChar(1, 16);   
        digitronDispChar(2, 17);  
        digitronDispChar(3, 14);  
        digitronDispChar(4, 15); 
	 }
 }
