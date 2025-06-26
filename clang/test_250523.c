#include <stdio.h>

// 배열
// 같은 데이터 type(형)의 변수들로 이루어진 유한집합
// 배열을 구성하는 각 값은 배열요소(element), 요소의 위치는 index
// index의 값은 언제나 0부터 시작, 양의 정수값만 가짐
// 배열의 모든 요소는 항상 연속된 메모리에 저장됨

// int num[0] 배열크기는 0 으로 지정 불가
// int size = 10; int num[size]; 배열크기는 변수로 지정 불가
// #define MAX 5; int num[MAX]; 배열크기는 매크로 상수로 지정 가능

int main() {
    int arr[5] = {0,};      // 4byte인 int 타입의 배열 5칸 선언, 요소 모두 0으로 초기화
    int byteArr = 0;        // 배열의 byte 크기를 저장할 변수
    int size = 0;           // 배열의 크기를 저정할 변수

    byteArr = sizeof(arr);
    printf("배열의 byte 크기 : %d\n", byteArr);

    size = sizeof(arr) / sizeof(arr[0]);
    printf("배열의 크기 : %d\n", size);

    // for (int i = 0; i < size; i++)    {
    //     arr[i] = i;         // 배열 초기화
    // }

    arr[2] = 7;

    for (int i = 0; i < size; i++)    {
        printf("arr[%d] : %d\n", i, arr[i]);
    }
}

/* overflow, underflow
int main() {
    unsigned char a;

    a = 0;
    printf("%d \n", a);

    a -= 1;
    printf("%d \n", a);      // underflow

    a = 255;
    printf("%d \n", a);

    a += 1;
    printf("%d \n", a);      // overflow
} */

/* bit mask -> 특정 bit 조작
int main() {
    // unsigned short data = 0x5678;       // 0101 0110 0111 1000
    unsigned short data = 0x0000;       // 0000 0000 0000 0000
    
    unsigned short msk1 = 0xf000;       // 1111 0000 0000 0000
    unsigned short msk2 = 0x0f00;       // 0000 1111 0000 0000
    unsigned short msk3 = 0x00f0;       // 0000 0000 1111 0000
    unsigned short msk4 = 0x000f;       // 0000 0000 0000 1111

    // printf("결과값 1 = %#.4x \n", data & msk1);
    // printf("결과값 2 = %#.4x \n", data & msk2);
    // printf("결과값 3 = %#.4x \n", data & msk3);
    // printf("결과값 4 = %#.4x \n", data & msk4);

    printf("결과값 1 = %#.4x \n", data | msk1);
    printf("결과값 2 = %#.4x \n", data | msk2);
    printf("결과값 3 = %#.4x \n", data | msk3);
    printf("결과값 4 = %#.4x \n", data | msk4);
}

// |(or) 특정 비트를 1로, 원하는 위치에 값을 입력
// 0101 -> 1101 3번 자리에 1을 입력
// 0001 << 3 -> 1000
// 0101 | 1000 = 1101

// &(and) 특정 비트를 0으로, 원하는 위치에 값을 추출
// 1101 -> 0101 3번 자리에 0을 입력
// ~(0001 << 3) -> ~1000 -> 0111
// 1101 & 0111 -> 0101

// ~ 특정 비트를 반전 */

/* 묵시적 형변환
int main() {
    int a, b, c;
    double average;

    printf("정수 3개를 입력하세요 : ");
    scanf("%d %d %d", &a, &b, &c);

    average = (a + b + c) / 3;
    printf("평균 : %f \n", average);

    average = (double)(a + b + c) / 3;      // 묵시적 형변환
    printf("평균 : %f \n", average);
} */

