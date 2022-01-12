/*
 * ucan_fd_protocol_stm32g431.c
 *
 *  Created on: Jun 3, 2020
 *      Author: Admin
 */

#include "ucan_fd_protocol_stm32g431.h"
#include "stm32g4xx_hal_fdcan.h"
#include "jump_to_boot.h"
#include "ring.h"
#include "dwt_delay.h"
#include <string.h>


extern FDCAN_HandleTypeDef hfdcan1;
extern Ring_buffer_type usb_rx;
extern Ring_buffer_type usb_tx;
extern uint8_t gotoboot_flag;
// extern uint32_t status_sys_tick;

UCAN_AckFrameDef ack_frame = 
{ 
	UCAN_FD_ACK,																						// frame_type
	UCAN_FD_COMMAND_OK, 																		//cmd status
	{ }, 																										//FDCAN_ProtocolStatusTypeDef
	{ 0x1A, 0x2B, 0x3C, 0x4D }, 														//FDCAN_ErrorCountersTypeDef
	{ 0xAABBCCDD, 1213, 5566, 44, 55, 66, 0xAABBCCDD }, 		//FDCAN_InitTypeDef
	{ 2, 1, UCAN_CAN_FD, { 1, 2, 3, 4, 5 } } 								//FDCAN_Device_DescritionDef
};

uint32_t UCAN_get_frame_size(UCAN_FRAME_TYPE ucan_frame) 
{
	static uint32_t sizeof_array[] = 
	{ 
		sizeof(UCAN_InitFrameDef), 						//UCAN_FD_INIT
		sizeof(UCAN_DeinitFrameDef), 					//UCAN_FD_DEINIT
		sizeof(UCAN_TxFrameDef), 							//UCAN_FD_TX
		sizeof(UCAN_SaveConfigFrameDef), 			//UCAN_FD_SAVE_CONFIG
		sizeof(UCAN_GoToBootladerFrameDef), 	//UCAN_FD_GO_TO_BOOTLOADER
		sizeof(UCAN_Get_CAN_Status), 					//UCAN_FD_GET_CAN_STATUS
		sizeof(UCAN_RxFrameDef),							//UCAN_FD_RX
		sizeof(UCAN_AckFrameDef) 							//UCAN_FD_ACK
	};

	if ((uint32_t) ucan_frame < (uint32_t) UCAN_FD_LAST)
	{
		return sizeof_array[(uint32_t) ucan_frame];
	}
	else
	{
		return 0;
	}
}

static void update_ACK(void) 
{
	HAL_FDCAN_GetProtocolStatus(&hfdcan1, &(ack_frame.can_protocol_status));
	HAL_FDCAN_GetErrorCounters(&hfdcan1, &(ack_frame.can_error_counters));
	//				memcpy(&ack_frame.can_init_structure, &hfdcan1.Instance,
	//						sizeof(hfdcan1.Instance));
}

