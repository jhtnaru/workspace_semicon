// main.c
#include "src/ap/ap.h"

int main () {
    apInit();

    apMain();

    while (1)    {

    }
}


/* // LED 8개 전부 점멸
int main() {
    DDRD = 0xff;

    while (1)    {
        PORTD = 0x00;
        _delay_ms(500);
        PORTD = 0xff;
        _delay_ms(500);
    }
} */

/* // LED 1개씩 점멸
#define LED_DDR     DDRD
#define LED_PORT    PORTD

int main() {
    LED_DDR = 0xff;     // D port를 출력으로 설정
    // LED_DDR = 0b11111111;
    
    while (1)    {
        for (uint8_t i = 0; i < 8; i++)        {
            // LED_PORT |= (1 << i);       // LED 1개씩 채워가며 점멸
            LED_PORT = (1 << i);        // LED 1개씩 이동하며 점멸
            _delay_ms(1000);            // 0.001초 정도 되면 거의 켜있는 상태로 보임
        }
        // LED_PORT = 0x00;
        // _delay_ms(1000);
    }
} */

/* // LED 채우기1
uint8_t ledArr[] = {
    0x00,       // 00000000
    0x80,       // 10000000
    0xC0,       // 11000000
    0xE0,       // 11100000
    0xF0,       // 11110000
    0xF8,       // 11111000
    0xFC,       // 11111100
    0xFE,       // 11111110
    0xFF,       // 11111111
    0x7F,       // 01111111
    0x3F,       // 00111111
    0x1F,       // 00011111
    0x0F,       // 00001111
    0x07,       // 00000111
    0x03,       // 00000011
    0x01        // 00000001
};

int main() {
    DDRD = 0xFF;
    uint8_t arrSize = sizeof(ledArr) / sizeof(ledArr[0]);
    // uint8_t는 8bit = 1byte 단위, unsigned interger 8bit
    // sizeof(ledArr) == 16, sizeof(ledArr[0]) == 1, int 라면 sizeof(ledArr[0]) == 4

    while (1)    {
        for (uint8_t i = 0; i < arrSize; i++)        {
            PORTD = ledArr[i];
            _delay_ms(200);
        }
    }
} */

/* // LED 채우고 비우기
int main() {
    DDRD = 0xFF;

    while (1)    {
        for (uint8_t i = 0; i < 8; i++)        {
            PORTD |= (0x80 >> i);
            _delay_ms(200);
        }
        for (uint8_t i = 0; i < 8; i++)        {
            // PORTD &= (0x7F >> i);
            PORTD &= ~(0x80 >> i);
            _delay_ms(200);
        }
    }
} */

/* // LED 양쪽 이동 점멸
#define LED_DDR     DDRD
#define LED_PORT    PORTD

int main () {
    LED_DDR = 0xFF;     // 출력 설정 0b11111111

    while (1)    {
        // for (uint8_t i = 0; i < 4; i++)        {
        //     LED_PORT = ((0x01 << i) | (0x80 >> i));
        //     _delay_ms(300);
        // }

        // for (uint8_t i = 0; i < 4; i++)        {
        //     LED_PORT = ((0x08 >> i) | (0x10 << i));
        //     _delay_ms(300);
        // }        

        for (uint8_t i = 0; i < 8; i++)        {
            if (i == 3)            {
                i++;
            }
            
            LED_PORT = ((0x01 << i) | (0x80 >> i));
            _delay_ms(300);
        }
        
    }    
} */

/* // 함수로 LED 동작1(분할)
#include "led.h"

int main() {
    ledInit();
        
    while (1)    {
        GPIO_Output(0x00);
        _delay_ms(500);
        GPIO_Output(0xff);
        _delay_ms(500);
    }
} */

/* // 함수로 LED 동작2 (source file 분할)
#include "led.h"

int main() {
    ledInit();

    uint8_t ledData = 0x81;
    
    while (1)    {
        for (uint8_t i = 0; i < 8; i++)        {
            ledShift(i, &ledData);
            GPIO_Output(ledData);
            _delay_ms(300);
        }
    }
} */

