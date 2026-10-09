/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "dma.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Run.h"
#include <stdint.h>  // 新增：用于标准整数类型定义
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
// 新增：SR602人体红外传感器引脚定义（根据实际硬件修改）
//#define SR602_PIN    GPIO_PIN_1
//#define SR602_PORT   GPIOC

// 新增：OLED屏幕控制引脚定义（根据实际硬件修改）
//#define OLED_POWER_PIN    GPIO_PIN_2
//#define OLED_POWER_PORT   GPIOC

// 新增：OLED亮屏超时时间（3分钟，单位：毫秒）
//#define OLED_TIMEOUT_MS   180000
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
// 新增：状态变量
//uint8_t oled_on_flag = 0;       // OLED状态：0-关闭，1-开启
//uint32_t oled_on_timestamp = 0; // 记录OLED开启的时间戳
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
// 新增：函数声明
//void SR602_Init(void);          // 初始化人体传感器
//uint8_t SR602_Detect(void);     // 检测是否有人靠近
//void OLED_SetPower(uint8_t on); // 控制OLED电源
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
// 新增：初始化SR602传感器（配置为输入模式）
//void SR602_Init(void)
//{
//  GPIO_InitTypeDef GPIO_InitStruct = {0};
//  
//  // 使能传感器所在GPIO端口时钟
//  __HAL_RCC_GPIOC_CLK_ENABLE();
//  
//  // 配置传感器引脚为输入，启用内部上拉（SR602检测到人体输出高电平）
//  GPIO_InitStruct.Pin = SR602_PIN;
//  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
//  GPIO_InitStruct.Pull = GPIO_PULLUP;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//  HAL_GPIO_Init(SR602_PORT, &GPIO_InitStruct);
//}

//// 新增：检测人体靠近状态
//uint8_t SR602_Detect(void)
//{
//  // 返回1表示检测到人体，0表示未检测到（根据传感器实际输出电平调整）
//  return HAL_GPIO_ReadPin(SR602_PORT, SR602_PIN);
//}

// 新增：控制OLED电源（0-关闭，1-开启）
//void OLED_SetPower(uint8_t on)
//{
//  if (on)
//  {
//    // 开启OLED（根据实际电路修改，此处假设高电平开启）
//    HAL_GPIO_WritePin(OLED_POWER_PORT, OLED_POWER_PIN, GPIO_PIN_SET);
//    oled_on_flag = 1;
//    oled_on_timestamp = HAL_GetTick(); // 记录开启时间
//  }
//  else
//  {
//    // 关闭OLED
//    HAL_GPIO_WritePin(OLED_POWER_PORT, OLED_POWER_PIN, GPIO_PIN_RESET);
//    oled_on_flag = 0;
//  }
//}
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
  MX_DMA_Init();
  MX_I2C1_Init();
  MX_USART2_UART_Init();
  MX_USART1_UART_Init();
  MX_TIM6_Init();
  /* USER CODE BEGIN 2 */
  Run_Init();
//  SR602_Init();               // 新增：初始化人体传感器
//  OLED_SetPower(0);           // 新增：初始关闭OLED（满足"一开始屏幕暗"）
  uint16_t action;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    Run();
    
    // 新增：人体检测逻辑
//    if (SR602_Detect() == 1)  // 检测到有人靠近
//    {
//      if (oled_on_flag == 0)  // 如果当前OLED是关闭的
//      {
//        OLED_SetPower(1);     // 点亮OLED
//      }
//      else                    // 如果已经点亮
//      {
//        oled_on_timestamp = HAL_GetTick(); // 刷新超时计时（重新计算3分钟）
//      }
//    }
//    
//    // 新增：超时关闭逻辑（无人靠近时，3分钟后自动关闭）
//    if (oled_on_flag == 1)
//    {
//      if ((HAL_GetTick() - oled_on_timestamp) >= OLED_TIMEOUT_MS)
//      {
//        OLED_SetPower(0);     // 超时关闭
//      }
//    }
	
    
//    HAL_Delay(200);  // 新增：降低检测频率，减少CPU占用
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
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
#ifdef USE_FULL_ASSERT
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
