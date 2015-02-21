/* Partner(s) Name & E-mail: Marcel Tawamba mtawa002@ucr.edu

 * Partner(s) Name & E-mail:Joshua DeForest-Williams jdefo002@ucr.edu

 * Lab Section: 022

 * Assignment: Lab # 3 Exercise # 4

 * Exercise Description: cycle the LEDs forward then backward, and change direction on input change.

 *

 * I acknowledge all content contained herein, excluding template or example

 * code, is my own original work.

 */
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <avr/portpins.h>
#include <avr/pgmspace.h>

//FreeRTOS include files
#include "FreeRTOS.h"
#include "task.h"
#include "croutine.h"
enum LEDState {INIT, forward, backward} led_state;

void LEDS_Init(){
	led_state = INIT;
}
unsigned char input = 0x01;
void LEDS_Tick(){
	unsigned char A = (~PINA) & 0x01;
	switch(led_state){//Transitions
		case INIT:
			PORTD = 0x00;
			led_state = forward;
		break;
		case forward:
			if(input != 0x80 && !A){
				led_state = forward;
			}else if(input == 0x80 || A){
				led_state = backward;
			}
			break;
		case backward:
			if(input != 0x01 && !A){
				led_state = backward;
			}else if(input == 0x01 || A){
				led_state = forward;
			}
			break;
		default:
			led_state = INIT;
			break;
	}
	switch(led_state){//Actions
		case forward:
			PORTD = input;
			input = input << 1;
			break;
		case backward:
			PORTD = input;
			input = input >> 1;
			break;
		default:
			break;
	}
}

void LedSecTask()
{
	LEDS_Init();
	for(;;)
	{
		LEDS_Tick();
		vTaskDelay(500);
	}
}

void StartSecPulse(unsigned portBASE_TYPE Priority)
{
	xTaskCreate(LedSecTask, (signed portCHAR *)"LedSecTask", configMINIMAL_STACK_SIZE, NULL, Priority, NULL );
}

int main(void)
{
	DDRA = 0x00; PORTA=0xFF;
	DDRD = 0xFF;
	//Start Tasks
	StartSecPulse(1);
	//RunSchedular
	vTaskStartScheduler();
	
	return 0;
}