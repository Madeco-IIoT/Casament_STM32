/*
 * boat.c
 *
 *  Created on: Jan 1, 2024
 *      Author: sobra
 */
#define pas_reixa 12


#include "boat.h"

uint8_t boat_matrix[9][4];


void boad_init(bool new_game){
	//fer les ratlles horitxontals
	for(uint8_t x=0; x<9; x++){
		ssd1306_SetCursor(14+x*12,0);
		ssd1306_WriteChar(x+65, Font_7x10, White);
	}
	for(uint8_t x=0; x<4; x++){
		ssd1306_SetCursor(0,14+x*12);
		ssd1306_WriteChar(x+49, Font_7x10, White);
	}
	for(uint8_t z=1; z<(SSD1306_HEIGHT/pas_reixa)+1; z++){
		ssd1306_Line(13, pas_reixa*z, SSD1306_WIDTH-9, pas_reixa*z, White);
	}
	for(uint8_t z=1; z<(SSD1306_WIDTH/pas_reixa)+1; z++){
			ssd1306_Line(pas_reixa*z, 13, pas_reixa*z, SSD1306_HEIGHT-5, White);
	}
	ssd1306_UpdateScreen();
	ssd1306_UpdateScreen();
	if (new_game) {
		for(uint8_t x=0; x<9; x++){
			for(uint8_t y=0; y<4; y++){
				boat_matrix[x][y] = 0;
			}
		}
	}
}

bool initMatrix(uint8_t boat_type, uint8_t x_boat, uint8_t y_boat, bool horitzotnal, bool boat_erase){
	bool colisio = false;
	if (boat_type == fragata){
		//no cal mirar si és horitzontal o vertical
		//cal verificar que no sigui un nuemro massa gros
		if(x_boat > 9) x_boat = 9;
		if(y_boat > 4) y_boat = 4;
		if(!boat_erase){
			if (boat_matrix[x_boat-1][y_boat-1] == 0){
				boat_matrix[x_boat-1][y_boat-1]=boat_type;
			}
			else colisio = true;
		}
		else{
			if (boat_matrix[x_boat-1][y_boat-1] != 0){
				boat_matrix[x_boat-1][y_boat-1] = 0;
			}
		}

	}
	if (boat_type == destructor){
		if(horitzotnal){
			//cal verificar que no sigui un nuemro massa gros
			if(x_boat > 8) x_boat = 8;
			if(y_boat > 4) y_boat = 4;
			if(!boat_erase){
				if (boat_matrix[x_boat-1][y_boat-1] == 0 || boat_matrix[x_boat][y_boat-1] == boat_type){
					if (boat_matrix[x_boat][y_boat-1] == 0){
						boat_matrix[x_boat][y_boat-1]=boat_type;
						boat_matrix[x_boat-1][y_boat-1]=boat_type;
					}
					else colisio = true;
				}
				else colisio = true;
			}
			else{
				boat_matrix[x_boat-1][y_boat-1] = 0;
				boat_matrix[x_boat][y_boat-1] = 0;
			}
		}
		else{
			//cal verificar que no sigui un nuemro massa gros
			if(x_boat > 9) x_boat = 9;
			if(y_boat > 3) y_boat = 3;
			if(!boat_erase){
				if (boat_matrix[x_boat-1][y_boat-1] == 0 ){
					if (boat_matrix[x_boat-1][y_boat] == 0 || boat_matrix[x_boat-1][y_boat] == boat_type){
						boat_matrix[x_boat-1][y_boat-1]=boat_type;
						boat_matrix[x_boat-1][y_boat]=boat_type;
					}
					else colisio = true;
				}
				else colisio = true;
			}
			else{
			boat_matrix[x_boat-1][y_boat-1] = 0;
			boat_matrix[x_boat-1][y_boat] = 0;
			}
		}
	}
	if (boat_type == acorasat){
		if(horitzotnal){
			//cal verificar que no sigui un nuemro massa gros
			if(x_boat > 7) x_boat = 7;
			if(y_boat > 4) y_boat = 4;
			if(!boat_erase){
				if (boat_matrix[x_boat-1][y_boat-1] == 0 || boat_matrix[x_boat][y_boat-1] == boat_type){
					if ( boat_matrix[x_boat+1][y_boat-1] == 0 || boat_matrix[x_boat+1][y_boat-1] == boat_type){
						if (boat_matrix[x_boat][y_boat-1] == 0){
							boat_matrix[x_boat][y_boat-1]=boat_type;
							boat_matrix[x_boat-1][y_boat-1]=boat_type;
							boat_matrix[x_boat+1][y_boat-1]=boat_type;
						}
						else colisio = true;
					}

					else colisio = true;
				}
				else colisio = true;
			}
			else{
				boat_matrix[x_boat-1][y_boat-1] = 0;
				boat_matrix[x_boat][y_boat-1] = 0;
				boat_matrix[x_boat+1][y_boat-1] = 0;
			}
		}
		else{
			//cal verificar que no sigui un nuemro massa gros
			if(x_boat > 9) x_boat = 9;
			if(y_boat > 2) y_boat = 2;
			if(!boat_erase){
				if (boat_matrix[x_boat-1][y_boat-1] == 0 ){
					if (boat_matrix[x_boat-1][y_boat] == 0 || boat_matrix[x_boat-1][y_boat] == boat_type){
						if( boat_matrix[x_boat+1][y_boat-1] == 0 || boat_matrix[x_boat+1][y_boat-1] == boat_type){
							boat_matrix[x_boat-1][y_boat-1]=boat_type;
							boat_matrix[x_boat-1][y_boat]=boat_type;
							boat_matrix[x_boat-1][y_boat+1]=boat_type;
						}
						else colisio = true;
					}
					else colisio = true;
				}
				else colisio = true;
			}
			else{
			boat_matrix[x_boat-1][y_boat-1] = 0;
			boat_matrix[x_boat-1][y_boat] = 0;
			boat_matrix[x_boat-1][y_boat+1] = 0;
			}
		}
	}


	return colisio;
}

