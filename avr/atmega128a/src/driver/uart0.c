
#include "uart0.h"

void UART0_Init() {
    // BaudRate 9600 bps
    UBRR0H = 0x00;
    UBRR0L = 207;

    UCSR0A |= (1 << U2X0);      // 2배속 mode
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);      // 수신, 송신 가능, RX, TX Enabled
    
    // Asynchronous 비동기, Parity mode Disabled, Stop bit 1 bit, 8 bit data
    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);    // 초기값이 1이라 별도로 넣지 않아도 무방
}

void UART0_Transmit(unsigned char data) {
    while (!(UCSR0A & (1 << UDRE0)));       // 송신 가능할때까지 대기, UDR0 비어 있는지 확인
    UDR0 = data;
}

unsigned char UART0_Receive() {
    while (!(UCSR0A & (1 << RXC0)));        // Data 수신 대기
    return UDR0;
}