/*
 * hora.c
 *
 *  Created on: Sep 28, 2024
 *      Author: sobra
 */
#include "hora.h"

extern RTC_HandleTypeDef hrtc;

static const char bsp_rtc_build_time[] = __TIME__;
static const char bsp_rtc_build_date[] = __DATE__;

void actualitzar_hora(void){
	uint8_t Hores_minuts_segons = 0;
	RTC_TimeTypeDef actualTime = {0};
	RTC_DateTypeDef actualDate = {0};
	HAL_RTC_GetTime(&hrtc, &actualTime, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &actualDate, RTC_FORMAT_BIN);
	char horastr[ARRAY_MODIFICAR_HORA] = {0};
	bool sortir_hora = true;
	bool sortir_estructura = true;
	while(sortir_estructura){
		ssd1306_Fill(Black);
		ssd1306_SetCursor(0,0);
		ssd1306_WriteString("Seleccionar una", Font_7x10, White);
		ssd1306_SetCursor(0,12);
		ssd1306_WriteString("opcio per ajustar", Font_7x10, White);
		sortir_hora = true;
		switch(Hores_minuts_segons){
		case 0:
			ssd1306_SetCursor(0,31);
			ssd1306_WriteString("Hora", Font_7x10, Black);
			ssd1306_SetCursor(42,31);
			ssd1306_WriteString("Data", Font_7x10, White);
			ssd1306_SetCursor(84,31);
			ssd1306_WriteString("Sortir", Font_7x10, White);

			break;
		case 1:
			ssd1306_SetCursor(0,31);
			ssd1306_WriteString("Hora", Font_7x10, White);
			ssd1306_SetCursor(42,31);
			ssd1306_WriteString("Data", Font_7x10, Black);
			ssd1306_SetCursor(84,31);
			ssd1306_WriteString("Sortir", Font_7x10, White);
			break;

		case 2:
			ssd1306_SetCursor(0,31);
			ssd1306_WriteString("Hora", Font_7x10, White);
			ssd1306_SetCursor(42,31);
			ssd1306_WriteString("Data", Font_7x10, White);
			ssd1306_SetCursor(84,31);
			ssd1306_WriteString("Sortir", Font_7x10, Black);
			break;

		default:
			Hores_minuts_segons = 0;
			break;

		}
		ssd1306_SetCursor(8,50);
		ssd1306_WriteString("<   acceptar   >", Font_7x10, White);
		ssd1306_UpdateScreen();
		while(sortir_hora){

			if(HAL_GPIO_ReadPin(SW4_GPIO_Port, SW4_Pin)){ // right
				while (HAL_GPIO_ReadPin(SW4_GPIO_Port, SW4_Pin)) HAL_Delay(1);
				if(Hores_minuts_segons == 0) Hores_minuts_segons++;
				else if(Hores_minuts_segons == 1) Hores_minuts_segons++;
				else Hores_minuts_segons = 0;
				sortir_hora = false;
			}
			if(HAL_GPIO_ReadPin(SW2_GPIO_Port, SW2_Pin)){ // left
				while (HAL_GPIO_ReadPin(SW2_GPIO_Port, SW2_Pin)) HAL_Delay(1);
				if(Hores_minuts_segons == 0) Hores_minuts_segons = 2;
				else if(Hores_minuts_segons == 1) Hores_minuts_segons--;
				else Hores_minuts_segons--;
				sortir_hora = false;
			}
			if(HAL_GPIO_ReadPin(SW5_GPIO_Port, SW5_Pin)){
				while (HAL_GPIO_ReadPin(SW5_GPIO_Port, SW5_Pin)) HAL_Delay(1);
				sortir_hora = false;
				sortir_estructura = false;
			}
		}
	}
	if(Hores_minuts_segons == 0){
		Hores_minuts_segons = 0;
		sortir_hora = true;
		sortir_estructura = true;
		while(sortir_estructura){
			sortir_hora = true;

			switch (Hores_minuts_segons) {
			case 0: //hores
				ssd1306_Fill(Black);
				memset(horastr, '\0', ARRAY_MODIFICAR_HORA);
				sprintf(horastr, "%02u", actualTime.Hours);
				ssd1306_SetCursor(15,0);
				ssd1306_WriteString(horastr, Font_11x18, Black);
				memset(horastr, '\0', ARRAY_MODIFICAR_HORA);
				sprintf(horastr, ":%02u:", actualTime.Minutes);
				ssd1306_SetCursor(34,0);
				ssd1306_WriteString(horastr, Font_11x18, White);
				memset(horastr, '\0', ARRAY_MODIFICAR_HORA);
				sprintf(horastr, "%02u", actualTime.Seconds);
				ssd1306_SetCursor(78,0);
				ssd1306_WriteString(horastr, Font_11x18, White);
				break;

			case 1: //minuts
				ssd1306_Fill(Black);
				memset(horastr, '\0', ARRAY_MODIFICAR_HORA);
				sprintf(horastr, "%02u:", actualTime.Hours);
				ssd1306_SetCursor(15,0);
				ssd1306_WriteString(horastr, Font_11x18, White);
				memset(horastr, '\0', ARRAY_MODIFICAR_HORA);
				sprintf(horastr, "%02u", actualTime.Minutes);
				ssd1306_SetCursor(45,0);
				ssd1306_WriteString(horastr, Font_11x18, Black);
				memset(horastr, '\0', ARRAY_MODIFICAR_HORA);
				sprintf(horastr, ":%02u", actualTime.Seconds);
				ssd1306_SetCursor(67,0);
				ssd1306_WriteString(horastr, Font_11x18, White);
				break;

			case 2: //segons
				ssd1306_Fill(Black);
				memset(horastr, '\0', ARRAY_MODIFICAR_HORA);
				sprintf(horastr, "%02u", actualTime.Hours);
				ssd1306_SetCursor(15,0);
				ssd1306_WriteString(horastr, Font_11x18, White);
				memset(horastr, '\0', ARRAY_MODIFICAR_HORA);
				sprintf(horastr, ":%02u:", actualTime.Minutes);
				ssd1306_SetCursor(34,0);
				ssd1306_WriteString(horastr, Font_11x18, White);
				memset(horastr, '\0', ARRAY_MODIFICAR_HORA);
				sprintf(horastr, "%02u", actualTime.Seconds);
				ssd1306_SetCursor(78,0);
				ssd1306_WriteString(horastr, Font_11x18, Black);
				break;

			default:
				sortir_hora = false;
				Hores_minuts_segons = 0;
				break;


			}
			ssd1306_SetCursor(63,24);
			ssd1306_WriteString("+", Font_7x10, White);
			ssd1306_SetCursor(8,36);
			ssd1306_WriteString("<   acceptar   >", Font_7x10, White);
			ssd1306_SetCursor(63,48);
			ssd1306_WriteString("-", Font_7x10, White);
			ssd1306_UpdateScreen();
			while(sortir_hora){
				if(HAL_GPIO_ReadPin(SW1_GPIO_Port, SW1_Pin)){ // up
					while (HAL_GPIO_ReadPin(SW1_GPIO_Port, SW1_Pin)) HAL_Delay(1);
					if(Hores_minuts_segons == 0){
						actualTime.Hours++;
						if(actualTime.Hours > 23) actualTime.Hours = 0;
					}

					else if(Hores_minuts_segons == 1){
						actualTime.Minutes++;
						if(actualTime.Minutes > 59) actualTime.Minutes = 0;
					}
					else{
						actualTime.Seconds++;
						if(actualTime.Seconds > 59) actualTime.Seconds = 0;
					}
					sortir_hora = false;
				}
				if(HAL_GPIO_ReadPin(SW3_GPIO_Port, SW3_Pin)){ // down
					while (HAL_GPIO_ReadPin(SW3_GPIO_Port, SW3_Pin)) HAL_Delay(1);
					if(Hores_minuts_segons == 0){
						actualTime.Hours--;
						if(actualTime.Hours > 23) actualTime.Hours = 23;
					}
					else if(Hores_minuts_segons == 1){
						actualTime.Minutes--;
						if(actualTime.Minutes > 59) actualTime.Minutes = 59;
					}
					else{
						actualTime.Seconds--;
						if(actualTime.Seconds > 59) actualTime.Seconds = 59;
					}
					sortir_hora = false;
				}
				if(HAL_GPIO_ReadPin(SW4_GPIO_Port, SW4_Pin)){ // right
					while (HAL_GPIO_ReadPin(SW4_GPIO_Port, SW4_Pin)) HAL_Delay(1);
					if(Hores_minuts_segons == 0) Hores_minuts_segons++;
					else if(Hores_minuts_segons == 1) Hores_minuts_segons++;
					else Hores_minuts_segons = 0;
					sortir_hora = false;
				}
				if(HAL_GPIO_ReadPin(SW2_GPIO_Port, SW2_Pin)){ // left
					while (HAL_GPIO_ReadPin(SW2_GPIO_Port, SW2_Pin)) HAL_Delay(1);
					if(Hores_minuts_segons == 0) Hores_minuts_segons = 2;
					else if(Hores_minuts_segons == 1) Hores_minuts_segons--;
					else Hores_minuts_segons--;
					sortir_hora = false;
				}
				if(HAL_GPIO_ReadPin(SW5_GPIO_Port, SW5_Pin)){ // accept
					while (HAL_GPIO_ReadPin(SW5_GPIO_Port, SW5_Pin)) HAL_Delay(1);
					sortir_estructura = false;
					sortir_hora = false;
					HAL_RTC_SetTime(&hrtc, &actualTime, RTC_FORMAT_BIN);
				}
			}

		}
	}
	else if (Hores_minuts_segons == 1){
		Hores_minuts_segons = 0;
		sortir_hora = true;
		sortir_estructura = true;
		while(sortir_estructura){
			sortir_hora = true;

			switch (Hores_minuts_segons) {
			case 0: //dia
				ssd1306_Fill(Black);
				memset(horastr, '\0', ARRAY_MODIFICAR_HORA);
				sprintf(horastr, "%02u", actualDate.Date);
				ssd1306_SetCursor(10,0);
				ssd1306_WriteString(horastr, Font_11x18, Black);
				memset(horastr, '\0', ARRAY_MODIFICAR_HORA);
				sprintf(horastr, "-%02u-", actualDate.Month);
				ssd1306_SetCursor(31,0);
				ssd1306_WriteString(horastr, Font_11x18, White);
				memset(horastr, '\0', ARRAY_MODIFICAR_HORA);
				sprintf(horastr, "20%02u", actualDate.Year);
				ssd1306_SetCursor(75,0);
				ssd1306_WriteString(horastr, Font_11x18, White);
				break;

			case 1: //mes
				ssd1306_Fill(Black);
				memset(horastr, '\0', ARRAY_MODIFICAR_HORA);
				sprintf(horastr, "%02u-", actualDate.Date);
				ssd1306_SetCursor(10,0);
				ssd1306_WriteString(horastr, Font_11x18, White);
				memset(horastr, '\0', ARRAY_MODIFICAR_HORA);
				sprintf(horastr, "%02u", actualDate.Month);
				ssd1306_SetCursor(42,0);
				ssd1306_WriteString(horastr, Font_11x18, Black);
				memset(horastr, '\0', ARRAY_MODIFICAR_HORA);
				sprintf(horastr, "-20%02u", actualDate.Year);
				ssd1306_SetCursor(64,0);
				ssd1306_WriteString(horastr, Font_11x18, White);
				break;

			case 2: //any
				ssd1306_Fill(Black);
				memset(horastr, '\0', ARRAY_MODIFICAR_HORA);
				sprintf(horastr, "%02u", actualDate.Date);
				ssd1306_SetCursor(10,0);
				ssd1306_WriteString(horastr, Font_11x18, White);
				memset(horastr, '\0', ARRAY_MODIFICAR_HORA);
				sprintf(horastr, "-%02u-", actualDate.Month);
				ssd1306_SetCursor(31,0);
				ssd1306_WriteString(horastr, Font_11x18, White);
				memset(horastr, '\0', ARRAY_MODIFICAR_HORA);
				sprintf(horastr, "20%02u", actualDate.Year);
				ssd1306_SetCursor(75,0);
				ssd1306_WriteString(horastr, Font_11x18, Black);
				break;

			default:
				sortir_hora = false;
				Hores_minuts_segons = 0;
				break;


			}
			ssd1306_SetCursor(63,24);
			ssd1306_WriteString("+", Font_7x10, White);
			ssd1306_SetCursor(8,36);
			ssd1306_WriteString("<   acceptar   >", Font_7x10, White);
			ssd1306_SetCursor(63,48);
			ssd1306_WriteString("-", Font_7x10, White);
			ssd1306_UpdateScreen();
			while(sortir_hora){
				if(HAL_GPIO_ReadPin(SW1_GPIO_Port, SW1_Pin)){ // up
					while (HAL_GPIO_ReadPin(SW1_GPIO_Port, SW1_Pin)) HAL_Delay(1);
					if(Hores_minuts_segons == 0){
						actualDate.Date++;
						if(actualDate.Date > 31) actualDate.Date = 0;
					}

					else if(Hores_minuts_segons == 1){
						actualDate.Month++;
						if(actualDate.Month > 12) actualDate.Month = 0;
					}
					else{
						actualDate.Year++;
						if(actualDate.Year > 99) actualDate.Year = 0;
					}
					sortir_hora = false;
				}
				if(HAL_GPIO_ReadPin(SW3_GPIO_Port, SW3_Pin)){ // down
					while (HAL_GPIO_ReadPin(SW3_GPIO_Port, SW3_Pin)) HAL_Delay(1);
					if(Hores_minuts_segons == 0){
						actualDate.Date--;
						if(actualDate.Date > 31) actualDate.Date = 31;
					}
					else if(Hores_minuts_segons == 1){
						actualDate.Month--;
						if(actualDate.Month > 12) actualDate.Month = 12;
					}
					else{
						actualDate.Year--;
						if(actualDate.Year > 99) actualDate.Year = 99;
					}
					sortir_hora = false;
				}
				if(HAL_GPIO_ReadPin(SW4_GPIO_Port, SW4_Pin)){ // right
					while (HAL_GPIO_ReadPin(SW4_GPIO_Port, SW4_Pin)) HAL_Delay(1);
					if(Hores_minuts_segons == 0) Hores_minuts_segons++;
					else if(Hores_minuts_segons == 1) Hores_minuts_segons++;
					else Hores_minuts_segons = 0;
					sortir_hora = false;
				}
				if(HAL_GPIO_ReadPin(SW2_GPIO_Port, SW2_Pin)){ // left
					while (HAL_GPIO_ReadPin(SW2_GPIO_Port, SW2_Pin)) HAL_Delay(1);
					if(Hores_minuts_segons == 0) Hores_minuts_segons = 2;
					else if(Hores_minuts_segons == 1) Hores_minuts_segons--;
					else Hores_minuts_segons--;
					sortir_hora = false;
				}
				if(HAL_GPIO_ReadPin(SW5_GPIO_Port, SW5_Pin)){ // accept
					while (HAL_GPIO_ReadPin(SW5_GPIO_Port, SW5_Pin)) HAL_Delay(1);
					sortir_estructura = false;
					sortir_hora = false;
					HAL_RTC_SetDate(&hrtc, &actualDate, RTC_FORMAT_BIN);
				}
			}

		}

	}
	else{
		HAL_Delay(1);
	}
	ssd1306_Fill(Black);
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


}
