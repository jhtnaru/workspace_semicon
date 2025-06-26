#ifndef __ADC_H__
#define __ADC_H__

#include "../common/def.h"

void adcInit();
void adcConvert();
uint8_t adcTrans(uint16_t val, uint8_t val_i);

#endif /* __ADC_H__ */