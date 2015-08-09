/*
 * LTC2309.h
 *
 *  Created on: 2013-4-28
 *      Author: chen
 */

#ifndef LTC2309_H_
#define LTC2309_H_

#include<stdint.h>

/*
 * SINGLE-ENDED (0~4.096V), UNIPOLAR, NAP MODE
 */
#define LTC2309_ADDR_W    (0x10)
#define LTC2309_ADDR_R    (LTC2309_ADDR_W+1)

#define LTC2309_AD0       (0x88)
#define LTC2309_AD1       (0xc8)
#define LTC2309_AD2       (0x98)
#define LTC2309_AD3       (0xd8)
#define LTC2309_AD4       (0xa8)
#define LTC2309_AD5       (0xe8)
#define LTC2309_AD6       (0xb8)
#define LTC2309_AD7       (0xf8)

uint8_t    LTC2309_init(void);                     // 1-failed, 0-ok
uint8_t    LTC2309_set_channel(uint8_t channel);   // 1-failed, 0-ok
uint32_t   LTC2309_read(void);                      //  > 0xffff failed

#endif /* LTC2309_H_ */
