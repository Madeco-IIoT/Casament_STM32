/*
 * simon.h
 *
 *  Created on: Feb 20, 2024
 *      Author: sobra
 */

#ifndef SIMON_H_
#define SIMON_H_

#include "main.h"
#include "stdbool.h"
#include "ssd1306.h"

#define lila 	0x201100
#define rosa 	0x753135
#define blanc	0x050505
#define negre	0x000000
#define vermell	0x0F0000
#define blau	0x000F00
#define verd	0x00000F
#define llanter 0xFFFFFF

void init_simon(void);
void test_led(void);
void Sel_color(uint8_t color);
uint8_t random_num(uint8_t max, uint8_t min);
uint8_t test_random_LED(void);
void Led_Sequence(void);
uint8_t SW_Sequence (void);
uint8_t SW_Control (uint8_t TimeOut_ms);
void simon_screen(uint8_t score);
void simon_game_over(void);


#endif /* SIMON_H_ */
