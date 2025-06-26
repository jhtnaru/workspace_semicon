/*
 * led.h
 *
 *  Created on: Jun 22, 2025
 *      Author: user16
 */
#ifndef INC_LED_H_
#define INC_LED_H_

#include "main.h"

typedef struct {
	GPIO_TypeDef	*port;
	uint16_t		pinNumber;
	GPIO_PinState	onState;
	GPIO_PinState	offState;
} LED_CONTROL;

void ledInit();

void ledOn(uint8_t num);
void ledOff(uint8_t num);
void ledToggle(uint8_t num);

void ledLeftShift(uint8_t num, uint8_t t);
void ledRightShift(uint8_t num, uint8_t t);
void ledFlower(uint8_t num, uint8_t t);

#endif /* INC_LED_H_ */
