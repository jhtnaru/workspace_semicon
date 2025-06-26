#ifndef __LED_H__
#define __LED_H__

#include "../common/def.h"

extern uint8_t ledPinNum;
extern uint8_t ledState;
extern uint8_t ledDelay;

void ledInit();

void ledOn();
void ledOff();
void ledToggle();

void ledLeftShift(uint8_t toggle, uint8_t d);
void ledRightShift(uint8_t toggle, uint8_t d);
void ledFlower(uint8_t toggle, uint8_t d);

#endif /* __LED_H__ */



/* // 함수로 LED 동작2 (source file 분할)
void GPIO_Output(uint8_t data);                 // LED 출력 함수
void ledInit();                                 // LED 초기화 함수
void ledShift(uint8_t i, uint8_t *data);        // LED 이동 함수
 */

/* // 구조체, 함수로 LED 동작1(분할)
// port에 대한 설정

#define LED_DDR     DDRD
#define LED_PORT    PORTD

typedef struct {
    volatile uint8_t    *port;
    uint8_t             pinNumber;
} LED;

// 함수의 원형 선언

void ledInit(LED *led);
void ledOn(LED *led);
void ledOff(LED *led); */

/* // 구조체, 함수로 LED 동작2(분할)
// port에 대한 설정

#define LED_DDR     DDRD
#define LED_PORT    PORTD

typedef struct {
    volatile uint8_t    *port;
    uint8_t             pinNumber;
} LED;

// 함수의 원형 선언

void ledInit(LED *led);
void ledOn(LED *led);
void ledOff(LED *led);

void ledLeftShift(LED *led);
void ledRightShift(LED *led);
void ledFlower(LED *led);
void ledOdd(LED *led);
void ledEven(LED *led);
 */

 /* // 버튼으로 PORTD LED 켜기2(분할)
// port에 대한 설정

#define LED_DDR     DDRD
#define LED_PORT    PORTD

typedef struct {
    volatile uint8_t    *port;
    uint8_t             pinNumber;
    double              delayTime;
} LED;

// 함수의 원형 선언

void ledInit(LED *led);
void ledOn(LED *led);
void ledOff(LED *led);

void ledLeftShift(LED *led);
void ledRightShift(LED *led);
void ledFlower(LED *led);
void ledOdd(LED *led);
void ledEven(LED *led); */

