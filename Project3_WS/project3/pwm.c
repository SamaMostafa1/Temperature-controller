/******************************************************************************
 *
 * Module:PWM
 *
 * File Name: pwm.c
 *
 * Description: Source file for the PWM driver
 *
 * Author: Sama Mostafa
 *
 *******************************************************************************/
#include <avr/io.h>
#include "pwm.h"
#include "std_types.h"
#include "gpio.h"
/*
 * Description :
 *The function responsible for trigger the Timer0 with the PWM Mode.
 * Setup the PWM mode with Non-Inverting.
 * Setup the prescaler with F_CPU/8.
 * Setup the compare value based on the required input duty cycle
 * Setup the direction for OC0 as output pin through the GPIO driver.
 * The generated PWM signal frequency will be 500Hz to control the DC
 Motor speed.
 */
void PWM_Timer0_Start(uint8 set_duty_cycle) {
	TCNT0 = 0; //Set Timer Initial value
	//if condition used to change duty cycle precentage into duty cycle number
	if (set_duty_cycle == FuLL_Speed) {
		set_duty_cycle = ((set_duty_cycle + (39 * (set_duty_cycle / 25))) - 1);
	} else {
		set_duty_cycle = set_duty_cycle + (39 * (set_duty_cycle / 25));
	}
	OCR0 = set_duty_cycle; // Set Compare Value
	GPIO_setupPinDirection(PWM_PORT_ID, PWM_PIN_ID, PIN_OUTPUT); /*set PB3/OC0 as output pin --> pin
	 where the PWM signal is generated from MC.*/
	/* Configure timer control register
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
	 * 4. clock = F_CPU/8 CS00=0 CS01=1 CS02=0
	 */
	TCCR0 = (1 << WGM00) | (1 << WGM01) | (1 << COM01) | (1 << CS01);
}

