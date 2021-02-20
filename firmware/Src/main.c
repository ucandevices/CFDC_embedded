/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under Ultimate Liberty license
 * SLA0044, the "License"; You may not use this file except in compliance with
 * the License. You may obtain a copy of the License at:
 *                             www.st.com/SLA0044
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ucan_fd_protocol_stm32g431.h"
#include "RING.h"
#include "usbd_cdc.h"
#include "dwt_delay.h"
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
FDCAN_HandleTypeDef hfdcan1;
WWDG_HandleTypeDef hwwdg;
/* USER CODE BEGIN PV */
Ring_type usb_rx;
Ring_type usb_tx;
static volatile int i = 0;
uint8_t gotoboot_flag = 0;
uint32_t status_sys_tick;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_WWDG_Init(void);
void MX_FDCAN1_Init(void);
/* USER CODE BEGIN PFP */
extern USBD_HandleTypeDef hUsbDeviceFS;
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

UCAN_RxFrameDef can_rx_frame = { UCAN_FD_RX,	// frame_type
		{ }, //FDCAN_RxHeaderTypeDef
		{ }, //can_data
		{ }, //FDCAN_ProtocolStatusTypeDef
		{ 0x1A, 0x2B, 0x3C, 0x4D }, //FDCAN_ErrorCountersTypeDef
		};

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
volatile static int counter = 1;
extern void TurnOffBoot0();
int main(void) {

	/* USER CODE BEGIN 1 */
	TurnOffBoot0();
	TurnOffBoot0();
	/* USER CODE END 1 */
	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */
	DWT_Init();

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();
	MX_WWDG_Init();
	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_USB_Device_Init();
	MX_FDCAN1_Init();

	/* USER CODE BEGIN 2 */
	HAL_FDCAN_Start(&hfdcan1);

	RING_init(&usb_rx);
	RING_init(&usb_tx);

	for (uint8_t i = 0; i < 10; i++) {
		HAL_Delay(i * 10);
		HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
	}

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
//	while (1){
//
//		static uint8_t TxData[8];
//		static FDCAN_TxHeaderTypeDef TxHeader;
//			  /* Prepare Tx Header */
//			  TxHeader.Identifier = 0x321;
//			  TxHeader.IdType = FDCAN_STANDARD_ID;
//			  TxHeader.TxFrameType = FDCAN_DATA_FRAME;
//			  TxHeader.DataLength = FDCAN_DLC_BYTES_8;
//			  TxHeader.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
//			  TxHeader.BitRateSwitch = FDCAN_BRS_OFF;
//			  TxHeader.FDFormat = FDCAN_CLASSIC_CAN;
//			  TxHeader.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
//			  TxHeader.MessageMarker = 0;
//
//			  while(1) {
//			  		HAL_Delay(1000);
//			  		/* Set the data to be transmitted */
//			  		TxData[0] = 1;
//			  		TxData[1] = 0xAD;
//			  		TxData[7] = 0x36;
//			  		/* Start the Transmission process */
//			  		if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxHeader, TxData) != HAL_OK)
//			  		{
//			  		  /* Transmission request Error */
//			  		  Error_Handler();
//			  		}
//
//					volatile uint32_t rx_fill = HAL_FDCAN_GetRxFifoFillLevel(&hfdcan1,
//					FDCAN_RX_FIFO0);
//			  }
//	}
	while (1) {
		volatile uint32_t rx_fill = HAL_FDCAN_GetRxFifoFillLevel(&hfdcan1,
		FDCAN_RX_FIFO0);
		volatile uint32_t tx_fill = HAL_FDCAN_GetTxFifoFreeLevel(&hfdcan1);
		static Ring_item *data_ptr;

		HAL_WWDG_Refresh(&hwwdg);

		data_ptr = RING_get(&usb_rx);
		if (data_ptr->data != NULL) {
			FDCAN_InitTypeDef init_values;
			if (UCAN_execute_USB_to_CAN_frame(data_ptr->data) == 0)
				;
		}

//		if (RING_is_empty(&usb_tx) == 0) {
			//last delay
			volatile uint32_t systic = HAL_GetTick();
//				DWT_Delay(300); /*300 us delay workaround for short frames  (@TODO fix this and test against 1 byte CAN data frame )*/
				if (DWT_us_Timer_Done() == 1) /*non blocking workaround*/
				{
					data_ptr = RING_get(&usb_tx);
					if (data_ptr->len != 0) {
						while (CDC_Transmit_FS(data_ptr->data, data_ptr->len) == USBD_BUSY);
						status_sys_tick = HAL_GetTick();
						if (gotoboot_flag == 1) {
							for (uint8_t i = 0; i < 5; i++) {
								HAL_Delay(i * 200);
								HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
							}
							RebootToBootloader();
						}
					}
				}
//		}

		/* reset device if no status frames */
		if ((HAL_GetTick() - status_sys_tick) > 5000)
			HAL_NVIC_SystemReset();

		if (rx_fill >= 1) {
			static FDCAN_RxHeaderTypeDef rx_h;
			static uint8_t pRxData[64];
			if (HAL_FDCAN_GetRxMessage(&hfdcan1, FDCAN_RX_FIFO0,
					&(can_rx_frame.can_rx_header), can_rx_frame.can_data)
					== HAL_OK) {

				HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
				i++;
				// can_rx_frame.can_rx_header.Identifier = i; // debug frame sequence 
				DWT_us_Timer_Start(300);// non blocking workaround for 300 usDelay
				RING_put(&usb_tx, &can_rx_frame, sizeof(can_rx_frame));
			}
		}
		/* USER CODE END WHILE */
		/* USER CODE BEGIN 3 */
	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };
	RCC_PeriphCLKInitTypeDef PeriphClkInit = { 0 };

	/** Configure the main internal regulator output voltage
	 */
	HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);
	/** Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV2;
	RCC_OscInitStruct.PLL.PLLN = 36;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV6;
	RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}
	/** Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK) {
		Error_Handler();
	}
	/** Initializes the peripherals clocks
	 */
	PeriphClkInit.PeriphClockSelection =
	RCC_PERIPHCLK_USB | RCC_PERIPHCLK_FDCAN;
	PeriphClkInit.FdcanClockSelection = RCC_FDCANCLKSOURCE_PCLK1;
	PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL;
	if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
		Error_Handler();
	}
}

