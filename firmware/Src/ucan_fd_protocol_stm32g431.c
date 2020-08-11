/*
 * ucan_fd_protocol_stm32g431.c
 *
 *  Created on: Jun 3, 2020
 *      Author: Admin
 */


#include "ucan_fd_protocol_stm32g431.h"
#include "stm32g4xx_hal_fdcan.h"
#include "jump_to_boot.h"
#include "RING.h"

static FDCAN_InitTypeDef init_values;
extern FDCAN_HandleTypeDef hfdcan1;
extern Ring_type usb_rx;
extern Ring_type usb_tx;


UCAN_AckFrameDef ack_frame = { UCAN_FD_ACK,	// frame_type
		UCAN_FD_COMMAND_OK, //cmd status
		{ }, //FDCAN_ProtocolStatusTypeDef
		{ 0x1A, 0x2B, 0x3C, 0x4D }, //FDCAN_ErrorCountersTypeDef
		{ 0xAABBCCDD, 1213, 5566, 44, 55, 66, 0xAABBCCDD }, //FDCAN_InitTypeDef
		{ 2, 1, UCAN_CAN_FD, { 1, 2, 3, 4, 5 } } //FDCAN_Device_DescritionDef
};


uint8_t UCAN_execute_USB_to_CAN_frame(uint8_t *data){
	UCAN_TxFrameDef* txf = data;
	UCAN_InitFrameDef* intframe = data;
	if (data == NULL)
    	return 1;

	switch(txf->frame_type)
	{
		case UCAN_FD_INIT:
			memcpy(&init_values,&intframe->can_init , sizeof(FDCAN_InitTypeDef));
			//UCAN_Init(init_values);
			HAL_FDCAN_GetProtocolStatus(&hfdcan1,
					&(ack_frame.can_protocol_status));
			HAL_FDCAN_GetErrorCounters(&hfdcan1,
					&(ack_frame.can_error_counters));
//				memcpy(&ack_frame.can_init_structure, &hfdcan1.Instance,
//						sizeof(hfdcan1.Instance));
			RING_put(&usb_tx, &ack_frame, sizeof(ack_frame));

		break;
		case UCAN_FD_DEINIT:
			//UCAN_Deinit();
			//add ACK to fifo
		break;
		case UCAN_FD_TX:
			if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &(txf->can_tx_header), txf->can_data) != HAL_OK)
			{
				//TODO add sth
				RING_put(&usb_tx, &ack_frame, sizeof(ack_frame));
			} else
			{
				//TODO add sth
			}
			break;
		case UCAN_FD_SAVE_CONFIG:
		break;
		case UCAN_FD_GO_TO_BOOTLOADER:
			//todo: send ack,
			jump_to_boot();

		break;
		case UCAN_FD_GET_CAN_STATUS:

		break;
		case UCAN_FD_RX:
			//not used
		break;
		case UCAN_FD_ACK:
			// not used
		break;

		default:
			return 1;
	}

    return 0;
}

uint8_t UCAN_execute_CAN_to_USB_frame(uint8_t *data, uint32_t len) {

	return 0;
}


