#ifndef __AP_H__
#define __AP_H__

#include "../common/def.h"

#include "../driver/adc.h"
#include "../driver/button.h"
#include "../driver/fnd.h"
#include "../driver/lcd.h"
#include "../driver/led.h"
#include "../driver/servo.h"
#include "../driver/timer8b.h"
#include "../driver/timer16b.h"
#include "../driver/uart0.h"        // falling 방식 UART header
#include "../driver/uart0_int.h"    // Interrupt 방식 UART header

void apInit();
void apMain();

#endif /* __AP_H__ */