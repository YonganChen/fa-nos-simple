//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------

#include "si470x_io2w.h"      // To double check prototypes
#include "si470x_wait.h"
#include "../xprintf/xprintf.h"


//-----------------------------------------------------------------------------
// Send a 2-wire start and address byte. LSB will be set to indicate a read,
// cleared to indicate a write.
//
// A START condition is defined as a high to low transition on the SDIO pin
// while SCLK is high.
//
// Inputs:
//      io2w_address:  Address of device to access.
//      operation: Set to 1 for a read, set to 0 for a write
//
// Pin drive status upon exit:
//      SDIO = high (open-drain input)
//      SCLK = high
//  return: 1=ok, 0=failed
//-----------------------------------------------------------------------------
static uint8_t io2w_start(uint8_t io2w_address, uint8_t operation)
{
    int8_t i;

    SCLK_HIGH;
    SDIO_HIGH;
    SET_SDIO_OUT;  // Configure SDIO as push-pull

    // issue the START condition
    wait_us(1); // tSU:STA
    SDIO_LOW;
    wait_us(1); // tHD:STA
    SCLK_LOW;

    // Set the least significant bit to indicate read or write
    io2w_address = (io2w_address & 0xFE) | (operation & 0x01);

    // issue the control word (7 bit chip address + R/W* bit)
    // Note that tr:IN + tLOW + tf:IN + tHIGH = 2500 ns = 400 kHz
    for ( i = 7; i >= 0; i-- )
    {
        SCLK_LOW;
        wait_us(1); // tf:IN
        if ((io2w_address >> i) & 0x01){
        	SDIO_HIGH;
        }
        else {
        	SDIO_LOW;
        }
        wait_us(1); // tLOW
        SCLK_HIGH;
        wait_us(1); // tf:IN + tHIGH
    }

    // check the acknowledge

    SCLK_LOW;
    SDIO_HIGH;
    SET_SDIO_IN;   // Configure SDIO as open-drain
    wait_us(2); // tf:IN + tLOW
    SCLK_HIGH;
    wait_us(1); // tf:IN + tHIGH

    if (GET_SDIO_VAL != 0){
    	return 0;
    }
    else{
    	return 1;
    }
}

//-----------------------------------------------------------------------------
// Send a 2-wire stop.  A STOP condition is defined as a low to high transition
// on the SDIO pin while SCLK is high.
//
// Pin drive status upon exit:
//      SDIO = high (open-drain input)
//      SCLK = high
//-----------------------------------------------------------------------------
static void io2w_stop(void)
{
	SET_SDIO_OUT;  // Configure SDIO as push-pull
	SCLK_LOW;
    wait_us(2); // tf:IN + tLOW
    SDIO_LOW;
    wait_us(1);
    SCLK_HIGH;
    wait_us(1); // tf:IN + tSU:STO
    SDIO_HIGH;
}

//-----------------------------------------------------------------------------
// Write one byte of data.
//
// Inputs:
//		wrdata:  Byte to be written
//
// Pin drive status upon exit:
//      SDIO = high (open-drain input)
//      SCLK = high
//-----------------------------------------------------------------------------
static uint8_t io2w_write_byte(uint8_t wrdata)
{
    int8_t i;

    SET_SDIO_OUT;  // Configure SDIO as push-pull
    for ( i = 7; i >= 0; i-- )
    {
        SCLK_LOW;
        wait_us(1); // tf:IN
        if ((wrdata >> i) & 0x01){
        	SDIO_HIGH;
        }
        else{
        	SDIO_LOW;
        }
        wait_us(2); // tLOW
        SCLK_HIGH;
        wait_us(1); // tf:IN + tHIGH
    }
    // check the acknowledge

    SCLK_LOW;
    SDIO_HIGH;
    SET_SDIO_IN;  // Configure SDIO as open-drain
    wait_us(2); // tf:IN + tLOW
    SCLK_HIGH;
    wait_us(1); // tf:IN + tHIGH

    if (GET_SDIO_VAL != 0){
     	return 0; // ack not received.  This should never happen. Device isn't responding.
     }
    else{
    	return 1;
    }

}

//-----------------------------------------------------------------------------
// Read one byte of data.
//
// Inputs:
//		remaining bytes:  Zero value indicates an ack will not be sent.
//
// Outputs:
// 		Returns byte read
//
// Pin drive status upon exit:
//      SDIO = high (open-drain input) if no more bytes to be read
//      SDIO = low (open-drain input) if read is to continue
//      SCLK = high
//-----------------------------------------------------------------------------
static uint8_t io2w_read_byte(uint8_t remaining_bytes)
{
    int8_t i;
    uint8_t rddata = 0;

    SDIO_HIGH;
    SET_SDIO_IN;  // Configure SDIO as open-drain
    for( i = 7; i >= 0; i-- )
    {
        SCLK_LOW;
        wait_us(1);                      // tf:IN
        wait_us(2);                      // tLOW
        SCLK_HIGH;
        wait_us(1);                      // tf:IN + tHIGH
        rddata = ((rddata << 1) | (uint8_t)GET_SDIO_VAL);
    }
    // set the acknowledge
    SCLK_LOW;

    SDIO_HIGH;
    SET_SDIO_OUT;   // Configure SDIO as push-pull

    if (remaining_bytes == 0)
        SDIO_HIGH;
    else
        SDIO_LOW;

    wait_us(2); // tf:IN + tLOW
    SCLK_HIGH;
    wait_us(1); // tf:IN + tHIGH
    SDIO_HIGH;

    return rddata;
}


//-----------------------------------------------------------------------------
// Sends 2-wire start, writes an array of data, sends 2-wire stop.
//
// Inputs:
//		number_bytes: The number of bytes to write
//		data_out:     Source array for data to be written
//
//-----------------------------------------------------------------------------
uint8_t io2w_write(uint8_t number_bytes, uint8_t *data_out)
{
    uint8_t addr;

    // issue the START condition with address lsb cleared for writes
	addr = IO2W_ADDRESS;
    if (io2w_start(addr, WRITE)==0)
    {
    	return 0;
    }

    // loop writing all bytes in the data_out array
    while(number_bytes--)
    {
        if ( io2w_write_byte(*data_out++) == 0){
        	return 0;
        }
    }

    // issue the STOP condition
    io2w_stop();

    return 1;
}

//-----------------------------------------------------------------------------
// Sends 2-wire start, reads an array of data, sends 2-wire stop.
//
// Inputs:
//		number_bytes: Number of bytes to be read
//		data_in:      Destination array for data read
//
//-----------------------------------------------------------------------------
uint8_t io2w_read(uint8_t number_bytes, uint8_t *data_in)
{
    uint8_t addr;

    // issue the START condition with address lsb set for reads
	addr = IO2W_ADDRESS;
    if (io2w_start(addr, READ)==0){
    	return 0;
    }

    // loop until the specified number of bytes have been read
    while(number_bytes--)
    {
        *data_in++ = io2w_read_byte(number_bytes);
    }

    // issue the STOP condition
    io2w_stop();

    return 1;
}
