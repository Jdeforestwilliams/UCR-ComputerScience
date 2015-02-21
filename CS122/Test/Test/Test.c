/*
 * Test.c
 *
 * Created: 10/16/2014 6:23:07 PM
 *  Author: JDeForestWilliams
 */ 


#include <avr/io.h>
// Ensure DDRC is setup as output
void transmit_data(unsigned char data) {
	int i;
	for (i = 7; i >= 0 ; --i) {
		// Sets SRCLR to 1 allowing data to be set
		// Also clears SRCLK in preparation of sending data
		PORTC = 0x08;
		// set SER = next bit of data to be sent.
		PORTC |= ((data >> i) & 0x01);
		// set SRCLK = 1. Rising edge shifts next bit of data into the shift register
		PORTC |= 0x04;
	}
	// set RCLK = 1. Rising edge copies data from the “Shift” register to the “Storage” register
	PORTC |= 0x02;
	// clears all lines in preparation of a new transmission
	PORTC = 0x00;
}
int main(void)
{
	unsigned char output = 0x00; 
	DDRC  = 0x00; 
    while(1)
    {
        transmit_data(output);
    }
}