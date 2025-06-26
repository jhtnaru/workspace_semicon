// ap.c
// 선풍기 Project 3조
// Button 에 따라 1(STOP), 2(LOW), 3(HIGH), 4(SPIN) 동작
// Fan 동작 + Servo 동작 + FND 출력 + FND4 출력 + LED 출력 + ADC 조작
#include "ap.h"

void apInit() {

}

void apMain() {

    t8bInit();                  // 8-bit Timer Fast PWM, Clear
    t8bPrescaler(1, 0, 0);      // CS02, CS01, CS00 100, 64분주

    t16bInit();                 // 16-bit Timer Fast PWM, Clear, TOP 4999, 50Hz
    t16bPrescaler(0, 1, 1);     // CS02, CS01, CS00 011, 64분주

    SERVO servo;
    servoInit(&servo);
    TIMER16B_OCR = servo.servoPos;      // Servo 초기 위치 적용

    // Button 1 ~ 4 의 구조체 변수 선언
    // Button 의 위치 등과 btnEnabled 이라는 상태 변수 포함
    BUTTON btn1;
    BUTTON btn2;
    BUTTON btn3;
    BUTTON btn4;

    // Button 1 ~ 4 의 변수 초기화
    buttonInit(&btn1, &BUTTON_DDR, &BUTTON_PIN, BUTTON_1);
    buttonInit(&btn2, &BUTTON_DDR, &BUTTON_PIN, BUTTON_2);
    buttonInit(&btn3, &BUTTON_DDR, &BUTTON_PIN, BUTTON_3);
    buttonInit(&btn4, &BUTTON_DDR, &BUTTON_PIN, BUTTON_4);
    btn1.btnEnabled = 1;        // Button 1 On 을 초기값으로 주어 STOP 상태로 시작
    btnPrev = 1;                // 이전 Button 상태를 기억해 회전 상태에서 FND, LED 출력 유지를 위한 변수

    fndInit();
    fnd4Init();

    ledInit();
    uint8_t ledLow = 20;        // Low 일때 delay 값, 50 ms * ledLow
    uint8_t ledHigh = 5;        // High 일때 delay 값, 50 ms * ledHigh

    adcInit();
    uint16_t potVal;
    uint16_t potVal_t;

    while (1) {
        adcConvert();
        potVal = ADC;
        potVal_t = adcTrans(potVal, 10);

        // Button 1 이 눌리면 Button 1 상태 On, 나머지 버튼과 Servo Off, 이전 버튼 상태는 1 기억
        if (buttonGetState(&btn1) == btnRELEASED) {
            btn1.btnEnabled = 1;
            btn2.btnEnabled = 0;
            btn3.btnEnabled = 0;
            btn4.btnEnabled = 0;
            servo.servoEnabled = 0;
            btnPrev = 1;
        }
        
        // Button 1 이 눌린 상태라면 다른 버튼이 눌리기 전까지 아래 동작 계속 실행
        if (btn1.btnEnabled == 1) {
            TIMER8B_OCR = 0;                    // FAN 0%

            fndDisplay_CC(0, 0);                            // FND 0 출력
            fnd4Display_CC(1, 18, 1, 19, 1, 14, 1, 15);     // FND4 STOP 출력

            ledOff();
        }

        // Button 2 눌리면 Button 2 상태 On, 나머지 버튼 Off, 이전 버튼 상태는 2 기억
        if (buttonGetState(&btn2) == btnRELEASED) {
            btn1.btnEnabled = 0;
            btn2.btnEnabled = 1;
            btn3.btnEnabled = 0;
            btn4.btnEnabled = 0;
            btnPrev = 2;
        }

        // Button 2 눌린 상태라면 다른 버튼이 눌리기 전까지 아래 동작 계속 실행
        if (btn2.btnEnabled == 1) {
            TIMER8B_OCR = 102 + potVal_t;       // FAN 40% + ADC 변환 값
            
            fndDisplay_CC(0, 1);                            // FND 1 출력
            fnd4Display_CC(1, 11, 1, 14, 1, 22, 2, 0);      // FND4 LOW 출력
            ledLeftShift(0, ledLow);                            // LED 왼쪽 이동, d 변수로 시간 조절
        }

        // Button 3 눌리면 Button 3 상태 On, 나머지 버튼 Off, 이전 버튼 상태는 3 기억
        if (buttonGetState(&btn3) == btnRELEASED) {
            btn1.btnEnabled = 0;
            btn2.btnEnabled = 0;
            btn3.btnEnabled = 1;
            btn4.btnEnabled = 0;
            btnPrev = 3;
        }

        // Button 3 눌린 상태라면 다른 버튼이 눌리기 전까지 아래 동작 계속 실행
        if (btn3.btnEnabled == 1) {
            TIMER8B_OCR = 204 + potVal_t;       // FAN 80% + ADC 변환 값

            fndDisplay_CC(0, 2);                            // FND 2 출력
            fnd4Display_CC(1, 7, 1, 8, 1, 6, 1, 7);         // FND4 HIGH 출력
            ledLeftShift(0, ledHigh);                            // LED 왼쪽 이동, d 변수로 시간 조절
        }

        if (buttonGetState(&btn4) == btnRELEASED) {
            btn1.btnEnabled = 0;
            btn2.btnEnabled = 0;
            btn3.btnEnabled = 0;
            btn4.btnEnabled = 1;
            servo.servoEnabled = !servo.servoEnabled;
        }

        // Button 4 눌린 상태 + servo 작동 상태면 다른 버튼이 눌리기 전까지 아래 동작 계속 실행
        if (btn4.btnEnabled == 1 && servo.servoEnabled == 1) {
            fnd4Display_CC(1, 18, 1, 15, 1, 8, 1, 13);      // FND4 SPIN 출력

            // servo 작동해도 이전 상태에 따라 LED 출력은 유지
            switch (btnPrev) {
                case 1:     // 이전에 눌렸던 Button 상태에 따라 LED 출력 유지
                ledOff();
                break;
            
                case 2:     
                ledLeftShift(0, ledLow);
                break;

                case 3:
                ledLeftShift(0, ledHigh);
                break;
            }
        }

        // Button 4 눌린 상태 + servo 미작동 상태면 다른 버튼이 눌리기 전까지 아래 동작 계속 실행
        else if (btn4.btnEnabled == 1 && servo.servoEnabled == 0){
            
            // servo 작동 정지하면 이전 상태에 따라 FND4, LED 출력
            switch (btnPrev) {
                case 1:     // 이전에 눌렸던 Button 상태에 따라 FND4, LED 출력 유지
                fnd4Display_CC(1, 18, 1, 19, 1, 14, 1, 15);
                ledOff();
                break;
            
                case 2:
                fnd4Display_CC(1, 11, 1, 14, 1, 22, 2, 0);
                ledLeftShift(0, ledLow);
                break;

                case 3:
                fnd4Display_CC(1, 7, 1, 8, 1, 6, 1, 7);
                ledLeftShift(0, ledHigh);
                break;
            }
        }

        // Servo 작동 상태면 회전 실행
        if (servo.servoEnabled == 1) {
            servoMove180(&servo);
            TIMER16B_OCR = servo.servoPos;
        }

        _delay_ms(10);      // 동작 반영 시간을 주기 위해 delay
    }
}


