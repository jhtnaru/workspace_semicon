#ifndef __UART0_INT_H__
#define __UART0_INT_H__

#include "../common/def.h"

void UART0_Int_Init();
void UART0_Int_Transmit(unsigned char data);
//int UART_Int_Transmit(char data, FILE *stream);
unsigned char UART0_Int_Receive();

extern FILE OUTPUT;
extern char rxBuff[100];
extern volatile uint8_t rxFlag;     // 최적화 하지 않도록 선언

#endif /* __UART0_INT_H__ */