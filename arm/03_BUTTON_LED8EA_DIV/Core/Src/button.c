/*
 * button.c
 *
 *  Created on: Jun 16, 2025
 *      Author: user16
 */
// button.c
#include "button.h"

BUTTON_CONTROL button[3] = {
		{GPIOC, GPIO_PIN_8, 0},
		{GPIOC, GPIO_PIN_6, 0},
		{GPIOC, GPIO_PIN_5, 0}
};

/*// HAL_Delay 함수 사용
bool buttonGetPressed(uint8_t num) {
	bool ret = false;

	if (HAL_GPIO_ReadPin(button[num].port, button[num].pinNumber) == button[num].onState) {
		HAL_Delay(30);		// Debounce Time
		if (HAL_GPIO_ReadPin(button[num].port, button[num].pinNumber) == button[num].onState) {
			ret = true;
		}
	}

	return ret;
}*/

/*// HAL_GetTick 함수 사용
bool buttonGetPressed(uint8_t num) {
	static uint32_t prevTime = 0;

	bool ret = false;

	if(HAL_GPIO_ReadPin(button[num].port, button[num].pinNumber) == button[num].onState) {
		uint32_t currTime = HAL_GetTick();

		if(currTime - prevTime > 30) {
			if(HAL_GPIO_ReadPin(button[num].port, button[num].pinNumber) == button[num].onState) {
				ret = true;
			}
			prevTime = currTime;
		}
	}

	return ret;
}*/

/*// HAL_GetTick 함수 사용, 처음부터 Debounce=
bool buttonGetPressed(uint8_t num) {
	static uint32_t prevTime = 0xffffffff;		// 초기값을 최대치로 설정

	if(prevTime == 0xffffffff) {
		prevTime = HAL_GetTick();				// prevTime 초기화 작업
	}

	bool ret = false;

	if(HAL_GPIO_ReadPin(button[num].port, button[num].pinNumber) == button[num].onState) {
		uint32_t currTime = HAL_GetTick();

		if(currTime - prevTime > 30) {
			if(HAL_GPIO_ReadPin(button[num].port, button[num].pinNumber) == button[num].onState) {
				ret = true;
			}
			prevTime = currTime;
		}
	}

	return ret;
}*/

// 각 배열별로 Debounce Code 입력
bool buttonGetPressed(uint8_t num) {
	static uint32_t prevTime[3] = {0xffffffff};		// 초기값을 최대치로 설정

	if(prevTime[num] == 0xffffffff) {
		prevTime[num] = HAL_GetTick();				// prevTime 초기화 작업
	}

	bool ret = false;

	if(HAL_GPIO_ReadPin(button[num].port, button[num].pinNumber) == button[num].onState) {
		uint32_t currTime = HAL_GetTick();

		if(currTime - prevTime[num] > 150) {
			if(HAL_GPIO_ReadPin(button[num].port, button[num].pinNumber) == button[num].onState) {
				ret = true;
			}
			prevTime[num] = currTime;
		}
	}

	return ret;
}
