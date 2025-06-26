#include <stdio.h>
#include <string.h>     // 문자열과 관련된 표준함수

// 구조체3
typedef struct test {       // 배열처럼 순서대로 메모리 공간 확보
    int a;
    int b;
} TEST;

int main() {
    TEST st = {0};      // st의 첫번째 메모리 주소 0x1234
    TEST *ptr;          // struct test 타입 구조체를 가리키는 포인터 변수, 구조체 아님

    ptr = &st;          // ptr 에 st 의 주소 0x1234 저장

    // (*ptr).a 와 ptr->a 는 동일
    (*ptr).a = 1;       // *(역참조) 보다 .(직접지정) 이 우선순위가 먼저라 괄호( ) 필요
    ptr->b = 2;
}

/* 배열 예제1
#define ARR_SIZE 5          // 매크로 상수 지정

int add(int a, int b) {
    return a + b;
}

int main() {
    int arr[ARR_SIZE] = {0};            // 배열 전체를 0으로 초기화
    
    arr[0] = 5;
    arr[1] = arr[0] + 10;               // 배열의 요소를 수식에 이용
    arr[2] = add(arr[0], arr[1]);       // 배열의 요소를 함수 인자로 사용

    printf("정수 2개를 입력하시오 : ");
    scanf("%d %d", &arr[3], &arr[4]);   // 입력값을 배열의 요소로 저장

    for (int i = 0; i < ARR_SIZE; i++)
    {
        printf(" %d ", arr[i]);
    }
    
    printf("\n\n");
    printf("arr[5] = %d\n", arr[5]);
} */

/* 변수의 주소값
int main() {
    int i = 5;
    char c = 'A';

    printf(" 변수 i의 주소값 : %p\t 변수 i의 값 : %d\n", &i, i);
    printf(" 변수 c의 주소값 : %p\t 변수 c의 값 : %d\n", &c, c);
} */

/* 배열의 주소값
int main() {
    int arr[4];
    // 연속되는 주소값이 int는 4씩, char은 1씩, double은 8씩 증가
    
    // int arr[4] = {1, 3, 5, 7, 9};        // 배열수를 초과하면 실행은 되나 에러
    // int arr[] = {1, 3, 5, 7, 9};         // 배열수를 지정안하면 요소에 맞게 설정

    
    // for (int i = 0; i < 4; i++)    {
    //     arr[i] = i * 2 + 1;
    // }
    
    printf(" arr 열의 첫번째 주소값 : %p\t 요소값 : %d\n", &arr[0], arr[0]);
    printf(" arr 열의 두번째 주소값 : %p\t 요소값 : %d\n", &arr[1], arr[1]);
    printf(" arr 열의 세번째 주소값 : %p\t 요소값 : %d\n", &arr[2], arr[2]);
    printf(" arr 열의 네번째 주소값 : %p\t 요소값 : %d\n", &arr[3], arr[3]);
} */

/* 2차원 배열
int main() {
    int arr_2[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // int arr_2[3][3] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    // int arr_2[][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};     // 행의 수는 생략 가능, 열이 수는 생략 불가
    // int arr_2[][3] = {{4, 5, 6}, {7, 8, 9}};     // 2행으로 인식
    // int arr_2[][3] = {{1, 2, 3}, {4, 5}, {7, 8}};       // 비어있는 곳은 0으로 초기화

    for (int i = 0; i < 3; i++)    {
        for (int j = 0; j < 3; j++)        {
            // printf(" %d행 %d열 : %d", i+1, j+1, arr_2[i][j]);
            // if(j < 2) printf("  | ");       // if 문에서 실행할 코드가 한줄이면 중괄호 생략 가능
            // if(j == 2) printf("\n");

            printf("%d행 %d열 : %d | 주소 : %p \n", i+1, j+1, arr_2[i][j], &arr_2[i][j]);
        }
    }
} */

