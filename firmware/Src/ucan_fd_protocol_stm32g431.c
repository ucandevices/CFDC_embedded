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

uint8_t UCAN_execute_USB_to_CAN_frame(uint8_t *data) 
{
	UCAN_TxFrameDef *txf = (UCAN_TxFrameDef*)data;
	UCAN_InitFrameDef *intframe = (UCAN_InitFrameDef*)data;
	extern FDCAN_HandleTypeDef hfdcan1;

	if (data == NULL)
	{
		return 1;
	}

	switch (txf->frame_type) 
	{
		case UCAN_FD_INIT:
		{
			HAL_FDCAN_Stop(&hfdcan1);
			memcpy((void*)&(hfdcan1.Init), (const void*)&intframe->can_init, sizeof(FDCAN_InitTypeDef));
			
			if (HAL_FDCAN_Init(&hfdcan1) != HAL_OK) 
			{
				Error_Handler();
			}

			HAL_FDCAN_Start(&hfdcan1);
			break;
		}

		case UCAN_FD_DEINIT:
		{
			break;
		}

		case UCAN_FD_TX:
		{
			HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &(txf->can_tx_header), txf->can_data);
			break;
		}

		case UCAN_FD_SAVE_CONFIG:
		{
			break;
		}

		case UCAN_FD_GO_TO_BOOTLOADER:
		{
			reboot_into_bootloader();
			break;
		}

		case UCAN_FD_GET_CAN_STATUS:
		{
			// update_ACK();
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