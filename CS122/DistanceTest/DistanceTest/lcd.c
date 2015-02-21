#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>

#include "main.h"

unsigned char s[21];			// Char array used to send text to the LCD03

void setupLCD(void)
{
	i2c_transmit(LCD03, 0, 4);	// Hide LCD03 cursor
	i2c_transmit(LCD03, 0, 12);	// Clears screen and returns cursor to the home screen
}

void writeString(void)
{
unsigned char index = 0;

	while(s[index])				// Send chars to LCD03 untill terminated by a null
	{
		i2c_transmit(LCD03, 0, s[index]);
		index++;
	}		
}

void setCur(char x)
{
	i2c_transmit(LCD03, 0, 2);	// Command to move LCD03 cursor
	i2c_transmit(LCD03, 0, x);	// Where to move cursor to
}