/* // 버튼으로 LED 조절

#include "ap.h"

void apInit() {

}

void apMain() {
    LED_DDR = 0xff;

    // 버튼 관련 변수 선언 (기능별 분류)
    BUTTON btnOn;
    BUTTON btnOff;
    BUTTON btnToggle;

    buttonInit(&btnOn, &BUTTON_DDR, &BUTTON_PIN, BUTTON_ON);    // 변수주소, DDR주소, PIN주소,  PIN번호
    buttonInit(&btnOff, &BUTTON_DDR, &BUTTON_PIN, BUTTON_OFF);
    buttonInit(&btnToggle, &BUTTON_DDR, &BUTTON_PIN, BUTTON_TOGGLE);

    while (1)    {
        if(buttonGetState(&btnOn) == RELEASED) {
            LED_PORT = 0xff;
        }
        if(buttonGetState(&btnOff) == RELEASED) {
            LED_PORT = 0x00;
        }
        if(buttonGetState(&btnToggle) == RELEASED) {
            LED_PORT ^= 0xff;
        }
    }
} */

/* // Interrupt 이용 LED 켜고 끄기
#include "ap.h"

void apInit() {
    ledInit();
}

ISR(INT4_vect) {        // Interrupt 가 걸리면 주작업 중단 시키고 실행
    // PORTD = 0xff;
    ledOn();
}

ISR(INT5_vect) {        // Interrupt 가 걸리면 주작업 중단 시키고 실행
    // PORTD = 0x00;
    ledOff();
}

void apMain () {
    sei();              // 전역 interrupt enable

    // EICRB = 0x0e;       // INT5 11(rising edge), INT4 11(falling edge)
    EICRB |= (1 << ISC51) | (1 << ISC50) | (1 < ISC41);     // ISC51 3, ISC50 2, ISC41 1 로 정의되어 있음

    // EIMSK = 0x30;       // INT5, INT4 Interrupt enable
    EIMSK |= (1 << INT5) | (1 << INT4);                     // INT5 5, INT4 4 로 정의되어 있음

    // DDRD = 0xff;
    
    while (1) {         // 주작업 입력
        
    }
} */

