#ifndef SPI_H
#define SPI_H

unsigned char receivedData;

//Master Code
void SPI_MasterInit(void)
{
	// Set DDRB to have MOSI, SCK, and SS as output and MISO as input
	//DDRB5 = MOSI, DDRB7 = SCK, DDRB4 = SS
	// 1s for output, 0s for input
	DDRB = ( (1 << DDRB5) | (1 << DDRB7) | (1 << DDRB4) | (0 << DDRB6) );
	PORTB = ( (0 << DDRB5) | (0 << DDRB7) | (0 << DDRB4) | (1 << DDRB6) );
	// Set SPCR register to enable SPI, enable master, and use SCK frequency
	//   of fosc/16  (pg. 168)
	SPCR = (  (1 << SPE) | (1 << MSTR) | (1 << SPR0) );
	// Make sure global interrupts are enabled on SREG register (pg. 9)

}

void SPI_MasterTransmit(unsigned char cData)
{
	// data in SPDR will be transmitted, e.g. SPDR = cData;
	SPDR = cData;
	
	PORTB = PORTB & ~(1 << DDRB4); // set SS low
	while(!(SPSR & (1<<SPIF))) { // wait for transmission to complete
		;
	}
	PORTB = PORTB | (1 << DDRB4); // set SS high
}

//Servant Code
void SPI_ServantInit(void)
{
	// set DDRB to have MISO line as output and MOSI, SCK, and SS as input
	DDRB = ( (1 << DDRB6) | (0 << DDRB5) | (0 << DDRB7) | (0 << DDRB4) );
	PORTB = ( (0 << DDRB6) | (1 << DDRB5) | (1 << DDRB7) | (1 << DDRB4) );
	// set SPCR register to enable SPI and enable SPI interrupt (pg. 168)
	SPCR = ( (1 << SPE) | (1 << SPIE) );
	// make sure global interrupts are enabled on SREG register (pg. 9)
}


ISR(SPI_STC_vect)
{
	// this is enabled in with the SPCR register�s �SPI
	// Interrupt Enable�
	// SPDR contains the received data, e.g. unsigned char receivedData =
	// SPDR;
	receivedData = SPDR;
}

#endif //SPI_H