/*
 * servo.h
 *
 *  Created on: Jun 20, 2025
 *      Author: user16
 */
#ifndef INC_SERVO_H_
#define INC_SERVO_H_

#include "main.h"
#include "delay_us.h"

// Servo 연결 Timer Channel CCR
#define SERVO_CCR		TIM3->CCR1

extern int8_t servoDirec;
extern int8_t servoPos;
extern int8_t servoEnabled;

void servoInit();
void servoMove(uint8_t mode, uint8_t pos);

#endif /* INC_SERVO_H_ */
