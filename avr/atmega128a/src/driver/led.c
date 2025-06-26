// led.c
#include "led.h"

uint8_t ledPinNum;
uint8_t ledState;
uint8_t ledDelay;

// LED 출력 설정 초기화 함수
void ledInit() {        // 매개변수로 포인터변수 선언
    LED_DDR = 0xff;             // LED Port Output 설정
    ledPinNum = 0;
    ledState = 0;
    ledDelay = 0;
}

// 전체 LED On 함수
void ledOn() {
    for (uint8_t i = 0; i < 8; i++) {
        LED_PORT |= (1 << i);
    }
}

// 전체 LED Off 함수
void ledOff() {
    for (uint8_t i = 0; i < 8; i++) {
        LED_PORT &= ~(1 << i);
    }
}

// 전체 LED On, Off 전환 함수
void ledToggle() {
    uint8_t i;

    if (ledState == 0) {
        for (i = 0; i < 8; i++) {
            LED_PORT |= (1 << i);
        }
        ledState = 1;
    }
    else if (ledState == 1) {
        for (i = 0; i < 8; i++) {
            LED_PORT &= ~(1 << i);
        }
        ledState = 0;
    }
}

// LED 왼쪽 이동하며 On 함수
// toggle set 깜빡이며 이동, d 값에 따라 delay 시간 조정
void ledLeftShift(uint8_t toggle, uint8_t d) {
    switch (toggle) {
        case 0:
        if (ledPinNum <=0) {
            LED_PORT |= (1 << 0);
            LED_PORT &= ~(1 << 7);
        }
        else {
            LED_PORT |= (1 << ledPinNum);
            LED_PORT &= ~(1 << (ledPinNum - 1));
        }

        if (ledDelay >= d) {
            if (ledPinNum >= 7) {
                ledPinNum = 0;
            }
            else {
                ledPinNum++;
            }
            ledDelay = 0;
        }
        else {
            ledDelay++;
        }
        break;
    
        case 1:
        if (ledState == 0) {
            LED_PORT |= (1 << ledPinNum);
            if (ledDelay >= d) {
                ledState = 1;
                ledDelay = 0;
            }
            else {
                ledDelay++;
            }
        }

        else if (ledState == 1) {
            LED_PORT &= ~(1 << ledPinNum);
            if (ledDelay >= d) {
                ledState = 0;
                if (ledPinNum >= 7) {
                    ledPinNum = 0;
                }
                else {
                    ledPinNum++;
                }
                ledDelay = 0;
            }
            else {
                ledDelay++;
            }
        }
        break;
    }
}

// LED 오른쪽 이동하며 On 함수
// toggle set 깜빡이며 이동, d 값에 따라 delay 시간 조정
void ledRightShift(uint8_t toggle, uint8_t d) {
    switch (toggle) {
        case 0:
        if (ledPinNum >= 7) {
            LED_PORT |= (1 << 7);
            LED_PORT &= ~(1 << 0);
        }
        else {
            LED_PORT |= (1 << ledPinNum);
            LED_PORT &= ~(1 << (ledPinNum + 1));
        }

        if (ledDelay >= d) {
            if (ledPinNum <= 0) {
                ledPinNum = 7;
            }
            else {
                ledPinNum--;
            }
            ledDelay = 0;
        }
        else {
            ledDelay++;
        }
        break;
    
        case 1:
        if (ledState == 0) {
            LED_PORT |= (1 << ledPinNum);
            if (ledDelay >= d) {
                ledState = 1;
                ledDelay = 0;
            }
            else {
                ledDelay++;
            }
        }

        else if (ledState == 1) {
            LED_PORT &= ~(1 << ledPinNum);
            if (ledDelay >= d) {
                ledState = 0;
                if (ledPinNum <= 0) {
                    ledPinNum = 7;
                }
                else {
                    ledPinNum--;
                }
                ledDelay = 0;
            }
            else {
                ledDelay++;
            }
        }
        break;
    }

}

// LED 좌우에서 동시에 이동하며 On 함수
// toggle set 깜빡이며 이동, d 값에 따라 delay 시간 조정
void ledFlower(uint8_t toggle, uint8_t d) {
    switch (toggle) {
        case 0:
        if (ledPinNum <=0) {
            LED_PORT |= (1 << 0) | (1 << 7);
        }
        else {
            LED_PORT |= (1 << ledPinNum) | (1 << (7 - ledPinNum));;
            LED_PORT &= ~((1 << (ledPinNum - 1)) | (1 << (8 - ledPinNum)));
        }
        
        if (ledDelay >= d) {
            if (ledPinNum >= 7) {
                ledPinNum = 1;
            }
            else if (ledPinNum == 3) {
                ledPinNum = 5;
            }
            else {
                ledPinNum++;
            }
            ledDelay = 0;
        }
        else {
            ledDelay++;
        }
        break;

        case 1:
        if (ledState == 0) {
            LED_PORT |= (1 << ledPinNum) | (1 << (7 - ledPinNum));
            if (ledDelay >= d) {
                ledState = 1;
                ledDelay = 0;
            }
            else {
                ledDelay++;
            }
        }
        else if (ledState == 1) {
            LED_PORT &= ~((1 << ledPinNum) | (1 << (7 - ledPinNum)));
            if (ledDelay >= d) {
                ledState = 0;
                if (ledPinNum >= 7) {
                    ledPinNum = 0;
                }
                else {
                    ledPinNum++;
                }
                ledDelay = 0;
            }
            else {
                ledDelay++;
            }
        }
        break;
    }
}


