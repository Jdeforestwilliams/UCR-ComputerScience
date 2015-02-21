/* Partner(s) Name & E-mail: Marcel Tawamba mtawa002@ucr.edu

 * Partner(s) Name & E-mail:Joshua DeForest-Williams jdefo002@ucr.edu

 * Lab Section: 022

 * Assignment: Lab # 3 Exercise # 1

 * Exercise Description:  Blink the LEDs at D0, D2 and D3 at a rate of 1000 ms one at the time.

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
enum LEDState {INIT,L0,L2,L4} led_state;

void LEDS_Init(){
	led_state = INIT;
}

void LEDS_Tick(){
	//Actions
	switch(led_state){
		case INIT:
			PORTD = 0;
			break;
		case L0:
			PORTD = 0x01;
			break;
		case L2:
			PORTD = 0x04;
			break;
		case L4:
			PORTD = 0x10;
			break;
		default:
			PORTD = 0;
			break;
	}
	//Transitions
	switch(led_state){
		case INIT:
			led_state = L0;
		break;
		case L0:
			led_state = L2;
			break;
		case L2:
			led_state = L4;
			break;
		case L4:
			led_state = L0;
			break;
		default:
			led_state = INIT;
			break;
	}
}

void LedSecTask()
{
	LEDS_Init();
   for(;;) 
   { 	
	LEDS_Tick();
	vTaskDelay(1000); 
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