/* // CTC 방식, 주파수 변경
#include "ap.h"

void apInit() {

}

void apMain() {
    DDRB = 0xff;            // PB4 를 통해서 주파수 출력, 16MHz
    // TCCR0 = 0x1C;           // Register Setting (CTC mode, Toggle, 분주비 64)
    // TCCR0 |= (1 < WGM01) | (1 << COM00) | (1 << CS02);

    TCCR0 = 0x1D;           // Register Setting (CTC mode, Toggle, 분주비 128)
    // TCCR0 |= (1 < WGM01) | (1 << COM00) | (1 << CS02) | (1 << CS00);
    
    // OCR0 = 124;             // 계산한 값, 분주비 64, 1KHz 로 변경
    OCR0 = 249;             // 계산한 값, 분주비 128, 250Hz 로 변경

    while (1) {
        while ((TIFR & 0x02) == 0) {    // TIFR 2 OCF0 0 이면 계속 주파수 발생, Interrupt 미발생
            
        }
        TIFR = 0x02;        // Interrupt 가 발생해 TIFR 2 OCF0 이 1 이 되면 1 을 입력해 다시 0 으로 변경
                            // OCF0 를 0을 만들어 다시 Interrupt 가 발생할 수 있도록 해줌
        OCR0 = 249;         // 다시 OCR0 값을 넣어 250 Hz 변경 유지
    }
} */

/* // Normal 방식, 주파수 변경
#include "ap.h"

void apInit() {

}

void apMain() {
    DDRD = 0xff;            // 보기 위해 D port 출력
    PORTD = 0;

    TCCR0 |= (1 << CS02) | (1 << CS00);
    
    TCNT0 = 131;

    while (1) {
        while ((TIFR & 0x01) == 0) {
            
        }
        PORTD = ~PORTD;
        TCNT0 = 131;
        TIFR = 0x01;
    }
} */

