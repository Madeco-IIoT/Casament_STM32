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


void test_led(void);
void Sel_color(uint8_t color);
uint8_t random_num(uint8_t max, uint8_t min);
void test_random_LED(void);


#endif /* SIMON_H_ */
