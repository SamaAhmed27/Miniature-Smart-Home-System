/*
 * dcmotor.c
 *
 *  Created on: Oct 6, 2024
 *      Author: samaa
 */

#include "dcmotor.h"
#include "common_macros.h"
#include "gpio.h"
#include "pwm.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*
 * Definition: This function initializes the dc motor by setting the pins direction
 * It will also initialize the dc motor to be off
 */
void DcMotor_init(void){
	/* Set motor pins as output */
	GPIO_setupPinDirection(DC_MOTOR_IN1_PORT,DC_MOTOR_IN1_PIN,PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_IN2_PORT,DC_MOTOR_IN2_PIN,PIN_OUTPUT);

	/* Initialize the motor to be off
	 * This is through IN1 and IN2 = 0
	 * */
	GPIO_writePin(DC_MOTOR_IN1_PORT,DC_MOTOR_IN1_PIN,LOGIC_LOW);
	GPIO_writePin(DC_MOTOR_IN2_PORT,DC_MOTOR_IN2_PIN,LOGIC_LOW);
}

/*
 * Definition: Controls the motor's state (Clockwise/Anti-Clockwise/Stop)
 * and adjusts the speed based on the input duty cycle.
 *
 */
void DcMotor_Rotate(DcMotor_State state, uint8 speed){

    /* Start PWM with the given duty cycle to control the speed */
    PWM_Timer0_Start(speed);

	/* Switch according to motor state */
	switch(state){
	case ACW:
		/* In case of clockwise, IN1=1 and IN2=0 */
		GPIO_writePin(DC_MOTOR_IN1_PORT,DC_MOTOR_IN1_PIN,LOGIC_HIGH);
		GPIO_writePin(DC_MOTOR_IN2_PORT,DC_MOTOR_IN2_PIN,LOGIC_LOW);
		break;
	case CW:
		/* In case of anti-clockwise, IN1=0 and IN2=1 */
		GPIO_writePin(DC_MOTOR_IN1_PORT,DC_MOTOR_IN1_PIN,LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_IN2_PORT,DC_MOTOR_IN2_PIN,LOGIC_HIGH);
		break;
	case STOP:
		/* In case of stopping, IN1=0 and IN2=0 */
		GPIO_writePin(DC_MOTOR_IN1_PORT,DC_MOTOR_IN1_PIN,LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_IN2_PORT,DC_MOTOR_IN2_PIN,LOGIC_LOW);
		break;
	}
}
