#ifndef __FND_H__
#define __FND_H__

#include "../common/def.h"

extern uint8_t segNum[10];
extern uint8_t segAlph[26];

void fndInit();
void fnd4Init();

void fndDisplay_CC(uint8_t select, uint8_t num);
void fndDisplay_CA(uint8_t select, uint8_t num);

void fnd4Display_CC(uint8_t select0, uint8_t num0, uint8_t select1, uint8_t num1,
                    uint8_t select2, uint8_t num2, uint8_t select3, uint8_t num3);
void fnd4Display_CA(uint8_t select0, uint8_t num0, uint8_t select1, uint8_t num1,
                    uint8_t select2, uint8_t num2, uint8_t select3, uint8_t num3);

#endif /* __FND_H__ */