/**
 * @brief FDCAN1 Initialization Function
 * @param None
 * @retval None
 */
void MX_FDCAN1_Init(void) {

	/* USER CODE BEGIN FDCAN1_Init 0 */

	/* USER CODE END FDCAN1_Init 0 */

	/* USER CODE BEGIN FDCAN1_Init 1 */

	/* USER CODE END FDCAN1_Init 1 */
	hfdcan1.Instance = FDCAN1;
	hfdcan1.Init.ClockDivider = FDCAN_CLOCK_DIV1;
	hfdcan1.Init.FrameFormat = FDCAN_FRAME_CLASSIC;
	hfdcan1.Init.Mode = FDCAN_MODE_NORMAL;
	hfdcan1.Init.AutoRetransmission = ENABLE;
	hfdcan1.Init.TransmitPause = DISABLE;
	hfdcan1.Init.ProtocolException = DISABLE;
	hfdcan1.Init.NominalPrescaler = 90;
	hfdcan1.Init.NominalSyncJumpWidth = 128;
	hfdcan1.Init.NominalTimeSeg1 = 13;
	hfdcan1.Init.NominalTimeSeg2 = 2;
	hfdcan1.Init.DataPrescaler = 1;
	hfdcan1.Init.DataSyncJumpWidth = 1;
	hfdcan1.Init.DataTimeSeg1 = 1;
	hfdcan1.Init.DataTimeSeg2 = 1;
	hfdcan1.Init.StdFiltersNbr = 0;
	hfdcan1.Init.ExtFiltersNbr = 0;
	hfdcan1.Init.TxFifoQueueMode = FDCAN_TX_FIFO_OPERATION;
	if (HAL_FDCAN_Init(&hfdcan1) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN FDCAN1_Init 2 */

	/* USER CODE END FDCAN1_Init 2 */

}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void) {
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOF_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin : LED_Pin */
	GPIO_InitStruct.Pin = LED_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct);

	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
	GPIO_InitStruct.Pin = GPIO_PIN_13;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */

	/* USER CODE END Error_Handler_Debug */
}

static void MX_WWDG_Init(void)
{

  /* USER CODE BEGIN WWDG_Init 0 */

  /* USER CODE END WWDG_Init 0 */

  /* USER CODE BEGIN WWDG_Init 1 */

  /* USER CODE END WWDG_Init 1 */
  hwwdg.Instance = WWDG;
  hwwdg.Init.Prescaler = WWDG_PRESCALER_1;
  hwwdg.Init.Window = 64;
  hwwdg.Init.Counter = 64;
  hwwdg.Init.EWIMode = WWDG_EWI_DISABLE;
  if (HAL_WWDG_Init(&hwwdg) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN WWDG_Init 2 */

  /* USER CODE END WWDG_Init 2 */

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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