/* if 문
int main() {
    int num = 0;

    printf("숫자를 입력하세요 : ");
    scanf("%d", &num);

    if (num < 5) {
        printf("입력한 숫자는 5보다 작다\n");
    }
    else if (num == 5) {
        printf("입력한 숫자는 5와 같다\n");
    }
    else {
        printf("입력한 숫자는 5보다 크다\n");
    }
    
    // else {
    //     if (num == 5) {
    //         printf("입력한 숫자는 5와 같다\n");
    //     }
    //     else {
    //         printf("입력한 숫자는 5보다 크다\n");
    //     }
        
    // }

    // if (num == 5) {
    //     printf("입력한 숫자는 5와 같다\n");
    // }

    // if (num > 5) {
    //     printf("입력한 숫자는 5보다 크다\n");
    // }
} */

/* switch case 문
int main() {
    int num;

    printf("미세먼지 농도를 선택하세요\n");
    printf("1 : 좋음\n");
    printf("2 : 보통\n");
    printf("3 : 나쁨\n");
    scanf("%d", &num);

    switch (num)    {
    case 1:
        printf("미세먼지 농도가 좋음이니 마스크 안써도 됩니다\n");
        break;      // 중블록을 빠져나감
    case 2:
        printf("미세먼지 농도가 보통이니 마스크 대충 쓰셔도 됩니다\n");
        break;
    case 3:
        printf("미세먼지 농도가 나쁨이니 마스크 잘 쓰셔야 됩니다\n");
        break;
    default:
        printf("잘못 눌렀습니다\n");
        break;
    }
} */

/* while 문 (반복문)
int main() {
    int weight = 80;
    int count = 0;

    // 조건을 만족하면 계속 반복 실행
    // while (1) 무한 반복, 임베디드에서 많이 사용, 전원 연결하면 계속 작동
    while (weight > 60)    {
        printf("매일 운동해서 1kg을 뺀다 %d일차\n", count + 1);
        weight--;
        count++;
    }

    printf("축하합니다 몸무게가 60kg가 되었습니다\n");
    printf("%d일 동안 운동\n", count);
} */

/* for 문 (반복문)
int main() {
    int count = 0;

    // for (초기식(값); 조건식; 증감식)
    // 초기식 -> 조건-실행-증감 -> 조건-실행-증감 -> ... -> 조건 만족 -> 종료
    // 조건식 넣지 않으면 무한 반복
    for (int weight = 80; weight > 70; weight--)    {
        printf("매일 운동해서 1kg을 뺀다 %d일차\n", count + 1);
        count++;
    }

    printf("축하합니다 몸무게가 %dkg가 되었습니다\n", weight);
    printf("%d일 동안 운동\n", count);
} */

/* for 문 중첩
int main() {
    int i, j;

    for(i = 0; i < 3; i++)      {
        printf("외부 for 문 시작 i = %d\n", i);
        for (j = 0; j < 3; j++)     {
            printf("내부 for 문 시작 i = %d, j = %d\n", i, j);
        }
        printf("내부 for 문 종료 i = %d, j = %d\n\n", i, j);
    }
    printf("외부 for 문 종료 i = %d\n\n", i);
} */

/* for 문 예제1
int main() {
int i, j;

    for (i = 0; i < 5; i++)    {
        for (j = 0; j <= i; j++)        {
            printf("*");
        }
        printf("\n");
    }
    
    for (i = 0; i < 4; i++)    {
        for (j = 3; j >= i; j--)        {
            printf("*");
        }
        printf("\n");
    }
} */

/* for 문 예제2
int main() {
    int i, j, k;

    for (i = 0; i < 5; i++)    {
        for (k = 3; k >= i; k--)        {
            printf(" ");
        }
        for (j = 0; j <= i*2; j++)        {
            printf("*");
        }
        printf("\n");
    }
    
    for (i = 0; i < 4; i++)    {
        for (k = 0; k <= i; k++)        {
            printf(" ");
        }
        for (j = 6; j >= i*2; j--)        {
            printf("*");
        }
        printf("\n");
    }
} */

