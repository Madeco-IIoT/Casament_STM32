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

void init_RGB (void);
void LED_RGB(uint32_t Color);
void BSP_RTC_SetInitialDateTime(void);
void hora(void);




#endif /* SOURCE_UTILS_H_ */
