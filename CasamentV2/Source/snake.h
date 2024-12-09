/*
 * snake.h
 *
 *  Created on: Dec 30, 2023
 *      Author: sobra
 */

#ifndef SNAKE_H_
#define SNAKE_H_

#ifndef MIXU_EMULATOR
#include "main.h"
#include "ssd1306.h"
#include "ssd1306_fonts.h"
#else
#include "stdbool.h"
#endif

void init_snake(void);
void draw_snake(int x,int y);
void draw_food(int x,int y);
void clear_block(int x,int y);
void update_grid();
void init_grid(void);
void move_snake();
void re_init(void);
void spawn_food(void);
int rand_no(int m);
void check_collision(bool re_new_game);
void wait_check(void);
void check_food(void);
void game_over_screen(void);




#endif /* SNAKE_H_ */
