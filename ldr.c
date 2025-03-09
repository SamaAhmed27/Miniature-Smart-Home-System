/*
 * ldr.c
 *
 *  Created on: Oct 6, 2024
 *      Author: samaa
 */

#include "ldr.h"
#include "adc.h"
#include "common_macros.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*
 * Definition: Reads the LDR sensor value and returns the light intensity
 */
uint16 LDR_getLightIntensity(void){

	uint16 ldr_value = 0;
	uint16 light_intensity = 0;
//	float voltage = 0;

	/* Read the value through ADC0 using ADC_readChannel and store it */
	ldr_value = ADC_readChannel(LDR_SENSOR_CHANNEL_ID);

	/* Adjust the intensity */
	light_intensity = (uint16)(((uint32)ldr_value*LDR_SENSOR_MAX_LIGHT_INTENSITY*ADC_REF_VOLT_VALUE)/(ADC_MAXIMUM_VALUE*LDR_SENSOR_MAX_VOLT_VALUE));

	return light_intensity;
}


