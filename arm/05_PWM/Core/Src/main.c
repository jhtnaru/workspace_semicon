/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "led.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t rxData;
uint8_t rxFlag;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	if (huart->Instance == USART2) {
		HAL_UART_Receive_IT(&huart2, &rxData, sizeof(rxData));
		ledOff(8);
	}

	if (rxData == 'a') {
		rxFlag = 1;
	}
	else if (rxData == 'b') {
		rxFlag = 2;
	}
	else if (rxData == 'c') {
		rxFlag = 3;
	}
	else if (rxData == 'd') {
		rxFlag = 4;
	}
	else if (rxData == 'e') {
		rxFlag = 5;
	}
}
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM3_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);			// Timer 3 Channel 1 PWM mode Start
  HAL_UART_Receive_IT(&huart2, &rxData, sizeof(rxData));

  uint8_t servoPos = 75;
  int8_t direct = 1;

  uint32_t curTick = 0;
  uint32_t servoTick = 20;
  uint32_t servoLastTick = 0;
  uint32_t ledTick = 200;
  uint32_t ledLastTick = 0;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  curTick = HAL_GetTick();

	  switch (rxFlag) {
		case 1:
			if ((curTick - servoLastTick) >= servoTick) {
				if (servoPos > 30) {
					servoPos--;
				}
				else {
					servoPos = 30;
				}
				servoLastTick = curTick;
			}

			if ((curTick - ledLastTick) >= ledTick) {
				ledLeftShift(8, 0);
				ledLastTick = curTick;
			}
			break;

		case 2:
			if ((curTick - servoLastTick) >= servoTick) {
				if (servoPos < 75) {
					servoPos++;
				}
				else if (servoPos > 75) {
					servoPos--;
				}
				servoLastTick = curTick;
			}

			if ((curTick - ledLastTick) >= ledTick) {
				ledToggle(8);
				ledLastTick = curTick;
			}
			break;

		case 3:
			if ((curTick - servoLastTick) >= servoTick) {
				if (servoPos < 120) {
					servoPos++;
				}
				else {
					servoPos = 120;
				}
				servoLastTick = curTick;
			}


			if ((curTick - ledLastTick) >= ledTick) {
				ledRightShift(8, 0);
				ledLastTick = curTick;
			}
			break;

		case 4:
			if ((curTick - servoLastTick) >= servoTick) {
				if (servoPos <= 30) {
					servoPos = 30;
					direct = 1;
				}
				else if (servoPos >= 120) {
					servoPos = 120;
					direct = -1;
				}
				servoPos += direct;
				servoLastTick = curTick;
			}


			if ((curTick - ledLastTick) >= ledTick) {
				ledFlower(8, 0);
				ledLastTick = curTick;
			}
			break;

		case 5:
			ledOff(8);
			break;
	}

	  TIM3->CCR1 = servoPos;

/*	  // Servo 각도 확인
	  TIM3->CCR1 = 30;		// 0도
	  TIM3->CCR1 = 75;		// 90도
	  TIM3->CCR1 = 120;		// 180도*/

/*	  // duty 변경
//	  for(uint16_t i = 0; i < 1000; i++) {
//		  TIM3->CCR1 = i;
//		  HAL_Delay(5);
//	  }*/
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 100;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
