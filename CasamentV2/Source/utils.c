/*
 * utils.c
 *
 *  Created on: Dec 23, 2023
 *      Author: sobra
 */
#include "utils.h"
//#include "main.h"

extern TIM_HandleTypeDef htim5;
extern TIM_HandleTypeDef htim11;
extern RTC_HandleTypeDef hrtc;

extern bool snake_en;
extern bool simon_en;
extern bool boad_en;

static const char bsp_rtc_build_time[] = __TIME__;
static const char bsp_rtc_build_date[] = __DATE__;

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

void BSP_RTC_SetInitialDateTime(void) {
	RTC_TimeTypeDef sTimeGlobal = {0};
	RTC_DateTypeDef sDateGlobal = {0};
	unsigned int day;
	unsigned int year;
	unsigned int hour;
	unsigned int min;
	unsigned int sec;
	char month[3 + 1];

	/* Fem matching del patrons:
	 * 	- Feb 26 2019
	 * 	- 12:50:50
	 * 	per obtenir la data de configuració d'inici.s
	 */
	sscanf(bsp_rtc_build_date, "%s %02u %04u", month, &day, &year);
	sscanf(bsp_rtc_build_time, "%02u:%02u:%02u", &hour, &min, &sec);

	sDateGlobal.Year = year - 2000;
	if (strcmp(month, "Jan") == 0)
		sDateGlobal.Month = 1;
	else if (strcmp(month, "Feb") == 0)
		sDateGlobal.Month = 2;
	else if (strcmp(month, "Mar") == 0)
		sDateGlobal.Month = 3;
	else if (strcmp(month, "Apr") == 0)
		sDateGlobal.Month = 4;
	else if (strcmp(month, "May") == 0)
		sDateGlobal.Month = 5;
	else if (strcmp(month, "Jun") == 0)
		sDateGlobal.Month = 6;
	else if (strcmp(month, "Jul") == 0)
		sDateGlobal.Month = 7;
	else if (strcmp(month, "Aug") == 0)
		sDateGlobal.Month = 8;
	else if (strcmp(month, "Sep") == 0)
		sDateGlobal.Month = 9;
	else if (strcmp(month, "Oct") == 0)
		sDateGlobal.Month = 10;
	else if (strcmp(month, "Nov") == 0)
		sDateGlobal.Month = 11;
	else if (strcmp(month, "Dec") == 0)
		sDateGlobal.Month = 12;
	sDateGlobal.Date = day;

	sTimeGlobal.Hours = hour;
	sTimeGlobal.Minutes = min;
	sTimeGlobal.Seconds = sec;
	sTimeGlobal.TimeFormat = (hour >= 12)? RTC_HOURFORMAT12_PM : RTC_HOURFORMAT12_AM;
	sTimeGlobal.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	sTimeGlobal.StoreOperation = RTC_STOREOPERATION_RESET;

	HAL_RTC_SetDate(&hrtc, &sDateGlobal, RTC_FORMAT_BIN);
	HAL_RTC_SetTime(&hrtc, &sTimeGlobal, RTC_FORMAT_BIN);

	/* Writes a data in a RTC Backup data Register0 #######################*/
	HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR0, 0x33);
}

void hora(void){
	RTC_TimeTypeDef actualTime = {0};
	RTC_DateTypeDef actualDate = {0};
	uint8_t hh;
	uint8_t mm;
	uint8_t dd;
	uint8_t mes;
	uint16_t any;
	char horastr[20] = {0};

	HAL_RTC_GetTime(&hrtc, &actualTime, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &actualDate, RTC_FORMAT_BIN);
	hh=actualTime.Hours;
	mm=actualTime.Minutes;
	dd=actualDate.Date;
	mes=actualDate.Month;
	any=actualDate.Year;
	memset(horastr, '\0', 20);
	sprintf(horastr, "%02u:%02u  %02u/%02u/20%02u %c", hh, mm, dd, mes, any, '\0');
	ssd1306_SetCursor(0,0);
	ssd1306_WriteString(horastr, Font_7x10, White);
	ssd1306_UpdateScreen();
}
void menu (void){
	switch (menu_sel){
	case 0:
		ssd1306_SetCursor(4,12);
		ssd1306_WriteString(" Snake ", Font_7x10, Black);
		ssd1306_SetCursor(4,24);
		ssd1306_WriteString(" Sink the float ", Font_7x10, White);
		ssd1306_SetCursor(4,36);
		ssd1306_WriteString(" Simon ", Font_7x10, White);
		ssd1306_UpdateScreen();
		if(HAL_GPIO_ReadPin(SW2_GPIO_Port, SW2_Pin)){ // down
			while (HAL_GPIO_ReadPin(SW2_GPIO_Port, SW2_Pin)) HAL_Delay(1);
			menu_sel ++;
		}
		if(HAL_GPIO_ReadPin(SW5_GPIO_Port, SW5_Pin)){ // accept
			while (HAL_GPIO_ReadPin(SW5_GPIO_Port, SW5_Pin)) HAL_Delay(1);
			snake_en = true;
		}
		break;
	case 1:
		ssd1306_SetCursor(4,12);
		ssd1306_WriteString(" Snake ", Font_7x10, White);
		ssd1306_SetCursor(4,24);
		ssd1306_WriteString(" Sink the float ", Font_7x10, Black);
		ssd1306_SetCursor(4,36);
		ssd1306_WriteString(" Simon ", Font_7x10, White);
		ssd1306_UpdateScreen();
		if(HAL_GPIO_ReadPin(SW1_GPIO_Port, SW1_Pin)){ // Up
			while (HAL_GPIO_ReadPin(SW1_GPIO_Port, SW1_Pin)) HAL_Delay(1);
			menu_sel --;
		}
		if(HAL_GPIO_ReadPin(SW2_GPIO_Port, SW2_Pin)){ // down
			while (HAL_GPIO_ReadPin(SW2_GPIO_Port, SW2_Pin)) HAL_Delay(1);
			menu_sel ++;
		}
		if(HAL_GPIO_ReadPin(SW5_GPIO_Port, SW5_Pin)){ // accept
			while (HAL_GPIO_ReadPin(SW5_GPIO_Port, SW5_Pin)) HAL_Delay(1);
			boad_en = true;
		}
		break;
	case 2:
		ssd1306_SetCursor(4,12);
		ssd1306_WriteString(" Snake ", Font_7x10, White);
		ssd1306_SetCursor(4,24);
		ssd1306_WriteString(" Sink the float ", Font_7x10, White);
		ssd1306_SetCursor(4,36);
		ssd1306_WriteString(" Simon ", Font_7x10, Black);
		ssd1306_UpdateScreen();
		if(HAL_GPIO_ReadPin(SW1_GPIO_Port, SW1_Pin)){ // up
			while (HAL_GPIO_ReadPin(SW1_GPIO_Port, SW1_Pin)) HAL_Delay(1);
			menu_sel --;
		}

		break;
	default:
		HAL_Delay(1);
	}
}
