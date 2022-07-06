/*
 ================================================================================================
 Name        : fan_comtrol.c
 Author      : Sama Mostafa
 Description : design a temperature-controlled fan,the fan is automatically turned ON or OFF according to the
 temperature
 ================================================================================================
 */
#include "pwm.h"
#include "dc_motor.h"
#include "adc.h"
#include "lcd.h"
#include "lm35_sensor.h"
#include <util/delay.h>
int main(void) {
	uint8 temp, speed;
	ADC_ConfigType ADC_Config = { F_CPU_8, internal }; //use internal voltage and prescalar 8
	DcMotor_Init(); //initialize DC Motor
	LCD_init(); //initialize LCD
	ADC_init(&ADC_Config); // initialize ADC
	LCD_moveCursor(1, 0);
	LCD_displayString("Temp =     C");
	while (1) {
		temp = LM35_getTemperature();
		if (temp < 30) {
			LCD_moveCursor(0, 1);
			LCD_displayString(" Fan is oFF");
			LCD_moveCursor(0, 0);
			LCD_moveCursor(1, 7);
			LCD_intgerToString(temp);
			LCD_displayCharacter(' ');
			speed = 0;
			DcMotor_Rotate(stop, speed);
		} else if (temp >= 30 && temp < 60) {
			LCD_moveCursor(0, 1);
			LCD_displayString(" Fan is on");
			LCD_displayCharacter(' ');
			LCD_moveCursor(1, 7);
			LCD_intgerToString(temp);
			LCD_displayCharacter(' ');
			speed = 25;
			DcMotor_Rotate(clockwise, speed);
		} else if (temp >= 60 && temp < 90) {
			LCD_moveCursor(0, 1);
			LCD_displayString(" Fan is on");
			LCD_displayCharacter(' ');
			LCD_moveCursor(1, 7);
			LCD_intgerToString(temp);
			LCD_displayCharacter(' ');
			speed = 50;
			DcMotor_Rotate(clockwise, speed);
		} else if (temp >= 90 && temp < 120) {
			LCD_moveCursor(0, 1);
			LCD_displayString(" Fan is on");
			LCD_displayCharacter(' ');
			LCD_moveCursor(1, 7);
			LCD_intgerToString(temp);
			LCD_displayCharacter(' ');
			speed = 75;
			DcMotor_Rotate(clockwise, speed);
		} else if (temp >= 120) {
			LCD_moveCursor(0, 1);
			LCD_displayString(" Fan is on");
			LCD_displayCharacter(' ');
			LCD_moveCursor(1, 7);
			LCD_intgerToString(temp);
			LCD_displayCharacter(' ');
			speed = 100;
			DcMotor_Rotate(clockwise, speed);
		}
	}
}

