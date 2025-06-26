// timer8b.c
#include "timer8b.h"

// 8-bit Timer 설정
void t8bInit() {
    TIMER8B_REG |= (1 << WGM00) | (1 << WGM01) | (1 << COM01);      // Fast PWM + Clear Mode
    FPWM_OUT |= (1 << PB4);                                         // PORTB 4 Pin Output 설정
}

// CS02, CS01, CS00 값 입력 받아 분주비 설정
void t8bPrescaler(uint8_t cs2, uint8_t cs1, uint8_t cs0) {
    TIMER8B_REG |= (cs2 << CS02) | (cs1 << CS01) | (cs0 << CS00);
}
