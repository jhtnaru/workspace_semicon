
#include "lcd.h"

void LCD_DATA(uint8_t data) {
    LCD_DATA_PORT = data;
    LCD_EnablePin();
}

// 상위 4 bit, 하위 4 bit 나눠서 2번 전송
void LCD_DATA_4Bit(uint8_t data) {
    LCD_DATA_PORT = (LCD_DATA_PORT & 0x0f) | (data & 0xf0);         // 상위 4 bit 추출 전송
    LCD_EnablePin();
    LCD_DATA_PORT = (LCD_DATA_PORT & 0x0f) | ((data & 0x0f) << 4);  // 하위 4 bit 추출 전송
    LCD_EnablePin();
}   // 4 bit mode 로 할 경우에는 0 ~ 3 port 제거

// LCD Write mode
void LCD_WritePin() {
    LCD_PORT &= ~(1 << LCD_RW);     // RW Pin Low 설정 -> Write mode
    // LCD_PORT |= (1 << LCD_RW);      // RW Pin High 설정 -> Read mode
}

// LCD 동작 신호
void LCD_EnablePin() {
    LCD_PORT &= ~(1 << LCD_E);      // E Pin Low 설정
    LCD_PORT |= (1 << LCD_E);       // E Pin High 설정
    LCD_PORT &= ~(1 << LCD_E);      // E Pin Low 설정
    _delay_us(1600);                // 일정시간 대기
}

// 명령어 전송
void LCD_WriteCommand(uint8_t commandData) {
    LCD_PORT &= ~(1 << LCD_RS);     // RS Pin Low 설정 -> 명령어 mode
    LCD_WritePin();                 // LCD Write mode
    // LCD_DATA(commandData);          // 8 bit 명령어 전송
    LCD_DATA_4Bit(commandData);     // 4 bit 명령어 전송
    // LCD_EnablePin();                // 중복?
}

// Data 전송
void LCD_WriteData(uint8_t charData) {
    LCD_PORT |= (1 << LCD_RS);      // RS Pin High 설정 -> Data mode
    LCD_WritePin();                 // LCD Write mode
    // LCD_DATA(charData);             // 8 bit Data 전송
    LCD_DATA_4Bit(charData);        // 4 bit Data 전송
    // LCD_EnablePin();                // LCD 동작 신호
}

void LCD_GotoXY(uint8_t row, uint8_t col) {
    row %= 2;       // Row Index 0 ~ 1 제한, 2행
    col %= 16;      // Column Index 0 ~ 15 제한, 16열

    uint8_t address = (0x40 * row) + col;       // 주소 계산
    uint8_t command = 0x80 + address;           // Set DDRAM Address
    LCD_WriteCommand(command);                  // 주소 설정 Command LCD 전송
}

void LCD_WriteString(char *string) {
    for(uint8_t i = 0; string[i]; i++) {
        LCD_WriteData(string[i]);
    }
}

void LCD_WriteStringXY(uint8_t row, uint8_t col, char *string) {
    LCD_GotoXY(row, col);
    LCD_WriteString(string);
}

void LCD_Init() {
    LCD_DATA_DDR = 0xff;        // Data Pin 출력 설정
    LCD_DDR |= (1 << LCD_RS);   // RS Pin 출력 설정
    LCD_DDR |= (1 << LCD_RW);   // RW Pin 출력 설정
    LCD_DDR |= (1 << LCD_E);    // Enable Pin 출력 설정

    // 8 bit Initialization
    // _delay_ms(20);              // 초기화 대기 시간
    // LCD_WriteCommand(COMMAND_8BIT_MODE);
    // _delay_ms(5);
    // LCD_WriteCommand(COMMAND_8BIT_MODE);
    // _delay_ms(5);
    // LCD_WriteCommand(COMMAND_8BIT_MODE);

    // LCD_WriteCommand(COMMAND_8BIT_MODE);
    // LCD_WriteCommand(COMMAND_DISPLAY_OFF);
    // LCD_WriteCommand(COMMAND_DISPLAY_CLEAR);
    // LCD_WriteCommand(COMMAND_DISPLAY_ON);       // Datasheet 에서 해당 내용 추가
    // LCD_WriteCommand(COMMAND_ENTRY_MODE);

    // 4 bit Initialization
    _delay_ms(20);              // 초기화 대기 시간
    LCD_WriteCommand(0x03);     // 상위 4 bit 0000 무시, 0x30 으로 할 경우 뒤에 0000 들어가므로 Error 가능성 존재
    _delay_ms(5);
    LCD_WriteCommand(0x03);
    _delay_ms(5);
    LCD_WriteCommand(0x03);

    LCD_WriteCommand(0x02);
    LCD_WriteCommand(COMMAND_4BIT_MODE);
    LCD_WriteCommand(COMMAND_DISPLAY_OFF);
    LCD_WriteCommand(COMMAND_DISPLAY_CLEAR);
    LCD_WriteCommand(COMMAND_DISPLAY_ON);       // Datasheet 에서 해당 내용 추가
    LCD_WriteCommand(COMMAND_ENTRY_MODE);
}