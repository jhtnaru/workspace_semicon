/*
 * led.c
 *
 *  Created on: Jun 12, 2025
 *      Author: user16
 */

#include "led.h"

LED_CONTROL led[8] = {
	{GPIOC, GPIO_PIN_9, GPIO_PIN_SET, GPIO_PIN_RESET},
	{GPIOB, GPIO_PIN_8, GPIO_PIN_SET, GPIO_PIN_RESET},
	{GPIOB, GPIO_PIN_9, GPIO_PIN_SET, GPIO_PIN_RESET},
	{GPIOA, GPIO_PIN_5, GPIO_PIN_SET, GPIO_PIN_RESET},
	{GPIOA, GPIO_PIN_6, GPIO_PIN_SET, GPIO_PIN_RESET},
	{GPIOA, GPIO_PIN_7, GPIO_PIN_SET, GPIO_PIN_RESET},
	{GPIOB, GPIO_PIN_6, GPIO_PIN_SET, GPIO_PIN_RESET},
	{GPIOC, GPIO_PIN_7, GPIO_PIN_SET, GPIO_PIN_RESET}
};

static uint8_t ledPin = 0;
static uint8_t ledState = 0;

void ledInit() {
	for (uint8_t i = 0; i < 8; i++) {
		HAL_GPIO_WritePin(led[i].port, led[i].pinNumber, led[i].offState);
	}
	ledPin = 0;
	ledState = 0;
}

void ledOn(uint8_t num) {
	for (uint8_t i = 0; i < num; i++) {
		HAL_GPIO_WritePin(led[i].port, led[i].pinNumber, led[i].onState);
	}
}

void ledOff(uint8_t num) {
	for (uint8_t i = 0; i < num; i++) {
		HAL_GPIO_WritePin(led[i].port, led[i].pinNumber, led[i].offState);
	}
}

void ledToggle(uint8_t num) {
	for (uint8_t i = 0; i < num; i++) {
		HAL_GPIO_TogglePin(led[i].port, led[i].pinNumber);
	}
}

void ledLeftShift(uint8_t num) {
//	num -= 1;
//	for (uint8_t i = 0; i <= num; i++) {
//		HAL_GPIO_WritePin(led[num - i].port, led[num - i].pinNumber, led[num - i].onState);
//		HAL_Delay(300);
//		HAL_GPIO_WritePin(led[num - i].port, led[num - i].pinNumber, led[num - i].offState);
//		HAL_Delay(300);
//	}

	if (ledPin == 0) {
		if (ledState == 0) {
			HAL_GPIO_WritePin(led[0].port, led[0].pinNumber, led[0].onState);
			ledState = 1;
		}
		else if (ledState == 1) {
			HAL_GPIO_WritePin(led[0].port, led[0].pinNumber, led[0].offState);
			ledState = 0;
			ledPin = 7;
		}
	}
	else {
		if (ledState == 0) {
			HAL_GPIO_WritePin(led[ledPin].port, led[ledPin].pinNumber, led[ledPin].onState);
			ledState = 1;
		}
		else if (ledState == 1) {
			HAL_GPIO_WritePin(led[ledPin].port, led[ledPin].pinNumber, led[ledPin].offState);
			ledState = 0;
			if (num == 8) {
				ledPin--;
			}
			else if (num < 8) {
				if (ledPin == (8 - num)) {
					ledPin = 7;
				}
				else if (ledPin > (8 - num)) {
					ledPin--;
				}
			}
		}
	}
}

void ledRightShift(uint8_t num) {
//	for (uint8_t i = 0; i < num; i++) {
//		HAL_GPIO_WritePin(led[i].port, led[i].pinNumber, led[i].onState);
//		HAL_Delay(300);
//		HAL_GPIO_WritePin(led[i].port, led[i].pinNumber, led[i].offState);
//		HAL_Delay(300);
//	}

	if (ledPin == (num - 1)) {
		if (ledState == 0) {
			HAL_GPIO_WritePin(led[num - 1].port, led[num - 1].pinNumber, led[num - 1].onState);
			ledState = 1;
		}
		else if (ledState == 1) {
		HAL_GPIO_WritePin(led[num - 1].port, led[num - 1].pinNumber, led[num - 1].offState);
			ledState = 0;
			ledPin = 0;
		}
	}
	else {
		if (ledState == 0) {
			HAL_GPIO_WritePin(led[ledPin].port, led[ledPin].pinNumber, led[ledPin].onState);
			ledState = 1;
		}
		else if (ledState == 1) {
			HAL_GPIO_WritePin(led[ledPin].port, led[ledPin].pinNumber, led[ledPin].offState);
			ledState = 0;
			ledPin++;
		}
	}

}

void ledFlower(uint8_t num) {
//	for (uint8_t i = 0; i < num; i++) {
//		HAL_GPIO_WritePin(led[i].port, led[i].pinNumber, led[i].onState);
//		HAL_GPIO_WritePin(led[num - 1 - i].port, led[num - 1 - i].pinNumber, led[num - 1 - i].onState);
//		HAL_Delay(300);
//		HAL_GPIO_WritePin(led[i].port, led[i].pinNumber, led[i].offState);
//		HAL_GPIO_WritePin(led[num - 1 - i].port, led[num - 1 - i].pinNumber, led[num - 1 - i].offState);
//		HAL_Delay(300);
//	}
	if (ledState == 0) {
		HAL_GPIO_WritePin(led[ledPin].port, led[ledPin].pinNumber, led[ledPin].onState);
		HAL_GPIO_WritePin(led[num - ledPin - 1].port, led[num - ledPin - 1].pinNumber, led[num - ledPin - 1].onState);
		ledState = 1;
	}
	else if (ledState == 1) {
		HAL_GPIO_WritePin(led[ledPin].port, led[ledPin].pinNumber, led[ledPin].offState);
		HAL_GPIO_WritePin(led[num - ledPin - 1].port, led[num - ledPin - 1].pinNumber, led[num - ledPin - 1].offState);
		ledState = 0;
		if (ledPin == (num - 1)) {
			ledPin = 0;
		}
		else if (ledPin < (num - 1)) {
			ledPin++;
		}
	}
}
