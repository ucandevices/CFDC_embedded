/*

The MIT License (MIT)

Copyright (c) 2022 Ryan Edwards

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permissSysion notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/

/* Includes ------------------------------------------------------------------*/
#include "board.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include "usbd_gs_can.h"
#include "can.h"
#include "led.h"

#define TASK_MY_PROGRAM_STACK_SIZE (512 / sizeof(portSTACK_TYPE))
#define TASK_MY_PROGRAM_PRIORITY   (tskIDLE_PRIORITY + 3)

extern void main_usbd_gs_can_set_channel_cb(USBD_HandleTypeDef *hUSB);

FDCAN_HandleTypeDef hfdcan1;
// FDCAN_HandleTypeDef hfdcan2;
LED_HandleTypeDef hled1;

extern USBD_GS_CAN_HandleTypeDef hGS_CAN;
extern TIM_HandleTypeDef htim2;

static TaskHandle_t xCreatedMyProgramTask;
static bool host_channel_is_active;

static void task_my_program(void *argument);

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

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
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the peripherals clocks
  */
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB|RCC_PERIPHCLK_FDCAN;
  PeriphClkInit.FdcanClockSelection = RCC_FDCANCLKSOURCE_PCLK1;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/** Configure pins
*/
void MX_GPIO_Init(void)
{

 GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(CAN_STBY_GPIO_Port, CAN_STBY_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = CAN_STBY_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(CAN_STBY_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct);
  
}

static void task_my_program(void *argument)
{
	UNUSED(argument);

	uint8_t prev_pressed_state = GPIO_PIN_SET;
	static struct gs_host_frame_object frame_object;

					// can_enable(hGS_CAN,
					// 		   (mode->flags & GS_CAN_MODE_LOOP_BACK) != 0,
					// 		   (mode->flags & GS_CAN_MODE_LISTEN_ONLY) != 0,
					// 		   (mode->flags & GS_CAN_MODE_ONE_SHOT) != 0,
					// 		   (mode->flags & GS_CAN_MODE_FD) != 0
					// 		   );

	/* Infinite loop */
	for (;;) {
		/* if GPIO is pressed then send*/
		
			// frame_object.frame.can_dlc = 8;
			// frame_object.frame.can_id = 0x111;
			// frame_object.frame.channel = 0;
			// frame_object.frame.echo_id = 0xFFFFFFFF;
			// frame_object.frame.flags = 0;
			// frame_object.frame.classic_can->data[0] = 0x11;
			// frame_object.frame.classic_can->data[1] = 0x22;
			// frame_object.frame.classic_can->data[2] = 0x34;
			// frame_object.frame.classic_can->data[3] = 0x44;
			// frame_object.frame.classic_can->data[4] = 0x55;
			// frame_object.frame.classic_can->data[5] = 0x66;
			// frame_object.frame.classic_can->data[6] = 0x77;
			// frame_object.frame.classic_can->data[7] = 0x88;
			// frame_object.frame.classic_can_ts->timestamp_us = __HAL_TIM_GET_COUNTER(&htim2);
			// if (host_channel_is_active) {
			// 	xQueueSendToBack(hGS_CAN.queue_to_hostHandle, &frame_object.frame, 0);
			// }
    static volatile int ii = 0;
    if ((ii % 2) == 0)
    {
      led_set_active(&hled1);
    }
    else 
    {
      led_set_inactive(&hled1);
    }
    ii = ii + 1;
		vTaskDelay(1000);
	}
}

void main_init_cb(void)
{
	hGS_CAN.channels[0] = &hfdcan1;
	// hGS_CAN.channels[1] = &hfdcan2;
	can_init(hGS_CAN.channels[0], FDCAN1);

  
  HAL_GPIO_WritePin(CAN_STBY_Pin, CAN_STBY_GPIO_Port, GPIO_PIN_RESET);
	// can_init(hGS_CAN.channels[1], FDCAN2);
	led_init(&hled1, LED_GPIO_Port, LED_Pin, LED_MODE_ACTIVE, LED_ACTIVE_LOW);
	host_channel_is_active = false;
}

void main_rtos_init_cb(void)
{
	xTaskCreate(task_my_program, "MyProgTask", TASK_MY_PROGRAM_STACK_SIZE, NULL,
				TASK_MY_PROGRAM_PRIORITY, &xCreatedMyProgramTask);
}

void main_task_cb(void)
{
  // static FDCAN_ProtocolStatusTypeDef ProtocolStatus;

	/* update all the LEDs */
	led_update(&hled1);
  // HAL_FDCAN_GetProtocolStatus(hGS_CAN.channels[0], &ProtocolStatus);
}

void can_on_enable_cb(uint8_t channel)
{
	UNUSED(channel);
	led_set_active(&hled1);
	host_channel_is_active = true;

    HAL_NVIC_SetPriority(FDCAN1_IT0_IRQn, 8 + 5, 0);
    HAL_NVIC_EnableIRQ(FDCAN1_IT0_IRQn);
}

void can_on_disable_cb(uint8_t channel)
{
	UNUSED(channel);
	led_set_inactive(&hled1);
	host_channel_is_active = false;
}

void can_on_tx_cb(uint8_t channel, struct gs_host_frame *frame)
{
	UNUSED(channel);
	UNUSED(frame);
	led_indicate_rxtx(&hled1);
}

void can_on_rx_cb(uint8_t channel, struct gs_host_frame *frame)
{
	UNUSED(channel);
	UNUSED(frame);
	led_indicate_rxtx(&hled1);
}

void can_identify_cb(uint32_t do_identify)
{
	if (do_identify) {
		led_blink_start(&hled1, 250);
	}
	else {
		led_blink_stop(&hled1);
	}
}
