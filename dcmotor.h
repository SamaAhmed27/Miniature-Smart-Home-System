/*
 * dcmotor.h
 *
 *  Created on: Oct 6, 2024
 *      Author: samaa
 */

#ifndef DCMOTOR_H_
#define DCMOTOR_H_

#include "std_types.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define DC_MOTOR_IN1_PORT			PORTB_ID
#define DC_MOTOR_IN1_PIN			PIN0_ID

#define DC_MOTOR_IN2_PORT			PORTB_ID
#define DC_MOTOR_IN2_PIN			PIN1_ID

#define DC_MOTOR_EN_PORT			PORTB_ID
#define DC_MOTOR_EN_PIN				PIN3_ID

/*******************************************************************************
 *                           Types Declaration                                 *
 *******************************************************************************/
typedef enum{
	CW,ACW,STOP
}DcMotor_State;
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Definition: This function initializes the dc motor by setting the pins direction
 * It will also initialize the dc motor to be off
 */
void DcMotor_init(void);

/*
 * Definition: Controls the motor's state (Clockwise/Anti-Clockwise/Stop)
 * and adjusts the speed based on the input duty cycle.
 *
 */
void DcMotor_Rotate(DcMotor_State state, uint8 speed);

#endif /* DCMOTOR_H_ */
