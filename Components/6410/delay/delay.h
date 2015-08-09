/*
 * delay.h
 *
 *  Created on: 2014-10-31
 *      Author: chya
 */

#ifndef DELAY_H_
#define DELAY_H_

#define DELAY_1S_VAL     (0x29a428)
#define DELAY_1MS_VAL    (0xAA9)
#define DELAY_1US_VAL    (0x01)

void delay(volatile uint32_t count);

#endif /* DELAY_H_ */