/* 함수 function
// 프로그래밍에서 함수란 특별한 목적의 작업을 수행하기 위해 독립적으로 설계된 프로그램 코드의 집합
// 표준 함수, 사용자정의 함수
// 사용자정의 함수는 main 앞에 작성, main 앞에 원형 선언만 하고 뒤에 작성해도 됨

type function_name(parameter list, , , , ) {
    declations
    statement
}

// 결과를 넘겨줄때는 해당 type
int sum(x, y) {
    int sum;        // 선언들
    sum = x + y;    // 함수의 본체
    return sum;     // 돌려주는값
}
// 넘겨줄게 없을때는 void
void sum(x, y) {
    int sum;
    sum = x + y;
}
*/

/* 함수 예제1
int printHello();   // 함수의 원형 선언

int main() {
    printf("함수를 호출합니다\n");
    printHello();

    printf("함수를 또 호출합니다\n");
    printHello();
}

int printHello() {
    printf("Hello World\n");
    return 0;
}
*/

/* 함수 예제2
int add(int a, int b);

int main() {
    int x, y, z;
    
    printf("정수 2개를 입력하세요 : ");
    scanf("%d %d", &x, &y);

    z = add(x, y);
    printf("합계 : %d\n", z);
}

int add(int a, int b) {
    int sum;
    sum = a + b;
    return sum;
} */

/* 지역변수 local variable
// 블록 {} 내에서 선언된 변수, 블록 내에서만 유효, 블록 종료되면 메모리에서 사라짐
// 메모리 영역내의 stack 영역에 저장, 초기화 하지 않으면 쓰레기값 부여
// 함수의 매개변수도 함수 내에서는 지역변수로 취급
// 프로그램이 실행될때 메모리 확보

void local(void);

int main() {
    int i = 5;      // main() 함수 내의 지역변수
    int var = 10;   // main() 함수 내의 지역변수

    printf("main() 함수 내의 지역변수 var의 값 : %d\n", var);

    if (i < 10)
    {
        local();        // 함수 호출
        int var = 30;   // if 문 내의 지역변수
        printf("if 문 내의 지역변수 var의 값 : %d\n", var);
    }
    printf("현재 지역변수 var의 값 : %d\n", var);
    
}

void local(void) {
    int var = 20;       // local() 내의 지역변수
    printf("local() 함수 내의 지역변수 var의 값 : %d\n", var);
} */

/* 정적변수 static variable
// static 로 정의된 변수(static int a), 전역변수와 지역변수의 특징을 모두 가짐
// 함수 내 선언된 정적변수는 단 한번만 초기화 가능, 초기화하지 않으면 전역변수 처럼 0으로 초기화 됨
// 프로그램이 종료되어야 메모리에서 삭제

void local();
void staticVar();

int main() {
    int i;
    for (i = 0; i < 3; i++)    {
        local();
        staticVar();
    }    
}

void local() {
    int count = 1;                  // 지역변수
    printf("local() 함수가 %d번째 호출\n", count);
    count++;
}

void staticVar() {
    static int staticCount = 1;     // 정적변수, 최초 1회만 선언
    printf("staticVar() 함수가 %d번째 호출\n", staticCount);
    staticCount++;
} */

/* 전역변수 global variable
// 함수 외부에 선언된 변수(main), 프로그램 어디서나 접근 가능, 프로그램 종료되어야 메모리에서 삭제
// 초기화 하지 않아도 0 으로 자동 초기화

void local();
int var;                // 전역변수

int main() {
    printf("전역변수 var 값 : %d\n", var);
    
    int var = 10;       // main() 내의 지역변수
    printf("main() 함수 내의 지역변수 var 값 : %d\n", var);

    if(1) {
        local();
        printf("if 문 내의 변수 var의 값 : %d\n", var);
    }
    
    printf("더이상 main() 함수에서는 전역변수 접근 불가\n");
}

void local() {
    int var = 20;       // local() 내의 지역변수
    printf("local() 함수 내의 변수 var 값 : %d\n", var);
} */


