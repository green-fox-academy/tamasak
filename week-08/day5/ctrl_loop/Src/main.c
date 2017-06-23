/**
  ******************************************************************************
  * @file    Templates/Src/main.c 
  * @author  MCD Application Team
  * @version V1.0.3
  * @date    22-April-2016 
  * @brief   STM32F7xx HAL API Template project 
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32746g_discovery_lcd.h"
#include "stm32f7xx_hal_adc.h"

/** @addtogroup STM32F7xx_HAL_Examples
  * @{
  */

/** @addtogroup Templates
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
typedef struct {
	uint32_t ovf;
	uint32_t prev;
	uint32_t last;
} input_capture_data_t;

/* Private define ------------------------------------------------------------*/
//#define USE_P_CTRLER
volatile uint32_t overflow_num = 0;
volatile uint32_t overflow_tmp = 0;
volatile uint32_t cnt_state = 0;
volatile uint32_t cnt_state_prev = 0;


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef tim3_handle;
TIM_HandleTypeDef tim2_handle;

/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
static void Error_Handler(void);
static void MPU_Config(void);
static void CPU_CACHE_Enable(void);
void HAL_ADC_MspInit(ADC_HandleTypeDef *hadc);

/* Private functions ---------------------------------------------------------*/
// ADC:
ADC_HandleTypeDef    AdcHandle;
/* Variable used to get converted value */
__IO uint16_t uhADCxConvertedValue = 0;

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */

int main(void)
{
  /* This project template calls firstly two functions in order to configure MPU feature
     and to enable the CPU Cache, respectively MPU_Config() and CPU_CACHE_Enable().
     These functions are provided as template implementation that User may integrate
     in his application, to enhance the performance in case of use of AXI interface
     with several masters. */

  /* Configure the MPU attributes as Write Through */
  MPU_Config();

  /* Enable the CPU Cache */
  CPU_CACHE_Enable();

  /* STM32F7xx HAL library initialization:
       - Configure the Flash ART accelerator on ITCM interface
       - Configure the Systick to generate an interrupt each 1 msec
       - Set NVIC Group Priority to 4
       - Low Level Initialization
     */
  HAL_Init();

  /* Configure the System clock to have a frequency of 216 MHz */
  SystemClock_Config();


  /* Add your application code here */
  // LCD:
  BSP_LCD_Init();
  BSP_LCD_LayerDefaultInit(0, LCD_FB_START_ADDRESS);
  BSP_LCD_SelectLayer(0);
  BSP_LCD_DisplayOn();
  BSP_LCD_Clear(LCD_COLOR_BLACK);
  BSP_LED_Init(LED_GREEN);

  // timer 3 for pwm:
  tim3_handle.Instance = TIM3;
  tim3_handle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  //tim3_handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  tim3_handle.Init.CounterMode = TIM_COUNTERMODE_UP;
  tim3_handle.Init.Period = 4096;
  tim3_handle.Init.Prescaler = 1;
  tim3_handle.Init.RepetitionCounter = 0;
  tim3_handle.State = HAL_TIM_STATE_RESET;
  tim3_handle.Channel = HAL_TIM_ACTIVE_CHANNEL_1;
  HAL_TIM_PWM_Init(&tim3_handle);
  //HAL_TIM_PWM_MspInit(&tim3_handle);
  TIM_OC_InitTypeDef tim_ocinit_struct;
  // ?
  tim_ocinit_struct.OCMode = TIM_OCMODE_PWM1;
  tim_ocinit_struct.OCFastMode = TIM_OCFAST_DISABLE;
  tim_ocinit_struct.Pulse = 0;
  tim_ocinit_struct.OCIdleState = TIM_OCIDLESTATE_RESET;
  tim_ocinit_struct.OCPolarity = TIM_OCPOLARITY_HIGH;
  HAL_TIM_OC_ConfigChannel(&tim3_handle, &tim_ocinit_struct, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&tim3_handle, TIM_CHANNEL_1);

  //timer 2 for input capture
  tim2_handle.Instance = TIM2;
  tim2_handle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  //tim3_handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  tim2_handle.Init.CounterMode = TIM_COUNTERMODE_UP;
  tim2_handle.Init.Period = 0xFFFF;
  tim2_handle.Init.Prescaler = 1;
  tim2_handle.Init.RepetitionCounter = 0;
  tim2_handle.State = HAL_TIM_STATE_RESET;
  tim2_handle.Channel = HAL_TIM_ACTIVE_CHANNEL_1;
  HAL_TIM_PWM_Init(&tim3_handle);
  //HAL_TIM_PWM_MspInit(&tim3_handle);
  TIM_OC_InitTypeDef tim2_ocinit_struct;
  // ?
  tim2_ocinit_struct.OCMode = TIM_OCMODE_TIMING;
  tim2_ocinit_struct.OCFastMode = TIM_OCFAST_DISABLE;
  tim2_ocinit_struct.Pulse = 0;
  tim2_ocinit_struct.OCIdleState = TIM_OCIDLESTATE_RESET;
  tim2_ocinit_struct.OCPolarity = TIM_OCPOLARITY_HIGH;
  HAL_TIM_IC_Start_IT(&tim2_ocinit_struct, TIM_CHANNEL_1);
  HAL_TIM_Base_Start_IT(&tim2_ocinit_struct);

  // ADC:
  ADC_ChannelConfTypeDef sConfig;
  AdcHandle.Instance          = ADC3;
  AdcHandle.Init.ClockPrescaler        = ADC_CLOCKPRESCALER_PCLK_DIV4;
  AdcHandle.Init.Resolution            = ADC_RESOLUTION_12B;
  AdcHandle.Init.ScanConvMode          = DISABLE;                       /* Sequencer disabled (ADC conversion on only 1 channel: channel set on rank 1) */
  AdcHandle.Init.ContinuousConvMode    = ENABLE;                       /* Continuous mode enabled to have continuous conversion  */
  AdcHandle.Init.DiscontinuousConvMode = DISABLE;                       /* Parameter discarded because sequencer is disabled */
  AdcHandle.Init.NbrOfDiscConversion   = 0;
  AdcHandle.Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_NONE;        /* Conversion start trigged at each external event */
  AdcHandle.Init.ExternalTrigConv      = ADC_EXTERNALTRIGCONV_T1_CC1;
  AdcHandle.Init.DataAlign             = ADC_DATAALIGN_RIGHT;
  AdcHandle.Init.NbrOfConversion       = 1;
  AdcHandle.Init.DMAContinuousRequests = DISABLE;
  AdcHandle.Init.EOCSelection          = DISABLE;

  sConfig.Channel      = ADC_CHANNEL_0;
  sConfig.Rank         = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  sConfig.Offset       = 0;

  HAL_ADC_Init(&AdcHandle);
  HAL_ADC_Start(&AdcHandle);
  HAL_ADC_ConfigChannel(&AdcHandle, &sConfig);
  HAL_ADC_MspInit(&AdcHandle);
  //HAL_ADC_Start_DMA(&AdcHandle, (uint32_t*)&uhADCxConvertedValue, 1);


  //int8_t cntr = 0;
  int32_t adc_value = 0;
  /* Infinite loop */
  while (1)
  {
	  HAL_ADC_Start(&AdcHandle);
	  HAL_ADC_PollForConversion(&AdcHandle, 10);
	  adc_value = HAL_ADC_GetValue(&AdcHandle);
	  tim_ocinit_struct.Pulse = adc_value;
	  HAL_TIM_OC_ConfigChannel(&tim3_handle, &tim_ocinit_struct, TIM_CHANNEL_1);
	  HAL_TIM_PWM_Start(&tim3_handle, TIM_CHANNEL_1);
	  char buff[100];
	  //sprintf(buff, "%d", cntr);
	  //BSP_LCD_ClearStringLine(0);
	  //BSP_LCD_DisplayStringAtLine(0, (uint8_t *)buff);
	  sprintf(buff, "%d", adc_value);
	  BSP_LCD_ClearStringLine(1);
	  BSP_LCD_DisplayStringAtLine(1, (uint8_t *)buff);
	  //cntr++;
	  BSP_LED_Toggle(LED_GREEN);
	  HAL_Delay(10);

  }
}