/* // 구조체, 함수로 LED 동작1(분할)
#include "src/led.h"

int main() {
    LED led;
    led.port = &PORTD;
    led.pinNumber = 0;

    while (1)    {
        for (uint8_t i = 0; i < 8; i++)        {
            led.pinNumber = i;

            ledInit(&led);      
            
            ledOn(&led);
            _delay_ms(500);
            ledOff(&led);
            _delay_ms(500);
        }
    }
} */

/* // 구조체, 함수로 LED 동작2(분할)
#include "src/led.h"

int main() {
    LED led;
    led.port = &PORTD;

    led.pinNumber = 0;

    while (1)    {
        // ledInit(&led);      
            
        // ledOn(&led);
        // ledOff(&led);
    
        led.pinNumber = 0;
        for (int i = 0; i < 8; i++)        {
            ledLeftShift(&led);
        }
        
        led.pinNumber = 0;
        for (int i = 0; i < 8; i++)        {
            ledRightShift(&led);
        }
        
        led.pinNumber = 0;
        for (int i = 0; i < 8; i++)        {
            ledFlower(&led);
        }
        
        ledOdd(&led);
        
        ledEven(&led);
    }
} */

/* // 한자리 8 LED 1 ~ 8 켜기
#include "src/led.h"

int main() {
    uint8_t fndNumber[] = {
                    // .GFEDCBA .GFEDCBA
        0x3f,       // 00111111 --FEDCBA 0
        0x06,       // 00000110 -----CB- 1
        0x5b,       // 01011011 -G-ED-BA 2
        0x4f,       // 01001111 -G--DCBA 3
        0x66,       // 01100110 -GF--CB- 4
        0x6d,       // 01101101 -GF-DC-A 5
        0x7d,       // 01111101 -GFEDC-A 6
        0x27,       // 00100111 --F--CBA 7
        0x7f,       // 01111111 -GFEDCBA 8
        0x67        // 01100111 -GF--CBA 9
    };
    
    uint16_t count = 0;     // int count = 0; 2byte(c언어에서는 4byte)
    DDRA = 0xff;            //  FND 연결한 포트    

    while (1)    {
        // PORTA = fndNumber[count];
        count = (count + 1) % 10;
        _delay_ms(500);
    }
} */

/* // 네자리 8 LED 1 ~ 8 켜기
#include "src/led.h"

// 상수 선언

#define FND_DATA_DDR        DDRB    // 실질적인 data port
#define FND_SELECT_DDR      DDRC    // digit select port
#define FND_DATA_PORT       PORTB
#define FND_SELECT_PORT     PORTC

// 함수 원형 선언

void FND_Display(int16_t data);

int main() {
    FND_DATA_DDR = 0xff;        // data port 출력 설정 (PORTB 0 ~ 7)
    FND_SELECT_DDR = 0xff;      // digit select port 출력 설정 (PORTC 0 ~ 3)
    FND_SELECT_PORT = 0x00;     // digit select port 

    uint16_t count = 0;         // 16bit(0~65535)
    uint32_t timeTick = 0;      // 32bit(0 ~ 42억...)
    uint32_t prevTime = 0;

    while (1)    {
        FND_Display(count);
        if (timeTick - prevTime >= 100) {    // count 를 100ms 마다 1 증가
            prevTime = timeTick;            // 현재 시간을 pervTime 에 저장
            count++;
            if (count == 10000) {
                count = 0;
            }
            
        }
        _delay_ms(1);                       // 1ms 대기
        timeTick++;                         // timeTick 을 1ms 마다 1 증가
    }
}

void FND_Display(int16_t data) {        // FND 숫자 표출 함수
    static uint8_t position = 0;         // digit position
    uint8_t fndData[10] = {
        0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f, 0x67
    };
    
    uint8_t fndData10[10] = {0, };
    //     0xbf, 0x86, 0xdb, 0xcf, 0xe6, 0xed, 0xfd, 0xa7, 0xff, 0xe7

    for (int i = 0; i < 10; i++) {
        fndData10[i] |= fndData[i] | 0x80;
    }
    
    switch (position) {     // 조건식은 정수값
    case 0:
        // 첫번째 자리의 FND data를 출력하기 위해 0번 pin Low, 1, 2, 3번 pin High
        FND_SELECT_PORT &= ~(1 << 0);
        FND_SELECT_PORT |= (1 << 1) | (1 << 2) | (1 << 3);
        // 입력된 데이터 천의 자리를 구해서 해당 FND data 출력
        FND_DATA_PORT = fndData[(data / 1000) % 10];
        break;

    case 1:
        // 두번째 자리의 FND data를 출력하기 위해 1번 pin Low, 0, 2, 3번 pin High
        FND_SELECT_PORT &= ~(1 << 1);
        FND_SELECT_PORT |= (1 << 0) | (1 << 2) | (1 << 3);
        // 입력된 데이터 백의 자리를 구해서 해당 FND data 출력
        FND_DATA_PORT = fndData[(data / 100) % 10];
        break;
    
    case 2:
        // 세번째 자리의 FND data를 출력하기 위해 2번 pin Low, 0, 1, 3번 pin High
        FND_SELECT_PORT &= ~(1 << 2);
        FND_SELECT_PORT |= (1 << 0) | (1 << 1) | (1 << 3);
        // 입력된 데이터 십의 자리를 구해서 해당 FND data 출력
        FND_DATA_PORT = fndData10[((data / 10) % 10)];
        break;
    
    case 3:
        // 네번째 자리의 FND data를 출력하기 위해 3번 pin Low, 0, 1, 2번 pin High
        FND_SELECT_PORT &= ~(1 << 3);
        FND_SELECT_PORT |= (1 << 0) | (1 << 1) | (1 << 2);
        // 입력된 데이터 일의 자리를 구해서 해당 FND data 출력
        FND_DATA_PORT = fndData[data % 10];
        break;
    }

    position++;         // 다음 자리로 이동하기 위해 posion 을 1 증가
    position = position % 4;
} */

