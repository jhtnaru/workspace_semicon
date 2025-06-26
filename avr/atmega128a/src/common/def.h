#ifndef __DEF_H__
#define __DEF_H__

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

// LED 연결 Port
#define LED_DDR             DDRD
#define LED_PORT            PORTD

// FND 1자리 연결 Port
#define FND_DDR             DDRC
#define FND_PORT            PORTC

// FND 4자리 연결 Port
#define FND4_DDR            DDRA
#define FND4_PORT           PORTA
#define FND4_SELECT_DDR     DDRB
#define FND4_SELECT_PORT    PORTB

// Button 연결 Port, Pull-Up 저항 연결
#define BUTTON_DDR          DDRG
#define BUTTON_PIN          PING

#define BUTTON_1            0
#define BUTTON_2            1
#define BUTTON_3            2
#define BUTTON_4            3

// Timer Register
#define FPWM_OUT            DDRB
#define TIMER8B_REG         TCCR0
#define TIMER8B_OCR         OCR0
#define TIMER16B_REGA       TCCR1A
#define TIMER16B_REGB       TCCR1B
#define TIMER16B_TOP        ICR1
#define TIMER16B_OCR        OCR1A

// ADC Register
#define ADC_SELECT          ADMUX
#define ADC_CONTROL         ADCSRA

#endif /* __DEF_H__ */