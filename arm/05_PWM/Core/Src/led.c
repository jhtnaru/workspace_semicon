/*
 * led.c
 *
 *  Created on: Jun 12, 2025
 *      Author: user16
 */
// led.c
#include "led.h"

LED_CONTROL led[8] = {
	{GPIOC, GPIO_PIN_9, GPIO_PIN_SET, GPIO_PIN_RESET},
	{GPIOB, GPIO_PIN_8, GPIO_PIN_SET, GPIO_PIN_RESET},
	{GPIOB, GPIO_PIN_9, GPIO_PIN_SET, GPIO_PIN_RESET},
	{GPIOA, GPIO_PIN_5, GPIO_PIN_SET, GPIO_PIN_RESET},
	{GPIOA, GPIO_PIN_7, GPIO_PIN_SET, GPIO_PIN_RESET},
	{GPIOB, GPIO_PIN_6, GPIO_PIN_SET, GPIO_PIN_RESET},
	{GPIOC, GPIO_PIN_7, GPIO_PIN_SET, GPIO_PIN_RESET},
	{GPIOA, GPIO_PIN_9, GPIO_PIN_SET, GPIO_PIN_RESET}
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

void ledLeftShift(uint8_t num, uint8_t t) {
	switch (t) {
		case 0:
			if (ledPin <= 0) {
				HAL_GPIO_WritePin(led[0].port, led[0].pinNumber, led[0].onState);
				HAL_GPIO_WritePin(led[num - 1].port, led[num - 1].pinNumber, led[num - 1].offState);
			}
			else {
				HAL_GPIO_WritePin(led[ledPin].port, led[ledPin].pinNumber, led[ledPin].onState);
				HAL_GPIO_WritePin(led[ledPin - 1].port, led[ledPin - 1].pinNumber, led[ledPin - 1].offState);
			}

			if (ledPin >= (num - 1)) {
				ledPin = 0;
			}
			else {
				ledPin++;
			}
			break;

		case 1:
			if (ledPin >= (num - 1)) {
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
			break;
	}
}

void ledRightShift(uint8_t num, uint8_t t) {
	switch (t) {
		case 0:
			if (ledPin >= 7) {
				HAL_GPIO_WritePin(led[7].port, led[7].pinNumber, led[7].onState);
				HAL_GPIO_WritePin(led[8 - num].port, led[8 - num].pinNumber, led[8 - num].offState);
			}
			else {
				HAL_GPIO_WritePin(led[ledPin].port, led[ledPin].pinNumber, led[ledPin].onState);
				HAL_GPIO_WritePin(led[ledPin + 1].port, led[ledPin + 1].pinNumber, led[ledPin + 1].offState);
			}

			if (ledPin <= (8 - num) ) {
				ledPin = 7;
			}
			else {
				ledPin--;
			}
			break;

		case 1:
			if (ledPin <= (8 - num)) {
				if (ledState == 0) {
					HAL_GPIO_WritePin(led[8 - num].port, led[8 - num].pinNumber, led[8 - num].onState);
					ledState = 1;
				}
				else if (ledState == 1) {
				HAL_GPIO_WritePin(led[8 - num].port, led[8 - num].pinNumber, led[8 - num].offState);
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
					ledPin--;
				}
			}
			break;
	}
}

void ledFlower(uint8_t num, uint8_t t) {
	switch (t) {
		case 0:
			if (ledPin == 0) {
				HAL_GPIO_WritePin(led[0].port, led[0].pinNumber, led[0].onState);
				HAL_GPIO_WritePin(led[7].port, led[7].pinNumber, led[7].onState);
				HAL_GPIO_WritePin(led[1].port, led[1].pinNumber, led[1].offState);
				HAL_GPIO_WritePin(led[6].port, led[6].pinNumber, led[6].offState);
				ledPin++;
			}
			else {
				HAL_GPIO_WritePin(led[ledPin].port, led[ledPin].pinNumber, led[ledPin].onState);
				HAL_GPIO_WritePin(led[7 - ledPin].port, led[7 - ledPin].pinNumber, led[7 - ledPin].onState);
				HAL_GPIO_WritePin(led[ledPin - 1].port, led[ledPin - 1].pinNumber, led[ledPin - 1].offState);
				HAL_GPIO_WritePin(led[8 - ledPin].port, led[8 - ledPin].pinNumber, led[8 - ledPin].offState);
				if (ledPin == 3) {
					ledPin = 5;
				}
				else if (ledPin == 6) {
					ledPin = 0;
				}
				else {
					ledPin++;
				}
			}
			break;

		case 1:
			if (ledState == 0) {
				HAL_GPIO_WritePin(led[ledPin].port, led[ledPin].pinNumber, led[ledPin].onState);
				HAL_GPIO_WritePin(led[7 - ledPin].port, led[7 - ledPin].pinNumber, led[7 - ledPin].onState);
				ledState = 1;
			}
			else if (ledState == 1) {
				HAL_GPIO_WritePin(led[ledPin].port, led[ledPin].pinNumber, led[ledPin].offState);
				HAL_GPIO_WritePin(led[7 - ledPin].port, led[7 - ledPin].pinNumber, led[7 - ledPin].offState);
				ledState = 0;
				if (ledPin >= 6) {
					ledPin = 0;
				}
				else if (ledPin == 3) {
					ledPin = 5;
				}
				else {
					ledPin++;
				}
			}
			break;
	}
}
