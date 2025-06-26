
#include "fnd.h"

// 숫자 출력 값 배열
uint8_t segNum[10] = { // .GFEDCBA
    0x3f, 0x06,     // 00111111 --FEDCBA 0, 00000110 -----CB- 1
    0x5b, 0x4f,     // 01011011 -G-ED-BA 2, 01001111 -G--DCBA 3
    0x66, 0x6d,     // 01100110 -GF--CB- 4, 01101101 -GF-DC-A 5
    0x7d, 0x27,     // 01111101 -GFEDC-A 6, 00100111 --F--CBA 7
    0x7f, 0x67      // 01111111 -GFEDCBA 8, 01100111 -GF--CBA 9
};

// 영문 출력 값 배열
uint8_t segAlph[26] = { // .GFEDCBA
    0x5f, 0x7c,     // 0101 1111 -G-EDCBA A, 0111 1100 -GFEDC-- B 0 1
    0x39, 0x5e,     // 0101 1001 --FED--A C, 0101 1110 -G-EDCB- D 2 3
    0x79, 0x71,     // 0111 1001 -GFED--A E, 0111 0001 -GFE---A F 4 5
    0x3d, 0x76,     // 0011 1101 --FEDC-A G, 0111 0110 -GFE-CB- H 6 7
    0x11, 0x0d,     // 0011 0000 ---E---A I, 0000 1101 ----DC-A J 8 9
    0x75, 0x38,     // 0111 0101 -GFE-C-A K, 0011 1000 --FED--- L 10 11
    0x55, 0x54,     // 0101 0101 -G-E-C-A M, 0101 0100 -G-E-C-- N 12 13
    0x5c, 0x73,     // 0101 1100 -G-EDC-- O, 0111 0011 -GFE--BA P 14 15
    0x67, 0x50,     // 0110 0111 -GF--CBA Q, 0101 0000 -G-E---- R 16 17
    0x2d, 0x78,     // 0010 1101 --F-DC-A S, 0111 1000 -GFED--- T 18 19
    0x1c, 0x2a,     // 0001 1100 ---EDC-- U, 0010 1010 --F-D-B- V 20 21
    0x6a, 0x14,     // 0110 1010 -GF-D-B- W, 0001 0100 ---E-C-- X 22 23
    0x6e, 0x1b      // 0110 1110 -GF-DCB- Y, 0001 1011 ---ED-BA Z 24 25
};

// FND 1자리 출력 설정 초기화 함수
void fndInit() {
    FND_DDR = 0x7f;         // FND Port Output 설정, DP 미사용
}

// FND 4자리 출력 설정 초기화 함수
void fnd4Init() {
    FND4_DDR = 0xff;        // FND4 Port Output 설정
    FND4_SELECT_DDR |= (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3);       // FND4 위치 Port 0 ~ 3 Output 설정
    FND4_SELECT_PORT &= ~((1 << 0) | (1 << 1) | (1 << 2) | (1 << 3));   // FND4 위치 Port 초기값 0
}

// FND 출력 함수, Common-Cathode
// select - 0 숫자, 1 영문, 2 초기화, num - 나타내려는 숫자나 영문 번호
void fndDisplay_CC(uint8_t select, uint8_t num) {
    // select 에 따라 숫자나 영문 출력하거나 초기화
    if (select == 0) {
        FND_PORT = segNum[num];
    }
    else if (select == 1) {
        FND_PORT = segAlph[num];
    }
    else if (select == 2) {
        FND_PORT = 0x00;
    }
}

// FND 출력 함수, Common-Anode
// select - 0 숫자, 1 영문, 2 초기화, num - 나타내려는 숫자나 영문 번호
void fndDisplay_CA(uint8_t select, uint8_t num) {
    // select 에 따라 숫자나 영문 출력하거나 초기화
    if (select == 0) {
        FND_PORT = ~segNum[num];
    }
    else if (select == 1) {
        FND_PORT = ~segAlph[num];
    }
    else if (select == 2) {
        FND_PORT = 0x00;
    }
}

