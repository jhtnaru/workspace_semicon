// button.c
#include "button.h"

uint8_t btnPrev = 1;        // Button 4 Spin 을 Off 했을 때 이전 버튼 상태를 기억해서 표현하기 위한 변수

void buttonInit(BUTTON *button, volatile uint8_t *ddr, volatile uint8_t *pin, uint8_t pinNumber) {
    button->ddr = ddr;
    button->pin = pin;
    button->btnPin = pinNumber;
    button->btnEnabled = 0;
    button->prevState = btnRELEASED;       // 아무것도 안누른 초기화 상태
    *button->ddr &= ~(1 << button->btnPin);     // button pin을 input 설정
    // BUTTON_DDR &= ~(1 << pinNumber);
}

uint8_t buttonGetState(BUTTON *button) {    // BUTTON *button --> ddr, pin 주소 받기 위해 이용
    uint8_t curState = *button->pin & (1 << button->btnPin);        // 버튼 상태를 읽어옴, close 0, open 1(기본 상태)

    if ((curState == btnPUSHED) && (button->prevState == btnRELEASED)) {
        _delay_ms(50);                      // Debounce code
        button->prevState = btnPUSHED;      // Button 누름 상태 변경
        return ACT_PUSH;                    // Button 누름을 반환
    }
    else if ((curState != btnPUSHED) && (button->prevState == btnPUSHED)) {
        _delay_ms(50);                      // Debounce code
        button->prevState = btnRELEASED;    // Button 안누름 상태 변경
        return ACT_RELEASE;                 // Button 안누름을 반환
    }
    return NO_ACT;
}