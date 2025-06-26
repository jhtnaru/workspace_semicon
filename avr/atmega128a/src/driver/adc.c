// adc.c
#include "adc.h"

uint8_t val_t;

// ADC 기능을 켜고 Pin, Prescaler 지정을 해주는 함수
void adcInit() {
    ADC_SELECT |= (1 << MUX2) | (1 << MUX1) | (1 << MUX0);          // ADC 7 Pin 을 Input 설정
    ADC_CONTROL |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);      // ADC Prescaler 를 128 로 설정, 50 ~ 200kHz 권장, 16MHz / 128분주 = 125KHz
    ADC_CONTROL |= (1 << ADEN);                                     // ADC 켜기
}

// Analog to Digital Convert 시작 함수
void adcConvert() {
    ADC_CONTROL |= (1 << ADSC);             // ADC 변환 시작
    while (ADC_CONTROL & (1<< ADSC)) {      // ADC 변환이 확실히 될때까지 기다리기

    }
}

// ADC에서 받은 10-bit 값을 구간을 나누어 8-bit 값으로 변환
uint8_t adcTrans(uint16_t val, uint8_t val_i) {
    // 구간은 필요에 따라 세분화
    if (val < 100) {
        val_t = 0;
    }
    else if (val > 150 && val < 300) {
        val_t = val_i;
    }
    else if (val > 350 && val < 500) {
        val_t = val_i * 2;
    }
    else if (val > 550 && val < 700) {
        val_t = val_i * 3;
    }
    else if (val > 750 && val < 900) {
        val_t = val_i * 4;
    }
    else if (val > 950) {
        val_t = val_i * 5;
    }

    return val_t;
}