/* Includes ------------------------------------------------------------------*/
#include "led_matrix.h"
#include "stm32f7xx_hal.h"
#include "lcd_log.h"
#include "cmsis_os.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

// Each LED state is stored in this 2D array
GPIO_PinState led_matrix_state[LED_MATRIX_ROWS][LED_MATRIX_COLS] = {
		   {1, 1, 1, 1, 1} ,
		   {1, 0, 1, 1, 1} ,
		   {0, 1, 1, 1, 0} ,
		   {0, 1, 1, 1, 1} ,
		   {0, 1, 1, 1, 0} ,
		   {1, 0, 1, 1, 1} ,
		   {1, 1, 1, 1, 1}
};

// Mutex definition
osMutexDef(LED_MATRIX_MUTEX_DEF);
// Mutex global variable
osMutexId led_matrix_mutex_id;
/* ADC handler declaration */
ADC_HandleTypeDef AdcHandle;

/* Variable used to get converted value */
__IO uint16_t uhADCxConvertedValue = 0;
uint32_t adc_value = 50;

/* Private function prototypes -----------------------------------------------*/
void led_matrix_set(uint8_t row, uint8_t col, uint8_t state);
/* Private functions ---------------------------------------------------------*/

// TODO:
// Write this function!
void led_matrix_set(uint8_t row, uint8_t col, uint8_t state) { // beallitja a tombben az ertekeket
	// TODO:
	// Wait for the mutex
	osStatus status;
	if (led_matrix_mutex_id != NULL)  {
		status = osMutexWait (led_matrix_mutex_id, 0);
	}

	// TODO:
	// Change the LED in the selected row and col to the specified state
	// Use the led_matrix_state 2D array variable!
	led_matrix_state[row][col] = !state;


	// TODO:
	// Release the mutex
	if (led_matrix_mutex_id != NULL)  {
		status = osMutexRelease(led_matrix_mutex_id);
	}
}

// TODO:
// Write this function!
void led_matrix_update_thread(void const *argument) // kirajzoltatja a tombben levo dolgokat
{
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOI_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();

	GPIO_InitTypeDef gpio_init_b;
	gpio_init_b.Pin = GPIO_PIN_4 | GPIO_PIN_9;
	gpio_init_b.Pull = GPIO_NOPULL;
	gpio_init_b.Mode = GPIO_MODE_OUTPUT_PP;
	gpio_init_b.Speed = GPIO_SPEED_FREQ_MEDIUM;

	GPIO_InitTypeDef gpio_init_i;
	gpio_init_i.Pin = GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_0;
	gpio_init_i.Pull = GPIO_NOPULL;
	gpio_init_i.Mode = GPIO_MODE_OUTPUT_PP;
	gpio_init_i.Speed = GPIO_SPEED_FREQ_MEDIUM;

	GPIO_InitTypeDef gpio_init_c;
	gpio_init_c.Pin = GPIO_PIN_6 | GPIO_PIN_7;
	gpio_init_c.Pull = GPIO_NOPULL;
	gpio_init_c.Mode = GPIO_MODE_OUTPUT_PP;
	gpio_init_c.Speed = GPIO_SPEED_FREQ_MEDIUM;

	GPIO_InitTypeDef gpio_init_g;
	gpio_init_g.Pin = GPIO_PIN_6 | GPIO_PIN_7;
	gpio_init_g.Pull = GPIO_NOPULL;
	gpio_init_g.Mode = GPIO_MODE_OUTPUT_PP;
	gpio_init_g.Speed = GPIO_SPEED_FREQ_MEDIUM;

	GPIO_InitTypeDef gpio_init_h;
	gpio_init_h.Pin = GPIO_PIN_6;
	gpio_init_h.Pull = GPIO_NOPULL;
	gpio_init_h.Mode = GPIO_MODE_OUTPUT_PP;
	gpio_init_h.Speed = GPIO_SPEED_FREQ_MEDIUM;

	GPIO_InitTypeDef gpio_init_a;
	gpio_init_a.Pin = GPIO_PIN_8 | GPIO_PIN_15;
	gpio_init_a.Pull = GPIO_NOPULL;
	gpio_init_a.Mode = GPIO_MODE_OUTPUT_PP;
	gpio_init_a.Speed = GPIO_SPEED_FREQ_MEDIUM;

	// TODO:
	// Initialize the pins as outputs and the led_matrix_state 2D array
	HAL_GPIO_Init(GPIOC, &gpio_init_c);
	HAL_GPIO_Init(GPIOG, &gpio_init_g);
	HAL_GPIO_Init(GPIOB, &gpio_init_b);
	HAL_GPIO_Init(GPIOI, &gpio_init_i);
	HAL_GPIO_Init(GPIOA, &gpio_init_a);
	HAL_GPIO_Init(GPIOH, &gpio_init_h);

	/*HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOI, GPIO_PIN_2, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_7, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOI, GPIO_PIN_0, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOI, GPIO_PIN_3, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOI, GPIO_PIN_1, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOH, GPIO_PIN_6, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);*/
	HAL_GPIO_WritePin(GPIOI, GPIO_PIN_1, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOI, GPIO_PIN_2, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOI, GPIO_PIN_0, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOI, GPIO_PIN_3, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_6, GPIO_PIN_SET);


	// TODO:
	// Create a mutex
	// Use the LED_MATRIX_MUTEX_DEF
	led_matrix_mutex_id = osMutexCreate  (osMutex (LED_MATRIX_MUTEX_DEF));
	if (led_matrix_mutex_id != NULL)  {
		// Mutex object created
	}

	LCD_UsrLog("led_matrix - initialized\n");
	//led_matrix_state[][] = {

	// Infinite loop
	while (1) {
		// TODO:
		// Implement the led matrix updater functionality

		// Step 1:
		// Iterate through every column or row
		int col;
		for (col = 0; col < LED_MATRIX_ROWS; col++) {

			// Step 2:
			// Wait for the mutex
			osStatus status;
			if (led_matrix_mutex_id != NULL)  {
			    status = osMutexWait (led_matrix_mutex_id, 0);
			}
			// Step 3:
			// Turn on the column or row
			switch (col) {
			case 0:
				HAL_GPIO_WritePin(GPIOI, GPIO_PIN_1, GPIO_PIN_SET);
				break;
			case 1:
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
				break;
			case 2:
				HAL_GPIO_WritePin(GPIOG, GPIO_PIN_7, GPIO_PIN_SET);
				break;
			case 3:;
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
				break;
			case 4:
				HAL_GPIO_WritePin(GPIOH, GPIO_PIN_6, GPIO_PIN_SET);
				break;
			}
			// Step 4:
			// Turn on the leds in that column or row
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, led_matrix_state[0][col]);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, led_matrix_state[1][col]);
			HAL_GPIO_WritePin(GPIOI, GPIO_PIN_2, led_matrix_state[2][col]);
			HAL_GPIO_WritePin(GPIOI, GPIO_PIN_0, led_matrix_state[3][col]);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, led_matrix_state[4][col]);
			HAL_GPIO_WritePin(GPIOI, GPIO_PIN_3, led_matrix_state[5][col]);
			HAL_GPIO_WritePin(GPIOG, GPIO_PIN_6, led_matrix_state[6][col]);


			// Step 5:
			// Release the mutex
			if (led_matrix_mutex_id != NULL)  {
				status = osMutexRelease(led_matrix_mutex_id);
			}

			// Step 6:
			// Delay
			osDelay(1);

			// Step 7:
			// Turn off the column or row
			HAL_GPIO_WritePin(GPIOI, GPIO_PIN_1, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOG, GPIO_PIN_7, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOH, GPIO_PIN_6, GPIO_PIN_RESET);
		}
	}

	// Terminating thread
	while (1) {
		LCD_ErrLog("led_matrix - terminating...\n");
		osThreadTerminate(NULL);
	}
}