bool updateMatrix(uint8_t x_boom, uint8_t y_boom){
	bool colisio = false;
	if(x_boom > 9) x_boom = 9;
	if(y_boom > 4) y_boom = 4;
	if (boat_matrix[x_boom-1][y_boom-1] == 0){
		boat_matrix[x_boom-1][y_boom-1]=aigua;
		colisio = true;
	}
	else boat_matrix[x_boom-1][y_boom-1]=tocat;
	return colisio;
}

bool update_OLED(void){
	bool hi_ha_barcos = false;

	//mostrar la matriu actualitzada
	for(uint8_t x=0; x<9; x++){
		for(uint8_t y=0; y<4; y++){
			if((boat_matrix[x][y]) == 0){
				ssd1306_SetCursor(16+x*12,15+y*12);
				ssd1306_WriteChar(' ', Font_6x8, White);
				hi_ha_barcos = true;
			}
			if((boat_matrix[x][y]) == fragata){
				ssd1306_SetCursor(16+x*12,15+y*12);
				ssd1306_WriteChar('f', Font_6x8, White);
				hi_ha_barcos = true;
			}
			if((boat_matrix[x][y]) == destructor){
				ssd1306_SetCursor(16+x*12,15+y*12);
				ssd1306_WriteChar('d', Font_6x8, White);
				hi_ha_barcos = true;
			}
			if((boat_matrix[x][y]) == acorasat){
				ssd1306_SetCursor(16+x*12,15+y*12);
				ssd1306_WriteChar('a', Font_6x8, White);
				hi_ha_barcos = true;
			}
			if((boat_matrix[x][y]) == aigua){
				ssd1306_SetCursor(16+x*12,15+y*12);
				ssd1306_WriteChar('o', Font_6x8, White);
			}
			if((boat_matrix[x][y]) == tocat){
				ssd1306_SetCursor(16+x*12,15+y*12);
				ssd1306_WriteChar('x', Font_6x8, White);
			}
		}
	}
	ssd1306_UpdateScreen();
	return hi_ha_barcos;
}

int8_t clamp(int8_t value, int8_t min, int8_t max) {
	return value < min ? min : (value > max ? max : value);
}

