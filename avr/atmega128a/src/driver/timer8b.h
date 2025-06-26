#ifndef __TIMER8B_H__
#define __TIMER8B_H__

#include "../common/def.h"

void t8bInit();
void t8bPrescaler(uint8_t cs2, uint8_t cs1, uint8_t cs0);

#endif /* __TIMER8B_H__ */