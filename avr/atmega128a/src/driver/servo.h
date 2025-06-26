#ifndef __SERVO_H__
#define __SERVO_H__

#include "../common/def.h"

typedef struct _servo {
    volatile int8_t servoDiret;
    volatile uint16_t servoPos;
    volatile uint8_t servoEnabled;
} SERVO;

void servoInit(SERVO *servo);

void servoMove180(SERVO *servo);

#endif /* __SERVO_H__ */