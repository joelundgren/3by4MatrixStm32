/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include <stdlib.h>
#include <stdio.h>
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
UART_HandleTypeDef huart1;

PCD_HandleTypeDef hpcd_USB_FS;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void PeriphCommonClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USB_PCD_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
#define R1_PORT GPIOC
#define R1_PIN GPIO_PIN_2
#define R2_PORT GPIOC
#define R2_PIN GPIO_PIN_3
#define R3_PORT GPIOA
#define R3_PIN GPIO_PIN_0
#define R4_PORT GPIOA
#define R4_PIN GPIO_PIN_1
#define C1_PORT GPIOC
#define C1_PIN GPIO_PIN_6
#define C2_PORT GPIOA
#define C2_PIN GPIO_PIN_3
#define C3_PORT GPIOA
#define C3_PIN GPIO_PIN_2

char get_keypad_input (void)
{
  HAL_GPIO_WritePin (R1_PORT, R1_PIN, GPIO_PIN_RESET);
  HAL_GPIO_WritePin (R2_PORT, R2_PIN, GPIO_PIN_SET);
  HAL_GPIO_WritePin (R3_PORT, R3_PIN, GPIO_PIN_SET);
  HAL_GPIO_WritePin (R4_PORT, R4_PIN, GPIO_PIN_SET);

  if (HAL_GPIO_ReadPin (C1_PORT, C1_PIN) == 0)
  {
    while (HAL_GPIO_ReadPin (C1_PORT, C1_PIN) == 0);
    return '1';
  }

  if (HAL_GPIO_ReadPin (C2_PORT, C2_PIN) == 0)
  {
    while (HAL_GPIO_ReadPin (C2_PORT, C2_PIN) == 0);
    return '2';
  }

  if (HAL_GPIO_ReadPin (C3_PORT, C3_PIN) == 0)
  {
    while (HAL_GPIO_ReadPin (C3_PORT, C3_PIN) == 0)
      HAL_Delay(200);
    return '3';
  }

  HAL_GPIO_WritePin (R1_PORT, R1_PIN, GPIO_PIN_SET);
  HAL_GPIO_WritePin (R2_PORT, R2_PIN, GPIO_PIN_RESET);
  HAL_GPIO_WritePin (R3_PORT, R3_PIN, GPIO_PIN_SET);
  HAL_GPIO_WritePin (R4_PORT, R4_PIN, GPIO_PIN_SET);

  if (HAL_GPIO_ReadPin (C1_PORT, C1_PIN) == 0)
  {
    while (HAL_GPIO_ReadPin (C1_PORT, C1_PIN) == 0);
    return '4';
  }

  if (HAL_GPIO_ReadPin (C2_PORT, C2_PIN) == 0)
  {
    while (HAL_GPIO_ReadPin (C2_PORT, C2_PIN) == 0);
    return '5';
  }

  if (HAL_GPIO_ReadPin (C3_PORT, C3_PIN) == 0)
  {
    while (HAL_GPIO_ReadPin (C3_PORT, C3_PIN) == 0);
    return '6';
  }

  HAL_GPIO_WritePin (R1_PORT, R1_PIN, GPIO_PIN_SET);
  HAL_GPIO_WritePin (R2_PORT, R2_PIN, GPIO_PIN_SET);
  HAL_GPIO_WritePin (R3_PORT, R3_PIN, GPIO_PIN_RESET);
  HAL_GPIO_WritePin (R4_PORT, R4_PIN, GPIO_PIN_SET);

  if (HAL_GPIO_ReadPin (C1_PORT, C1_PIN) == 0)
  {
    while (HAL_GPIO_ReadPin (C1_PORT, C1_PIN) == 0);
    return '7';
  }

  if (HAL_GPIO_ReadPin (C2_PORT, C2_PIN) == 0)
  {
    while (HAL_GPIO_ReadPin (C2_PORT, C2_PIN) == 0);
    return '8';
  }

  if (HAL_GPIO_ReadPin (C3_PORT, C3_PIN) == 0)
  {
    while (HAL_GPIO_ReadPin (C3_PORT, C3_PIN) == 0);
    return '9';
  }

  HAL_GPIO_WritePin (R1_PORT, R1_PIN, GPIO_PIN_SET);
  HAL_GPIO_WritePin (R2_PORT, R2_PIN, GPIO_PIN_SET);
  HAL_GPIO_WritePin (R3_PORT, R3_PIN, GPIO_PIN_SET);
  HAL_GPIO_WritePin (R4_PORT, R4_PIN, GPIO_PIN_RESET);

  if (HAL_GPIO_ReadPin (C1_PORT, C1_PIN) == 0)
  {
    while (HAL_GPIO_ReadPin (C1_PORT, C1_PIN) == 0);
    return '+';
  }

  if (HAL_GPIO_ReadPin (C2_PORT, C2_PIN) == 0)
  {
    while (HAL_GPIO_ReadPin (C2_PORT, C2_PIN) == 0);
    return '0';
  }

  if (HAL_GPIO_ReadPin (C3_PORT, C3_PIN) == 0)
  {
    while (HAL_GPIO_ReadPin (C3_PORT, C3_PIN) == 0);
    return '-';
  }

  return 't';

  }

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

