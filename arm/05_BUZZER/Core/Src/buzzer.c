/*
 * buzzer.c
 *
 *  Created on: Jun 23, 2025
 *      Author: user16
 */
// buzzer.c
#include "buzzer.h"

uint16_t bzScale[8] = {
		382, 341, 303, 286, 255, 227, 202, 191
};


void bzSound(uint8_t scale, uint16_t volume) {
	BUZZER_PSC = bzScale[scale];
	BUZZER_CCR = volume;
}
