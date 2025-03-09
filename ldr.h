/*
 * ldr.h
 *
 *  Created on: Oct 6, 2024
 *      Author: samaa
 */

#ifndef LDR_H_
#define LDR_H_

#include "std_types.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define LDR_SENSOR_CHANNEL_ID			0
#define LDR_SENSOR_MAX_VOLT_VALUE		2.56
#define LDR_SENSOR_MAX_LIGHT_INTENSITY	100

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Definition: Reads the LDR sensor value and returns the light intensity
 */
uint16 LDR_getLightIntensity(void);


#endif /* LDR_H_ */
