//  Defines

#define START_CLK	0x0A				// Start clock with 1:8 prescaler CTC mode
#define START_CLK_N	0x02				// Start clock running 1:8 prescaler in normal mode
#define STOP_CLK	0x08				// Stop clock
#define LCD03		0xC6				// Address of LCD03

// Prototypes

// main.c
void startRange(void);
unsigned int getEcho(void);
void displayData(unsigned int r);
void setup(void);						// General chip setup
void startTimer(unsigned int time);		// Starts the timer running for a number of uS defined by value of time
void waitForTimer(void);				// Waits for the timer to stop

// port.c
void i2c_transmit(char address, char reg, char data);
char i2cRead(char address, char reg);

// lcd.c
void setupLCD(void);					// Readies the LCD screen
void writeString(void);					// Writes a string to the LCD03
void setCur(char x);					// Moves cursor to position in x
void clrScr(void);						// clears the LCD03 screen	