/* // Fast PWM 방식, 주파수 변경
#include "ap.h"

void apInit() {

}

void apMain() {
    // DDRB = 0xff;            // B port 전체 출력
    DDRB |= (1 << PB4);     // PB4 port 만 출력

    // TCCR0 = 0x6c;
    TCCR0 |= (1 << WGM00) | (1 << COM01) | (1 << WGM01) | (1 << CS02);
    
    OCR0 = 204;
    // GND(-) 연결하면 0 에서 커질수록 HIGH 상태 시간 길어짐
    // + 연결하면 반대로 작동

    while (1) {
        OCR0 = 0;
        _delay_ms(3000);
        OCR0 = 102;
        _delay_ms(3000);
        OCR0 = 204;
        _delay_ms(3000);
    }
}
*/

/* // 16-bit Timer/Counter Fast PWM 방식, 주파수 변경
#include "ap.h"

void apInit() {

}

void apMain() {
    DDRB |= (1 << PB5);     // PB5 port 만 출력

    // 16-bit, Fast PWM, 64 분주, 50Hz
    TCCR1A |= (1 << COM1A1) | (1 << WGM11);
    TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << CS11) | (1 << CS10);
    
    ICR1 = 4999;        // TOP 값, 50Hz
    // OCR1A = 2500;

    while (1) {
        // 1ms 펄스 OCR1A = 250;
        // 최소 105, 최대 635

        // OCR1A = 125;        // 0.5ms, 0 degree
        // _delay_ms(2000);
        // OCR1A = 375;        // 1.5ms, 90 degree
        // _delay_ms(2000);
        // OCR1A = 625;        // 2.5ms, 180 degree
        // _delay_ms(2000);
        for (uint16_t i = 0; i <= 530; i++) {
            OCR1A = 105 + i;
            _delay_ms(10);
        }

        for (uint16_t i = 0; i <= 530; i++) {
            OCR1A = 635 - i;
            _delay_ms(10);
        }
    }
}
 */

/* // ADC 이용 예시
void apInit() {

}

void apMain() {
    uint16_t pot_val;                // 가변저항 값을 저장할 변수 지정
    uint16_t threshold = 512;        // 쓰레시홀드(어떤 값을 고정좌표로 사용할지) 지정. 10비트 ADC를 사용하기 때문에 0~1024의 중간값인 512로 설정.
    DDRD |= (1 << PD0);              // LED를 사용하기 위해 포트 D의 0번핀 출력으로 설정.

    init_ADC0();                     // ADC 기능 켜는 함수
    PORTD = 0x00;

    while (1) {
        ADC_convert();                   // ADC 변환 시작
        pot_val = ADC;                   // 변환이 끝난 디지털 값을 port_val에 저장

        if (pot_val > threshold) {       // 임계값보다 현재 가변저항 노브가 더 많이 돌아갔으면(중간보다 시계방향으로 더 돌아가면)
            PORTD= 0x01;                 // LED 켜기
        }
        else {                          // 나머지 상황(중간보다 반시계로 돌아갔을 때)
            PORTD= 0x00;                // LED 끄기
        }
    }
} */