// FND 4자리 출력 함수, Common-Cathode
// select 0 숫자, 1 영문, 2 초기화, num 숫자나 영문 번호, 왼쪽부터 0 ~ 3 자리
void fnd4Display_CC(uint8_t select0, uint8_t num0, uint8_t select1, uint8_t num1,
                    uint8_t select2, uint8_t num2, uint8_t select3, uint8_t num3) {
    for (uint8_t pos = 0; pos < 4; pos++) {
        switch (pos) {
        case 0:     // 0번 자리 Output select
        FND4_SELECT_PORT &= ~(1 << 0);
        FND4_SELECT_PORT |= (1 << 1) | (1 << 2) | (1 << 3);
        
        // select 에 따라 숫자나 영문 출력하거나 초기화
        if (select0 == 0) {
            FND4_PORT = segNum[num0];
        }
        else if (select0 == 1) {
            FND4_PORT = segAlph[num0];
        }
        else if (select0 == 2) {
            FND4_PORT = 0x00;
        }
        _delay_ms(1);
        break;

        case 1:     // 1번 자리 Output select
        FND4_SELECT_PORT &= ~(1 << 1);
        FND4_SELECT_PORT |= (1 << 0) | (1 << 2) | (1 << 3);
        if (select1 == 0) {
            FND4_PORT = segNum[num1];
        }
        else if (select1 == 1) {
            FND4_PORT = segAlph[num1];
        }
        else if (select1 == 2) {
            FND4_PORT = 0x00;
        }
        _delay_ms(1);                       // 1ms 대기
        break;

        case 2:     // 2번 자리 Output select
        FND4_SELECT_PORT &= ~(1 << 2);
        FND4_SELECT_PORT |= (1 << 0) | (1 << 1) | (1 << 3);
        if (select2 == 0) {
            FND4_PORT = segNum[num2];
        }
        else if (select2 == 1) {
            FND4_PORT = segAlph[num2];
        }
        else if (select2 == 2) {
            FND4_PORT = 0x00;
        }
        _delay_ms(1);                       // 1ms 대기
        break;

        case 3:     // 3번 자리 Output select
        FND4_SELECT_PORT &= ~(1 << 3);
        FND4_SELECT_PORT |= (1 << 0) | (1 << 1) | (1 << 2);
        if (select3 == 0) {
            FND4_PORT = segNum[num3];
        }
        else if (select3 == 1) {
            FND4_PORT = segAlph[num3];
        }
        else if (select3 == 2) {
            FND4_PORT = 0x00;
        }
        _delay_ms(1);                       // 1ms 대기
        break;
        }
    }
}

// FND 4자리 출력 함수, Common-Anode
// select 0 숫자, 1 영문, 2 초기화, num 숫자나 영문 번호, 왼쪽부터 0 ~ 3 자리
void fnd4Display_CA(uint8_t select0, uint8_t num0, uint8_t select1, uint8_t num1,
                    uint8_t select2, uint8_t num2, uint8_t select3, uint8_t num3) {
    for (uint8_t pos = 0; pos < 4; pos++) {
        switch (pos) {
        case 0:     // 0번 자리 Output select
        FND4_SELECT_PORT &= ~(1 << 0);
        FND4_SELECT_PORT |= (1 << 1) | (1 << 2) | (1 << 3);
        
        // select 에 따라 숫자나 영문 출력하거나 초기화
        if (select0 == 0) {
            FND4_PORT = ~segNum[num0];
        }
        else if (select0 == 1) {
            FND4_PORT = ~segAlph[num0];
        }
        else if (select0 == 2) {
            FND4_PORT = 0x00;
        }
        _delay_ms(1);
        break;

        case 1:     // 1번 자리 Output select
        FND4_SELECT_PORT &= ~(1 << 1);
        FND4_SELECT_PORT |= (1 << 0) | (1 << 2) | (1 << 3);
        if (select1 == 0) {
            FND4_PORT = ~segNum[num1];
        }
        else if (select1 == 1) {
            FND4_PORT = ~segAlph[num1];
        }
        else if (select1 == 2) {
            FND4_PORT = 0x00;
        }
        _delay_ms(1);                       // 1ms 대기
        break;

        case 2:     // 2번 자리 Output select
        FND4_SELECT_PORT &= ~(1 << 2);
        FND4_SELECT_PORT |= (1 << 0) | (1 << 1) | (1 << 3);
        if (select2 == 0) {
            FND4_PORT = ~segNum[num2];
        }
        else if (select2 == 1) {
            FND4_PORT = ~segAlph[num2];
        }
        else if (select2 == 2) {
            FND4_PORT = 0x00;
        }
        _delay_ms(1);                       // 1ms 대기
        break;

        case 3:     // 3번 자리 Output select
        FND4_SELECT_PORT &= ~(1 << 3);
        FND4_SELECT_PORT |= (1 << 0) | (1 << 1) | (1 << 2);
        if (select3 == 0) {
            FND4_PORT = ~segNum[num3];
        }
        else if (select3 == 1) {
            FND4_PORT = ~segAlph[num3];
        }
        else if (select3 == 2) {
            FND4_PORT = 0x00;
        }
        _delay_ms(1);                       // 1ms 대기
        break;
        }
    }
}