/* Configure the peripherals common clocks */
  PeriphCommonClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_USB_PCD_Init();

  uint8_t data[]="Calculator Program\r\n";
  HAL_UART_Transmit(&huart1, data, sizeof(data), HAL_MAX_DELAY);

  uint8_t newline[] = "\r\n";
  uint8_t key;

  char currentOperand[100];
  int currentOperandIndex = 0;

  int currentNumberInteger = 0;

  int operands[20];
  int operandIndex = 0;

  char operations[20];
  int operationsIndex = 0;

  long total = 0;

  while (1)
  {
	  key = get_keypad_input();

	  if (key != 't') // if a key was pressed and the default value t was not returned
	  {
		  // buffer characters into an array
		  HAL_UART_Transmit(&huart1, &key, 1, HAL_MAX_DELAY);
		  currentOperand[currentOperandIndex] = key;
		  currentOperandIndex = currentOperandIndex + 1;
	  }

	  if (key == '+')
	  {
		  // convert the characters buffered in to a whole integer
		  // store the integer into a an array of operands
		  currentNumberInteger = atoi(currentOperand);
		  operands[operandIndex] = currentNumberInteger;
		  operandIndex = operandIndex + 1;

		  // store addition into array of operators
		  operations[operationsIndex] = '+';
		  operationsIndex = operationsIndex + 1;

		  // clear the current character buffer
		  bzero(currentOperand, sizeof(currentOperand));
		  currentOperandIndex = 0;
	  }
	  else if(key == '-')
	  {
		  // convert the characters buffered in to a whole integer
		  // store the integer into a an array of operands
		  currentNumberInteger = atoi(currentOperand);
		  operands[operandIndex] = currentNumberInteger;
		  operandIndex = operandIndex + 1;

		  // store subtraction into array of operators
		  operations[operationsIndex] = '-';
		  operationsIndex = operationsIndex + 1;

		  // clear the current character buffer
		  bzero(currentOperand, sizeof(currentOperand));
		  currentOperandIndex = 0;
	  }

	  // this is the clear pushbutton on the Nucleo board
	  // create a new line and clear all arrays to 0
	  if (HAL_GPIO_ReadPin (GPIOD, GPIO_PIN_0) == 0)
	  {
		  HAL_UART_Transmit(&huart1, newline, sizeof(newline), HAL_MAX_DELAY);
		  HAL_Delay(200);

		  bzero(currentOperand, sizeof(currentOperand));
		  bzero(operands, sizeof(operands));
		  bzero(operations, sizeof(operations));
		  operandIndex = 0;
		  operationsIndex = 0;
		  currentOperandIndex = 0;
		  currentNumberInteger = 0;
	  }
	  // this is the sum button on the Nucleo board
	  // add or subtract operands based on the array of operators
	  // clear all arrays
	  else if (HAL_GPIO_ReadPin (GPIOD, GPIO_PIN_1) == 0)
	  {
		  currentNumberInteger = atoi(currentOperand);
		  operands[operandIndex] = currentNumberInteger;

		  total = operands[0];

		  for (int x = 0; x < operationsIndex ; x++)
		  {
			  if (operations[x] == '+')
			      total = total + operands[x + 1];
			  else
				  total = total - operands[x + 1];
		  }

		  HAL_UART_Transmit(&huart1, "=", 1, HAL_MAX_DELAY);
		  HAL_UART_Transmit(&huart1, (uint8_t*)currentOperand, sprintf(currentOperand,"%d", total), HAL_MAX_DELAY);

		  bzero(currentOperand, sizeof(currentOperand));
		  bzero(operands, sizeof(operands));
		  bzero(operations, sizeof(operations));
		  operandIndex = 0;
		  operationsIndex = 0;
		  currentOperandIndex = 0;
		  currentNumberInteger = 0;
		  total = 0;

		  HAL_UART_Transmit(&huart1, newline, sizeof(newline), HAL_MAX_DELAY);
		  HAL_Delay(200);
	  }
	  //HAL_UART_Transmit(&huart1, (uint8_t*)currentOperand, sprintf(currentOperand,"%d", currentNumberInteger), HAL_MAX_DELAY);
	  //HAL_UART_Transmit(&huart1, currentOperand, sizeof(currentOperand), HAL_MAX_DELAY);
  }


}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Macro to configure the PLL multiplication factor
  */
  __HAL_RCC_PLL_PLLM_CONFIG(RCC_PLLM_DIV1);
  /** Macro to configure the PLL clock source
  */
  __HAL_RCC_PLL_PLLSOURCE_CONFIG(RCC_PLLSOURCE_MSI);
  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);
  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSE
                              |RCC_OSCILLATORTYPE_LSE|RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure the SYSCLKSource, HCLK, PCLK1 and PCLK2 clocks dividers
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK4|RCC_CLOCKTYPE_HCLK2
                              |RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.AHBCLK2Divider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLK4Divider = RCC_SYSCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Enable MSI Auto calibration
  */
  HAL_RCCEx_EnableMSIPLLMode();
}

