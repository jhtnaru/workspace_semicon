/*
 * delay_us.c
 *
 *  Created on: Jun 16, 2025
 *      Author: user16
 */
// delay.c
#include "delay_us.h"

void delay_us(uint16_t us) {
	__HAL_TIM_SET_COUNTER(&htim11, 0);		// 호출하면 Count 0 부터 다시 시작
	while ((__HAL_TIM_GET_COUNTER(&htim11)) < us);
}

