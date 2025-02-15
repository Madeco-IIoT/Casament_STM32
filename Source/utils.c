/*
 * utils.c
 *
 *  Created on: Dec 23, 2023
 *      Author: sobra
 */
#include "utils.h"
//#include "main.h"
#include "stdint.h"

extern TIM_HandleTypeDef htim5;
extern TIM_HandleTypeDef htim11;

extern bool snake_en;
extern bool simon_en;
extern bool boad_en;
extern bool ajustar_hora;

uint8_t menu_sel = 0;

void init_RGB (void){
	HAL_TIM_PWM_Start(&htim11, TIM_CHANNEL_1); //RED
	HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_3); //GREEN
	HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_4); //BLUE
}

void LED_RGB(uint32_t Color){
	uint8_t Blue = 0x00;
	uint8_t Green = 0x00;
	uint8_t Red = 0x00;
	Blue = Color & 0x0000FF;
	Color = Color >> 8;
	Green = Color & 0x0000FF;
	Color = Color >> 8;
	Red = Color & 0x0000FF;
	TIM11->CCR1 = Red; // RED
	TIM5->CCR3 = Green; //GREEN
    TIM5->CCR4 = Blue; // BLUE

}

void menu (void){
	bool sortir = false;
	switch (menu_sel){
	case 0:
		ssd1306_SetCursor(4,12);
		ssd1306_WriteString("  Snake ", Font_7x10, Black);
		ssd1306_SetCursor(4,24);
		ssd1306_WriteString("  Sink the float ", Font_7x10, White);
		ssd1306_SetCursor(4,36);
		ssd1306_WriteString("  Simon ", Font_7x10, White);
		ssd1306_SetCursor(4,48);
		ssd1306_WriteString("v Llanterna ", Font_7x10, White);
		ssd1306_UpdateScreen();
		if(HAL_GPIO_ReadPin(SW3_GPIO_Port, SW3_Pin)){ // down
			while (HAL_GPIO_ReadPin(SW3_GPIO_Port, SW3_Pin)) HAL_Delay(1);
			menu_sel ++;
		}
		if(HAL_GPIO_ReadPin(SW5_GPIO_Port, SW5_Pin)){ // accept
			while (HAL_GPIO_ReadPin(SW5_GPIO_Port, SW5_Pin)) HAL_Delay(1);
			snake_en = true;
			boad_en = false;
			simon_en = false;
			ajustar_hora = false;
		}
		break;
	case 1:
		ssd1306_SetCursor(4,12);
		ssd1306_WriteString("  Snake ", Font_7x10, White);
		ssd1306_SetCursor(4,24);
		ssd1306_WriteString("  Sink the float ", Font_7x10, Black);
		ssd1306_SetCursor(4,36);
		ssd1306_WriteString("  Simon ", Font_7x10, White);
		ssd1306_SetCursor(4,48);
		ssd1306_WriteString("v Llanterna ", Font_7x10, White);
		ssd1306_UpdateScreen();
		if(HAL_GPIO_ReadPin(SW1_GPIO_Port, SW1_Pin)){ // Up
			while (HAL_GPIO_ReadPin(SW1_GPIO_Port, SW1_Pin)) HAL_Delay(1);
			menu_sel --;
		}
		if(HAL_GPIO_ReadPin(SW3_GPIO_Port, SW3_Pin)){ // down
			while (HAL_GPIO_ReadPin(SW3_GPIO_Port, SW3_Pin)) HAL_Delay(1);
			menu_sel ++;
		}

		if(HAL_GPIO_ReadPin(SW5_GPIO_Port, SW5_Pin)){ // accept
			while (HAL_GPIO_ReadPin(SW5_GPIO_Port, SW5_Pin)) HAL_Delay(1);
			boad_en = true;
			snake_en = false;
			simon_en = false;
			ajustar_hora = false;
		}
		break;
	case 2:
		ssd1306_SetCursor(4,12);
		ssd1306_WriteString("  Snake ", Font_7x10, White);
		ssd1306_SetCursor(4,24);
		ssd1306_WriteString("  Sink the float ", Font_7x10, White);
		ssd1306_SetCursor(4,36);
		ssd1306_WriteString("  Simon ", Font_7x10, Black);
		ssd1306_SetCursor(4,48);
		ssd1306_WriteString("v Llanterna", Font_7x10, White);
		ssd1306_UpdateScreen();
		if(HAL_GPIO_ReadPin(SW1_GPIO_Port, SW1_Pin)){ // Up
			while (HAL_GPIO_ReadPin(SW1_GPIO_Port, SW1_Pin)) HAL_Delay(1);
			menu_sel --;
		}
		if(HAL_GPIO_ReadPin(SW3_GPIO_Port, SW3_Pin)){ // down
			while (HAL_GPIO_ReadPin(SW3_GPIO_Port, SW3_Pin)) HAL_Delay(1);
			menu_sel ++;
		}

		if(HAL_GPIO_ReadPin(SW5_GPIO_Port, SW5_Pin)){ // accept
			while (HAL_GPIO_ReadPin(SW5_GPIO_Port, SW5_Pin)) HAL_Delay(1);
			boad_en = false;
			snake_en = false;
			simon_en = true;
			ajustar_hora = false;
			init_simon();
		}
		break;
	case 3:
		ssd1306_SetCursor(4,12);
		ssd1306_WriteString("  Snake          ", Font_7x10, White);
		ssd1306_SetCursor(4,24);
		ssd1306_WriteString("  Sink the float ", Font_7x10, White);
		ssd1306_SetCursor(4,36);
		ssd1306_WriteString("  Simon          ", Font_7x10, White);
		ssd1306_SetCursor(4,48);
		ssd1306_WriteString("v Llanterna      ", Font_7x10, Black);
		ssd1306_UpdateScreen();
		if(HAL_GPIO_ReadPin(SW1_GPIO_Port, SW1_Pin)){ // up
			while (HAL_GPIO_ReadPin(SW1_GPIO_Port, SW1_Pin)) HAL_Delay(1);
			menu_sel --;
		}
		if(HAL_GPIO_ReadPin(SW3_GPIO_Port, SW3_Pin)){ // down
			while (HAL_GPIO_ReadPin(SW3_GPIO_Port, SW3_Pin)) HAL_Delay(1);
			menu_sel ++;
		}
		if(HAL_GPIO_ReadPin(SW5_GPIO_Port, SW5_Pin)){ // accept
			while (HAL_GPIO_ReadPin(SW5_GPIO_Port, SW5_Pin)) HAL_Delay(1);
			simon_en = false;
			boad_en = false;
			snake_en = false;
			ajustar_hora = false;
			menu_sel = 200;
		}

		break;
	case 4:
		ssd1306_SetCursor(4,12);
		ssd1306_WriteString("^ QR GitHub        ", Font_7x10, Black);
		ssd1306_SetCursor(4,24);
		ssd1306_WriteString("  Fotos Casament   ", Font_7x10, White);
		ssd1306_SetCursor(4,36);
		ssd1306_WriteString("  Ajustar hora     ", Font_7x10, White);
		ssd1306_SetCursor(4,48);
		ssd1306_WriteString("  About            ", Font_7x10, White);
		ssd1306_UpdateScreen();
		if(HAL_GPIO_ReadPin(SW1_GPIO_Port, SW1_Pin)){ // up
			while (HAL_GPIO_ReadPin(SW1_GPIO_Port, SW1_Pin)) HAL_Delay(1);
			menu_sel --;
		}
		if(HAL_GPIO_ReadPin(SW3_GPIO_Port, SW3_Pin)){ // down
			while (HAL_GPIO_ReadPin(SW3_GPIO_Port, SW3_Pin)) HAL_Delay(1);
			menu_sel ++;
		}
		if(HAL_GPIO_ReadPin(SW5_GPIO_Port, SW5_Pin)){ // accept
			while (HAL_GPIO_ReadPin(SW5_GPIO_Port, SW5_Pin)) HAL_Delay(1);
			simon_en = false;
			boad_en = false;
			snake_en = false;
			menu_sel = 201;
			ajustar_hora = false;
		}

		break;
	case 5:
		ssd1306_SetCursor(4,12);
		ssd1306_WriteString("^ QR GitHub        ", Font_7x10, White);
		ssd1306_SetCursor(4,24);
		ssd1306_WriteString("  Fotos Casament   ", Font_7x10, Black);
		ssd1306_SetCursor(4,36);
		ssd1306_WriteString("  Ajustar hora     ", Font_7x10, White);
		ssd1306_SetCursor(4,48);
		ssd1306_WriteString("  About", Font_7x10, White);
		ssd1306_UpdateScreen();
		if(HAL_GPIO_ReadPin(SW1_GPIO_Port, SW1_Pin)){ // up
			while (HAL_GPIO_ReadPin(SW1_GPIO_Port, SW1_Pin)) HAL_Delay(1);
			menu_sel --;
		}
		if(HAL_GPIO_ReadPin(SW3_GPIO_Port, SW3_Pin)){ // down
			while (HAL_GPIO_ReadPin(SW3_GPIO_Port, SW3_Pin)) HAL_Delay(1);
			menu_sel ++;
		}
		if(HAL_GPIO_ReadPin(SW5_GPIO_Port, SW5_Pin)){ // accept
			while (HAL_GPIO_ReadPin(SW5_GPIO_Port, SW5_Pin)) HAL_Delay(1);
			simon_en = false;
			boad_en = false;
			snake_en = false;
			menu_sel = 202;
			ajustar_hora = false;
		}

		break;

	case 6:
		ssd1306_SetCursor(4,12);
		ssd1306_WriteString("^ QR GitHub", Font_7x10, White);
		ssd1306_SetCursor(4,24);
		ssd1306_WriteString("  Fotos Casament ", Font_7x10, White);
		ssd1306_SetCursor(4,36);
		ssd1306_WriteString("  Ajustar hora   ", Font_7x10, Black);
		ssd1306_SetCursor(4,48);
		ssd1306_WriteString("  About          ", Font_7x10, White);
		ssd1306_UpdateScreen();
		if(HAL_GPIO_ReadPin(SW1_GPIO_Port, SW1_Pin)){ // up
			while (HAL_GPIO_ReadPin(SW1_GPIO_Port, SW1_Pin)) HAL_Delay(1);
			menu_sel --;
		}
		if(HAL_GPIO_ReadPin(SW3_GPIO_Port, SW3_Pin)){ // down
			while (HAL_GPIO_ReadPin(SW3_GPIO_Port, SW3_Pin)) HAL_Delay(1);
			menu_sel ++;
		}
		if(HAL_GPIO_ReadPin(SW5_GPIO_Port, SW5_Pin)){ // accept
			while (HAL_GPIO_ReadPin(SW5_GPIO_Port, SW5_Pin)) HAL_Delay(1);
			simon_en = false;
			boad_en = false;
			snake_en = false;
			ajustar_hora = true;
		}

		break;

	case 7:
		ssd1306_SetCursor(4,12);
		ssd1306_WriteString("^ QR GitHub", Font_7x10, White);
		ssd1306_SetCursor(4,24);
		ssd1306_WriteString("  Fotos Casament", Font_7x10, White);
		ssd1306_SetCursor(4,36);
		ssd1306_WriteString("  Ajustar Hora     ", Font_7x10, White);
		ssd1306_SetCursor(4,48);
		ssd1306_WriteString("  About            ", Font_7x10, Black);
		ssd1306_UpdateScreen();
		if(HAL_GPIO_ReadPin(SW1_GPIO_Port, SW1_Pin)){ // up
			while (HAL_GPIO_ReadPin(SW1_GPIO_Port, SW1_Pin)) HAL_Delay(1);
			menu_sel --;
		}

		if(HAL_GPIO_ReadPin(SW5_GPIO_Port, SW5_Pin)){ // accept
			while (HAL_GPIO_ReadPin(SW5_GPIO_Port, SW5_Pin)) HAL_Delay(1);
			simon_en = false;
			boad_en = false;
			snake_en = false;
			ajustar_hora = false;
			menu_sel = 203;
		}

		break;

	case 200:
		sortir = false;
		LED_RGB(llanter);
		ssd1306_Fill(White);
		ssd1306_UpdateScreen();
		while(!sortir){
			while(HAL_GPIO_ReadPin(SW5_GPIO_Port, SW5_Pin)){
				menu_sel = 0;
				ssd1306_Fill(Black);
				LED_RGB(negre);
				sortir = true;
			}
			HAL_Delay(1);
		}
		break;
	case 201:
			sortir = false;
			codiQR();
			while(!sortir){
				while(HAL_GPIO_ReadPin(SW5_GPIO_Port, SW5_Pin)){
					menu_sel = 0;
					ssd1306_Fill(Black);
					LED_RGB(negre);
					sortir = true;
				}
				HAL_Delay(1);
			}
			break;
	case 202:
		sortir = false;
		wedshoot();
		while(!sortir){
			while(HAL_GPIO_ReadPin(SW5_GPIO_Port, SW5_Pin)){
				menu_sel = 0;
				ssd1306_Fill(Black);
				LED_RGB(negre);
				sortir = true;
			}
			HAL_Delay(1);
		}
		break;
	case 203:
		about_PCB();
		menu_sel=0;

		break;

	default:
		HAL_Delay(1);
	}
}
void codiQR (void){
	uint32_t codiQR_var[29]={
		0x1FD0837F,
		0x10530B41,
		0x17598b5d,
		0x175d6d5d,
		0x174da65d,
		0x105c1941,
		0x1FD5557F,
		0x00060900,
		0x19c5922F,
		0x08A08034,
		0x1e5cf65d,
		0x05998a88,
		0x16d31e7e,
		0x18a5e204,
		0x1842f67e,
		0x08b26302,
		0x127d9AAe,
		0x1b2bf0b6,
		0x02fb527c,
		0x0004d382,
		0x1dd403f0,
		0x001b911c,
		0x1FC36F5D,
		0x10546116,
		0x175857F9,
		0x174CB22E,
		0x17445E97,
		0x105B41FC,
		0x1FDD9452
	};
	uint32_t mask = 0x10000000;
	uint8_t x = 35;
	uint8_t y = 3;
	ssd1306_Fill(Black);
	for(uint8_t i=0; i<29; i++){ //buscar tot l'array tamporalment
		for(uint8_t z=0; z<29; z++){
			if(codiQR_var[i] & mask){
				ssd1306_DrawPixel(x, y, White);
				ssd1306_DrawPixel(x+1, y, White);
				ssd1306_DrawPixel(x, y+1, White);
				ssd1306_DrawPixel(x+1, y+1, White);
			}
			x += 2;
			mask >>= 1;
		}
		mask = 0x10000000;
		x = 35;
		y += 2;
	}
	ssd1306_UpdateScreen();
}
bool is_pressed_button(SW_button_t button){
	bool temp = false;
	switch(button){
	case SW_1:
		temp =HAL_GPIO_ReadPin(SW1_GPIO_Port, SW1_Pin);
		break;
	case SW_2:
		temp = HAL_GPIO_ReadPin(SW2_GPIO_Port, SW2_Pin);
		break;
	case SW_3:
		temp = HAL_GPIO_ReadPin(SW3_GPIO_Port, SW3_Pin);
		break;
	case SW_4:
		temp = HAL_GPIO_ReadPin(SW4_GPIO_Port, SW4_Pin);
		break;
	case SW_5:
		temp = HAL_GPIO_ReadPin(SW5_GPIO_Port, SW5_Pin);
		break;
	default:
		break;
	}
	return temp;
}
uint8_t is_any_button_pressed(void){
	uint8_t temp = 0b00000000;
	if(HAL_GPIO_ReadPin(SW1_GPIO_Port, SW1_Pin)){
		temp |= 0b00000001;
	}
	while(HAL_GPIO_ReadPin(SW2_GPIO_Port, SW2_Pin)){
		temp |= 0b00000010;
	}
	while(HAL_GPIO_ReadPin(SW3_GPIO_Port, SW3_Pin)){
		temp |= 0b00000100;
	}
	while(HAL_GPIO_ReadPin(SW4_GPIO_Port, SW4_Pin)){
		temp |= 0b00001000;
	}
	while(HAL_GPIO_ReadPin(SW5_GPIO_Port, SW5_Pin)){
		temp |= 0b00010000;
	}
	return temp;
}
void is_button_realize(SW_button_t button){
	switch(button){
	case SW_1:
		while(HAL_GPIO_ReadPin(SW1_GPIO_Port, SW1_Pin)){
			HAL_Delay(1);
		}
		break;
	case SW_2:
		while(HAL_GPIO_ReadPin(SW2_GPIO_Port, SW2_Pin)){
			HAL_Delay(1);
		}
		break;
	case SW_3:
		while(HAL_GPIO_ReadPin(SW3_GPIO_Port, SW3_Pin)){
			HAL_Delay(1);
		}
		break;
	case SW_4:
		while(HAL_GPIO_ReadPin(SW4_GPIO_Port, SW4_Pin)){
			HAL_Delay(1);
		}
		break;
	case SW_5:
		while(HAL_GPIO_ReadPin(SW5_GPIO_Port, SW5_Pin)){
			HAL_Delay(1);
		}
		break;
	default:
		HAL_Delay(1);
		break;
	}
}
void wedshoot(void){
	ssd1306_Fill(Black);
	ssd1306_SetCursor(0,0);
	ssd1306_WriteString("Descarregar app:", Font_7x10, White);
	ssd1306_SetCursor(9,12);
	ssd1306_WriteString(" WEDSHOOT ", Font_11x18, Black);
	ssd1306_SetCursor(0,32);
	ssd1306_WriteString("Codi Acces", Font_7x10, White);
	ssd1306_SetCursor(8,44);
	ssd1306_WriteString("ES1676a715", Font_11x18, Black);
	ssd1306_UpdateScreen();
}

