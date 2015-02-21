#include <avr/io.h>
#include <avr/interrupt.h>

unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

void TimerSet(unsigned long M) {
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

void TimerOn() {
	TCCR1B 	= 0x0B;
	OCR1A 	= 125;
	TIMSK1 	= 0x02;
	TCNT1 = 0;
	_avr_timer_cntcurr = _avr_timer_M;
	SREG |= 0x80;
}

void TimerOff() {
	TCCR1B 	= 0x00;
}

typedef struct task {
	int state;                  // Task's current state
	unsigned long period;       // Task period
	unsigned long elapsedTime;  // Time elapsed since last task tick
	int (*TickFct)(int);        // Task tick function
} task;

unsigned char tasksNum = 2;
unsigned char tasksPeriodGCD = 1;
task tasks[2];

void TimerISR() {
	unsigned char i;
	for (i=0; i < tasksNum; i++) {
		if (tasks[i].elapsedTime >= tasks[i].period){
			tasks[i].state = tasks[i].TickFct(tasks[i].state);
			tasks[i].elapsedTime = 0;
		}
		tasks[i].elapsedTime += tasksPeriodGCD;
	}
}

ISR(TIMER1_COMPA_vect)
{
	_avr_timer_cntcurr--;
	if (_avr_timer_cntcurr == 0) {
		TimerISR();
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

unsigned char pattern[3] = {0x3C, 0x24, 0x3C};
unsigned char row[3] = {0xFD, 0xFB, 0xF7};
unsigned char ind = 0;

enum SM1_States{init_1, wait_input, down, up, left, right};
int Tick_Fct1(int state){
	unsigned char input = (~PINA) & 0x0F;
	
	switch(state){ //transition
		case init_1:
			state = wait_input;
			break;
		
		case wait_input:
		case down:
		case up:
		case right:
		case left:
			if(input == 0x01) state = down;
			else if(input == 0x02) state = up;
			else if(input == 0x04) state = right;
			else if(input == 0x08) state = left;
			else state = wait_input;
			break;
		
		default:
			state = init_1;
	}
	switch(state){ //actions
		case wait_input:
			break;
		
		case up:
			if(row[2] != 0xEF){
				row[0] = (row[0] << 1) | 0x01;
				row[1] = (row[1] << 1) | 0x01;
				row[2] = (row[2] << 1) | 0x01;
			}
			break;
		
		case down:
			if(row[0] != 0xFE){				
				row[0] = (row[0] >> 1) | 0x80;
				row[1] = (row[1] >> 1) | 0x80;
				row[2] = (row[2] >> 1) | 0x80;
			}
			break;
		
		case right:
			if(pattern[0] != 0xF0){
				pattern[0] <<= 1;
				pattern[1] <<= 1;
				pattern[2] <<= 1;
			}
			break;
			
		case left:			
			if(pattern[0] != 0x0F){
				pattern[0] >>= 1;
				pattern[1] >>= 1;
				pattern[2] >>= 1;
			}
			break;
		
		default:
			break;
	}
	return state;
}

enum SM2_States{init_2, row_2, row_3, row_4};
int Tick_Fct2(int state){
	switch(state){ //transitions
		case init_2:
			state = row_2;
			break;
		
		case row_2:
			state = row_3;
			break;	
		
		case row_3:
			state = row_4;
			break;
		
		case row_4:
			state =  row_2;
			break;
		
		default:
			state = init_2;
			break;
	}
	switch(state){ //actions
		case row_2:
		case row_3:
		case row_4:
			PORTC = pattern[ind];
			PORTD = row[ind];
			ind = (ind + 1)%3;
			break;
		
		default:
			break;
	}	
	return state;
}

int main(void)
{
	  DDRC = 0xFF; PORTC = 0x00;
	  DDRD = 0xFF; PORTD = 0x00;
	  DDRA = 0x00; PORTA = 0xFF;
	  
	  unsigned char i=0;
	  tasks[i].state = init_2;
	  tasks[i].period = 1;
	  tasks[i].elapsedTime = tasks[i].period;
	  tasks[i].TickFct = &Tick_Fct2;
	  ++i;
	  tasks[i].state = init_1;
	  tasks[i].period = 100;
	  tasks[i].elapsedTime = tasks[i].period;
	  tasks[i].TickFct = &Tick_Fct1;

	  TimerSet(tasksPeriodGCD);
	  TimerOn();
	  
	  while(1) {
	  }
	  return 0;
}