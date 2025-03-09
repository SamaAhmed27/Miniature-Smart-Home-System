/*
 * flamesensor.c
 *
 *  Created on: Oct 7, 2024
 *      Author: samaa
 */
#include "flamesensor.h"
#include "common_macros.h"
#include "gpio.h"
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Definition: This function initializes the flame sensor pin direction
 */
void FlameSensor_init(void){
	/* Setup pin direction */
	GPIO_setupPinDirection(FLAME_SENSOR_PORT_ID,FLAME_SENSOR_PIN_ID,PIN_INPUT);
}


/*
 * Definition: This function gets the value from the sensor and returns it
 * to be used later in displaying alarms
 * We will use the polling technique to get the flame sensor flag value
 */
uint8 FlameSensor_getValue(void){

	/* FlameSensor_active variable to indicate status */
	uint8 FlameSensor_active = 0;

	if(GPIO_readPin(FLAME_SENSOR_PORT_ID,FLAME_SENSOR_PIN_ID)){
		FlameSensor_active = LOGIC_HIGH;
	}
	else{
		FlameSensor_active = LOGIC_LOW;
	}

	return FlameSensor_active;
}

