// servo.c
#include "servo.h"

void servoInit(SERVO *servo) {
    servo->servoPos = 370;
    servo->servoDiret = 1;
    servo->servoEnabled = 0;
}

void servoMove180(SERVO *servo) {
    servo->servoPos += servo->servoDiret;
    
    if(servo->servoPos >= 635) {
        servo->servoPos = 635;
        servo->servoDiret = -1;
    }
    else if (servo->servoPos < 105) {
        servo->servoPos = 105;
        servo->servoDiret = 1;
    }
}
