/*
 * timer.c
 *
 *  Created on: 2015-18-15
 *      Author: yonganch
 */


#include "timer.h"
#include "../clock/clock.h"

//------------------------------------------------------------------
//-- timer_n = 0~4, for timer0~4; value = 0~255
static void set_prescaler( uint32_t timer_n, uint32_t value ) {

   value &= 0x0000000ff;

   switch (timer_n){

   	case 0 :
    case 1 :{
    	TCFG0 &= ~0x0000000ff;
    	TCFG0 |= value;
    	break;
    }
    case 2:
    case 3:
    case 4:{
    	TCFG0 &= ~0x00000ff00;
    	TCFG0 |= value<<8;
    }
    default:
    	break;
   }
}
//--set_prescaler end--


//------------------------------------------------------------------
//-- timer_n = 0~4, for timer0~4; value = 1,2,4,8,16, 0 for SCLK_PWM
static void set_divider( uint32_t timer_n, uint32_t value ) {

   switch (value){
   	case 0:{
   		TCFG1 &= ~(0x0f<<(timer_n*4));
   		TCFG1 |= 0x05<<(timer_n*4);
   		break;
   	}
   	case 1:{
   		TCFG1 &= ~(0x0f<<(timer_n*4));
   		break;
   	}
   	case 2:{
   		TCFG1 &= ~(0x0f<<(timer_n*4));
   		TCFG1 |= 0x01<<(timer_n*4);
   		break;
   	}
   	case 4:{
   		TCFG1 &= ~(0x0f<<(timer_n*4));
   		TCFG1 |= 0x02<<(timer_n*4);
   		break;
   	}
   	case 8:{
   		TCFG1 &= ~(0x0f<<(timer_n*4));
   		TCFG1 |= 0x03<<(timer_n*4);
   		break;
   	}
   	case 16:{
   		TCFG1 &= ~(0x0f<<(timer_n*4));
   		TCFG1 |= 0x04<<(timer_n*4);
   		break;
   	}
    default:
    	break;
   }
}
//--set_divider end--

//--------------------------------------------------------------------------
//--using timer4 
void start_timimg() {

   volatile uint32_t i;

   set_prescaler(4, 1);
   set_divider(4, 1);

   TCNTB4 = 0xffffffff;

   TCON |= 0x02<<20;
  
   TCON &= ~(0x02<<20);

   TCON |= (0x01<<20);

}
//--start_timimg end--

//--------------------------------------------------------------------------
//--using timer4, return time in us
void stop_timimg( float *value ) {

  TCON &= ~(0x01<<20);
    
  *value = (0xffffffff-TCNTO4)*0.03f;
}
//--stop_timimg end--


static volatile uint32_t timer_delayus_tmp = 0;
//--------------------------------------------------------------------------
//--using timer4, called before timer_delayus_start
void timer_delayus_init( uint32_t value ){

  // init timer4
   set_prescaler(4, 1);
   set_divider(4, 1);

   TCNTB4 = 0xffffffff;

   timer_delayus_tmp = ( (float)0xffffffff - ((float)value/0.03f) );
}
//--timer_delayus_init--



//--------------------------------------------------------------------------
//--using timer4, delay us
void timer_delayus_waiting() {

   // update TCNTB4 to TCNT4
   TCON |= 0x02<<20;
  
   TCON &= ~(0x02<<20);

   // start timer4
   TCON |= (0x01<<20);

   // waiting....
   while ( TCNTO4 > timer_delayus_tmp ) {
    ;
   }

   // stop timer4
   TCON &= ~(0x01<<20);

   return ;

}
//--timer_delay end--

//--------------------------------------------------------------------------
//--using timer4, delay us,  value > 50
void timer_delayus( uint32_t value ) {

    // init timer4
   set_prescaler(4, 1);
   set_divider(4, 1);

   TCNTB4 = 0xffffffff;

   timer_delayus_tmp = ( (float)0xffffffff - ((float)value/0.03f) );

   // update TCNTB4 to TCNT4
   TCON |= 0x02<<20;
  
   TCON &= ~(0x02<<20);

   // start timer4
   TCON |= (0x01<<20);

   // waiting....
   while ( TCNTO4 > timer_delayus_tmp ) {
    ;
   }

   // stop timer4
   TCON &= ~(0x01<<20);

   return ;

}
//--timer_delayus--
