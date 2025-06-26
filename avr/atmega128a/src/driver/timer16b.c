// timer16b.c
#include "timer16b.h"

// 16-bit Timer 설정
void t16bInit() {         
    TIMER16B_REGA |= (1 << WGM11) | (1 << COM1A1);      // Fast PWM + Clear Mode
    TIMER16B_REGB |= (1 << WGM12) | (1 << WGM13);
    TIMER16B_TOP = 4999;                                // TOP = (16MHz / (64분주 * (50Hz 설정))) - 1
    FPWM_OUT |= (1 << PB5);                             // PORTB 5 Pin Output 설정
}

// CS02, CS01, CS00 값 입력 받아 분주비 설정
void t16bPrescaler(uint8_t cs2, uint8_t cs1, uint8_t cs0) {   
    TIMER16B_REGB |= (cs2 << CS12) | (cs1 << CS11) | (cs0 << CS10);
}