/* // 선풍기 Project 3조
// Button 에 따라 1(STOP), 2(LOW), 3(HIGH), 4(SPIN) 동작
// Fan 동작 + Servo 동작 + FND 출력 + FND4 출력 + LED 출력 + ADC 조작
#include "ap.h"

void apInit() {

}

void apMain() {
    FND_DDR = 0x7f;             // PORTF 출력 설정, FND 연결
    FND4_Init();                // PORTA, PORTB 0 ~ 3 초기화
    LED_DDR = 0xff;             // PORTD 출력 설정, LED 연결
    
    FPWM_OUT |= (1 << PB4) | (1 << PB5);     // PB4, PB5 port 출력
    
    // PORTG 1, 2, 3, 4 입력 설정
    BUTTON_DDR &= ~((1 << 0) | (1 << 1) | (1 << 2) | (1 << 3));

    regist_set();               // 8-bit, Fast PWM, Clear
    prescaler_set(1, 0, 0);     // CS02, CS01, CS00 값 입력, 100 -> 64분주

    all_regist_set();           // 16-bit, Fast PWM, 64 분주, 50Hz
    prescaler_set_16(0, 1, 1);  // CS02, CS01, CS00 값 입력, 011 -> 64분주
    
    // Button 1 ~ 4 의 구조체 변수 선언
    // Button 의 위치 등과 btnEnabled 이라는 상태 변수 포함
    BUTTON btn1;
    BUTTON btn2;
    BUTTON btn3;
    BUTTON btn4;

    // Button 1 ~ 4 의 변수 초기화
    buttonInit(&btn1, &BUTTON_DDR, &BUTTON_PIN, BUTTON_1);
    buttonInit(&btn2, &BUTTON_DDR, &BUTTON_PIN, BUTTON_2);
    buttonInit(&btn3, &BUTTON_DDR, &BUTTON_PIN, BUTTON_3);
    buttonInit(&btn4, &BUTTON_DDR, &BUTTON_PIN, BUTTON_4);
    btn1.btnEnabled = 1;        // Button 1 상태는 초기값을 On 을 주어 STOP 상태로 시작
    uint8_t btnPrev = 1;        // Button 4 Spin 을 Off 했을 때 이전 버튼 상태를 기억해서 표현하기 위한 변수

    seg_number_CC(0);               // FND 초기값 0 출력
    
    int8_t servoDiret = 1;          // servo 의 이동 방향
    uint16_t servoPos = 370;        // servo 의 초기 위치
    uint8_t servoEnabled = 0;       // servo 의 작동 상태 기억, Fan 회전과 별도로 동작하게 하려고 별도 변수 지정
    
    OCR1A = servoPos;               // servo 의 초기 위치 적용

    uint8_t led_index = 0;          // LED 출력 위치
    // uint8_t led_direction = 1;
    uint8_t led_delay = 0;          // 함수가 아닌 자체적으로 delay 를 주기 위한 변수
    uint8_t led_delayLow = 20;      // Low 일때 delay 값, 50 ms * led_delayLow
    uint8_t led_delayHigh = 5;      // Low 일때 delay 값, 50 ms * led_delayHigh

    uint16_t pot_val;
    uint8_t pot_val_t = 0;
    uint8_t pot_val_i = 10;
    init_ADC0();

    ICR1 = 4999;        // TOP 값, 50Hz

    while (1) {
        ADC_convert();
        pot_val = ADC;

        if (pot_val < 100) {
            pot_val_t = 0;
        }
        else if (pot_val > 150 && pot_val < 300) {
            pot_val_t = pot_val_i;
        }
        else if (pot_val > 350 && pot_val < 500) {
            pot_val_t = pot_val_i * 2;
        }
        else if (pot_val > 550 && pot_val < 700) {
            pot_val_t = pot_val_i * 3;
        }
        else if (pot_val > 750 && pot_val < 900) {
            pot_val_t = pot_val_i * 4;
        }
        else if (pot_val > 950) {
            pot_val_t = pot_val_i * 5;
        }

        // Button 1 이 눌리면 Button 1 상태 On, 나머지 버튼과 Servo Off, 이전 버튼 상태는 1 기억
        if (buttonGetState(&btn1) == btnRELEASED) {
            btn1.btnEnabled = 1;
            btn2.btnEnabled = 0;
            btn3.btnEnabled = 0;
            btn4.btnEnabled = 0;
            servoEnabled = 0;
            btnPrev = 1;
        }
        
        // Button 1 이 눌린 상태라면 다른 버튼이 눌리기 전까지 아래 동작 계속 실행
        if (btn1.btnEnabled == 1) {
            // COUNT2TOP = 0;          // FAN 작동 안함
            if (pot_val_t >= 10) {
                COUNT2TOP = 70 + (pot_val_t * 2);       // 처음 작동을 위한 최소값 확보를 위해 초기값 지정
            } else {
                COUNT2TOP = 0;
            }

            seg_number_CC(0);       // FND 0 출력
            // seg_number_CA(0);

            FND4_Display(1, 18, 1, 19, 1, 14, 1, 15);   // FND4 STOP 출력

            LED_PORT = 0x00;        // LED 출력 안함
        }

        // Button 2 눌리면 Button 2 상태 On, 나머지 버튼 Off, 이전 버튼 상태는 2 기억
        if (buttonGetState(&btn2) == btnRELEASED) {
            btn1.btnEnabled = 0;
            btn2.btnEnabled = 1;
            btn3.btnEnabled = 0;
            btn4.btnEnabled = 0;
            btnPrev = 2;
        }

        // Button 2 눌린 상태라면 다른 버튼이 눌리기 전까지 아래 동작 계속 실행
        if (btn2.btnEnabled == 1) {
            // COUNT2TOP = 102;        // FAN 40%
            COUNT2TOP = 100 + pot_val_t;
            
            seg_number_CC(1);       // FND 1 출력
            // seg_number_CA(1);

            FND4_Display(1, 11, 1, 14, 1, 22, 2, 0);   // FND4 LOW 출력

            // LED 를 index 위치에 출력, delay 변수에 따라 index 변경 시간 조절
            LED_PORT = (1 << led_index);
            if (led_delay >= led_delayLow) {
                led_index++;
                led_delay = 0;
            }
            led_delay++;
            if (led_index > 8) {
                    led_index = 0;      // LED 가 끝에 도달하면 다시 처음으로 index 변경
            }
        }

        // Button 3 눌리면 Button 3 상태 On, 나머지 버튼 Off, 이전 버튼 상태는 3 기억
        if (buttonGetState(&btn3) == btnRELEASED) {
            btn1.btnEnabled = 0;
            btn2.btnEnabled = 0;
            btn3.btnEnabled = 1;
            btn4.btnEnabled = 0;
            btnPrev = 3;
        }

        // Button 3 눌린 상태라면 다른 버튼이 눌리기 전까지 아래 동작 계속 실행
        if (btn3.btnEnabled == 1) {
            // COUNT2TOP = 204;        // FAN 80%
            COUNT2TOP = 170 + pot_val_t;

            seg_number_CC(2);       // FND 2 출력
            // seg_number_CA(2);

            FND4_Display(1, 7, 1, 8, 1, 6, 1, 7);   // FND4 HIGH 출력

            // LED 를 index 위치에 출력, delay 변수에 따라 index 변경 시간 조절
            LED_PORT = (1 << led_index);
            if (led_delay >= led_delayHigh) {
                led_index++;
                led_delay = 0;
            }
            led_delay++;
            if (led_index >= 8) {
                led_index = 0;      // LED 가 끝에 도달하면 다시 처음으로 index 변경
            }
        }

        if (buttonGetState(&btn4) == btnRELEASED) {
            btn1.btnEnabled = 0;
            btn2.btnEnabled = 0;
            btn3.btnEnabled = 0;
            btn4.btnEnabled = 1;
            servoEnabled = !servoEnabled;
        }

        // Button 4 눌린 상태 + servo 작동 상태면 다른 버튼이 눌리기 전까지 아래 동작 계속 실행
        if (btn4.btnEnabled == 1 && servoEnabled == 1) {
            FND4_Display(1, 18, 1, 15, 1, 8, 1, 13);        // FND4 SPIN 출력

            // servo 작동해도 이전 상태에 따라 LED 출력은 유지
            switch (btnPrev) {
            case 1:     // 이전에 눌렸던 Button 상태에 따라 LED 출력 유지
                LED_PORT = 0x00;
                break;
            
            case 2:     
                LED_PORT = (1 << led_index);
                if (led_delay >= led_delayLow) {
                    led_index++;
                    led_delay = 0;
                }
                led_delay++;
                if (led_index >= 8) {
                    led_index = 0;
                }
                break;

            case 3:
                LED_PORT = (1 << led_index);
                if (led_delay >= led_delayHigh) {
                    led_index++;
                    led_delay = 0;
                }
                led_delay++;
                if (led_index >= 8) {
                    led_index = 0;
                }
                break;
            }
        }

        // Button 4 눌린 상태 + servo 미작동 상태면 다른 버튼이 눌리기 전까지 아래 동작 계속 실행
        else if (btn4.btnEnabled == 1 && servoEnabled == 0){
            
            // servo 가 작동하지 않게 되면 이전 상태에 따라 FND4 출렬
            // servo 작동 안해도 이전 상태에 따라 LED 출력은 유지
            switch (btnPrev) {
            case 1:     // 이전에 눌렸던 Button 상태에 따라 FND4, LED 출력 유지
                FND4_Display(1, 18, 1, 19, 1, 14, 1, 15);   // FND4 STOP 출력

                LED_PORT = 0x00;

                break;
            
            case 2:
                FND4_Display(1, 11, 1, 14, 1, 22, 2, 0);    // FND4 LOW 출력

                LED_PORT = (1 << led_index);
                if (led_delay >= led_delayLow) {
                    led_index++;
                    led_delay = 0;
                }
                led_delay++;
                if (led_index >= 8) {
                    led_index = 0;
                }
                break;

            case 3:
                FND4_Display(1, 7, 1, 8, 1, 6, 1, 7);       // FND4 HIGH 출력

                LED_PORT = (1 << led_index);
                if (led_delay >= led_delayHigh) {
                    led_index++;
                    led_delay = 0;
                }
                led_delay++;
                if (led_index >= 8) {
                    led_index = 0;
                }
                break;
            }
        }

        // servo 작동 상태면 다른 버튼이 눌리기 전까지 아래 동작 계속 실행
        if (servoEnabled == 1) {
            // servo 위치를 이동 방향에 따라 변경
            servoPos += servoDiret;

            // servo 끝에 도달하면 방향 전환
            if(servoPos >= 635) {
                servoPos = 635;
                servoDiret = -1;
            }
            else if (servoPos <= 105) {
                servoPos = 105;
                servoDiret = 1;
            }

            // servo 를 저장된 위치로 이동
            OCR1A = servoPos;
        }

        _delay_ms(10);      // 동작 반영 시간을 주기 위해 delay
    }
} */

