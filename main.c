/*
 * main.c
 *
 *  Created on: Oct 6, 2024
 *      Author: samaa
 */
#include <util/delay.h> /* To use delays */

/* Include all drivers */
#include "adc.h"
#include "lcd.h"
#include "pwm.h"
#include "lm35_sensor.h"
#include "dcmotor.h"
#include "ldr.h"
#include "led.h"
#include "flamesensor.h"
#include "buzzer.h"

int main(void) {
    /* initialize all required drivers */
    LCD_init();
    DcMotor_init();
    LEDS_init();
    FlameSensor_init();
    Buzzer_init();
    ADC_init();

    /* variables init */
    uint8 speed = 0, temperature = 0;
    uint16 light_intensity = 0;
    uint8 alertFlag = 0; /* Flag of the alert state */

    /*------------------------ System: LCD display -----------------------------*/
    /* Clear screen */
    LCD_clearDisplay();
    /* Move cursor to desired place and display TEMP */
    LCD_displayStringRowColumn(2, 0, "TEMP=  ");
    /* Move cursor to desired place and display LDR */
    LCD_displayStringRowColumn(2, 8, "LDR=   %");

    while (1) {
        /*------------------------ System: Flame Sensor -----------------------------*/
        if(FlameSensor_getValue()) {
            if(!alertFlag) { /* If not already in alert mode */
                Buzzer_on();
                LCD_clearDisplay(); /* Clear the screen when alert starts */
                LCD_displayStringRowColumn(1, 0, "Critical alert!");
                alertFlag = 1; /* Set the alert flag */
            }
        }
        else{
            if(alertFlag) { /* If the alert mode is ending */
                Buzzer_off();
                alertFlag = 0; /* Reset the alert flag */
                LCD_clearDisplay(); /* Clear the display for normal operation */
                /* Re-display the temp and LDR values */
                LCD_displayStringRowColumn(2, 0, "TEMP=  C");
                LCD_displayStringRowColumn(2, 9, "LDR=   %");
            }
        }

        /* Only update temperature and LDR when not in alert mode */
        /*------------------------ System: Fan control -----------------------------*/
        if(!alertFlag){
            /* Store temperature of LM35 in a variable */
            temperature = LM35_getTemperature();

            /* Adjust the motor speed based on temperature */
            if (temperature < 25) {
                speed = 0;  /* Stop the motor if temperature is below 25C */
            }
            else if (temperature >= 25 && temperature < 30) {
                speed = 25;
            }
            else if (temperature >= 30 && temperature < 35) {
                speed = 50;
            }
            else if (temperature >= 35 && temperature < 40) {
                speed = 75;
            }
            else {
                speed = 100;  /* Max speed if temperature exceeds 40C */
            }

            /* Send the speed variable and the motor direction to rotate the motor */
            DcMotor_Rotate(CW, speed);

            /* Display fan status */
            if (speed == 0) {
                LCD_displayStringRowColumn(1, 3, "Fan is OFF");
            }
            else {
                LCD_displayStringRowColumn(1, 3, "Fan is ON ");
                LCD_displayCharacter(' '); /* Clear residual characters */
            }

        /*--------------- System: Light detection and intensity ---------------------*/
            light_intensity = LDR_getLightIntensity();

            if (light_intensity <= 15) {
                LED_on(RED);
                LED_on(GREEN);
                LED_on(BLUE);
            }
            else if (light_intensity > 15 && light_intensity <= 50) {
                LED_on(RED);
                LED_on(GREEN);
                LED_off(BLUE);
            }
            else if (light_intensity > 50 && light_intensity <= 70) {
                LED_on(RED);
                LED_off(GREEN);
                LED_off(BLUE);
            }
            else {
                LED_off(RED);
                LED_off(GREEN);
                LED_off(BLUE);
            }

            /* Update LCD with temperature and light intensity */
            LCD_moveCursor(2, 5);
            if (temperature >= 10) {
                LCD_integerToString(temperature);
            }
            else {
                LCD_integerToString(temperature);
                LCD_displayCharacter(' '); /* Clear the next digit place */
            }

            /* Display the light intensity value */
            LCD_moveCursor(2, 12);
            if (light_intensity >= 100) {
                LCD_integerToString(light_intensity);
            }
            else {
                LCD_integerToString(light_intensity);
                LCD_displayCharacter(' '); /* Clear the next digit place */
            }
        }

        _delay_ms(100); /* Add a small delay to smooth transitions and reduce flicker */
    }

    return 0;
}
