/*
 * wait.h
 *
 *  Created on: 2014-11-4
 *      Author: chya
 */

#ifndef SI470X_WAIT_H_
#define SI470X_WAIT_H_

#include<stdint.h>

void wait_ms(uint16_t ms);
void wait_us(uint16_t us);
void wait_ns(uint16_t ns);
void _nop_(void);

#endif /* WAIT_H_ */