uint8_t UCAN_execute_USB_to_CAN_frame(uint8_t *data) 
{
	UCAN_TxFrameDef *txf = (UCAN_TxFrameDef*)data;
	UCAN_InitFrameDef *intframe = (UCAN_InitFrameDef*)data;
	extern FDCAN_HandleTypeDef hfdcan1;

	if (data == NULL)
	{
		return 1;
	}

	// status_sys_tick = HAL_GetTick();

	switch (txf->frame_type) 
	{
		case UCAN_FD_INIT:
		{
			// HAL_FDCAN_Stop(&hfdcan1);
			// HAL_FDCAN_DeInit(&hfdcan1);

			// hfdcan1.Instance = FDCAN1;
			// hfdcan1.Init.ClockDivider = intframe->can_init.ClockDivider;
			// hfdcan1.Init.FrameFormat = intframe->can_init.FrameFormat;
			// hfdcan1.Init.Mode = FDCAN_MODE_NORMAL;
			// hfdcan1.Init.AutoRetransmission = DISABLE;
			// hfdcan1.Init.TransmitPause = DISABLE;
			// hfdcan1.Init.ProtocolException = DISABLE;
			// hfdcan1.Init.NominalPrescaler = intframe->can_init.NominalPrescaler;
			// hfdcan1.Init.NominalSyncJumpWidth = intframe->can_init.NominalSyncJumpWidth;
			// hfdcan1.Init.NominalTimeSeg1 = intframe->can_init.NominalTimeSeg1;
			// hfdcan1.Init.NominalTimeSeg2 = intframe->can_init.NominalTimeSeg1;
			// hfdcan1.Init.DataPrescaler = intframe->can_init.DataPrescaler;
			// hfdcan1.Init.DataSyncJumpWidth = intframe->can_init.DataSyncJumpWidth;
			// hfdcan1.Init.DataTimeSeg1 = intframe->can_init.DataTimeSeg1;
			// hfdcan1.Init.DataTimeSeg2 = intframe->can_init.DataTimeSeg2;
			// hfdcan1.Init.StdFiltersNbr = 0;
			// hfdcan1.Init.ExtFiltersNbr = 0;
			// hfdcan1.Init.TxFifoQueueMode = FDCAN_TX_FIFO_OPERATION;

			// hfdcan1.Instance = FDCAN1;
			// hfdcan1.Init.ClockDivider = FDCAN_CLOCK_DIV1;
			// hfdcan1.Init.FrameFormat = FDCAN_FRAME_CLASSIC;
			// hfdcan1.Init.Mode = FDCAN_MODE_NORMAL;
			// hfdcan1.Init.AutoRetransmission = DISABLE;
			// hfdcan1.Init.TransmitPause = DISABLE;
			// hfdcan1.Init.ProtocolException = DISABLE;
			// hfdcan1.Init.NominalPrescaler = 1;
			// hfdcan1.Init.NominalSyncJumpWidth = 1;
			// hfdcan1.Init.NominalTimeSeg1 = 2;
			// hfdcan1.Init.NominalTimeSeg2 = 2;
			// hfdcan1.Init.DataPrescaler = 1;
			// hfdcan1.Init.DataSyncJumpWidth = 1;
			// hfdcan1.Init.DataTimeSeg1 = 1;
			// hfdcan1.Init.DataTimeSeg2 = 1;
			// hfdcan1.Init.StdFiltersNbr = 0;
			// hfdcan1.Init.ExtFiltersNbr = 0;
			// hfdcan1.Init.TxFifoQueueMode = FDCAN_TX_FIFO_OPERATION;

			// // if (HAL_FDCAN_Init(&hfdcan1) != HAL_OK)
			// // {
			// // 	Error_Handler();
			// // }

			// HAL_FDCAN_Start(&hfdcan1);
			// update_ACK();
			// ring_buffer_push(&usb_tx, (uint8_t*)&ack_frame, sizeof(ack_frame));

			break;
		}

		case UCAN_FD_DEINIT:
		{
			// UCAN_Deinit();
			// add ACK to fifo
			break;
		}

		case UCAN_FD_TX:
		{
			if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &(txf->can_tx_header), txf->can_data) == HAL_OK) 
			{
				update_ACK();
				// ring_buffer_push(&usb_tx, &ack_frame, sizeof(ack_frame));
			} 
			else
			{
				//TODO add sth
			}
			break;
		}

		case UCAN_FD_SAVE_CONFIG:
		{
			break;
		}

		case UCAN_FD_GO_TO_BOOTLOADER:
		{
			ring_buffer_push(&usb_tx, (uint8_t*)&ack_frame, sizeof(ack_frame));
			gotoboot_flag = 1;

			break;
		}

		case UCAN_FD_GET_CAN_STATUS:
		{
			update_ACK();
			// RING_put(&usb_tx, &ack_frame, sizeof(ack_frame));
			break;
		}

		case UCAN_FD_RX:
		{
			//not used
			break;
		}

		case UCAN_FD_ACK:
		{
			break;
		}

		default:
		{
			return 1;
		}

	}

	return 0;
}


uint8_t UCAN_execute_CAN_to_USB_frame(uint8_t *data, uint32_t len) 
{
	return 0;
}