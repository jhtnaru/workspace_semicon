#include <stdio.h>

// shift 연산자 <<, >>
// << 2 ~ 2만큼 왼쪽 이동, 1111 -> 1100
// >> 2 ~ 2만큼 오른쪽 이동, 1111 -> 0011

int main() {
    int n1 = 1;                 // 0b00000000 00000000 00000000 00000001
    int s1 = n1 << 1;           // 0b00000000 00000000 00000000 00000010
    int s2 = n1 << 2;           // 0b00000000 00000000 00000000 00000100
    int s3 = n1 << 3;           // 0b00000000 00000000 00000000 00001000
    int s4 = n1 << 4;           // 0b00000000 00000000 00000000 00010000

    printf("s1 = %d \n", n1);
    printf("s1 = %d \n", s1);
    printf("s1 = %d \n", s2);
    printf("s1 = %d \n", s3);
    printf("s1 = %d \n", s4);
}

/* // Hello World
 #include <stdio.h>      // #include 전처리기
// stdio.h I/O 관련 헤더파일, std ~ standard, io ~ input + output

// void는 return 값 없음
int main() {        // 하나의 프로그램에 main 함수는 하나
    printf("Hello World \n\n\n");   // ; 은 문장 마침
    // \n 줄바꿈, \r 커서를 맨앞으로, \t 탭
     
    return 0;
}
*/

/* // 주석
// 한줄 주석 ~ Ctrl + /
// 범위 한줄 주석 ~ 범위 잡고 Ctrl + /
// 범위 여러줄 주석 ~ Ctrl + Shift + A
*/

/* // 서식지정자
// %s 문자열, %c 문자, %d 정수, %x 16진수, %표시 %%, %p 주소값
// char 문자, string 문자열, int 정수, unsigned 부호 없음
// #define 정의, 선언

#define APPLE 10
#define NAME "사과"

int main()
{
    int a = 20;
    int b = 0xff;

    printf("%s, %d, %c, %d%%, %x, %d \n\n\n", NAME, APPLE, 'a', a, b, b);
    // 순서대로 서식지정자와 매칭, 수가 같아야 함
    
    return 0;
}
*/

/* // 데이터형 Byte 크기
int main() {
    char ch;    // 데이이형 변수명
    int num;
    double x;

    printf("char 형의 바이트 크기 : %d \n", sizeof(char));
    printf("short 형의 바이트 크기 : %d \n", sizeof(short));
    printf("long 형의 바이트 크기 : %d \n", sizeof(long));
    printf("float 형의 바이트 크기 : %d \n", sizeof(float));

    printf("ch 형의 바이트 크기 : %d \n", sizeof(ch));
    printf("num 형의 바이트 크기 : %d \n", sizeof(num));
    printf("x 형의 바이트 크기 : %d \n", sizeof(x));
}
*/

/* // 변수 선언, 표기법
// 의미가 이미 정해져 있는 예약어는 사용 안됨, 변수명 등
// c언어에서 변수 선언과 사용 ~ 영문자, 숫자, 특수문자(_)
// 첫문자는 반드시 영문자, 특수문자만 가능, 대소문자 구분
// 카멜표기법 int manAge ~ 첫단어는 소문자, 결합되는 단어는 대문자로 시작
// 스테이크 표기법 int man_age ~ 단어 사이 언더스코어로 연결
// 파스칼 표기법 int ManAge ~ 모든 단어를 대문자로 시작
// 헝가리안 표기법 int iManAge ~ 변수명을 데이타형의 약자로 시작
*/

/* // 지역변수, 전역변수, 정적변수
// 지역변수를 선언하고 초기화 하지 않으면 쓰레기 값이 들어감

int g;  // 전역변수 ~ 함수 밖에 있는 변수, 자동 초기화

int main() {
    int price = 6;  // 지역변수(Local variable) ~ 블록 {} 안에 잡혀 있는 변수
    static int num; // 정적변수 ~ 지역변수와 전역변수의 중간 성질, 자동 초기화

    printf("%d \n", price);
    printf("%d \n", g);
    printf("%d \n", num);
}
*/

/* // Input & output
int main() {
    int amount = 0;
    int price = 0;
    int totalPrice = 0;

    printf("amount = %d, price = %d \n", amount, price);
    printf("수량을 넣으시오 : ");   // output
    scanf("%d", &amount);   // input

    price = 100;

    totalPrice = amount * price;
    
    printf("amount = %d, price = %d \n", amount, price);
    printf("합계 = %d \n\n\n", totalPrice);
}
*/

/* // 산술연산자 +, -, *, /, %(나머지), ++(증가), --(증감)
int main() {
    int a = 39;
    int b = 17;
    int result; // 초기화?

    result = a + b;
    printf("a + b = %d \n", result);
    result = a - b;
    printf("a - b = %d \n", result);
    result = a * b;
    printf("a * b = %d \n", result);
    result = a / b;
    printf("a / b = %d \n", result);
    result = a % b;
    printf("a %% b = %d \n", result);
    result = ++a;
    printf("++a = %d \n", result);
    result = --a;
    printf("--a = %d \n", result);
}
*/

/* // 대입연산자 =, +=, -=, *=, /=, %=
// a += b ~ a = a + b
*/

/* // 관계연산자 ==, !=(같지않음), >, <, >=, <=
*/

/* // 논리연산자 &&(and), ||(or), !(not), 
// true ~ 1 ~ 5v ~ high
// false ~ 0 ~ GWD ~ low

int main() {
    int month = 0;
    
    printf("몇 월? : ");
    scanf("%d", &month);

    if(month >= 6 && month <= 8) {  // AND
        printf("성수기 요금 적용 \n\n");
    }
    
    if(month < 6 || month > 8) {    // OR
        printf("일반 요금 적용 \n\n");
    }
}
*/

/* // 삼항연산자 (또는 조건연산자)
// expression1 ? expression2 : expression3
// expression1 true 이면 expression2 수행, false 면 expression3 수행
*/

/* // 특수연산자
// sizeof() ~ 소괄호 안의 변수 바이트 크기 반환
// & ~ 변수가 저장된 메모리상의 주소값을 반환
// * ~ 변수의 포인터
*/

/* // 비트연산자 &, |, ~, ^
// bit 단위 비교
// ^ ~ 같으면 0, 다르면 1

int main() {
    int n1 = 15;            // 0b00000000 00000000 00000000 00001111
    int n2 = 20;            // 0b00000000 00000000 00000000 00010100
    int result = n1 & n2;   // 0b00000000 00000000 00000000 00000100

    printf("n1 = %d \n", n1);
    printf("n2 = %d \n", n2);
    printf("n1 & n2 result = %d \n", result);

    result = n1 | n2;       // 0b00000000 00000000 00000000 00011111
    printf("n1 | n2 result = %d \n", result);

    result = n1 ^ n2;       // 0b00000000 00000000 00000000 00011011
    printf("n1 ^ n2 result = %d \n", result);

    result = ~n1;           // 0b11111111 11111111 11111111 11110000
    printf("~n1 result = %d \n", result);
}
*/