/* // 비트마스킹
// 비트를 제어할 때
// 원하는 위치에 1을 넣고 싶으면
// 원하는 위치만큼 1을 SHIFT 해서 OR 연산
// PORTA 4번에 1을 넣고 싶으면 PORTA |= (1 << 4);

// 원하는 위치에 0을 넣고 싶으면
// 원하는 위치만큼 1을 SHIFT 하고 NOT 연산 해서 AND 연산
// PORTA 4번에 0을 넣고 싶으면 PORTA &= ~(1 << 4);

// 원하는 위치에 현재 값을 확인하는 방법
// 원하는 위치만큼 1을 SHIFT 하고 AND 연산
// PORTA 4번의 값을 알고 싶으면 PORTA &= (1 << 4); */

/* // 버튼으로 PORTD LED 켜기1
#include "src/led.h"

// Button 을 PORTG 1, 2, 3에 연결
// Pull-Up 저항 연결, open 1, close 0

int main() {
    DDRD = 0xff;            // LED 연결된 곳

    DDRG &= ~(1 << 1);      // PORTG 1번 pin을 입력으로 설정

    while (1)    {
        if (PING & (1 << 1)) {
            PORTD = 0x00;
        }
        else {
            PORTD = 0xff;
        }
        
    }
} */

/* // 버튼으로 PORTD LED 켜기2(분할)
#include "src/led.h"

// Button 을 PORTG 1, 2, 3에 연결
// Pull-Up 저항 연결, open 1, close 0

int main() {
    LED led;
    led.port = &PORTD;
    led.pinNumber = 0;
    led.delayTime = 150;

    // DDRG = 0x00;      // PORTG 모든 pin을 입력으로 설정
    DDRG &= ~((1 << 1) | (1 << 2) | (1 << 3));      // PORTG 1, 2, 3번 pin을 입력으로 설정

    uint8_t buttonData;
    uint8_t button2Mode = 0;

    while (1)    {
        buttonData = PING;
        
        if (buttonData & (1 << 3)) {
            
        }
        else {
            button2Mode = 0;
            LED_PORT = 0x00;
            LED_DDR = 0x00;
        }

        if (buttonData & (1 << 1)) {
            
        }
        else {
            LED_DDR = 0xff;
            LED_PORT = 0xff;
        }
        
        if (buttonData & (1 << 2)) {
            
        }
        else {
            button2Mode = 1;
        }

        if (button2Mode == 1) {
            ledLeftShift(&led);
        }

        if (buttonData & (1 << 3)) {
            
        }
        else {
            button2Mode = 0;
            LED_PORT = 0x00;
            LED_DDR = 0x00;
        }
    }
} */
