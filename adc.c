/*
 * adc.c
 *
 *  Created on: Oct 2, 2024
 *      Author: samaa
 */

#include "adc.h"
#include "common_macros.h"
#include <avr/io.h> /* to access the registers of the ADC */

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void ADC_init(void){
	/* Choose Vref Mode
	 * REFS1:0 -> REFS1 = 1 and REFS0 = 1 for AVCC = 2.56v
	 * */
	SET_BIT(ADMUX,REFS0);
	SET_BIT(ADMUX,REFS1);

	/* Right adjust */
	CLEAR_BIT(ADMUX,ADLAR);

	/* Assume channel 0 for initialization*/
	CLEAR_BIT(ADMUX,MUX0);
	CLEAR_BIT(ADMUX,MUX1);
	CLEAR_BIT(ADMUX,MUX2);
	CLEAR_BIT(ADMUX,MUX3);
	CLEAR_BIT(ADMUX,MUX4);

	/* Enable ADC (ADEN = 1 ) and disable interrupt (ADIE = 0) */
	SET_BIT(ADCSRA,ADEN);
	CLEAR_BIT(ADCSRA,ADIE);

	/*Set pre-scaler
	 * Here we set ADPS2:0 to adjust a pre-scaler of 128
	 * ADC_Clock = F_CPU/128 = 16Mhz/128 = 125Khz --> ADC must operate in range 50-200Khz
	 * */
	SET_BIT(ADCSRA,ADPS0);
	SET_BIT(ADCSRA,ADPS1);
	SET_BIT(ADCSRA,ADPS2);

}

/* To read the ADC channels */
uint16 ADC_readChannel(uint8 ch_num)
{
	/* Insert channel number into ADMUX Reg */
	ADMUX =  (ADMUX & 0xE0) | (ch_num & 0x07);

	/* Start conversion */
	SET_BIT(ADCSRA,ADSC);

	/* Polling till flag is on*/
	while (BIT_IS_CLEAR(ADCSRA, ADIF)); // Correct polling logic

	/* Clear ADC Flag (by setting it) */
	SET_BIT(ADCSRA,ADIF);

	return ADC;
}
