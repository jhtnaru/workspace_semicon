// main.c
#include <stdint.h>


#define RCC_CR_HSEON			(1 << 16)	// HSE Oscillator On bit
#define RCC_CR_HSERDY			(1 << 17)	// HSE Ready flag
#define RCC_CR_PLLON			(1 << 24)	// PLL Oscillator On bit
#define RCC_CR_PLLRDY			(1 << 25)	// PLL Ready flag

#define RCC_PLLCFGR_PLLM_Pos	0			// PLLM Position
#define RCC_PLLCFGR_PLLN_Pos	6			// PLLN Position
#define RCC_PLLCFGR_PLLP_Pos	16			// PLLP Position
#define RCC_PLLCFGR_PLLSRC_Pos	22			// PLLSRC Position

#define RCC_CFGR_SW_Pos			0			// System Clock Source Select Switch
#define RCC_CFGR_SW_PLL			(2 << RCC_CFGR_SW_Pos)			// PLL 선택
#define RCC_CFGR_HPRE_Pos		4			// AHB Prescaler
#define RCC_CFGR_PPRE1_Pos		10			// APB1 Prescaler
#define RCC_CFGR_PPRE2_Pos		13			// APB2 Prescaler

#define RCC_AHB1ENR_GPIOAEN		(1 << 0)	// GPIOA Cloak Enable bit

#define FLASH_ACR_LATENCY_Pos	0
#define FLASH_ACR_LATENCY_3WS	(3 << FLASH_ACR_LATENCY_Pos)	// 3 Wait State

#define GPIOA_MODER_MODER5		(1 << (5*2))	// GPIOA Output mode 설정
#define GPIOA_ODR_ODR5			(1 << 5)	// PA5 Output Data Set

#define RCC_BASE				0x40023800	// RCC Base Address
#define FLASH_BASE				0x40023C00	// FLASH Base Address
#define GPIOA_BASE				0x40020000	// GPIOA Base Address

#define RCC_CR					(*(volatile uint32_t *)(RCC_BASE + 0x00))
#define RCC_PLLCFGR				(*(volatile uint32_t *)(RCC_BASE + 0x04))
#define RCC_CFGR				(*(volatile uint32_t *)(RCC_BASE + 0x08))
#define RCC_AHB1ENR				(*(volatile uint32_t *)(RCC_BASE + 0x30))
#define FLASH_ACR				(*(volatile uint32_t *)(FLASH_BASE + 0x00))
#define GPIOA_MODER				(*(volatile uint32_t *)(GPIOA_BASE + 0x00))
#define GPIOA_ODR				(*(volatile uint32_t *)(GPIOA_BASE + 0x14))

#define SYSTICK_CTRL			(*(volatile uint32_t *)0xE000E010)	// SysTick Control and Status Register
#define SYSTICK_LOAD			(*(volatile uint32_t *)0xE000E014)	// SysTick Reload Value Register
#define SYSTICK_VAL				(*(volatile uint32_t *)0xE000E018)	// SysTick Current Value Register

#define SYSTICK_CTRL			(*(volatile uint32_t *)0xE000E010)	// SysTick Control and Status Register
#define SYSTICK_LOAD			(*(volatile uint32_t *)0xE000E014)	// SysTick Reload Value Register
#define SYSTICK_VAL				(*(volatile uint32_t *)0xE000E018)	// SysTick Current Value Register
#define SYSTICK_CALIB			(*(volatile uint32_t *)0xE000E01C)	// SysTick Calibration Value Register


// System Clock Setting
void Systemclock_Config(void) {
	// HSE Clock Enable
	RCC_CR |= RCC_CR_HSEON;				// HSE On
	while(!(RCC_CR & RCC_CR_HSERDY));	// HSE 안정화 대기

	// PLL Setting
	RCC_PLLCFGR |=
			(4 << RCC_PLLCFGR_PLLM_Pos) |		// PLLM = 4
			(200 << RCC_PLLCFGR_PLLN_Pos) |		// PLLN = 200
			(0x1 << RCC_PLLCFGR_PLLP_Pos) |		// PLLP = 4
			(1 << RCC_PLLCFGR_PLLSRC_Pos);		// PLL Source = HSE

	// PLL Enable
	RCC_CR |= RCC_CR_PLLON;				// PLL On
	while(!(RCC_CR & RCC_CR_PLLRDY));	// PLL Ready 대기

	// AHB, APB1, APB2 분주 설정
	RCC_CFGR |= (0 << RCC_CFGR_HPRE_Pos);		// AHB Prescaler = 1 (SYSCLK 적용)
	RCC_CFGR |= (5 << RCC_CFGR_PPRE1_Pos);		// APB1 Prescaler = 4
	RCC_CFGR |= (4 << RCC_CFGR_PPRE2_Pos);		// APB2 Prescaler = 2

	// Flash Memory Setting, Latency 조정
	FLASH_ACR |= FLASH_ACR_LATENCY_3WS;

	// System Clock Source 로 PLL 선택
	RCC_CFGR |= RCC_CFGR_SW_PLL;
	while((RCC_CFGR & RCC_CFGR_SW_PLL) != RCC_CFGR_SW_PLL);		// SWS 확인
}

void SysTick_Init(void) {
    SYSTICK_LOAD = (20000 - 1);		// 1ms 주기 설정 (100MHz 기준)
    SYSTICK_VAL = 0;				// 현재 값 초기화
    SYSTICK_CTRL = (1 << 0) |		// SysTick Enable
                   (1 << 2);		// Clock Source = Process Clock
}

void delay_ms(uint32_t ms) {
    for(uint32_t i = 0; i < ms; i++) {
        while(!(SYSTICK_CTRL & (1 << 16)));		// COUNTFLAG bit 대기
    }
}

int main() {
	Systemclock_Config();		// System Clock Setting
	SysTick_Init();				// SysTick 초기화

	// Test GPIO Setting
	RCC_AHB1ENR |= RCC_AHB1ENR_GPIOAEN;		// GPIOA Clock Enable
	GPIOA_MODER |= GPIOA_MODER_MODER5;		// PA5 Output mode Setting

	while(1) {
		GPIOA_ODR ^= GPIOA_ODR_ODR5;		// PA5 Toggle
		for(volatile int i = 0; i < 1000000; i++);

//		GPIOA_ODR |= GPIOA_ODR_ODR5;		// PA5 Set
//		for(volatile int i = 0; i < 1000000; i++);
//		GPIOA_ODR &= ~GPIOA_ODR_ODR5;		// PA5 Reset
//		for(volatile int i = 0; i < 1000000; i++);

//		GPIOA_ODR ^= GPIOA_ODR_ODR5;		// PA5 Toggle
//		delay_ms(1000);						// 1000 ms delay
	}
}
