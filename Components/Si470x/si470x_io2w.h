//-----------------------------------------------------------------------------
//
// io.h
//
// Contains the function prototypes for the functions contained in io2w.c and
// io3w.c
//
//-----------------------------------------------------------------------------
#ifndef _SI470X_IO_H_
#define _SI470X_IO_H_

#include <stdint.h>
#include "../gpio/gpio.h"

#define SET_SDIO_IN     S3C6410_GPIO_REG->GPBCON &= ~(0xf000000)
#define SET_SDIO_OUT    S3C6410_GPIO_REG->GPBCON |= (0x1000000)
#define SDIO_LOW        S3C6410_GPIO_REG->GPBDAT &= ~(1<<6)
#define SDIO_HIGH       S3C6410_GPIO_REG->GPBDAT |= (1<<6)
#define GET_SDIO_VAL    !((S3C6410_GPIO_REG->GPBDAT & (1<<6))== 0 )

#define SET_SCLK_IN     S3C6410_GPIO_REG->GPBCON &= ~(0xf00000)
#define SET_SCLK_OUT    S3C6410_GPIO_REG->GPBCON |= (0x100000)
#define SCLK_LOW        S3C6410_GPIO_REG->GPBDAT &= ~(1<<5)
#define SCLK_HIGH       S3C6410_GPIO_REG->GPBDAT |= (1<<5)

#define SET_RSTB_IN     S3C6410_GPIO_REG->GPHCON0 &= ~(0xf000)
#define SET_RSTB_OUT    S3C6410_GPIO_REG->GPHCON0 |= (0x1000)
#define RSTB_LOW        S3C6410_GPIO_REG->GPHDAT &= ~(1<<3)
#define RSTB_HIGH       S3C6410_GPIO_REG->GPHDAT |= (1<<3)

#define READ    1
#define WRITE   0

#define IO2W_ADDRESS 0x20


//-----------------------------------------------------------------------------
// Function prototypes
//-----------------------------------------------------------------------------
uint8_t io2w_write(uint8_t number_bytes, uint8_t *data_out);
uint8_t io2w_read(uint8_t number_bytes, uint8_t *data_in);

#endif
