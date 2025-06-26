/*
 * buzzer.c
 *
 *  Created on: Jun 23, 2025
 *      Author: user16
 */
// buzzer.c
#include "buzzer.h"

// 음별 분주비, 낮은 도, 레, 미, 파, 솔, 라, 시, 높은 도
uint16_t bzScale[8] = {
		383, 340, 303, 286, 255, 227, 202, 191
};

// scale 0 ~ 7 낮은 도 ~ 높은 도, volume 소리 크기 0 ~ 1000
void bzSound(uint8_t scale, uint16_t volume) {
	BUZZER_PSC = bzScale[scale];
	BUZZER_CCR = volume;
}
