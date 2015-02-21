/* Partner(s) Name & E-mail: Marcel Tawamba mtawa002@ucr.edu

 * Partner(s) Name & E-mail:Joshua DeForest-Williams jdefo002@ucr.edu

 * Lab Section: 022

 * Assignment: Lab # 3 Exercise # 2

 * Exercise Description: 1) Blink the LED at D0 at a rate of 500 ms.

	2) Blink the LED at D2 at a rate of 1000 ms.

	3) Blink the LED at D4 at a rate of 2500 ms.

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

enum SM1_states {SM1_start, SM1_On, SM1_Off} SM1_state;
void TickFct_SM1(){
	switch(SM1_state){//actions
		case SM1_On:
		PORTD |= 0x01;
		break;
		case SM1_Off:
		PORTD &= 0xFE;
		break;
		default:
		break;
	}
	switch(SM1_state){//transitions
		case SM1_start:
			PORTD &= 0xFE;
			SM1_state = SM1_On;
			break;
		
		case SM1_On:
			SM1_state = SM1_Off;
			break;
		
		case SM1_Off:
			SM1_state = SM1_On;
			break;
		
		default:
			SM1_state = SM1_start;
			break;
	}
}
enum SM2_states {SM2_start, SM2_On, SM2_Off} SM2_state;
void TickFct_SM2(){
	switch(SM2_state){
		case SM2_On:
		PORTD |= 0x04;
		break;
		case SM2_Off:
		PORTD &= 0xFB;
		break;
		default:
		break;
	}
	switch(SM2_state){
		case SM2_start:
			PORTD &= 0xFB;
			SM2_state = SM2_On;
			break;
		
		case SM2_On:
			SM2_state = SM2_Off;
			break;
		
		case SM2_Off:
			SM2_state = SM2_On;
			break;
		
		default:
			SM2_state = SM2_start;
			break;
	}
}

enum SM3_states {SM3_start, SM3_On, SM3_Off} SM3_state;
void TickFct_SM3(){
	switch(SM3_state){
		case SM3_On:
		PORTD |= 0x10;
		break;
		case SM3_Off:
		PORTD &= 0xEF;
		break;
		default:
		break;
	}
	switch(SM3_state){
		case SM3_start:
			PORTD &= 0xEF;
			SM3_state = SM3_On;
			break;
		
		case SM3_On:
			SM3_state = SM3_Off;
			break;
		
		case SM3_Off:
			SM3_state = SM3_On;
			break;
		
		default:
			SM3_state = SM3_start;
			break;
	}
}
void LED0_Init(){
	SM1_state = SM1_start;	
}

void LED2_Init(){
	SM2_state = SM2_start;
}

void LED4_Init(){
	SM3_state = SM3_start;
}

void Led0_Task()
{
	LED0_Init();
   for(;;) 
   { 	
		TickFct_SM1();
		vTaskDelay(500);
   } 
}

void Led2_Task()
{
	LED2_Init();
	for(;;)
	{
		TickFct_SM2();
		vTaskDelay(1000);
	}
}

void Led4_Task()
{
	LED4_Init();
	for(;;)
	{
		TickFct_SM3();
		vTaskDelay(2500);
	}
}

void StartSecPulse(unsigned portBASE_TYPE Priority)
{
	xTaskCreate(Led0_Task, (signed portCHAR *)"Led0_Task", configMINIMAL_STACK_SIZE, NULL, Priority, NULL );
	xTaskCreate(Led2_Task, (signed portCHAR *)"Led2_Task", configMINIMAL_STACK_SIZE, NULL, Priority, NULL );
	xTaskCreate(Led4_Task, (signed portCHAR *)"Led4_Task", configMINIMAL_STACK_SIZE, NULL, Priority, NULL );
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