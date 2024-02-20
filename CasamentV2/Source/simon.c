/*
 * simon.c
 *
 *  Created on: Feb 20, 2024
 *      Author: sobra
 */

#include "simon.h"

uint8_t simon_array [250];
uint8_t comptador_simon = 0;

void test_led(void){
	LED_RGB(groc);
	HAL_Delay(400);
	LED_RGB(rosa);
	HAL_Delay(400);
	LED_RGB(blanc);
	HAL_Delay(400);
	LED_RGB(vermell);
	HAL_Delay(400);
	LED_RGB(verd);
	HAL_Delay(400);
	LED_RGB(blau);
	HAL_Delay(400);
	LED_RGB(llanter);
	HAL_Delay(400);
}