/* // LCD 초기화, 입출력
#include "ap.h"

void apInit () {

}

void apMain () {
    LCD_Init();

    // LCD_GotoXY(0, 0);
    // LCD_WriteString("Hello LCD");
    // LCD_GotoXY(1, 0);
    // LCD_WriteString("Hello AVR");

    char buff[30];
    sprintf(buff, "Hello ATmega128A");
    LCD_WriteStringXY(0, 0, buff);
    
    uint16_t count = 0;

    while (1) {
        LCD_WriteCommand(0x1c);     // 오른쪽으로 Shift
        _delay_ms(300);
        // sprintf(buff, "Count : %d", count++);
        // LCD_WriteStringXY(1, 2, buff);
        // _delay_ms(100);
    }
} */

/* // UART 통신1
#include "ap.h"

void apInit() {

}

void apMain() {
    UART0_Init();

    uint8_t rxData;     // 수신 data

    while (1) {
        UART0_Transmit(UART0_Receive());    // 수신한 값을 송신
    }
    
} */

/* // UART 통신2
#include "ap.h"

void apInit() {

}

void apMain() {
    stdout = &OUTPUT;       // 

    UART0_Int_Init();

    sei();

    while (1) {
        if (rxFlag == 1) {      // 문자열 수신이 완료된 경우
            rxFlag = 0;         // 문자열 수신 Flag 초기화
            printf(rxBuff);     // 수신 문자열 출력
            // printf("%s", rxBuff);
        }
    }
} */

