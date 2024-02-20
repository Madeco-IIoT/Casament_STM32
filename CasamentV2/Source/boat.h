/*
 * boat.h
 *
 *  Created on: Jan 1, 2024
 *      Author: sobra
 */

#ifndef BOAT_H_
#define BOAT_H_
#include "main.h"
#include "ssd1306.h"

#define fragata 1
#define destructor 2
#define acorasat 3
#define portaavions 4
#define aigua 100
#define tocat 101

void boad_init(bool new_game);
bool initMatrix(uint8_t boat_type, uint8_t x_boat, uint8_t y_boat, bool horitzotnal, bool boat_erase);
bool updateMatrix(uint8_t x_boom, uint8_t y_boom);
bool update_OLED(void);
void boad_matrix_build (void);



#endif /* BOAT_H_ */
