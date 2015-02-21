#include <avr/io.h>

// Bit-access functions
unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
	return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}
unsigned char GetBit(unsigned char x, unsigned char k) {
	return ((x & (0x01 << k)) != 0);
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; // Config port A as inputs, init 1s
	DDRC = 0xFF; PORTC = 0x00; // Config port C as outputs, init 0s
	while(1)
	{
		// if PA0 is 1, set PB1PB0=01, else =10
		if (GetBit(PINA,0)==0) { // Button pressed
			PORTC = 0x7F; // PC6..PC0 all 1s; lights all 7 segments
		}
		else {
			PORTC = 0x00; // Turn off all 7 segments
		}
	}
}