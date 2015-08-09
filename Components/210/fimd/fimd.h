/*
 * fimd.h
 *
 *  Created on: 2012-12-20
 *      Author: cya
 */

#ifndef FIMD_H_
#define FIMD_H_

#include <stdint.h>

#define VIDCON0       (*((volatile uint32_t *)0xF8000000))   // Video Main Control 0 Register
#define VIDCON1       (*((volatile uint32_t *)0xF8000004))
#define VIDCON2       (*((volatile uint32_t *)0xF8000008))
#define VIDCON3       (*((volatile uint32_t *)0xF800000C))
#define VIDTCON0      (*((volatile uint32_t *)0xF8000010))
#define VIDTCON1      (*((volatile uint32_t *)0xF8000014))
#define VIDTCON2      (*((volatile uint32_t *)0xF8000018))
#define VIDTCON3      (*((volatile uint32_t *)0xF800001C))
#define WINCON0       (*((volatile uint32_t *)0xF8000020))
#define VIDOSD0A      (*((volatile uint32_t *)0xF8000040))
#define VIDOSD0B 	  (*((volatile uint32_t *)0xF8000044))
#define VIDOSD0C      (*((volatile uint32_t *)0xF8000048))
#define VIDW00ADD0B0  (*((volatile uint32_t *)0xF80000A0))
#define VIDW00ADD0B1  (*((volatile uint32_t *)0xF80000A4))
#define VIDW00ADD0B2  (*((volatile uint32_t *)0xF80020A0))
#define VIDW01ADD0B0  (*((volatile uint32_t *)0xF80000A8))
#define VIDW01ADD0B1  (*((volatile uint32_t *)0xF80000AC))
#define VIDW01ADD0B2  (*((volatile uint32_t *)0xF80020A8))
#define VIDW02ADD0B0  (*((volatile uint32_t *)0xF80000B0))
#define VIDW02ADD0B1  (*((volatile uint32_t *)0xF80000B4))
#define VIDW02ADD0B2  (*((volatile uint32_t *)0xF80020B0))
#define VIDW03ADD0B0  (*((volatile uint32_t *)0xF80000B8))
#define VIDW03ADD0B1  (*((volatile uint32_t *)0xF80000BC))
#define VIDW03ADD0B2  (*((volatile uint32_t *)0xF80020B8))
#define VIDW04ADD0B0  (*((volatile uint32_t *)0xF80000C0))
#define VIDW04ADD0B1  (*((volatile uint32_t *)0xF80000C4))
#define VIDW04ADD0B2  (*((volatile uint32_t *)0xF80020C0))

#define VIDW00ADD1B0  (*((volatile uint32_t *)0xF80000D0))
#define VIDW00ADD1B1  (*((volatile uint32_t *)0xF80000D4))
#define VIDW00ADD1B2  (*((volatile uint32_t *)0xF80020D0))
#define VIDW01ADD1B0  (*((volatile uint32_t *)0xF80000D8))
#define VIDW01ADD1B1  (*((volatile uint32_t *)0xF80000DC))
#define VIDW01ADD1B2  (*((volatile uint32_t *)0xF80020D8))
#define VIDW02ADD1B0  (*((volatile uint32_t *)0xF80000E0))
#define VIDW02ADD1B1  (*((volatile uint32_t *)0xF80000E4))
#define VIDW02ADD1B2  (*((volatile uint32_t *)0xF80020E0))
#define VIDW03ADD1B0  (*((volatile uint32_t *)0xF80000E8))
#define VIDW03ADD1B1  (*((volatile uint32_t *)0xF80000EC))
#define VIDW03ADD1B2  (*((volatile uint32_t *)0xF80020E8))
#define VIDW04ADD1B0  (*((volatile uint32_t *)0xF80000F0))
#define VIDW04ADD1B1  (*((volatile uint32_t *)0xF80000F4))
#define VIDW04ADD1B2  (*((volatile uint32_t *)0xF80020F0))
#define VIDW00ADD2    (*((volatile uint32_t *)0xF8000100))
#define VIDW01ADD2    (*((volatile uint32_t *)0xF8000104))
#define VIDW02ADD2    (*((volatile uint32_t *)0xF8000108))
#define VIDW03ADD2    (*((volatile uint32_t *)0xF800010C))
#define VIDW04ADD2    (*((volatile uint32_t *)0xF8000110))

#define SHODOWCON     (*((volatile uint32_t *)0xF8000034))

#define WIN0MAP       (*((volatile uint32_t *)0xF8000180))
#define WPALCON_L     (*((volatile uint32_t *)0xF80001A0))

#define W0RTQOSCON	  (*((volatile uint32_t *)0xF8000264))

#define SHD_VIDW00ADD0 (*((volatile uint32_t *)0xF80040A0))
#define SHD_VIDW00ADD1 (*((volatile uint32_t *)0xF80040D0))
#define SHD_VIDW00ADD2 (*((volatile uint32_t *)0xF80040A0))


#define DISPLAY_PATH_SEL (*((volatile uint32_t *)0xE0107008))

void fimd_init(void);



#endif /* FIMD_H_ */
