#ifndef __LCD_H__
#define __LCD_H__

#include "../common/def.h"


#define LCD_DATA_DDR        DDRF
#define LCD_DATA_PORT       PORTF

/* LCD_DDR, PORT 구분 설정
#define LCD_RS_DDR          DDRE
#define LCD_RW_DDR          DDRE
#define LCD_E_DDR           DDRE
#define LCD_RS_PORT         PORTE
#define LCD_RW_PORT         PORTE
#define LCD_E_PORT          PORTE */

#define LCD_DDR             DDRE
#define LCD_PORT            PORTE

#define LCD_RS              7
#define LCD_RW              6
#define LCD_E               5

// Command Setting
#define COMMAND_DISPLAY_CLEAR       0x01
#define COMMAND_DISPLAY_ON          0x0C
#define COMMAND_DISPLAY_OFF         0x08
#define COMMAND_ENTRY_MODE          0x06
#define COMMAND_8BIT_MODE           0x38
#define COMMAND_4BIT_MODE           0x28

void LCD_DATA(uint8_t data);        // 8 bit data
void LCD_DATA_4Bit(uint8_t data);   // 4 bit data
void LCD_WritePin();
void LCD_EnablePin();
void LCD_WriteCommand(uint8_t commandData);
void LCD_WriteData(uint8_t charData);
void LCD_GotoXY(uint8_t row, uint8_t col);
void LCD_WriteString(char *string);
void LCD_WriteStringXY(uint8_t row, uint8_t col, char *string);
void LCD_Init();

#endif /* __LCD_H__ */