/**
  * @brief Peripherals Common Clock Configuration
  * @retval None
  */
void PeriphCommonClock_Config(void)
{
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Initializes the peripherals clock
  */
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SMPS;
  PeriphClkInitStruct.SmpsClockSelection = RCC_SMPSCLKSOURCE_HSI;
  PeriphClkInitStruct.SmpsDivSelection = RCC_SMPSCLKDIV_RANGE0;

  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN Smps */

  /* USER CODE END Smps */
}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USB Initialization Function
  * @param None
  * @retval None
  */
static void MX_USB_PCD_Init(void)
{

  /* USER CODE BEGIN USB_Init 0 */

  /* USER CODE END USB_Init 0 */

  /* USER CODE BEGIN USB_Init 1 */

  /* USER CODE END USB_Init 1 */
  hpcd_USB_FS.Instance = USB;
  hpcd_USB_FS.Init.dev_endpoints = 8;
  hpcd_USB_FS.Init.speed = PCD_SPEED_FULL;
  hpcd_USB_FS.Init.phy_itface = PCD_PHY_EMBEDDED;
  hpcd_USB_FS.Init.Sof_enable = DISABLE;
  hpcd_USB_FS.Init.low_power_enable = DISABLE;
  hpcd_USB_FS.Init.lpm_enable = DISABLE;
  hpcd_USB_FS.Init.battery_charging_enable = DISABLE;
  if (HAL_PCD_Init(&hpcd_USB_FS) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USB_Init 2 */

  /* USER CODE END USB_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2|GPIO_PIN_3, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|GPIO_PIN_1, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LD2_Pin|LD3_Pin|LD1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PC2 PC3 */
  GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA0 PA1 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PA2 PA3 */
  GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PC4 PC6 */
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : LD2_Pin LD3_Pin LD1_Pin */
  GPIO_InitStruct.Pin = LD2_Pin|LD3_Pin|LD1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : B2_Pin B3_Pin */
  GPIO_InitStruct.Pin = B2_Pin|B3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

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

