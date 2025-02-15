/*
 * hora.h
 *
 *  Created on: Sep 28, 2024
 *      Author: sobra
 */

#ifndef HORA_H_
#define HORA_H_

#include "main.h"
#include "stdbool.h"
#include "ssd1306.h"

void actualitzar_hora(void);
void hora(void);
void BSP_RTC_SetInitialDateTime(void);

#endif /* HORA_H_ */
