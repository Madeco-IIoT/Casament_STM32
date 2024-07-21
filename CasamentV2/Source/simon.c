/*
 * simon.c
 *
 *  Created on: Feb 20, 2024
 *      Author: sobra
 */
#define delay_Led 400
#include "simon.h"

uint8_t simon_led [250];
uint8_t simon_SW [250];
uint8_t comptador_simon = 0;

void init_simon(void){
	 comptador_simon = 0;
	 ssd1306_Fill(Black);
	 ssd1306_SetCursor(40,20);
	 ssd1306_WriteString("vermell", Font_7x10, White);
	 ssd1306_SetCursor(40,50);
	 ssd1306_WriteString("verd", Font_7x10, White);
	 ssd1306_SetCursor(0,35);
	 ssd1306_WriteString("blau   lila  blanc", Font_7x10, White);
}

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

uint8_t test_random_LED(void){
	uint8_t num = random_num(5, 1);
	Sel_color(num);
	HAL_Delay(delay_Led);
	return num;
}

void Led_Sequence(void){
	simon_screen(comptador_simon);
	if (comptador_simon == 0){
		simon_led[comptador_simon] = test_random_LED();
		comptador_simon++;
	}
	else{
		for(uint8_t x=0; x<comptador_simon; x++){
			Sel_color(simon_led[x]);
			HAL_Delay(delay_Led);
			Sel_color(0);
			HAL_Delay(delay_Led);
		}
		simon_led[comptador_simon] = test_random_LED();
		comptador_simon++;
	}
	Sel_color(0);

}
uint8_t SW_Sequence (void){
	uint8_t i = 0;
	uint8_t seq_con_err = 0;
	while(i < comptador_simon){
		uint8_t temp = SW_Control(0);
		simon_SW[i]=temp;
		if(simon_led[i] != temp){ //puslador equibocat
			seq_con_err = 100;
			break;
		}
		i++;
	}
	return seq_con_err;
}

uint8_t SW_Control (uint8_t TimeOut_ms){
	//falta implamentar el timeout
	uint8_t pulsador = 0;
	while (pulsador == 0){
		if (HAL_GPIO_ReadPin(SW1_GPIO_Port, SW1_Pin)) { //vermell
			pulsador = 1;
			while (HAL_GPIO_ReadPin(SW1_GPIO_Port, SW1_Pin)) {
				HAL_Delay(1);
				Sel_color(pulsador);
			}
		} else if (HAL_GPIO_ReadPin(SW2_GPIO_Port, SW2_Pin)) { // blau
			pulsador = 2;
			while (HAL_GPIO_ReadPin(SW2_GPIO_Port, SW2_Pin)) {
				HAL_Delay(1);
				Sel_color(pulsador);
			}
		}
		else if(HAL_GPIO_ReadPin(SW3_GPIO_Port, SW3_Pin)){ // verd
			pulsador = 3;
			while (HAL_GPIO_ReadPin(SW3_GPIO_Port, SW3_Pin)){
				HAL_Delay(1);
				Sel_color(pulsador);
			}
		}
		else if(HAL_GPIO_ReadPin(SW4_GPIO_Port, SW4_Pin)){ // blanc
			pulsador = 4;
			while (HAL_GPIO_ReadPin(SW4_GPIO_Port, SW4_Pin)){
				HAL_Delay(1);
				Sel_color(pulsador);
			}
		}
		else if (HAL_GPIO_ReadPin(SW5_GPIO_Port, SW5_Pin)){ // lila
			pulsador = 5;
			while (HAL_GPIO_ReadPin(SW5_GPIO_Port, SW5_Pin)){
				HAL_Delay(1);
				Sel_color(pulsador);
			}
		}
	}
	Sel_color(0);
	return pulsador;
}

void simon_screen(uint8_t score) {
	//a la inicialització he fet la neteja de la plantalla
	char simon_str[20];
	memset(simon_str, '\0', 20);
	ssd1306_SetCursor(0,0);
	sprintf(simon_str, "score: %d", score);
	ssd1306_WriteString(simon_str, Font_11x18, White);
	ssd1306_UpdateScreen();
}
