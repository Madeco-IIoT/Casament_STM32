/*
 * snake.c
 *
 *  Created on: Dec 30, 2023
 *      Author: sobra
 */
#include "snake.h"

#define gruix 4 //entre 4 i 8
#define ymax SSD1306_HEIGHT/gruix
#define xmax SSD1306_WIDTH/gruix

int draw_grid[xmax][ymax];
int snake_speed[2]={1,0};
int size_of_snake=2;
int snake_pos[2][20];
int old_poshx;
int old_poshy;
int pos_head[2];
bool sw_up;
bool sw_down;
bool sw_right;
bool sw_left;
int score;


void init_snake(void){
	init_grid();
	draw_grid[0][0]=2;
	draw_grid[1][0]=2;
	snake_pos[0][0]=0;
	snake_pos[1][0]=0;
	snake_pos[0][1]=1;
	snake_pos[1][1]=0;
	size_of_snake=2;
	snake_speed[0]=1;
	snake_speed[1]=0;
	sw_up=true;
	sw_down=true;
	sw_right=true;
	sw_left=true;
	score=0;
	spawn_food();
}

void draw_snake(int x,int y){

	int x0=x*gruix;
	int y0=y*gruix;
	int x1=x0+gruix;
	int y1=y0+gruix;
	for(int i=x0;i<x1;i++){
		for(int j=y0;j<y1;j++){
			ssd1306_DrawPixel(i,j,0x01);
		}
	}
}
void draw_food(int x,int y){
	int x0=x*gruix;
	int y0=y*gruix;
	int x1=x0+gruix;
	int y1=y0+gruix;
	for(int i=x0;i<x1;i++){
		for(int j=y0;j<y1;j++){
			ssd1306_DrawPixel(i,j,0x01);
		}
	}
}

void clear_block(int x,int y){
	int x0=x*8;
	int y0=y*8;
	int x1=x0+8;
	int y1=y0+8;
	for(int i=x0;i<x1;i++){
		for(int j=y0;j<y1;j++){
			ssd1306_DrawPixel(i,j,0x00);
		}
	}
}

void update_grid(){
	ssd1306_Fill(Black);
	for(int i=0;i<xmax;i++){
		for(int j=0;j<ymax;j++){
			if(draw_grid[i][j]==2){
				draw_snake(i,j);
			}
			else if(draw_grid[i][j]==1){
				draw_food(i,j);
			}
			else{
				clear_block(i,j);
			}
		}
	}
	ssd1306_UpdateScreen();
}

//Fill grid with 0
void init_grid(void){
	for(int i=0; i<16;i++){
		for(int j=0;j<8;j++){
			draw_grid[i][j]=0;
		}
	}
}

void move_snake(){
		for(int i=size_of_snake-1;i>=0;i--){
			draw_grid[snake_pos[0][i]][snake_pos[1][i]]=0;
		}
		old_poshx=snake_pos[0][size_of_snake-1];
		old_poshy=snake_pos[1][size_of_snake-1];
		snake_pos[0][size_of_snake-1]=snake_pos[0][size_of_snake-1]+snake_speed[0];
		snake_pos[1][size_of_snake-1]=snake_pos[1][size_of_snake-1]+snake_speed[1];
		pos_head[0]=snake_pos[0][size_of_snake-1];
		pos_head[1]=snake_pos[1][size_of_snake-1];
		for(int i=size_of_snake-2;i>=0;i--){
			int nx = snake_pos[0][i];
			int ny = snake_pos[1][i];
			snake_pos[0][i]=old_poshx;
			snake_pos[1][i]=old_poshy;
			old_poshx=nx;
			old_poshy=ny;
		}
		for(int i=size_of_snake-1;i>=0;i--){
			draw_grid[snake_pos[0][i]][snake_pos[1][i]]=2;
		}
}

void re_init(void){
	init_grid();
	draw_grid[0][0]=2;
	draw_grid[1][0]=2;
	snake_pos[0][0]=0;
	snake_pos[1][0]=0;
	snake_pos[0][1]=1;
	snake_pos[1][1]=0;
	size_of_snake=2;
	snake_speed[0]=1;
	snake_speed[1]=0;
	sw_up=true;
	sw_down=true;
	sw_right=true;
	sw_left=true;
	score=0;
	spawn_food();
}

void spawn_food(void){
	int xf=rand_no(xmax-1);
	int yf=rand_no(ymax-1);
	while(draw_grid[xf][yf]==2){
		xf=rand_no(xmax-1);
		yf=rand_no(ymax-1);
	}
	draw_grid[xf][yf]=1;
}

int rand_no(int m){
	int num = (rand()%(m+1));
	return num;
}

void check_collision(bool re_new_game){
	if(pos_head[0]>= xmax || pos_head[0]<0){
		game_over_screen();
		if(re_new_game)	re_init();
	}
	if(pos_head[1]>=ymax || pos_head[1]<0){
		game_over_screen();
		if(re_new_game)	re_init();
	}
	if(draw_grid[pos_head[0]+snake_speed[0]][pos_head[1]+snake_speed[1]]==2){
		game_over_screen();
		if(re_new_game)	re_init();
	}
}

void wait_check(void){
	for(int i=0;i<20;i++){
		sw_down=HAL_GPIO_ReadPin(SW2_GPIO_Port, SW2_Pin);

		if(sw_down==true && snake_speed[1]==0){
			snake_speed[0]=0;
			snake_speed[1]=1;
			break;
		}
		sw_up=HAL_GPIO_ReadPin(SW1_GPIO_Port,SW1_Pin);
		if(sw_up==true && snake_speed[1]==0){
			snake_speed[0]=0;
			snake_speed[1]=-1;
			break;
		}
		sw_right=HAL_GPIO_ReadPin(SW4_GPIO_Port,SW4_Pin);
		if(sw_right==true && snake_speed[0]==0){
			snake_speed[0]=1;
			snake_speed[1]=0;
			break;
		}
		sw_left=HAL_GPIO_ReadPin(SW3_GPIO_Port,SW3_Pin);
		if(sw_left==true && snake_speed[0]==0){
			snake_speed[0]=-1;
			snake_speed[1]=0;
			break;
		}
		HAL_Delay(5);
	}
}
void check_food(void){
	if(draw_grid[pos_head[0]+snake_speed[0]][pos_head[1]+snake_speed[1]]==1){
		score++;
		size_of_snake++;
		snake_pos[0][size_of_snake-1]=pos_head[0]+snake_speed[0];
		snake_pos[1][size_of_snake-1]=pos_head[1]+snake_speed[1];
		spawn_food();
	}
}

void game_over_screen(void){
	ssd1306_Fill(Black);
	ssd1306_SetCursor(16,20);
	ssd1306_WriteString("Game Over", Font_11x18, 0x01);
	ssd1306_SetCursor(16,40);
	ssd1306_WriteString("Score: ", Font_11x18, 0x01);
	ssd1306_SetCursor(80,40);
	char sc1=score+'0';
	ssd1306_WriteChar(sc1, Font_11x18,0x01);
	ssd1306_UpdateScreen();
	HAL_Delay(1000);
}
