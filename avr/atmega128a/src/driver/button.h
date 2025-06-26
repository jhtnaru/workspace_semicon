#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "../common/def.h"

enum {btnPUSHED, btnRELEASED};        // 기본 시작은 0, 별도 숫자 지정 가능, 지정 다음부터 이어서 숫자
enum {NO_ACT, ACT_PUSH, ACT_RELEASE};

extern uint8_t btnPrev;

typedef struct _button {
    volatile uint8_t    *ddr;           // Register 에 입력, 읽기 등은 volatile 붙여서 최적화 금지
    volatile uint8_t    *pin;           // pin 이라는 Register 에서 값 읽기
    uint8_t             btnPin;
    uint8_t             prevState;
    uint8_t             btnEnabled;
} BUTTON;

void buttonInit(BUTTON *button, volatile uint8_t *ddr, volatile uint8_t *pin, uint8_t pinNumber);
uint8_t buttonGetState(BUTTON *button);

#endif /* __BUTTON_H__ */

/* #define BUTTON_DDR      DDRG
#define BUTTON_PIN      PING
#define BUTTON_ON       1       // Button PORTG에 연결 1, 2, 3, Pull-Up 저항 연결
#define BUTTON_OFF      2
#define BUTTON_TOGGLE   3

enum {PUSHED, RELEASED};        // 기본 시작은 0, 별도 숫자 지정 가능, 지정 다음부터 이어서 숫자
enum {NO_ACT, ACT_PUSH, ACT_RELEASE};

typedef struct _button {
    volatile uint8_t    *ddr;           // Register 에 입력, 읽기 등은 volatile 붙여서 최적화 금지
    volatile uint8_t    *pin;           // pin 이라는 Register 에서 값 읽기
    uint8_t             btnPin;
    uint8_t             prevState;
} BUTTON;

void buttonInit(BUTTON *button, volatile uint8_t *ddr, volatile uint8_t *pin, uint8_t pinNumber);
uint8_t buttonGetState(BUTTON *button);
 */


