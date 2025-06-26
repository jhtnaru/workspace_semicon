
#include "uart0_int.h"

// 출력 Stream 설정, stdio.h 에 있음
FILE OUTPUT = FDEV_SETUP_STREAM(UART0_Int_Transmit, NULL, _FDEV_SETUP_WRITE);

char rxBuff[100] = {0};             // 수신 Buffer
volatile uint8_t rxFlag = 0;                 // 수신 완료 Flag


ISR(USART0_RX_vect) {               // 수신 Interrupt handler
    static uint8_t rxHead = 0;      // 수신된 Data 의 Index
    uint8_t rxData = UDR0;

    if(rxData == '\n' || rxData == '\r') {      // 수신 data 가 개행이나 Return 이면
        rxBuff[rxHead] = '\0';      // 수신된 문자열 마지막에 Null 문자 추가
        rxHead = 0;                 // Index 초기화
        rxFlag = 1;                 // 문자열 수신 Flag 설정
    }
    else {                          // 조건 해당할때까지 계속 수신
        rxBuff[rxHead] = rxData;    // Buffer 에 수신 Data 추가
        rxHead++;                   // Index 증가
    }
}

void UART0_Int_Init() {
    UBRR0H = 0x00;
    UBRR0L = 0xcf;              // 207 을 16진수로 표현

    UCSR0A |= (1 << U2X0);      // 2배속 mode
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);      // 수신, 송신 가능
    
    UCSR0B |= (1 << RXCIE0);                    // 수신 Interrupt 가능

    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);    // 초기값이 1이라 별도로 넣지 않아도 무방
}

void UART0_Int_Transmit(unsigned char data) {
    while (!(UCSR0A & (1 << UDRE0)));       // 송신 가능할때까지 대기, UDR0 비어 있는지 확인
    UDR0 = data;
}

// 포인터 타입 맞추기용
// int UART_Int_Transmit(char data, FILE *stream)
// {
//     while (!(UCSR0A & (1 << UDRE0)));
//     UDR0 = data;
//     return 0;
// }

unsigned char UART0_Int_Receive() {
    while (!(UCSR0A & (1 << RXC0)));        // Data 수신 대기
    return UDR0;
}
