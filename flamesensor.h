/*
 * flamesensor.h
 *
 *  Created on: Oct 7, 2024
 *      Author: samaa
 */

#ifndef FLAMESENSOR_H_
#define FLAMESENSOR_H_

#include "std_types.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define FLAME_SENSOR_PORT_ID		PORTD_ID
#define FLAME_SENSOR_PIN_ID			PIN2_ID
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Definition: This function initializes the flame sensor pin direction
 */
void FlameSensor_init(void);

/*
 * Definition: This function gets the value from the sensor and returns it
 * to be used later in displaying alarms
 * We will use the polling technique to get the flame sensor flag value
 */
uint8 FlameSensor_getValue(void);

#endif /* FLAMESENSOR_H_ */
