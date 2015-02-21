#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>

#include "main.h"

void i2c_transmit(char address, char reg, char data)
{
	TWCR = 0xA4;                                                  // send a start bit on i2c bus
	while(!(TWCR & 0x80));                                        // wait for confirmation of transmit 
	TWDR = address;                                               // load address of i2c device
	TWCR = 0x84;                                                  // transmit
	while(!(TWCR & 0x80));                                        // wait for confirmation of transmit
	TWDR = reg;
	TWCR = 0x84;                                                  // transmit
	while(!(TWCR & 0x80));                                        // wait for confirmation of transmit
	TWDR = data;
	TWCR = 0x84;                                                  // transmit
	while(!(TWCR & 0x80));                                        // wait for confirmation of transmit
	TWCR = 0x94;                                                  // stop bit
}