// This thread is a waterfall type animation
void led_matrix_waterfall_thread(void const *argument)
{
	while (1) {
		for (uint8_t r = 0; r < LED_MATRIX_ROWS; r++) {
			for (uint8_t c = 0; c < LED_MATRIX_COLS; c++) {
				led_matrix_set(r, c, 1);
				//osDelay(50);
				osDelay(adc_value / 10);
				led_matrix_set(r, c, 0);
			}
		}
	}

	while (1) {
		LCD_ErrLog("led_matrix_waterfall - terminating...\n");
		osThreadTerminate(NULL);
	}
}

void adc_speed(void)
{
	//__HAL_RCC_ADC_CLK_ENABLE();
	//HAL_ADC_MspInit()
	// __HAL_RCC_GPIOA_CLK_ENABLE(); //korabban meghivva
	// HAL_GPIO_Init() // korabban meghivva
	ADC_ChannelConfTypeDef sConfig;

	AdcHandle.Instance = ADC3;

	AdcHandle.Init.ClockPrescaler        = ADC_CLOCKPRESCALER_PCLK_DIV4;
	AdcHandle.Init.Resolution            = ADC_RESOLUTION_12B;
	AdcHandle.Init.ScanConvMode          = DISABLE;                       /* Sequencer disabled (ADC conversion on only 1 channel: channel set on rank 1) */
	AdcHandle.Init.ContinuousConvMode    = DISABLE;
	AdcHandle.Init.DiscontinuousConvMode = DISABLE;                       /* Parameter discarded because sequencer is disabled */
	AdcHandle.Init.NbrOfDiscConversion   = 0;
	AdcHandle.Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_NONE;        /* Conversion start trigged at each external event */
	AdcHandle.Init.ExternalTrigConv      = ADC_EXTERNALTRIGCONV_T1_CC1;
	AdcHandle.Init.DataAlign             = ADC_DATAALIGN_RIGHT;
	AdcHandle.Init.NbrOfConversion       = 1;
	AdcHandle.Init.DMAContinuousRequests = DISABLE;
	AdcHandle.Init.EOCSelection          = DISABLE;



	HAL_ADC_Init(&AdcHandle);

	/*##-2- Configure ADC regular channel ######################################*/
	sConfig.Channel      = ADC_CHANNEL_0;
	sConfig.Rank         = 1;
	sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
	sConfig.Offset       = 0;

	HAL_ADC_ConfigChannel(&AdcHandle, &sConfig);


	/*##-3- Start the conversion process #######################################*/
	//HAL_ADC_Start(&AdcHandle);
	//HAL_ADC_PollForConversion(&AdcHandle, 1000); // Wait for end of conversion

	/* Infinite loop */
	while (1)
	{
		HAL_ADC_Start(&AdcHandle);
		HAL_ADC_PollForConversion(&AdcHandle, 50);
		adc_value = HAL_ADC_GetValue(&AdcHandle);
		printf("%d\n", adc_value);
		osDelay(10);
		HAL_ADC_Stop(&AdcHandle);
	}
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