/* // 함수로 LED 동작2 (source file 분할)
// LED 출력 함수
void GPIO_Output(uint8_t data) {        // LED 포트에 8bit data를 매개변수로 받음
    LED_PORT = data;        // 매개변수로 받은 data를 LED port에 대입
}

// LED 초기화 함수
void ledInit() {
    LED_DDR = 0xff;    // 모든 PORTD를 출력 설정
}

// LED 이동 함수
void ledShift(uint8_t i, uint8_t *data) {   // 포인터 선언
    *data = (1 << i) | (1 << (7 - i));
} */

/* // 구조체, 함수로 LED 동작1(분할)
#include "led.h"

void ledInit(LED *led) {        // 매개변수로 포인터변수 선언
    // LED_DDR = 0xff;
    
    *(led->port - 1) |= (1 << led->pinNumber);
    // DDR 레지스터는 PORT 레지스터보다 1 낮게 위치하므로
    // *(led->port - 1)을 이용해 PORT 에서 DDR 로 접근
    // (1 << led->pinNumber)을 OR 연산을 통해
    // led->pinNumber로 지정된 포트를 출력으로 설정
}

void ledOn(LED *led) {
    // 해당 핀(원하는 자리)을 high 로 설정해서 LED on
    *(led->port) |= (1 << led->pinNumber);
    _delay_ms(300);
}

void ledOff(LED *led) {
    // 해당 핀(원하는 자리)을 low 로 설정해서 LED off
    *(led->port) &= ~(1 << led->pinNumber);
    *(led->port - 1) &= ~(1 << led->pinNumber);
    _delay_ms(300);
} */

/* // 구조체, 함수로 LED 동작2(분할)
#include "led.h"

void ledInit(LED *led) {        // 매개변수로 포인터변수 선언
    // LED_DDR = 0xff;
    
    *(led->port - 1) |= (1 << led->pinNumber);
    // DDR 레지스터는 PORT 레지스터보다 1 낮게 위치하므로
    // *(led->port - 1)을 이용해 PORT 에서 DDR 로 접근
    // (1 << led->pinNumber)을 OR 연산을 통해
    // led->pinNumber로 지정된 포트를 출력으로 설정
}

void ledOn(LED *led) {
    // 해당 핀(원하는 자리)을 high 로 설정해서 LED on
    *(led->port) |= (1 << led->pinNumber);
    _delay_ms(300);
}

void ledOff(LED *led) {
    // 해당 핀(원하는 자리)을 low 로 설정해서 LED off
    *(led->port) &= ~(1 << led->pinNumber);
    *(led->port - 1) &= ~(1 << led->pinNumber);
    _delay_ms(300);
}

void ledLeftShift(LED *led) {    
    *(led->port - 1) |= (1 << led->pinNumber);
    *(led->port) |= (1 << led->pinNumber);
    _delay_ms(300);

    *(led->port) &= ~(1 << led->pinNumber);
    *(led->port - 1) &= ~(1 << led->pinNumber);
    _delay_ms(300);

    led->pinNumber++;

    if (led->pinNumber > 7)    {
        led->pinNumber = 0;
    }
}

void ledRightShift(LED *led) {
    if (led->pinNumber == 0)     {
        led->pinNumber = 8;
    }
    led->pinNumber--;

    *(led->port - 1) |= (1 << led->pinNumber);
    *(led->port) |= (1 << led->pinNumber);
    _delay_ms(300);

    *(led->port) &= ~(1 << led->pinNumber);
    *(led->port - 1) &= ~(1 << led->pinNumber);
    _delay_ms(300);    
}

void ledFlower(LED *led) {
    *(led->port - 1) |= (1 << led->pinNumber);
    *(led->port) |= (1 << led->pinNumber);
    *(led->port - 1) |= (1 << (7 - led->pinNumber));
    *(led->port) |= (1 << 7 - (led->pinNumber));
    _delay_ms(300);

    *(led->port) &= ~(1 << led->pinNumber);
    *(led->port - 1) &= ~(1 << led->pinNumber);
    *(led->port) &= ~(1 << (7 - led->pinNumber));
    *(led->port - 1) &= ~(1 << (7 - led->pinNumber));
    _delay_ms(300);

    led->pinNumber++;
    if (led->pinNumber > 7)    {
        led->pinNumber = 0;
    }
}

void ledOdd(LED *led) {
    for (uint8_t i = 0; i < 4; i++)    {
        led->pinNumber = i * 2 + 1;
        *(led->port - 1) |= (1 << led->pinNumber);
        *(led->port) |= (1 << led->pinNumber);
    }
    _delay_ms(300);
    
    for (uint8_t i = 0; i < 4; i++)    {
        led->pinNumber = i * 2 + 1;
        *(led->port) &= ~(1 << led->pinNumber);
        *(led->port - 1) &= ~(1 << led->pinNumber);
    }
    _delay_ms(300);
}

void ledEven(LED *led) {
    for (uint8_t i = 0; i < 4; i++)    {
        led->pinNumber = i * 2;
        *(led->port - 1) |= (1 << led->pinNumber);
        *(led->port) |= (1 << led->pinNumber);
    }
    _delay_ms(300);
    
    for (uint8_t i = 0; i < 4; i++)    {
        led->pinNumber = i * 2;
        *(led->port) &= ~(1 << led->pinNumber);
        *(led->port - 1) &= ~(1 << led->pinNumber);
    }
    _delay_ms(300);
} */