/* 포인터
// 메모리 상에 위치한 특정 데이터의 시작주소를 보관하는 변수

// 포인터 변수 선언 ~ 데이터형 *변수명; ~ *위치는 무관, int *ptr; int* ptr;, int * ptr;

// 포인터의 크기는 일정, 플랫폼에 따라 결정, 32bit : 4byte, 64bit : 8byte

// 포인터의 초기화
// 절대 포인터에 주소를 직접 대입해서는 안됨, 오류 발생 확률 높음
// 특정 주소에 특정 값이나 역할이 있을 수 있고 우리가 다 알 수 없음
// int *ptr;    ptr = 0x12345678;   ~ 안됨
// int *prt;    prt = NULL;         ~ 권장

// 포인터 변수의 크기
int main() {
    int *pi;            // int 타입의 포인터 변수 선언, pointer to int
    double *pd;         // double 타입의 포인터 변수 선언
    char *pc;           // char 타입의 포인터 변수 선언

    printf(" int 형의 포인터 크기 : %d\n", sizeof(pi));
    printf(" double 형의 포인터 크기 : %d\n", sizeof(pd));
    printf(" char 형의 포인터 크기 : %d\n", sizeof(pc));
    printf("\n");

    printf(" int 형의 포인터 크기 : %d\n", sizeof(int*));
    printf(" double 형의 포인터 크기 : %d\n", sizeof(double*));
    printf(" char 형의 포인터 크기 : %d\n", sizeof(char*));
} */

/* 포인터 연산자(&, *)
// 주소 연산자(&) ~ 변수의 이름 앞에 사용, 해당 변수의 주소값을 반환(번지연산자)
// 참조 연산자(*) ~ 포인터의 이름 앞에 사용, 포인터가 가르키는 곳(주소)에 저장된 값 반환

int main() {
    int *ptr;
    int a = 2;

    ptr = &a;

    // printf("포인터 변수 ptr에 들어있는 값 : %p\n", ptr);
    // printf("포인터 변수 ptr의 주소값 : %p\n", &ptr);
    // printf("int 변수 a의 메모리 주소값 : %p\n", &a);    

    printf(" a의 값 : %d\n", a);
    printf(" a의 주소값 : %p\n", &a);

    printf(" *ptr의 값 : %d\n", *ptr);
    printf(" ptr이 가르키는곳 : %p\n", ptr);

} */

/* 포인터도 변수
int main() {
    int a, b;       // 일반 변수 선언
    int *ptr;       // 여기서 int의 의미는 포인터가 가르키는 곳의 데이터 타입

    ptr = &a;       // 포인터 ptr 변수에 a의 주소값 저장
    *ptr = 2;       // 포인터 ptr이 가르키는 곳에 2를 저장(결국은 a)
    ptr = &b;       // 포인터 ptr 변수에 b의 주소값 변경 저장
    *ptr = 3;       // 포인터 ptr이 가르키는 곳에 3를 저장(결국은 b)
    
    printf(" a의 값 : %d\n", a);
    printf(" b의 값 : %d\n", b);
} */

/* 포인터 상수
// const int *p; ~ 읽기 전용 포인터
// int * const p; ~ 특정 변수 전용 포인터
// const int * const p; ~ 읽기 전용이면서 특정 변수 전용 포인터

// int main() {
//     int a, b;
//     const int *ptr;

//     ptr = &a;       // 정상, 포인터가 가리키는 곳은 변경 가능
//     *ptr = 3;       // 오류, 포인터가 가리키는 곳의 값은 변경 불가
//     ptr = &b;       // 정상, 포인터가 가리키는 곳은 변경 가능
// }

int main() {
    int a, b;
    int *const ptr = &a;        // 반드시 선언과 동시에 초기화 해야함

    *ptr = 3;       // 정상, 포인터가 가르키는 곳의 값은 변경 가능
    ptr = &b;       // 오류, 포인터가 가르키는 곳은 변경 불가
} */

