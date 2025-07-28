/*
 * delay_us.c
 *
 *  Created on: Jul 24, 2025
 *      Author: user16
 */
// delay_us.c
#include "delay_us.h"

// micro 단위 delay 함수
void delay_us(uint16_t us) {
//	uint16_t start = __HAL_TIM_GET_COUNTER(&htim11);
	__HAL_TIM_SET_COUNTER(&htim11, 0);
	while(__HAL_TIM_GET_COUNTER(&htim11) < us);
}