void TIM4_IRQHandler()
{
	HAL_TIM_IRQHandler(&tim3_handle);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	BSP_LED_Toggle(LED_GREEN);
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
	__HAL_RCC_TIM4_CLK_ENABLE();
	HAL_NVIC_SetPriority(TIM4_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(TIM4_IRQn);
}


/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 216000000
  *            HCLK(Hz)                       = 216000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 25000000
  *            PLL_M                          = 25
  *            PLL_N                          = 432
  *            PLL_P                          = 2
  *            PLL_Q                          = 9
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 7
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_OFF;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 432;  
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 9;
  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /* activate the OverDrive to reach the 216 Mhz Frequency */
  if(HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }
  
  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;  
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void Error_Handler(void)
{
  /* User may add here some code to deal with this error */
  while(1)
  {
  }
}

/**
  * @brief  Configure the MPU attributes as Write Through for SRAM1/2.
  * @note   The Base Address is 0x20010000 since this memory interface is the AXI.
  *         The Region Size is 256KB, it is related to SRAM1 and SRAM2  memory size.
  * @param  None
  * @retval None
  */
static void MPU_Config(void)
{
  MPU_Region_InitTypeDef MPU_InitStruct;
  
  /* Disable the MPU */
  HAL_MPU_Disable();

  /* Configure the MPU attributes as WT for SRAM */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.BaseAddress = 0x20010000;
  MPU_InitStruct.Size = MPU_REGION_SIZE_256KB;
  MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.SubRegionDisable = 0x00;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);

  /* Enable the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
}

/**
  * @brief  CPU L1-Cache enable.
  * @param  None
  * @retval None
  */
static void CPU_CACHE_Enable(void)
{
  /* Enable I-Cache */
  SCB_EnableICache();

  /* Enable D-Cache */
  SCB_EnableDCache();
}
void HAL_ADC_MspInit(ADC_HandleTypeDef *hadc)
{
  __HAL_RCC_ADC3_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
