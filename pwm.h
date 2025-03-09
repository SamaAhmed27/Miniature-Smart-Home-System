/*
 * pwm.h
 *
 *  Created on: Oct 6, 2024
 *      Author: samaa
 */

#ifndef PWM_H_
#define PWM_H_

#include "std_types.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Definition: This function shall initialize Timer0
 * Prescaler of: F_CPU/1024
 * Non-inverting mode
 * Set OC0 as the output pin
 * duty_cycle is a variable of 0 to 100%
 */
void PWM_Timer0_Start(uint8 duty_cycle);


#endif /* PWM_H_ */
