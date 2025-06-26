#ifndef __TIMER16B_H__
#define __TIMER16B_H__

#include "../common/def.h"  

void t16bInit();
void t16bPrescaler(uint8_t cs2, uint8_t cs1, uint8_t cs0);

#endif /* __TIMER16B_H__ */
