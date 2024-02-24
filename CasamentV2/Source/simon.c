/*
 * simon.c
 *
 *  Created on: Feb 20, 2024
 *      Author: sobra
 */

#include "simon.h"

uint8_t simon_led [250];
uint8_t simon_SW [250];
uint8_t comptador_simon = 0;

void test_led(void){
	while (1){
		for(uint8_t i = 1; i < 6; i++){
			Sel_color(i);
			HAL_Delay(600);
		}
	}
}

void Sel_color(uint8_t color){
	switch (color){
	case 0:
		LED_RGB(negre);
		break;
	case 1:
		LED_RGB(vermell);
		break;
	case 2:
		LED_RGB(blau);
		break;
	case 3:
		LED_RGB(verd);
		break;
	case 4:
		LED_RGB(blanc);
		break;
	case 5:
		LED_RGB(lila);
		break;
	default:
		LED_RGB(negre);
	}
}

uint8_t random_num(uint8_t max, uint8_t min){
	uint8_t num = 0;
	num = (rand() % (max-min+1));
	num = num + min;
	return (num);
}

void test_random_LED(void){
	while(1){
		Sel_color(random_num(5, 1));
		HAL_Delay(200);
	}
}