/* // 버튼으로 PORTD LED 켜기2(분할)
void ledInit(LED *led) {        // 매개변수로 포인터변수 선언
    // LED_DDR = 0xff;
    
    *(led->port - 1) |= (1 << led->pinNumber);
    // DDR 레지스터는 PORT 레지스터보다 1 낮게 위치하므로
    // *(led->port - 1)을 이용해 PORT 에서 DDR 로 접근
    // (1 << led->pinNumber)을 OR 연산을 통해
    // led->pinNumber로 지정된 포트를 출력으로 설정
}

void ledOn(LED *led) {
    // 해당 핀(원하는 자리)을 high 로 설정해서 LED on
    *(led->port) |= (1 << led->pinNumber);
    _delay_ms(led->delayTime);
}

void ledOff(LED *led) {
    // 해당 핀(원하는 자리)을 low 로 설정해서 LED off
    *(led->port) &= ~(1 << led->pinNumber);
    *(led->port - 1) &= ~(1 << led->pinNumber);
    _delay_ms(led->delayTime);
}

void ledLeftShift(LED *led) {    
    *(led->port - 1) |= (1 << led->pinNumber);
    *(led->port) |= (1 << led->pinNumber);
    _delay_ms(led->delayTime);

    *(led->port) &= ~(1 << led->pinNumber);
    *(led->port - 1) &= ~(1 << led->pinNumber);
    _delay_ms(led->delayTime);

    led->pinNumber++;

    if (led->pinNumber > 7)    {
        led->pinNumber = 0;
    }
}

void ledRightShift(LED *led) {
    if (led->pinNumber == 0)     {
        led->pinNumber = 8;
    }
    led->pinNumber--;

    *(led->port - 1) |= (1 << led->pinNumber);
    *(led->port) |= (1 << led->pinNumber);
    _delay_ms(led->delayTime);

    *(led->port) &= ~(1 << led->pinNumber);
    *(led->port - 1) &= ~(1 << led->pinNumber);
    _delay_ms(led->delayTime);    
}

void ledFlower(LED *led) {
    *(led->port - 1) |= (1 << led->pinNumber);
    *(led->port) |= (1 << led->pinNumber);
    *(led->port - 1) |= (1 << (7 - led->pinNumber));
    *(led->port) |= (1 << 7 - (led->pinNumber));
    _delay_ms(led->delayTime);

    *(led->port) &= ~(1 << led->pinNumber);
    *(led->port - 1) &= ~(1 << led->pinNumber);
    *(led->port) &= ~(1 << (7 - led->pinNumber));
    *(led->port - 1) &= ~(1 << (7 - led->pinNumber));
    _delay_ms(led->delayTime);

    led->pinNumber++;
    if (led->pinNumber > 7)    {
        led->pinNumber = 0;
    }
}

void ledOdd(LED *led) {
    for (uint8_t i = 0; i < 4; i++)    {
        led->pinNumber = i * 2 + 1;
        *(led->port - 1) |= (1 << led->pinNumber);
        *(led->port) |= (1 << led->pinNumber);
    }
    _delay_ms(led->delayTime);
    
    for (uint8_t i = 0; i < 4; i++)    {
        led->pinNumber = i * 2 + 1;
        *(led->port) &= ~(1 << led->pinNumber);
        *(led->port - 1) &= ~(1 << led->pinNumber);
    }
    _delay_ms(led->delayTime);
}

void ledEven(LED *led) {
    for (uint8_t i = 0; i < 4; i++)    {
        led->pinNumber = i * 2;
        *(led->port - 1) |= (1 << led->pinNumber);
        *(led->port) |= (1 << led->pinNumber);
    }
    _delay_ms(led->delayTime);
    
    for (uint8_t i = 0; i < 4; i++)    {
        led->pinNumber = i * 2;
        *(led->port) &= ~(1 << led->pinNumber);
        *(led->port - 1) &= ~(1 << led->pinNumber);
    }
    _delay_ms(led->delayTime);
} */
