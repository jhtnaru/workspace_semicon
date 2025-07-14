/*
 * dht11.h
 *
 *  Created on: Jul 1, 2025
 *      Author: user16
 */
#ifndef INC_DHT11_H_
#define INC_DHT11_H_

//#include "main.h"
#include "stm32f4xx.h"			// STM32F411 관련 기본적인 사항,
#include "stdint.h"
#include "stdio.h"
#include "stdbool.h"
#include "tim.h"
#include "delay_us.h"

enum {
	INPUT,
	OUTPUT
};

typedef struct dht11 {
	GPIO_TypeDef		*port;
	uint16_t			pin;
	uint8_t			temperature;
	uint8_t			humidity;
} DHT11;

void dht11Init(DHT11 *dht, GPIO_TypeDef *port, uint16_t pin);
void dht11GpioMode(DHT11 *dht, uint8_t mode);
uint8_t dht11Read(DHT11 *dht);

#endif /* INC_DHT11_H_ */
