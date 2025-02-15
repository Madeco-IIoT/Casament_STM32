/*
 * utils.h
 *
 *  Created on: Dec 23, 2023
 *      Author: sobra
 */

#ifndef SOURCE_UTILS_H_
#define SOURCE_UTILS_H_
//#include "../Core/Src/main.h"
#include "main.h"
#include "stdbool.h"
#include "ssd1306.h"

#define ARRAY_MODIFICAR_HORA 8

typedef enum{
	SW_1 = 0,
	SW_2,
	SW_3,
	SW_4,
	SW_5
}SW_button_t;

void init_RGB (void);
void LED_RGB(uint32_t Color);
void menu (void);
void codiQR (void);
bool is_pressed_button(SW_button_t button);
uint8_t is_any_button_pressed(void);
void is_button_realize(SW_button_t button);
void wedshoot(void);

void about_PCB(void);

#endif /* SOURCE_UTILS_H_ */