/* 포인터의 덧셈(주소값 증가)
int main() {
    int a;
    char b;
    double c;
    
    // 자료형에 따라 크기가 변함
    int *pa = &a;           // 4byte
    char *pb = &b;          // 1byte
    double *pc = &c;        // 8byte

    printf("pa의 값 : %p\n", pa);
    printf("(pa + 1)의 값 : %p\n", pa + 1);
    printf("pb의 값 : %p\n", pb);
    printf("(pb + 1)의 값 : %p\n", pb + 1);
    printf("pc의 값 : %p\n", pc);
    printf("(pc + 1)의 값 : %p\n", pc + 1);

    // int a;
    // int *pa = &a;
    // int b;
    // int *pb = &b;
    // int *pc = pa + pc;      // 포인터 변수끼리의 덧셈은 불가, 주소값이기 때문에
} */

/* 포인터의 대입
int main() {
    int a;
    int *pa = &a;
    int *pb;

    *pa = 3;
    pb = pa;        // 포인터 변수끼리 대입은 가능, 둘 다 주소이기 때문에

    printf(" pa가 가리키는 것의 값 : %d\n", *pa);
    printf(" pb가 가리키는 것의 값 : %d\n", *pb);
} */

/* 배열과 포인터의 관계
// 배열은 변수가 여러개 모인 것으로 메모리상에서 연속적으로 공간을 확보

int main() {
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    for (int i = 0; i < 10; i++)    {
        printf("arr[%d]의 주소값 : %p\n", i, &arr[i]);
    }
} */

/* 포인터로 배열에 접근
int main() {
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int *parr;
    parr = &arr[0];

    for (int i = 0; i < 10; i++)
    {
        printf("arr[%d]의 주소값 : %p\t", i, &arr[i]);
        printf("(parr + %d)의 값 : %p\t", i, (parr + i));
        
        
        if (&arr[i] == (parr + i))        {
            // 만약 (parr+i)가 성공적으로 arr[i]를 가르킨다면
            printf("-> 일치\n");
        }
        else        {
            printf("-> 불일치\n");
        }
    }
} */

/* 참조연산자(*)로 배열에 접근
int main() {
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int *parr;
    parr = &arr[0];

    printf(" arr[3] = %d\n *(parr + 3) = %d\n", arr[3], *(parr + 3));
} */

/* 배열의 이름과 포인터의 관계
// arr[0]과 주소값의 관계

int main() {
    int arr[3] = {1, 2, 3};

    // 배열의 이름 arr과 arr[0]의 주소값이 동일
    // 배열의 이름이 배열 첫번째 요소를 가르키는데 포인터는 아님
    printf("arr의 정체 : %p\n", arr);
    printf("arr[0]의 주소값 : %p\n\n", &arr[0]);

    // 배열은 배열이고, 포인터는 포인터
    int *parr = arr;
    
    // c언어에서 배열의 이름이 sizeof, &(주소연산자) 등과 같이 사용할 때를 제외하면
    // 배열의 이름이 암묵적으로 첫번째 원소를 가리키는 포인터 타입으로 변환됨
    printf("sizeof(arr) : %d\n", sizeof(arr));
    printf("sizeof(parr) : %d\n\n", sizeof(parr));
} */

/* 배열의 이름의 암묵적 포인터 타입 변환 예제1
int main() {
    int arr[3] = {1, 2, 3};

    int *parr;
    parr = arr;     // parr = &arr[0];
    //  arr[i] 는 컴파일러가 (arr + i) 로 해석
    printf(" arr[1] : %d\n", arr[1]);
    printf(" parr[1] : %d\n", parr[1]);
} */

/* 배열의 이름의 암묵적 포인터 타입 변환 예제2
int main() {
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int *parr = arr;        // 포인터 변수 선언과 동시에 배열을 가리킴, 배열의 0번 index
    int sum;

    while (parr - arr <= 9)    {
        sum += (*parr);     // sum = sum + (*parr);
        parr++;             // arr++; 은 안됨, 포인터 처럼 행동하지만 포인터는 아님
    }

    printf("평균값 : %d\n\n", sum / 10);
} */