void about_PCB(void){
	bool sortir_menu = true;
	bool sortir_estructura = true;
	uint8_t menu_about = 0;
	ssd1306_Fill(Black);
	ssd1306_SetCursor(10,5);
	ssd1306_WriteString("Designers", Font_7x10, White);
	ssd1306_SetCursor(85,5);
	ssd1306_WriteString("GPIO", Font_7x10, White);
	ssd1306_SetCursor(0,18);
	ssd1306_WriteString("I2C", Font_7x10, White);
	ssd1306_SetCursor(32,18);
	ssd1306_WriteString("ADC", Font_7x10, White);
	ssd1306_SetCursor(65,18);
	ssd1306_WriteString("UART", Font_7x10, White);
	ssd1306_SetCursor(102,18);
	ssd1306_WriteString("SPI", Font_7x10, White);
	ssd1306_SetCursor(35,31);
	ssd1306_WriteString("ICSP", Font_7x10, White);
	ssd1306_SetCursor(70,31);
	ssd1306_WriteString("SW", Font_7x10, White);
	while(sortir_estructura){

		sortir_menu = true;
		switch(menu_about){
		case 0:
			ssd1306_SetCursor(10,5);
			ssd1306_WriteString("Designers", Font_7x10, Black);
			ssd1306_SetCursor(85,5);
			ssd1306_WriteString("GPIO", Font_7x10, White);
			ssd1306_SetCursor(70,31);
			ssd1306_WriteString("SW", Font_7x10, White);
			break;
		case 1:
			ssd1306_SetCursor(10,5);
			ssd1306_WriteString("Designers", Font_7x10, White);
			ssd1306_SetCursor(85,5);
			ssd1306_WriteString("GPIO", Font_7x10, Black);
			ssd1306_SetCursor(0,18);
			ssd1306_WriteString("I2C", Font_7x10, White);
			break;

		case 2:
			ssd1306_SetCursor(85,5);
			ssd1306_WriteString("GPIO", Font_7x10, White);
			ssd1306_SetCursor(0,18);
			ssd1306_WriteString("I2C", Font_7x10, Black);
			ssd1306_SetCursor(32,18);
			ssd1306_WriteString("ADC", Font_7x10, White);
			break;

		case 3:
			ssd1306_SetCursor(0,18);
			ssd1306_WriteString("I2C", Font_7x10, White);
			ssd1306_SetCursor(32,18);
			ssd1306_WriteString("ADC", Font_7x10, Black);
			ssd1306_SetCursor(65,18);
			ssd1306_WriteString("UART", Font_7x10, White);
			break;

		case 4:
			ssd1306_SetCursor(32,18);
			ssd1306_WriteString("ADC", Font_7x10, White);
			ssd1306_SetCursor(65,18);
			ssd1306_WriteString("UART", Font_7x10, Black);
			ssd1306_SetCursor(102,18);
			ssd1306_WriteString("SPI", Font_7x10, White);
			break;

		case 5:
			ssd1306_SetCursor(35,31);
			ssd1306_WriteString("ICSP", Font_7x10, White);
			ssd1306_SetCursor(65,18);
			ssd1306_WriteString("UART", Font_7x10, White);
			ssd1306_SetCursor(102,18);
			ssd1306_WriteString("SPI", Font_7x10, Black);
			break;
		case 6:
			ssd1306_SetCursor(70,31);
			ssd1306_WriteString("SW", Font_7x10, White);
			ssd1306_SetCursor(35,31);
			ssd1306_WriteString("ICSP", Font_7x10, Black);
			ssd1306_SetCursor(102,18);
			ssd1306_WriteString("SPI", Font_7x10, White);
			break;

		case 7:
			ssd1306_SetCursor(10,5);
			ssd1306_WriteString("Designers", Font_7x10, White);
			ssd1306_SetCursor(35,31);
			ssd1306_WriteString("ICSP", Font_7x10, White);
			ssd1306_SetCursor(70,31);
			ssd1306_WriteString("SW", Font_7x10, Black);
			break;

		default:
			menu_about = 0;
			sortir_menu = false;
			break;

		}
		ssd1306_SetCursor(8,50);
		ssd1306_WriteString("<   acceptar   >", Font_7x10, White);
		ssd1306_UpdateScreen();
		while(sortir_menu){
			if(is_pressed_button(SW_4)){//right
				is_button_realize(SW_4);
				menu_about++;
				sortir_menu = false;
			}
			if(is_pressed_button(SW_2)){ // left
				is_button_realize(SW_2);
				if(menu_about == 0) menu_about = 7;
				else menu_about--;
				sortir_menu = false;
			}
			if(is_pressed_button(SW_5)){
				is_button_realize(SW_5);
				sortir_menu = false;
				sortir_estructura = false;
			}
		}
	}

	if(menu_about == 0){
		sortir_estructura = true;
		sortir_menu = true;
		ssd1306_Fill(Black);
		ssd1306_SetCursor(0,0);
		ssd1306_WriteString("Hardware designer:", Font_7x10, White);
		ssd1306_SetCursor(0,12);
		ssd1306_WriteString("Anna Planas Bahí", Font_11x18, Black);
		ssd1306_SetCursor(0,32);
		ssd1306_WriteString("linkedin:", Font_6x8, White);
		ssd1306_SetCursor(0,42);
		ssd1306_WriteString("annaplanasb", Font_7x10, White);
		ssd1306_SetCursor(0,54);
		ssd1306_WriteString("v next", Font_6x8, White);

		ssd1306_UpdateScreen();
		while(sortir_menu){
			if(is_pressed_button(SW_3)){
				is_button_realize(SW_3);
				sortir_menu = false;
			}
		}
		sortir_estructura = true;
		sortir_menu = true;
		ssd1306_Fill(Black);
		ssd1306_SetCursor(0,0);
		ssd1306_WriteString("Firmware designer:", Font_7x10, White);
		ssd1306_SetCursor(0,12);
		ssd1306_WriteString("Eudald Arbós Camps", Font_11x18, Black);
		ssd1306_SetCursor(0,32);
		ssd1306_WriteString("linkedin:", Font_6x8, White);
		ssd1306_SetCursor(0,42);
		ssd1306_WriteString("e-arbos", Font_7x10, White);
		ssd1306_SetCursor(0,54);
		ssd1306_WriteString("v next", Font_6x8, White);

		ssd1306_UpdateScreen();
		while(sortir_menu){
			if(is_pressed_button(SW_3)){
				is_button_realize(SW_3);
				sortir_menu = false;
			}
		}
		sortir_estructura = true;
		sortir_menu = true;
		ssd1306_Fill(Black);
		ssd1306_SetCursor(0,0);
		ssd1306_WriteString("Software designer:", Font_7x10, White);
		ssd1306_SetCursor(0,12);
		ssd1306_WriteString("Pau Grau Palomar", Font_11x18, Black);
		ssd1306_SetCursor(0,32);
		ssd1306_WriteString("linkedin:", Font_6x8, White);
		ssd1306_SetCursor(0,42);
		ssd1306_WriteString("p-g-p", Font_7x10, White);
		ssd1306_SetCursor(0,54);
		ssd1306_WriteString("v next", Font_6x8, White);

		ssd1306_UpdateScreen();
		while(sortir_menu){
			if(is_pressed_button(SW_5)){
				is_button_realize(SW_5);
				sortir_menu = false;
			}
		}
		sortir_estructura = true;
		sortir_menu = true;
		ssd1306_Fill(Black);
		ssd1306_SetCursor(0,0);
		ssd1306_WriteString("Full-Stack designer:", Font_7x10, White);
		ssd1306_SetCursor(0,12);
		ssd1306_WriteString("Arnau Costabella", Font_11x18, Black);
		ssd1306_SetCursor(0,32);
		ssd1306_WriteString("linkedin:", Font_6x8, White);
		ssd1306_SetCursor(0,42);
		ssd1306_WriteString("arnau-costabella-nogera", Font_7x10, White);
		ssd1306_SetCursor(0,54);
		ssd1306_WriteString("v next", Font_6x8, White);

		ssd1306_UpdateScreen();
		while(sortir_menu){
			if(is_pressed_button(SW_3)){
				is_button_realize(SW_3);
				sortir_menu = false;
			}
		}

	}

	else if(menu_about == 1){
			sortir_estructura = true;
			sortir_menu = true;
			ssd1306_Fill(Black);
			ssd1306_SetCursor(0,0);
			ssd1306_WriteString("^Pin1..........Pin12^", Font_6x8, White);
			ssd1306_SetCursor(0,12);
			ssd1306_WriteString("                     ", Font_6x8, Black);
			ssd1306_SetCursor(0,13);
			ssd1306_WriteString(" 3v3 GND A0 A1 B9 B8 ", Font_6x8, Black);
			ssd1306_SetCursor(0,24);
			ssd1306_WriteString("Pin:1 2  3  4  5  6", Font_6x8, White);
			ssd1306_SetCursor(0,35);
			ssd1306_WriteString("                     ", Font_6x8, Black);
			ssd1306_SetCursor(0,36);
			ssd1306_WriteString(" A12 A2 A3 B0 B1 B10 ", Font_6x8, Black);
			ssd1306_SetCursor(0,47);
			ssd1306_WriteString("  7   8  9  10 11 12", Font_6x8, White);

			ssd1306_UpdateScreen();
			while(sortir_menu){
				if(is_pressed_button(SW_5)){
					is_button_realize(SW_5);
					sortir_menu = false;
			}
		}
	}
	else if(menu_about == 2){
		sortir_estructura = true;
		sortir_menu = true;
		ssd1306_Fill(Black);
		ssd1306_SetCursor(0,0);
		ssd1306_WriteString("I2C1 screen SSD1306", Font_6x8, White);
		ssd1306_SetCursor(0,9);
		ssd1306_WriteString("I2C2 Expansion port", Font_6x8, White);
		ssd1306_SetCursor(0,25);
		ssd1306_WriteString("                     ", Font_6x8, Black);
		ssd1306_SetCursor(0,26);
		ssd1306_WriteString("   3v3 GND SDA SCL   ", Font_6x8, Black);
		ssd1306_SetCursor(0,36);
		ssd1306_WriteString("  50mA      B9  B10", Font_6x8, White);
		ssd1306_SetCursor(0,46);
		ssd1306_WriteString("Pin:1   2   5   12", Font_6x8, White);

		ssd1306_UpdateScreen();
		while(sortir_menu){
			if(is_pressed_button(SW_5)){
				is_button_realize(SW_5);
				sortir_menu = false;
			}
		}
	}
	else if(menu_about == 3){
		sortir_estructura = true;
		sortir_menu = true;
		ssd1306_Fill(Black);
		ssd1306_SetCursor(0,0);
		ssd1306_WriteString("ADC0 Expansion port", Font_6x8, White);
		ssd1306_SetCursor(0,25);
		ssd1306_WriteString("                     ", Font_6x8, Black);
		ssd1306_SetCursor(0,26);
		ssd1306_WriteString("   3v3 GND ADC0 ADC1 ", Font_6x8, Black);
		ssd1306_SetCursor(0,36);
		ssd1306_WriteString("  50mA      A0  A1", Font_6x8, White);
		ssd1306_SetCursor(0,46);
		ssd1306_WriteString("Pin:1   2   3   4", Font_6x8, White);

		ssd1306_UpdateScreen();
		while(sortir_menu){
			if(is_pressed_button(SW_5)){
				is_button_realize(SW_5);
				sortir_menu = false;
			}
		}
	}
	else if(menu_about == 4){ //UART pendent
		sortir_estructura = true;
		sortir_menu = true;
		ssd1306_Fill(Black);
		ssd1306_SetCursor(0,0);
		ssd1306_WriteString("USART1 J3 IN_Com", Font_6x8, White);
		ssd1306_SetCursor(0,10);
		ssd1306_WriteString("USART6 J2 OUT_Com", Font_6x8, White);
		ssd1306_SetCursor(0,20);
		ssd1306_WriteString("USART2 ICSP (printf)", Font_6x8, White);
		ssd1306_SetCursor(0,30);
		ssd1306_WriteString("USART2 Expansion port", Font_6x8, White);
		ssd1306_SetCursor(0,52);
		ssd1306_WriteString("v next", Font_6x8, White);


		ssd1306_UpdateScreen();
		while(sortir_menu){
			if(is_pressed_button(SW_3)){
				is_button_realize(SW_3);
				sortir_menu = false;
			}
		}
		sortir_estructura = true;
		sortir_menu = true;
		ssd1306_Fill(Black);
		ssd1306_SetCursor(0,0);
		ssd1306_WriteString("UART1(J3) & 6(J2) JST", Font_6x8, White);
		ssd1306_SetCursor(0,9);
		ssd1306_WriteString("S3B-PH-SM4-TB(LF)(SN)", Font_6x8, White);
		ssd1306_SetCursor(4,22);
		ssd1306_WriteString("1  < J3 Tx / J2 Rx", Font_6x8, White);
		ssd1306_SetCursor(4,31);
		ssd1306_WriteString("2    J3 Rx / J2 Tx", Font_6x8, White);
		ssd1306_SetCursor(4,40);
		ssd1306_WriteString("3    GND", Font_6x8, White);
		ssd1306_SetCursor(0,9);
		ssd1306_WriteString("S3B-PH-SM4-TB(LF)(SN)", Font_6x8, White);


		ssd1306_DrawRectangle(0, 20, 16 ,50 ,White);
		ssd1306_SetCursor(0,52);
		ssd1306_WriteString("v next", Font_6x8, White);


		ssd1306_UpdateScreen();
		while(sortir_menu){
			if(is_pressed_button(SW_3)){
				is_button_realize(SW_3);
				sortir_menu = false;
			}
		}
		sortir_estructura = true;
		sortir_menu = true;
		ssd1306_Fill(Black);
		ssd1306_SetCursor(0,0);
		ssd1306_WriteString("UART2 Expansion port", Font_6x8, White);
		ssd1306_SetCursor(0,25);
		ssd1306_WriteString("                     ", Font_6x8, Black);
		ssd1306_SetCursor(0,26);
		ssd1306_WriteString("   3v3 GND  TX  RX ", Font_6x8, Black);
		ssd1306_SetCursor(0,36);
		ssd1306_WriteString("  50mA      A2  A3", Font_6x8, White);
		ssd1306_SetCursor(0,46);
		ssd1306_WriteString("Pin:1   2   8   9", Font_6x8, White);
		ssd1306_UpdateScreen();
		while(sortir_menu){
			if(is_pressed_button(SW_5)){
				is_button_realize(SW_5);
				sortir_menu = false;
			}
		}
	}
	else if(menu_about == 5){
		sortir_estructura = true;
		sortir_menu = true;
		ssd1306_Fill(Black);
		ssd1306_SetCursor(0,0);
		ssd1306_WriteString("SPI Expansion port", Font_6x8, White);
		ssd1306_SetCursor(0,25);
		ssd1306_WriteString("                     ", Font_6x8, Black);
		ssd1306_SetCursor(0,26);
		ssd1306_WriteString("3v3 GND MOSI MISO NSS", Font_6x8, Black);
		ssd1306_SetCursor(0,36);
		ssd1306_WriteString("50mA     B8   A12 B1", Font_6x8, White);
		ssd1306_SetCursor(0,46);
		ssd1306_WriteString("P:1  2   6    7   11", Font_6x8, White);

		ssd1306_UpdateScreen();
		while(sortir_menu){
			if(is_pressed_button(SW_5)){
				is_button_realize(SW_5);
				sortir_menu = false;
			}
		}
	}
	else if(menu_about == 6){
		sortir_estructura = true;
		sortir_menu = true;
		ssd1306_Fill(Black);
		ssd1306_SetCursor(0,0);
		ssd1306_WriteString("   NP 1    2 NP", Font_6x8, White);
		ssd1306_SetCursor(0,9);
		ssd1306_WriteString("  VCC 3    4 SWDIO", Font_6x8, White);
		ssd1306_SetCursor(0,18);
		ssd1306_WriteString("  GND 5    6 SWCLK", Font_6x8, White);
		ssd1306_SetCursor(0,27);
		ssd1306_WriteString("  GND 7    8 SWO", Font_6x8, White);
		ssd1306_SetCursor(0,36);
		ssd1306_WriteString("   NP 9   10 NP", Font_6x8, White);
		ssd1306_SetCursor(0,45);
		ssd1306_WriteString("  GND 11  12 NRST", Font_6x8, White);
		ssd1306_SetCursor(0,54);
		ssd1306_WriteString("  RX2 13  14 TX2", Font_6x8, White);

		ssd1306_UpdateScreen();
		while(sortir_menu){
			if(is_pressed_button(SW_5)){
				is_button_realize(SW_5);
				sortir_menu = false;
			}
		}
	}
	else if(menu_about == 7){
		sortir_estructura = true;
		sortir_menu = true;
		ssd1306_Fill(Black);
		ssd1306_SetCursor(0,0);
		ssd1306_WriteString("Pulsadors PCB", Font_6x8, White);
		ssd1306_SetCursor(50,18);
		ssd1306_WriteString("SW1", Font_6x8, White);
		ssd1306_SetCursor(20,32);
		ssd1306_WriteString("SW2  SW5  SW4", Font_6x8, White);
		ssd1306_SetCursor(50,46);
		ssd1306_WriteString("SW3", Font_6x8, White);
		ssd1306_UpdateScreen();
		while(sortir_menu){
			if(is_pressed_button(SW_5)){
				is_button_realize(SW_5);
				sortir_menu = false;
			}
		}
	}
	ssd1306_Fill(Black);
	menu_sel = 0;
}