void boad_matrix_build (void){
	int8_t x_boat = 1;
	int8_t y_boat = 1;
	uint8_t min_x = 1, max_x = 9;
	uint8_t min_y = 1, max_y = 4;
	bool horitzontal = false;
	uint32_t cont = 0;
	uint8_t boat_num = 0;
	uint8_t boat_type = 1;

	if (boat_num < 3) boat_type = fragata;
	else if (boat_num > 2 && boat_num < 5 ) boat_type = destructor;
	else boat_type = acorasat;

	initMatrix(boat_type, x_boat, y_boat, horitzontal, false);

	while(boat_num < 6){
		update_OLED();


		if(HAL_GPIO_ReadPin(SW1_GPIO_Port, SW1_Pin)){ // down
			initMatrix(boat_type, x_boat, y_boat, horitzontal, true);
			y_boat = clamp(y_boat - 1, min_y, max_y);
			while (HAL_GPIO_ReadPin(SW1_GPIO_Port, SW1_Pin)) HAL_Delay(1);
			if(initMatrix(boat_type, x_boat, y_boat, horitzontal, false)){
				y_boat = clamp(y_boat + 1, min_y, max_y);
				initMatrix(boat_type, x_boat, y_boat, horitzontal, false);
			}
		}
		else if(HAL_GPIO_ReadPin(SW2_GPIO_Port, SW2_Pin)){ // up
			initMatrix(boat_type, x_boat, y_boat, horitzontal, true);
			y_boat = clamp(y_boat + 1, min_y, max_y);
			while (HAL_GPIO_ReadPin(SW2_GPIO_Port, SW2_Pin)) HAL_Delay(1);
			if(initMatrix(boat_type, x_boat, y_boat, horitzontal, false)){
				y_boat = clamp(y_boat - 1, min_y, max_y);
				initMatrix(boat_type, x_boat, y_boat, horitzontal, false);
			}
		}
		else if(HAL_GPIO_ReadPin(SW3_GPIO_Port, SW3_Pin)){ // left
			initMatrix(boat_type, x_boat, y_boat, horitzontal, true);
			x_boat = clamp(x_boat - 1, min_x, max_x);
			while (HAL_GPIO_ReadPin(SW3_GPIO_Port, SW3_Pin)) HAL_Delay(1);
			if(initMatrix(boat_type, x_boat, y_boat, horitzontal, false)){
				x_boat = clamp(x_boat + 1, min_x, max_x);
				initMatrix(boat_type, x_boat, y_boat, horitzontal, false);
			}
		}
		else if(HAL_GPIO_ReadPin(SW4_GPIO_Port, SW4_Pin)){ // right
			initMatrix(boat_type, x_boat, y_boat, horitzontal, true);
			x_boat = clamp(x_boat + 1, min_x, max_x);
			while (HAL_GPIO_ReadPin(SW4_GPIO_Port, SW4_Pin)) HAL_Delay(1);
			if(initMatrix(boat_type, x_boat, y_boat, horitzontal, false)){
				x_boat = clamp(x_boat - 1, min_x, max_x);
				initMatrix(boat_type, x_boat, y_boat, horitzontal, false);
			}
		}
		else if (HAL_GPIO_ReadPin(SW5_GPIO_Port, SW5_Pin)){ // accept boat
			cont = 0;
			while (HAL_GPIO_ReadPin(SW5_GPIO_Port, SW5_Pin)){
				HAL_Delay(10);
				cont++;
			}
			if (cont < 100){
				//girar pesa
				initMatrix(boat_type, x_boat, y_boat, horitzontal, true);
				if (horitzontal) horitzontal = false;
				else horitzontal = true;
				if (initMatrix(boat_type, x_boat, y_boat, horitzontal, false)){
					if (horitzontal) horitzontal = false;
					else horitzontal = true;
				}
				initMatrix(boat_type, x_boat, y_boat, horitzontal, false);
			}
			else {
				boat_num ++;
				if (boat_num < 3) boat_type = fragata;
				else if (boat_num > 2 && boat_num < 5 ) boat_type = destructor;
				else boat_type = acorasat;

				x_boat = 1;
				y_boat = 1;
				while (initMatrix(boat_type, x_boat, y_boat, horitzontal, false)){
					x_boat ++;
					if(x_boat > max_x){
						x_boat = 0;
						y_boat ++;
					}
				}
			}
		}
	}
}