/* 이중포인터(포인터의 포인터)
int main() {
    int a;
    int *pa;
    int **ppa;      //

    pa = &a;
    ppa = &pa;

    a = 3;

    // &&은 사용 불가, **ppa = *(*ppa)
    printf(" a의 값 : %d\t *pa의 값 : %d\t **ppa의 값 : %d\n", a, *pa, **ppa);
    printf(" a의 주소 : %p\t pa 가리키는 주소 : %p\t *ppa의 값 : %p\n", &a, pa, *ppa);
    printf(" pa의 주소 : %p\t ppa 가리키는 주소 : %p\n", &pa, ppa);
    printf(" ppa의 주소 : %p\n", &ppa);
} */

/* 2차원 배열, 행 배열 이름의 암묵적 포인터 타입 변환
int main() {
    int arr[2][3];
    
    printf("arr[0] : %p\n", arr[0]);
    printf("&arr[0][0] : %p\n", &arr[0][0]);

    printf("arr[1] : %p\n", arr[1]);
    printf("&arr[1][0] : %p\n", &arr[1][0]);
} */

/* 구조체1
// 서로 다른 데이터형의 변수들을 묶어서 사용, 사용자 정의 데이터형 생성

struct human {      // human 이라는 구조체 정의
    int age;        // 나이 멤버변수
    int height;     // 키 멤버변수
    int weight;     // 몸무게 멤버변수
};                  // 마지막에 세미콜론

int main() {
    struct human info;      // 데이터형 struct human, 변수명 info

    // 변수를 초기화
    info.age = 99;
    info.height = 180;
    info.weight = 100;

    printf("info 의 멤버변수 키 : %d\n", info.height);    
} */

/* 구조체2
struct contact {
    char name[20];
    char phone[20];
    int ringtone;
};

int main() {
    struct contact ct = {"김석진", "010-1234-5678", 0};
    struct contact ct1 = {0};                   // 구조체 변수 초기화
    struct contact ct2 = ct;                    // 구조체 변수간 대입 가능
    
    ct.ringtone = 5;
    strcpy(ct.phone, "010-3333-4444");          // 오른쪽 문자열을 왼쪽으로 복사

    printf("이    름 : %s\n", ct.name);
    printf("전화번호 : %s\n", ct.phone);
    printf("벨 소 리 : %d\n\n", ct.ringtone);

    printf("이    름 : %s\n", ct1.name);
    printf("전화번호 : %s\n", ct1.phone);
    printf("벨 소 리 : %d\n\n", ct1.ringtone);

    printf("이    름 : %s\n", ct2.name);
    printf("전화번호 : %s\n", ct2.phone);
    printf("벨 소 리 : %d\n\n", ct2.ringtone);
}

// c언어에는 문자열이 없음, 문자열은 "very"(연속된 문자의 집합), 문자는 'a' (하나의 문자)
// 문자열의 표현방법은 배열에 저장, char[ ], 마지막에 Null 문자가 있어야함
// very\0 -> very 자체는 4개의 문자지만 문자열은 Null 추가해서 5칸의 크기 필요 */

/* 데이터형 재정의
typedef unsigned int myunsignedInteger;

int main() {
    myunsignedInteger a;        // unsigned int a; 과 같은 데이터형

    a = 10;
    
    printf(" a : %d\n", a);
} */

/* 구조체 데이터형 재정의
typedef struct food {   // 구조체 이름
    char name[10];
    int price;
    int cookTime;
} FOOD;                 // 구조체 별칭

int main() {
    // struct food good;
    // FOOD good = {0};
    FOOD good = {"ggoodd", 30, 50};
    
    // strcpy(good.name, "ggggoodd");

    printf(" 음식 이름 : %s\n", good.name);
    printf(" 음식 가격 : %d\n", good.price);
    printf(" 요리 시간 : %d\n", good.cookTime);
} */


