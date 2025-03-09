/*
 * pwm.c
 *
 *  Created on: Oct 6, 2024
 *      Author: samaa
 */
#include "pwm.h"
#include "common_macros.h"
#include <avr/io.h> /* to access the registers of the Timer0 */

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*
 * Definition: This function shall initialize Timer0
 * Prescaler of: F_CPU/1024
 * Non-inverting mode
 * Set OC0 as the output pin
 * duty_cycle is a variable of 0 to 100%
 */
void PWM_Timer0_Start(uint8 duty_cycle){
	/* To initialize timer0 */
	TCNT0 = 0; /* Set Timer Initial Value to 0 */

	uint8 corrected_duty_cycle = (uint8)(((uint32)(duty_cycle * 255)) / 100); // Scale speed to 0-255 for PWM

	OCR0  = corrected_duty_cycle; /* Set Compare Value */


	SET_BIT(DDRB,PB3); /* Configure PB3/OC0 as output pin */

	/* Timer control register
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
	 * 4. clock = F_CPU/1024 CS00=1 CS01=0 CS02=1
	 */
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS02) | (1<<CS00);
}

